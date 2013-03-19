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
#include "objects/mainMenu/MenuObjects.h"
#include "gameStates/State.h"
#include "gameStates/Running.h"
#include "gameStates/MainMenu.h"
#include "Main.h"

#define DRAW_BRIAN_FLOOR 0
#define DRAW_ROOM 0
#define DRAW_BRIAN_CUBES 0

#define PI 3.14159

using namespace std;
using namespace glm;

GameConstants gc, lc, sc;
DeferredShadingConstants drc, dsc;
bool g_hasWon, g_hasQuit, g_moveMouse;
glm::vec3 roomFloorHeight;
float roomCeilHeight;

GLuint quad_vertexbuffer;
GLuint FramebufferName = 0;
GLuint renderedTexture;

GLuint m_diffuseRT, m_positionRT, m_normalsRT, m_depthBuffer;
GLuint m_diffuseTexture, m_positionTexture, m_normalsTexture;
GLuint m_diffuseID, m_positionID, m_normalsID;

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
GLuint uAmbColor, uSpecColor, uDiffColor;
GLuint uLightPos;
GLuint aTexCoord;
GLuint uTexUnit;
GLuint uTexUnit2;
GLuint uSmokeUnit;
GLuint uLightColor;
GLuint uShininess;
GLuint uSpecStrength;
GLuint uCamTrans;
GLuint uUseTex;
GLuint uUseTex2;
GLuint uTime;

// Shader Handle
GLuint ShadeProg[MAX_SHADERS];

// Program Variables
float Accumulator;
glm::vec3 camLookAt = glm::vec3(0.f, 0.f, 0.f);
float camAlpha = 0;
float camBeta = 0;

glm::vec2 mousePos = glm::vec2(0.f);

int keyDown[128] = {0};

RenderingHelper ModelTrans;



// shadow map info 
const int shadowMapSize = 128;
GLuint shadowMapTexture;
GLuint shadowMapBuffer;
GLuint uLightProjMatrix;
GLuint uLightViewMatrix;
GLuint uLightDir;
bool setShadowMap = true;

GameConstants* getGC() {
    return &gc;
}

GameConstants* getLC() {
    return &lc;
}

GameConstants* getSC() {
    return &sc;
}

DeferredShadingConstants* getDRC() {
    return &drc;
}

DeferredShadingConstants* getDSC() {
    return &dsc;
}

unsigned int getWindowWidth() {
    return windowWidth;
}

unsigned int getWindowHeight() {
    return windowHeight;
}

bool hasWon() {
    return g_hasWon;
}

void setIfWon(bool winning) {
    g_hasWon = winning;
}

glm::vec3 getRoomFloorHeight() {
    return roomFloorHeight;
}

void setRoomFloorHeight(glm::vec3 newHeight) {
    roomFloorHeight = newHeight;
}

float getRoomCeilHeight() {
    return roomCeilHeight;
}

void setRoomCeilHeight(float newHeight) {
    roomCeilHeight = newHeight;
}

void SetProjectionMatrix() {
    glm::mat4 Projection = glm::perspective(80.0f, ((float) windowWidth) /
            ((float) windowHeight), 0.1f, 100.f);
    safe_glUniformMatrix4fv(uProjMatrix, glm::value_ptr(Projection));
}

/*void SetView() {
    glm::mat4 View = glm::lookAt(playerCamera->trans, camLookAt, vec3(0.f, 1.f, 0.f));
    safe_glUniformMatrix4fv(uViewMatrix, glm::value_ptr(View));
}*/

void SetModel() {
    safe_glUniformMatrix4fv(uModelMatrix,
            glm::value_ptr(ModelTrans.modelViewMatrix));
    safe_glUniformMatrix4fv(uNormalMatrix,
            glm::value_ptr(glm::transpose(glm::inverse(ModelTrans.modelViewMatrix))));
}

bool InstallComplexShader(
        std::string const & vShaderName,
        std::string const & gShaderName,
        std::string const & fShaderName, int shader) {
    GLuint VS; // handles to shader object
    GLuint GS;
    GLuint FS; // handles to frag shader object
    GLint vCompiled, gCompiled, fCompiled, linked; // status of shader

    VS = glCreateShader(GL_VERTEX_SHADER);
    GS = glCreateShader(GL_GEOMETRY_SHADER);
    FS = glCreateShader(GL_FRAGMENT_SHADER);

    // load the source
    char const * vSource = textFileRead(vShaderName);
    char const * gSource = textFileRead(gShaderName);
    char const * fSource = textFileRead(fShaderName);
    glShaderSource(VS, 1, & vSource, NULL);
    glShaderSource(GS, 1, & gSource, NULL);
    glShaderSource(FS, 1, & fSource, NULL);

    // compile shader and print log
    glCompileShader(VS);
    printOpenGLError();
    glGetShaderiv(VS, GL_COMPILE_STATUS, & vCompiled);
    printShaderInfoLog(VS);

    glCompileShader(GS);
    printOpenGLError();
    glGetShaderiv(GS, GL_COMPILE_STATUS, & gCompiled);
    printShaderInfoLog(GS);

    // compile shader and print log
    glCompileShader(FS);
    printOpenGLError();
    glGetShaderiv(FS, GL_COMPILE_STATUS, & fCompiled);
    printShaderInfoLog(FS);

    if (!vCompiled || !gCompiled || !fCompiled) {
        std::cerr << "Error compiling either shader " << vShaderName <<
                " or " << gShaderName <<
                " or " << fShaderName << std::endl;
        return false;
    }

    // create a program object and attach the compiled shader
    ShadeProg[shader] = glCreateProgram();
    glAttachShader(ShadeProg[shader], VS);
    glAttachShader(ShadeProg[shader], GS);
    glAttachShader(ShadeProg[shader], FS);

    glLinkProgram(ShadeProg[shader]);

    // check shader status requires helper functions
    printOpenGLError();
    glGetProgramiv(ShadeProg[shader], GL_LINK_STATUS, &linked);
    printProgramInfoLog(ShadeProg[shader]);

    return true;

}

bool InstallShader(std::string const & vShaderName, std::string const & fShaderName,
        int shader) {
    GLuint VS; // handles to shader object
    GLuint FS; // handles to frag shader object
    GLint vCompiled, fCompiled, linked; // status of shader

    printOpenGLError();
    VS = glCreateShader(GL_VERTEX_SHADER);
    printOpenGLError();
    FS = glCreateShader(GL_FRAGMENT_SHADER);
    printOpenGLError();

    // load the source
    char const * vSource = textFileRead(vShaderName);
    char const * fSource = textFileRead(fShaderName);
    glShaderSource(VS, 1, & vSource, NULL);
    printOpenGLError();
    glShaderSource(FS, 1, & fSource, NULL);
    printOpenGLError();

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
    ShadeProg[shader] = glCreateProgram();
    glAttachShader(ShadeProg[shader], VS);
    glAttachShader(ShadeProg[shader], FS);

    glLinkProgram(ShadeProg[shader]);

    // check shader status requires helper functions
    printOpenGLError();
    glGetProgramiv(ShadeProg[shader], GL_LINK_STATUS, &linked);
    printProgramInfoLog(ShadeProg[shader]);

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
    glEnable(GL_TEXTURE_2D);
    //nearest neighbor algorithm
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    //no border between shadow maps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    printOpenGLError();
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_ARB, GL_COMPARE_R_TO_TEXTURE_ARB);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_ARB, GL_LEQUAL);
    // glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE_ARB, GL_INTENSITY);

    // GLfloat border[] = {0.0f, 0.0f, 0.0f, 0.0f};
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, border);

    //bind default
    glBindTexture(GL_TEXTURE_2D, 0);

    //create depth buffer
    glGenFramebuffers(1, &shadowMapBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, shadowMapBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, shadowMapTexture, 0);
    printOpenGLError();
    //no color
    glDrawBuffer(GL_NONE);
    printOpenGLError();
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        printf("error in framebuffer\n");
        exit(-1);
    }
    printOpenGLError();
    //bind default
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    printOpenGLError();
    //set up matrices for light's POV
    glm::vec3 lightPos = glm::vec3(0, 8, 0);
    glm::vec3 lightDir = glm::vec3(0, 0, 0);

    glm::mat4 LightViewMatrix = glm::lookAt(lightPos, lightPos + lightDir, vec3(0, 1, 0));
    // glm::mat4 projMat = glm::perspective (FOV_deg, aspect, nearClip, farClip);
    glm::mat4 LightProjMatrix = glm::perspective(90.0f, 1.0f, 1.0f, 15.0f);

    //safe_glUniformMatrix4fv(uLightProjMatrix, glm::value_ptr(LightProjMatrix));
    //safe_glUniformMatrix4fv(uLightViewMatrix, glm::value_ptr(LightViewMatrix));
    printOpenGLError();



    //enable alpha for color
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    glClearColor(0.f, 0.f, 0.0f, 1.0f);

    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_MULTISAMPLE);

    glClearStencil(0);

    ModelTrans.useModelViewMatrix();
    ModelTrans.loadIdentity();

    //======Framebuffer Initialization======//
    glGenFramebuffers(1, &FramebufferName);
    glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

    glGenRenderbuffers(1, &m_diffuseRT);
    glGenRenderbuffers(1, &m_positionRT);
    glGenRenderbuffers(1, &m_normalsRT);
    glGenRenderbuffers(1, &m_depthBuffer);

    //bind the diffuse render target
    glBindRenderbuffer(GL_RENDERBUFFER, m_diffuseRT);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_diffuseRT);

    //bind the position render target
    glBindRenderbuffer(GL_RENDERBUFFER, m_positionRT);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA32F, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, m_diffuseRT);

    //bind the normal render target
    glBindRenderbuffer(GL_RENDERBUFFER, m_normalsRT);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA16F, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_RENDERBUFFER, m_diffuseRT);

    glBindRenderbuffer(GL_RENDERBUFFER, m_depthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, windowWidth, windowHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBuffer);

    //Generate and bind the OGL texture for diffuse
    glGenTextures(1, &m_diffuseTexture);
    glBindTexture(GL_TEXTURE_2D, m_diffuseTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, windowWidth, windowHeight, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
            m_diffuseTexture, 0);

    //Generate and bind the OGL texture for positions
    glGenTextures(1, &m_positionTexture);
    glBindTexture(GL_TEXTURE_2D, m_positionTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowWidth, windowHeight, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D,
            m_positionTexture, 0);

    //Generate and bind the OGL texture for normals
    glGenTextures(1, &m_normalsTexture);
    glBindTexture(GL_TEXTURE_2D, m_normalsTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, windowWidth, windowHeight, 0,
            GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D,
            m_normalsTexture, 0);

    // Always check that our framebuffer is ok
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "FramebufferStatus yucky :<" << std::endl;
        exit(EXIT_FAILURE);
    }

    // The fullscreen quad's FBO
    static const GLfloat g_QuadVBOdata[] = {
        /*-1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,*/
        0.0f, 0.0f, 0.0f,
        (float)windowWidth, 0.0f, 0.0f,
        (float)windowWidth, (float)windowHeight, 0.f,
        0.0f, (float)windowHeight, 0.0f
    };

    glGenBuffers(1, &quad_vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, quad_vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof (g_QuadVBOdata),
            g_QuadVBOdata, GL_STATIC_DRAW);

    //go back to the usual screen framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Draw() {
    if (setShadowMap) {
        setShadowMap = false;

        //store depth map, 1 per depth map tex
        glBindFramebuffer(GL_FRAMEBUFFER, shadowMapBuffer);
        glClear(GL_DEPTH_BUFFER_BIT);
        glViewport(0, 0, shadowMapSize, shadowMapSize);

        // render into texture using light's POV
        currState->draw();

        glViewport(0, 0, windowWidth, windowHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    //draw what the current state wants (atm, draw the scene in "Running.cpp")
    currState->draw();
    printOpenGLError();

    glfwSwapBuffers();
    printOpenGLError();
}

void Shadow() {

}

std::string printVec3(glm::vec3 coordinates) {
    std::string out = "(";
    out += static_cast<ostringstream*> (&(ostringstream() << coordinates.x))->str();
    out += ", ";
    out += static_cast<ostringstream*> (&(ostringstream() << coordinates.y))->str();
    out += ", ";
    out += static_cast<ostringstream*> (&(ostringstream() << coordinates.z))->str();
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
            std::cout << "lightPos: " << printVec3(gc.lightPos) << std::endl;
            break;
        case GLFW_KEY_RIGHT:
            gc.lightPos = glm::vec3(gc.lightPos.x + .1, gc.lightPos.y, gc.lightPos.z);
            std::cout << "lightPos: " << printVec3(gc.lightPos) << std::endl;
            break;
        case GLFW_KEY_UP:
            gc.lightPos = glm::vec3(gc.lightPos.x, gc.lightPos.y + .1, gc.lightPos.z);
            std::cout << "lightPos: " << printVec3(gc.lightPos) << std::endl;
            break;
        case GLFW_KEY_DOWN:
            gc.lightPos = glm::vec3(gc.lightPos.x, gc.lightPos.y - .1, gc.lightPos.z);
            std::cout << "lightPos: " << printVec3(gc.lightPos) << std::endl;
            break;
        case 'I':
            gc.lightPos = glm::vec3(gc.lightPos.x, gc.lightPos.y, gc.lightPos.z + .1);
            std::cout << "lightPos: " << printVec3(gc.lightPos) << std::endl;
            break;
        case 'K':
            gc.lightPos = glm::vec3(gc.lightPos.x, gc.lightPos.y, gc.lightPos.z - .1);
            std::cout << "lightPos: " << printVec3(gc.lightPos) << std::endl;
            break;
        case 'R':
            gc.lightPos = glm::vec3(0, 9, 0);
            std::cout << "Reset lightPos to " << printVec3(gc.lightPos) << std::endl;
            // Quit program
        case 'Q':
            g_hasQuit = true;


            //exit(EXIT_SUCCESS);
            break;
    }
}

/*void updateLookAt() {
    //camLookAt = playerCamera->trans - glm::vec3(
    camLookAt = camNextTrans - glm::vec3(
            cos(camAlpha) * cos(camBeta),
            sin(camAlpha),
            cos(camAlpha) * sin(camBeta));
}*/

void MouseClick(int button, int action) {
    currState->mouseClicked(button, action);
}

bool canMoveMouse() {
    return g_moveMouse;
}

void setCanMoveMouse(bool moving) {
    g_moveMouse = moving;
}

void MouseMove(int x, int y) {
    glm::vec2 newPos = glm::vec2(x, y);
    currState->mouseMoved(newPos.x, newPos.y, mousePos.x, mousePos.y);

    if (!g_moveMouse) {
        glfwSetMousePos(windowWidth / 2, windowHeight / 2);
        mousePos = glm::vec2(windowWidth / 2, windowHeight / 2);
    }
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

void gameLoop() {
    int running = GL_TRUE;
    double oldTime = glfwGetTime();
    double curTime;
    double timeDelta = 1.0 / 60.0;
    double timeAccumulator = 0.0;

    while (!g_hasQuit) {

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

        if (timeAccumulator) {
            currState->update(timeAccumulator);
            timeAccumulator = 0;
        }
        //it's expensive to update thousands of particles
        //so update once a frame and let the particle updater handle
        //errors from large time steps
        //updateParticles(glfwGetTime() - oldTime, particleSystem);

        Draw();
        //DrawParticles(particleSystem);
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
    gc.shader = ShadeProg[0];
    gc.aspectRatio = (float) windowWidth / windowHeight;
    gc.lightPos = glm::vec3(0.0f, 7.2f, 0.0f);
    gc.lightColor = glm::vec3(.75f, 0.75f, 0.75f);
    gc.lightAlpha = 1.f;
    gc.h_aPosition = aPosition;
    gc.h_aNormal = aNormal;
    gc.h_uAmbColor = uAmbColor;
    gc.h_uDiffColor = uDiffColor;
    gc.h_uSpecColor = uSpecColor;
    gc.h_uProjMatrix = uProjMatrix;
    gc.h_uViewMatrix = uViewMatrix;
    gc.h_uModelMatrix = uModelMatrix;
    gc.h_uNormalMatrix = uNormalMatrix;
    gc.h_uLightPos = uLightPos;
    gc.h_uLightColor = uLightColor;
    gc.h_uShininess = uShininess;
    gc.h_uSpecStrength = uSpecStrength;
    gc.h_uCamTrans = uCamTrans;
    gc.h_aTexCoord = aTexCoord;
    gc.h_uTexUnit = uTexUnit;
    gc.h_uTexUnit2 = uTexUnit2;
    gc.h_uUseTex = uUseTex;
    gc.h_uUseTex2 = uUseTex2;
    gc.h_uTime = uTime;

    gc.uLightProjMatrix = uLightProjMatrix;
    gc.uLightViewMatrix = uLightViewMatrix;

    glUseProgram(gc.shader);
    shadowMapTexture = safe_glGetUniformLocation(gc.shader, "ShadowMap");
    glUseProgram(0);
    sc.ShadowMap = shadowMapTexture;
}

void initializeLaplaceShaderVariables() {
    //initialize openGL and shader variables
    lc.shader = ShadeProg[1];
    lc.aspectRatio = (float) windowWidth / windowHeight;
    lc.lightPos = glm::vec3(0.0f, 7.2f, 0.0f);
    lc.lightColor = glm::vec3(.75f, 0.75f, 0.75f);
    lc.lightAlpha = 1.f;
    lc.h_aPosition = aPosition;
    lc.h_aNormal = aNormal;
    lc.h_uAmbColor = uAmbColor;
    lc.h_uDiffColor = uDiffColor;
    lc.h_uSpecColor = uSpecColor;
    lc.h_uProjMatrix = uProjMatrix;
    lc.h_uViewMatrix = uViewMatrix;
    lc.h_uModelMatrix = uModelMatrix;
    lc.h_uNormalMatrix = uNormalMatrix;
    lc.h_uLightPos = uLightPos;
    lc.h_uLightColor = uLightColor;
    lc.h_uShininess = uShininess;
    lc.h_uSpecStrength = uSpecStrength;
    lc.h_uCamTrans = uCamTrans;
    lc.h_aTexCoord = aTexCoord;
    lc.h_uTexUnit = uTexUnit;
    lc.h_uTexUnit2 = uTexUnit2;
    lc.h_uUseTex = uUseTex;
    lc.h_uUseTex2 = uUseTex2;
    lc.h_uTime = uTime;
}

void initializeShadowShaderVariables() {
    //initialize openGL and shader variables
    sc.shader = ShadeProg[2];
    sc.aspectRatio = (float) windowWidth / windowHeight;
    sc.lightPos = glm::vec3(0.0f, 7.2f, 0.0f);
    sc.lightColor = glm::vec3(.75f, 0.75f, 0.75f);
    sc.lightAlpha = 1.f;
    sc.h_aPosition = aPosition;
    sc.h_aNormal = aNormal;
    sc.h_uAmbColor = uAmbColor;
    sc.h_uDiffColor = uDiffColor;
    sc.h_uSpecColor = uSpecColor;
    sc.h_uProjMatrix = uProjMatrix;
    sc.h_uViewMatrix = uViewMatrix;
    sc.h_uModelMatrix = uModelMatrix;
    sc.h_uNormalMatrix = uNormalMatrix;
    sc.h_uLightPos = uLightPos;
    sc.h_uLightColor = uLightColor;
    sc.h_uShininess = uShininess;
    sc.h_uSpecStrength = uSpecStrength;
    sc.h_uCamTrans = uCamTrans;
    sc.h_aTexCoord = aTexCoord;
    sc.h_uTexUnit = uTexUnit;
    sc.h_uTexUnit2 = uTexUnit2;
    sc.h_uUseTex = uUseTex;
    sc.h_uUseTex2 = uUseTex2;
    sc.h_uTime = uTime;

    sc.uLightProjMatrix = uLightProjMatrix;
    sc.uLightViewMatrix = uLightViewMatrix;
}

void initializeDeferredShadingVariables() {
    //initialize openGL and shader variables
    drc.shader = ShadeProg[3];
    drc.aspectRatio = (float) windowWidth / windowHeight;
    drc.lightPos = glm::vec3(0.0f, 7.2f, 0.0f);
    drc.lightColor = glm::vec3(.75f, 0.75f, 0.75f);
    drc.lightAlpha = 1.f;
    drc.h_aPosition = aPosition;
    drc.h_aNormal = aNormal;
    drc.h_uAmbColor = uAmbColor;
    drc.h_uDiffColor = uDiffColor;
    drc.h_uSpecColor = uSpecColor;
    drc.h_uProjMatrix = uProjMatrix;
    drc.h_uViewMatrix = uViewMatrix;
    drc.h_uModelMatrix = uModelMatrix;
    drc.h_uNormalMatrix = uNormalMatrix;
    drc.h_uLightPos = uLightPos;
    drc.h_uLightColor = uLightColor;
    drc.h_uShininess = uShininess;
    drc.h_uSpecStrength = uSpecStrength;
    drc.h_uCamTrans = uCamTrans;
    drc.h_aTexCoord = aTexCoord;
    drc.h_uTexUnit = uTexUnit;
    drc.h_uTexUnit2 = uTexUnit2;
    drc.h_uUseTex = uUseTex;
    drc.h_uUseTex2 = uUseTex2;
    drc.h_uTime = uTime;
    
    drc.FramebufferName = FramebufferName;
}

void initializePassThroughShaderVariables() {
    //initialize openGL and shader variables
    dsc.shader = ShadeProg[4];
    dsc.aspectRatio = (float) windowWidth / windowHeight;
    dsc.lightPos = glm::vec3(0.0f, 7.2f, 0.0f);
    dsc.lightColor = glm::vec3(.75f, 0.75f, 0.75f);
    dsc.lightAlpha = 1.f;
    dsc.h_aPosition = aPosition;
    dsc.h_aNormal = aNormal;
    dsc.h_uAmbColor = uAmbColor;
    dsc.h_uDiffColor = uDiffColor;
    dsc.h_uSpecColor = uSpecColor;
    dsc.h_uProjMatrix = uProjMatrix;
    dsc.h_uViewMatrix = uViewMatrix;
    dsc.h_uModelMatrix = uModelMatrix;
    dsc.h_uNormalMatrix = uNormalMatrix;
    dsc.h_uLightPos = uLightPos;
    dsc.h_uLightColor = uLightColor;
    dsc.h_uShininess = uShininess;
    dsc.h_uSpecStrength = uSpecStrength;
    dsc.h_uCamTrans = uCamTrans;
    dsc.h_aTexCoord = aTexCoord;
    dsc.h_uTexUnit = uTexUnit;
    dsc.h_uTexUnit2 = uTexUnit2;
    dsc.h_uUseTex = uUseTex;
    dsc.h_uUseTex2 = uUseTex2;
    dsc.h_uTime = uTime;
    
    dsc.diffuseTexture = m_diffuseTexture;
    dsc.PositionTexture = m_positionTexture;
    dsc.NormalsTexture = m_normalsTexture;
    dsc.m_diffuseID = m_diffuseID;
    dsc.m_positionID = m_positionID;
    dsc.m_normalsID = m_normalsID;
    dsc.quad_vertexbuffer = quad_vertexbuffer;
}

void initializeShaderConnection(int shader) {
    glUseProgram(ShadeProg[shader]);

    // get handles to attribute data
    aPosition = safe_glGetAttribLocation(ShadeProg[shader], "aPosition");
    aNormal = safe_glGetAttribLocation(ShadeProg[shader], "aNormal");

    uAmbColor = safe_glGetUniformLocation(ShadeProg[shader], "uAmbColor");
    uSpecColor = safe_glGetUniformLocation(ShadeProg[shader], "uSpecColor");
    uDiffColor = safe_glGetUniformLocation(ShadeProg[shader], "uDiffColor");
    uProjMatrix = safe_glGetUniformLocation(ShadeProg[shader], "uProjMatrix");
    uViewMatrix = safe_glGetUniformLocation(ShadeProg[shader], "uViewMatrix");
    uModelMatrix = safe_glGetUniformLocation(ShadeProg[shader], "uModelMatrix");
    uNormalMatrix = safe_glGetUniformLocation(ShadeProg[shader], "uNormalMatrix");

    uLightPos = safe_glGetUniformLocation(ShadeProg[shader], "uLightPos");
    uLightColor = safe_glGetUniformLocation(ShadeProg[shader], "uLightColor");
    uShininess = safe_glGetUniformLocation(ShadeProg[shader], "uShininess");
    uSpecStrength = safe_glGetUniformLocation(ShadeProg[shader], "uSpecStrength");
    uCamTrans = safe_glGetUniformLocation(ShadeProg[shader], "uCamTrans");

    aTexCoord = safe_glGetAttribLocation(ShadeProg[shader], "aTexCoord");
    uTexUnit = safe_glGetUniformLocation(ShadeProg[shader], "uTexUnit");
    uTexUnit2 = safe_glGetUniformLocation(ShadeProg[shader], "uTexUnit2");
    uUseTex = safe_glGetUniformLocation(ShadeProg[shader], "uUseTex");
    uUseTex2 = safe_glGetUniformLocation(ShadeProg[shader], "uUseTex2");
    uTime = safe_glGetUniformLocation(ShadeProg[shader], "uTime");

    std::cout << "Successfully installed shader " << ShadeProg[shader] << std::endl;
}

void initializeDeferredShaderConnection(int shader) {
    glUseProgram(ShadeProg[shader]);

    // get handles to attribute data
    aPosition = safe_glGetAttribLocation(ShadeProg[shader], "aPosition");
    aNormal = safe_glGetAttribLocation(ShadeProg[shader], "aNormal");

    uAmbColor = safe_glGetUniformLocation(ShadeProg[shader], "uAmbColor");
    uSpecColor = safe_glGetUniformLocation(ShadeProg[shader], "uSpecColor");
    uDiffColor = safe_glGetUniformLocation(ShadeProg[shader], "uDiffColor");
    uProjMatrix = safe_glGetUniformLocation(ShadeProg[shader], "uProjMatrix");
    uViewMatrix = safe_glGetUniformLocation(ShadeProg[shader], "uViewMatrix");
    uModelMatrix = safe_glGetUniformLocation(ShadeProg[shader], "uModelMatrix");
    uNormalMatrix = safe_glGetUniformLocation(ShadeProg[shader], "uNormalMatrix");

    uLightPos = safe_glGetUniformLocation(ShadeProg[shader], "uLightPos");
    uLightColor = safe_glGetUniformLocation(ShadeProg[shader], "uLightColor");
    uShininess = safe_glGetUniformLocation(ShadeProg[shader], "uShininess");
    uSpecStrength = safe_glGetUniformLocation(ShadeProg[shader], "uSpecStrength");
    uCamTrans = safe_glGetUniformLocation(ShadeProg[shader], "uCamTrans");

    aTexCoord = safe_glGetAttribLocation(ShadeProg[shader], "aTexCoord");
    uTexUnit = safe_glGetUniformLocation(ShadeProg[shader], "uTexUnit");
    uTexUnit2 = safe_glGetUniformLocation(ShadeProg[shader], "uTexUnit2");
    uUseTex = safe_glGetUniformLocation(ShadeProg[shader], "uUseTex");
    uUseTex2 = safe_glGetUniformLocation(ShadeProg[shader], "uUseTex2");
    uTime = safe_glGetUniformLocation(ShadeProg[shader], "uTime");

    m_diffuseID = safe_glGetUniformLocation(ShadeProg[shader], "tDiffuse");
    m_positionID = safe_glGetUniformLocation(ShadeProg[shader], "tPosition");
    m_normalsID = safe_glGetUniformLocation(ShadeProg[shader], "tNormals");
    
    std::cout << "Successfully installed shader " << ShadeProg[shader] << std::endl;
}

int main(int argc, char *argv[]) {
    g_hasWon = g_hasQuit = false;
    g_moveMouse = false;//true;

    roomFloorHeight = vec3(0.f);
    roomCeilHeight = 0.f;

    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 8);

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
    printOpenGLError();
    getGLversion();
    printOpenGLError();

    // Shader Setup: Main Shader
    if (!InstallShader(
            "mesh_vert.glsl",
            "mesh_frag.glsl", 0)) {
        printf("Error installing main shader!\n");
        return 1;
    }

    initializeShaderConnection(0);
    initializeShaderVariables();

    //highlight shader
    if (!InstallShader("laplacian_vert.glsl", "laplacian_frag.glsl", 1)) {
        printf("Error installing highlight shader!\n");
        return 1;
    }

    initializeShaderConnection(1);
    initializeLaplaceShaderVariables();

    //shadow shader
    if (!InstallShader("shadow_vert.glsl", "shadow_frag.glsl", 2)) {
        printf("Error installing shadow shader!\n");
        return 1;
    }

    initializeShaderConnection(2);
    initializeShadowShaderVariables();

    //deferred rendering shader
    if (!InstallShader("deferredShader_vert.glsl", "deferredShader_frag.glsl", 3)) {
        printf("Error installing deferred render shader!\n");
        return 1;
    }

    initializeDeferredShaderConnection(3);
    initializeDeferredShadingVariables();

    //deferred shading shader
    if (!InstallShader("passThrough_vert.glsl", "passThrough_frag.glsl", 4)) {
        printf("Error installing deferred shading shader!\n");
        return 1;
    }

    initializeDeferredShaderConnection(4);
    initializePassThroughShaderVariables();


    //start the random counter
    srand(time(NULL));

    //set input callback functions
    glfwSetMousePos(windowWidth / 2, windowHeight / 2);
    currState =  new Running(); //new MainMenu(); 
    glfwSetKeyCallback(Keyboard);
    glfwSetMousePosCallback(MouseMove);
    glfwSetMouseButtonCallback(MouseClick);
    //initialize the current state to running atm
    //this should start off as MainMenu() when we get to that point

    //begin game loop
    gameLoop();

    delete currState;
    glfwTerminate();
    return 0;
}
