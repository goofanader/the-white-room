/*
 * CPE 476 Project: The White Room
 * Team Members:
 *    Sean Risser (srisser)
 *    Brian Yabuki (byabuki)
 *    Ben Tupas (btupas)
 *    Phyllis Douglas (pdouglas)
 */

#include <GL/glfw.h>
#include <X11/Xlib.h>

#include <iostream>
#include <sstream>
#include <string>
#include <math.h>
#include <time.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLSL_helper.h"
#include "MStackHelp.h"
#include "GeometryCreator.h"

#include "objects/GameObject.h"
#include "gameStates/State.h"
#include "gameStates/Running.h"
#include "Main.h"

#define DRAW_BRIAN_FLOOR 0
#define DRAW_ROOM 0
#define DRAW_BRIAN_CUBES 0

#define PI 3.14159

using namespace std;
using namespace glm;

GameConstants gc;

int const numSquares = 100;

GameObject cubes[numSquares];
GameObject room[6];

//linked list of meshes 
GameObject *root;
GameObject *current;
GameObject *traverser;

GameObject *playerCamera;

int numObjects = 0;

// Parameters
unsigned int windowWidth = 800, windowHeight = 600;
State* currState;

// Variable Handles
GLuint aPosition;
GLuint aNormal;
GLuint uModelMatrix;
GLuint uNormalMatrix;
GLuint uViewMatrix;
GLuint uProjMatrix;
GLuint uColor;
GLuint uLightPos;
GLuint uLightColor;
GLuint uShininess;
GLuint uSpecStrength;
GLuint uCamTrans;

// Shader Handle
GLuint ShadeProg;

// Program Variables
float Accumulator;
glm::vec3 camLookAt = glm::vec3(0.f, 0.f, 0.f);
float camAlpha = 0;
float camBeta = 0;

glm::vec2 mousePos = glm::vec2(0.f);

int keyDown[128] = {0};

RenderingHelper ModelTrans;

// NEEDS FIXING *****************************************
    glm::vec3 cameraPosition = gc.lightPos;
    GLfloat lightPosition[3] = {0.0f, 0.0f, 0.0f};
  
    const int shadowMapSize = 512;
    GLuint shadowMapTexture;
    
    GLfloat white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat dimwhite[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat black[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    
    GLfloat lightProjectionMatrix[16], lightViewMatrix[16];
    GLfloat cameraProjectionMatrix[16], cameraViewMatrix[16];

GameConstants* getGC() {
    return &gc; //this is a lot of data being pushed onto the stack...
}

unsigned int getWindowWidth() {
    return windowWidth;
}

unsigned int getWindowHeight() {
    return windowHeight;
}

void SetProjectionMatrix() {
    glm::mat4 Projection = glm::perspective(80.0f, ((float) windowWidth) /
            ((float) windowHeight), 0.1f, 100.f);
    safe_glUniformMatrix4fv(uProjMatrix, glm::value_ptr(Projection));
}

void SetView() {
    glm::mat4 View = glm::lookAt(playerCamera->trans, camLookAt, vec3(0.f, 1.f, 0.f));
    safe_glUniformMatrix4fv(uViewMatrix, glm::value_ptr(View));
}

void SetModel() {
    safe_glUniformMatrix4fv(uModelMatrix,
            glm::value_ptr(ModelTrans.modelViewMatrix));
    safe_glUniformMatrix4fv(uNormalMatrix,
            glm::value_ptr(glm::transpose(glm::inverse(ModelTrans.modelViewMatrix))));
}

bool InstallShader(std::string const & vShaderName, std::string const & fShaderName) {
    GLuint VS; // handles to shader object
    GLuint FS; // handles to frag shader object
    GLint vCompiled, fCompiled, linked; // status of shader

    VS = glCreateShader(GL_VERTEX_SHADER);
    FS = glCreateShader(GL_FRAGMENT_SHADER);

    // load the source
    char const * vSource = textFileRead(vShaderName);
    char const * fSource = textFileRead(fShaderName);
    glShaderSource(VS, 1, & vSource, NULL);
    glShaderSource(FS, 1, & fSource, NULL);

    // compile shader and print log
    glCompileShader(VS);
    printOpenGLError();
    glGetShaderiv(VS, GL_COMPILE_STATUS, & vCompiled);
    printShaderInfoLog(VS);

    // compile shader and print log
    glCompileShader(FS);
    printOpenGLError();
    glGetShaderiv(FS, GL_COMPILE_STATUS, & fCompiled);
    printShaderInfoLog(FS);

    if (!vCompiled || !fCompiled) {
        std::cerr << "Error compiling either shader " << vShaderName <<
                " or " << fShaderName << std::endl;
        return false;
    }

    // create a program object and attach the compiled shader
    ShadeProg = glCreateProgram();
    glAttachShader(ShadeProg, VS);
    glAttachShader(ShadeProg, FS);

    glLinkProgram(ShadeProg);

    // check shader status requires helper functions
    printOpenGLError();
    glGetProgramiv(ShadeProg, GL_LINK_STATUS, &linked);
    printProgramInfoLog(ShadeProg);

    glUseProgram(ShadeProg);

    // get handles to attribute data
    aPosition = safe_glGetAttribLocation(ShadeProg, "aPosition");
    aNormal = safe_glGetAttribLocation(ShadeProg, "aNormal");

    uColor = safe_glGetUniformLocation(ShadeProg, "uColor");
    uProjMatrix = safe_glGetUniformLocation(ShadeProg, "uProjMatrix");
    uViewMatrix = safe_glGetUniformLocation(ShadeProg, "uViewMatrix");
    uModelMatrix = safe_glGetUniformLocation(ShadeProg, "uModelMatrix");
    uNormalMatrix = safe_glGetUniformLocation(ShadeProg, "uNormalMatrix");

    uLightPos = safe_glGetUniformLocation(ShadeProg, "uLightPos");
    uLightColor = safe_glGetUniformLocation(ShadeProg, "uLightColor");
    uShininess = safe_glGetUniformLocation(ShadeProg, "uShininess");
    uSpecStrength = safe_glGetUniformLocation(ShadeProg, "uSpecStrength");
    uCamTrans = safe_glGetUniformLocation(ShadeProg, "uCamTrans");

    std::cout << "Successfully installed shader " << ShadeProg << std::endl;
    return true;
}

void advanceState(State* newState) {
    delete currState;
    currState = newState;
}

void Initialize() {
    
         //create shadow map texture
    glGenTextures(1, &shadowMapTexture);
    glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowMapSize,
            shadowMapSize, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
 
    
    //setting color, etc.
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, white);
    glMaterialf(GL_FRONT, GL_SHININESS, 16.0f);
    
           //initializing matrices
 glPushMatrix();
 
    glLoadIdentity();
    gluPerspective(45.0f, (float)windowWidth/windowHeight, 1.0f, 100.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX, cameraProjectionMatrix);
  
    glLoadIdentity();
    gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2],
    0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX, cameraViewMatrix);
    
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 2.0f, 8.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX, lightProjectionMatrix);
    
    glLoadIdentity();
    gluLookAt(lightPosition[0], lightPosition[1], lightPosition[2],
               0.0f, 0.0f, 0.0f,
               0.0f, 1.0f, 0.0f);
    glGetFloatv(GL_MODELVIEW_MATRIX, lightViewMatrix);
  
 glPopMatrix();
    
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    ModelTrans.useModelViewMatrix();
    ModelTrans.loadIdentity();
}

void Draw() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw what the current state wants (atm, draw the scene in "Running.cpp")
    currState->draw();
    
    

    glfwSwapBuffers();
    printOpenGLError();
}

void Shadow() {    
    // 1st pass - draw light's POV
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(lightProjectionMatrix);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(lightViewMatrix);

    //viewport same size as shadow map
    glViewport(0, 0, shadowMapSize, shadowMapSize);

    //draw back faces to shadowmap
    glCullFace(GL_FRONT);
    glShadeModel(GL_FLAT);
    glColorMask(0, 0, 0, 0);

    //draw scene
    //Draw();

    //read depth buffer into shadow map texture
    glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0,
            shadowMapSize, shadowMapSize);

    //restore states
    glCullFace(GL_BACK);
    glShadeModel(GL_SMOOTH);
    glColorMask(1, 1, 1, 1);


    //second pass (draw scene from camera's POV):
    //light set to brightness of shadowed areas. clear depth buffer,
    //set up matrices to camera's POV, use viewport that covers whole window
    glClear(GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(cameraProjectionMatrix);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(cameraViewMatrix);

    glViewport(0, 0, windowWidth, windowHeight);

    //dim light to represent shadow
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_AMBIENT, dimwhite);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, dimwhite);
    glLightfv(GL_LIGHT1, GL_SPECULAR, black);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);

    //draw scene
 //   Draw();


    //third pass(shadow calculations):
    //bright light w/ full brightness to illuminate unshadowed objects
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);

    //texture matrix (eye space -> light's clip space)
    //using column major
    static GLfloat biasMatrix[16] =
      {0.5f, 0.0f, 0.0f, 0.0f,
       0.0f, 0.5f, 0.0f, 0.0f,
       0.0f, 0.0f, 0.5f, 0.0f,
       0.5f, 0.5f, 0.5f, 1.0f};
    //bias from [-1, 1] to [0,1]

    GLfloat textureMatrix[16];
    for(int i = 0; i < 16; i++) {
       textureMatrix[i] = biasMatrix[i]*lightProjectionMatrix[i]*lightViewMatrix[i];
    }
    GLfloat row1[] = {textureMatrix[0], textureMatrix[4], textureMatrix[8], textureMatrix[12]};
    GLfloat row2[] = {textureMatrix[1], textureMatrix[5], textureMatrix[9], textureMatrix[13]};
    GLfloat row3[] = {textureMatrix[2], textureMatrix[6], textureMatrix[10], textureMatrix[14]};
    GLfloat row4[] = {textureMatrix[3], textureMatrix[7], textureMatrix[11], textureMatrix[15]};
    //texture coordinate generation
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_S, GL_EYE_PLANE, row1);
    glEnable(GL_TEXTURE_GEN_S);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_S, GL_EYE_PLANE, row2);
    glEnable(GL_TEXTURE_GEN_T);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_S, GL_EYE_PLANE, row3);
    glEnable(GL_TEXTURE_GEN_R);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_S, GL_EYE_PLANE, row4);
    glEnable(GL_TEXTURE_GEN_Q);

    //bind & enable shadow map texture
    glBindTexture(GL_TEXTURE_2D, shadowMapTexture);
    glEnable(GL_TEXTURE_2D);

    //shadow comparison
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE);

    //(r <= texture) means not in shadow (true)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);

    //intensity result
    glTexParameteri (GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

    //alpha test to discard false comparisons (alpha < 0.99)
    glAlphaFunc(GL_GEQUAL, 0.99f);
    glEnable(GL_ALPHA_TEST);

    //draw scene
    Draw();

    //disable textures and texgen
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    glDisable(GL_TEXTURE_GEN_R);
    glDisable(GL_TEXTURE_GEN_Q);

    //restore other states
    glDisable(GL_LIGHTING);
    glDisable(GL_ALPHA_TEST);

    //reset matrices
    glMatrixMode(GL_PROJECTION);
    //glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();

glFinish();
glfwSwapBuffers();
//glutPostRedisplay();
//Draw();
}

std::string printVec3Coordinates(glm::vec3 coordinates) {
    std::string out = "(";
    out += static_cast<ostringstream*>( &(ostringstream() << coordinates.x) )->str();
    out += ", ";
    out += static_cast<ostringstream*>( &(ostringstream() << coordinates.y) )->str();;
    out += ", ";
    out += static_cast<ostringstream*>( &(ostringstream() << coordinates.z) )->str();;
    out += ")";
    return out;
}

void Reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
}

void Keyboard(int key, int state) {
    if (state == GLFW_PRESS)
        keyDown[key] = 1;
    else
        keyDown[key] = 0;
    switch (key) {
            // Toggle wireframe
        case 'N':
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_CULL_FACE);
            break;
        case 'M':
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_CULL_FACE);
            break;
        case GLFW_KEY_LEFT:
            gc.lightPos = glm::vec3(gc.lightPos.x - .1, gc.lightPos.y, gc.lightPos.z);
            std::cout << "lightPos: " << printVec3Coordinates(gc.lightPos) << std::endl;
            break;
        case GLFW_KEY_RIGHT:
            gc.lightPos = glm::vec3(gc.lightPos.x + .1, gc.lightPos.y, gc.lightPos.z);
            std::cout << "lightPos: " << printVec3Coordinates(gc.lightPos) << std::endl;
            break;
        case GLFW_KEY_UP:
            gc.lightPos = glm::vec3(gc.lightPos.x, gc.lightPos.y + .1, gc.lightPos.z);
            std::cout << "lightPos: " << printVec3Coordinates(gc.lightPos) << std::endl;
            break;
        case GLFW_KEY_DOWN:
            gc.lightPos = glm::vec3(gc.lightPos.x, gc.lightPos.y - .1, gc.lightPos.z);
            std::cout << "lightPos: " << printVec3Coordinates(gc.lightPos) << std::endl;
            break;
        case 'I':
            gc.lightPos = glm::vec3(gc.lightPos.x, gc.lightPos.y, gc.lightPos.z + .1);
            std::cout << "lightPos: " << printVec3Coordinates(gc.lightPos) << std::endl;
            break;
        case 'K':
            gc.lightPos = glm::vec3(gc.lightPos.x, gc.lightPos.y, gc.lightPos.z - .1);
            std::cout << "lightPos: " << printVec3Coordinates(gc.lightPos) << std::endl;
            break;
        case 'R':
            gc.lightPos = glm::vec3(0,9,0);
            std::cout << "Reset lightPos to " << printVec3Coordinates(gc.lightPos) << std::endl;
            // Quit program
        case 'Q':
            exit(EXIT_SUCCESS);
            break;
    }
}

void updateLookAt() {
    camLookAt = playerCamera->trans - glm::vec3(
            cos(camAlpha) * cos(camBeta),
            sin(camAlpha),
            cos(camAlpha) * sin(camBeta));
}

void MouseClick(int button, int action) {
    currState->mouseClicked(button, action);
}

void MouseMove(int x, int y) {
    glm::vec2 newPos = glm::vec2(x, y);
    currState->mouseMoved(newPos.x, newPos.y, mousePos.x, mousePos.y);
    
    glfwSetMousePos(windowWidth / 2, windowHeight / 2);
    mousePos = glm::vec2(windowWidth / 2, windowHeight / 2);
}

int getScreenSize() {
    Display* pdsp = NULL;
    Screen* pscr = NULL;

    pdsp = XOpenDisplay(NULL);
    if (!pdsp) {
        fprintf(stderr, "Failed to open default display.\n");
        return -1;
    }

    pscr = DefaultScreenOfDisplay(pdsp);
    if (!pscr) {
        fprintf(stderr, "Failed to obtain the default screen of given display.\n");
        return -2;
    }

    windowWidth = pscr->width - 100;
    windowHeight = pscr->height - 100;

    XCloseDisplay(pdsp);
    return 0;
}

void handleFirstPersonMovement(float dt) {
    // Camera movement
    glm::vec3 up = glm::vec3(0, 1, 0);
    glm::vec3 forward = glm::normalize(camLookAt - playerCamera->trans);
    glm::vec3 right = glm::normalize(glm::cross(forward, up));
    const float MOVE_SPEED = 8.f;

    //bind player to the floor so they can't fly through the scene :)
    forward = glm::vec3(forward.x, 0, forward.z);

    if (keyDown['W'])
        playerCamera->trans += MOVE_SPEED * forward * dt;
    if (keyDown['S'])
        playerCamera->trans -= MOVE_SPEED * forward * dt;
    if (keyDown['D'])
        playerCamera->trans += MOVE_SPEED * right * dt;
    if (keyDown['A'])
        playerCamera->trans -= MOVE_SPEED * right * dt;
    if (playerCamera->trans.y <= 0.f)
        playerCamera->trans.y = 0.f;
    updateLookAt();
}

void gameLoop() {
    int running = GL_TRUE;
    double oldTime = glfwGetTime();
    double curTime;
    double timeDelta = 1.0/60.0;
    double timeAccumulator = 0.0;

    while (running) {

        curTime = glfwGetTime();
       
        
        currState->keyPressed(timeAccumulator, keyDown);
        
        //timeAccumulator is the amount of time we spent on the last frame
        //By stepping through our physics calculation with a constant DT, we
        //prevent any graphical lag from causing strange hitbox detection from
        //happening
        
        while (timeAccumulator >= timeDelta) {
            currState->update(timeDelta);
            timeAccumulator -= timeDelta;
        }

        
        Draw();
        //Shadow();
        oldTime = curTime;
        //don't calculate time based off of how long we slept
        //base it off of when the next loop starts
        if (glfwGetTime() - curTime < timeDelta) {
            glfwSleep(timeDelta - (glfwGetTime() - curTime));
        }
        //set timeAccumulator to the amount of time spent calculating and 
        //rendering this frame
        timeAccumulator += glfwGetTime() - curTime;
    }
}

void initializeShaderVariables() {
    //initialize openGL and shader variables
    gc.shader = ShadeProg;
    gc.aspectRatio = (float) windowWidth / windowHeight;
    gc.lightPos = glm::vec3(0.0f, 9.0f, 0.0f);
    gc.lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    gc.h_aPosition = aPosition;
    gc.h_aNormal = aNormal;
    gc.h_uColor = uColor;
    gc.h_uProjMatrix = uProjMatrix;
    gc.h_uViewMatrix = uViewMatrix;
    gc.h_uModelMatrix = uModelMatrix;
    gc.h_uNormalMatrix = uNormalMatrix;
    gc.h_uLightPos = uLightPos;
    gc.h_uLightColor = uLightColor;
    gc.h_uShininess = uShininess;
    gc.h_uSpecStrength = uSpecStrength;
    gc.h_uCamTrans = uCamTrans;
}

int main(int argc, char *argv[]) {
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    //set window size to screen size
    getScreenSize();
    windowWidth = 800;
    windowHeight = 600;
    if (!glfwOpenWindow(windowWidth, windowHeight, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwSetWindowTitle("The White Room");

    // OpenGL Setup
    Initialize();
    getGLversion();

    // Shader Setup
    if (!InstallShader("mesh_vert.glsl", "mesh_frag.glsl")) {
        printf("Error installing shader!\n");
        return 1;
    }
    initializeShaderVariables();

    //start the random counter
    srand(time(NULL));

    //set input callback functions
    currState = new Running();
    glfwSetKeyCallback(Keyboard);
    glfwSetMousePosCallback(MouseMove);
    glfwSetMouseButtonCallback(MouseClick);
    //initialize the current state to running atm
    //this should start off as MainMenu() when we get to that point

    //begin game loop
    gameLoop();

    glfwTerminate();
    return 0;
}
