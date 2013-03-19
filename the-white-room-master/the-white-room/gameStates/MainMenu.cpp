/* 
 * File:   MainMenu.cpp
 * Author: goofanader
 * 
 * Created on January 29, 2013, 10:19 PM
 */

#include "MainMenu.h"
#include "../objects/MeshLoader.h"
#include "../GeometryCreator.h"
//#include "../objects/mainMenu/MenuObjects.h"
//#include "objects/mainMenu/MenuObjects.h"

#define MAX_EVENTS 0

#define MOVE_SPEED 15.f
#define PI 3.14159f

#define MAX_FOOT_SPACE .4
#define MAX_CLICK_DISTANCE 15

MainMenu::MainMenu() {
    camAlpha = -0.545f;
    camBeta = -PI / 2.f - 1.f;
    camLookAt = glm::vec3(0.f);
    timeSpent = 0;

    if (IS_SOUND_ON) {
        soundPlayer = new SoundPlayer("audio/sounds.txt"); //change what sounds are accessed
        printf("loaded the sound player\n");
    }

    initializeCamera();
    initializeLight();
    
    //objects.insert(new Mouse());
    objects.insert(new KeyboardKeys());
}

void MainMenu::initializeCamera() {
    //initialize camera
    playerCamera = new DeferredShadingObject();
    playerCamera->AABBmin = glm::vec3(-0.5f, -7.0f, -0.5f);
    playerCamera->AABBmax = glm::vec3(0.5f, 7.0f, 0.5f);
    playerCamera->dir = vec3(0.f);
    playerCamera->speed = 0.f;
    playerCamera->rotAxis = vec3(0.f, 1.f, 0.f);
    playerCamera->rotSpeed = 0.f;
    playerCamera->trans = glm::vec3(0.f);
    playerCamera->scale = glm::vec3(1.f);
    playerCamera->rotate = glm::mat4(1.f);

    playerCamera->doTranslate(vec3(0.f,
            getRoomFloorHeight().y - playerCamera->getAABBmin().y, 20.f));

    camPrevTrans = camNextTrans = playerCamera->trans;

    prevAlpha = camAlpha;
    prevBeta = camBeta;
}

void MainMenu::initializeLight() {
    Mesh *globe = GeometryCreator::CreateSphere(glm::vec3(1), 32, 32);
    lightPos = new DeferredShadingObject();
    lightPos->IBO = globe->IndexHandle;
    lightPos->NBO = globe->NormalHandle;
    lightPos->VBO = globe->PositionHandle;
    lightPos->IBOlen = globe->IndexBufferLength;
    lightPos->ambColor = glm::vec3(.75f, 0.f, 0.f);

    lightPos->AABBmin = glm::vec3(-.5);
    lightPos->AABBmax = glm::vec3(.5);
    lightPos->doTranslate(getGC()->lightPos);

    delete globe;
}

MainMenu::MainMenu(const MainMenu& orig) {
}

MainMenu::~MainMenu() {
    //std::cout << "Deleting MainMenu" << std::endl;
    for (std::set<DeferredShadingObject*>::iterator iter = objects.begin();
            iter != objects.end(); iter++) {
        DeferredShadingObject* curr = (*iter);
        //std::cout << "Deleting " << curr->className() << "..." << std::endl;
        delete curr;
    }

    objects.clear();

    delete playerCamera;
    delete lightPos;
    delete soundPlayer;
}

void MainMenu::draw() {
    DeferredShadingObject *curr, *radio;
    bool hasRadio = false;

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    //glDepthFunc(GL_LESS);

    //====Deferred Render to Framebuffer====//
    glBindFramebuffer(GL_FRAMEBUFFER, getDRC()->FramebufferName);
    glViewport(0, 0, getWindowWidth(), getWindowHeight());
    
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    
    GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2};
    glDrawBuffers(3, buffers);
    
    for (std::set<DeferredShadingObject*>::iterator iter = objects.begin();
            iter != objects.end(); iter++) {
        curr = (*iter);

        curr->draw(playerCamera->trans, camLookAt, getDRC()->lightPos,
                getDRC()->lightColor, getDRC());
    }
    
    //====Deferred Shading to Main Frame====//
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    // Render on the whole framebuffer, complete from the lower left corner to the upper right
    glViewport(0, 0, getWindowWidth(), getWindowHeight());

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use our shader
    glUseProgram(getDSC()->shader);

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getDSC()->diffuseTexture);
    glUniform1i(getDSC()->m_diffuseID, 0);
    
    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getDSC()->PositionTexture);
    glUniform1i(getDSC()->m_positionID, 1);
    
    glActiveTexture(GL_TEXTURE2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, getDSC()->NormalsTexture);
    glUniform1i(getDSC()->m_normalsID, 2);
    
    glDisable(GL_CULL_FACE);
    glm::mat4 projection = glm::ortho(0.f, (float)getWindowWidth(), 0.f, (float)getWindowHeight());//, .1f, 2.f);
    safe_glUniformMatrix4fv(getDSC()->h_uProjMatrix, glm::value_ptr(projection));
    
    vec3 cameraPos = playerCamera->trans;
    vec3 lightPos = getDRC()->lightPos;
    vec3 lightColor = getDRC()->lightColor;
    
    glUniform3f(getDSC()->h_uLightPos, lightPos.x, lightPos.y, lightPos.z);
    glUniform4f(getDSC()->h_uLightColor, lightColor.x, lightColor.y, lightColor.z, 1.0);
    glUniform3f(getDSC()->h_uCamTrans, cameraPos.x, cameraPos.y, cameraPos.z);
    
    // 1st attribute buffer : vertices
    safe_glEnableVertexAttribArray(getDSC()->h_aPosition); //instead of 0, use h_Quad
    glBindBuffer(GL_ARRAY_BUFFER, getDSC()->quad_vertexbuffer);
    safe_glVertexAttribPointer(
            getDSC()->h_aPosition, // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3, // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            0, // stride
            (void*) 0 // array buffer offset
            );

    // Draw the triangles !
    glDrawArrays(GL_TRIANGLES, 0, 6); // 2*3 indices starting at 0 -> 2 triangles

    safe_glDisableVertexAttribArray(getDSC()->h_aPosition); //use h_Quad
    //====if you want to draw where the light is, uncomment code below.====//
    //lightPos->draw(playerCamera->trans, camLookAt, getGC()->lightPos,
    //      getGC()->lightColor, getGC());
}

void MainMenu::update(float dt) {
    if (!isPaused()) {
        timeSpent += dt;

        lightPos->trans = getGC()->lightPos;
        DeferredShadingObject* curr;

        camPrevTrans = playerCamera->trans;
        playerCamera->trans = camNextTrans;

        for (std::set<DeferredShadingObject*>::iterator iter = objects.begin();
                iter != objects.end(); iter++) {
            curr = (*iter);

            curr->update(dt, playerCamera, camLookAt);
        }
        camPrevTrans = playerCamera->trans;
        prevAlpha = camAlpha;
        prevBeta = camBeta;
    }
}

void MainMenu::mouseClicked(int button, int action) {
    DeferredShadingObject* curr;

    if (action == GLFW_RELEASE) {
        //switch to the loading screen, and then start Running.cpp
        setCanMoveMouse(false);
        //glfwDisable(GLFW_MOUSE_CURSOR);
        glDepthFunc(GL_LEQUAL);
    }
}

void MainMenu::pause() {
    State::pause();
}

void MainMenu::resume() {
    State::resume();
}

void MainMenu::updateLookAt() {
    //camLookAt = playerCamera->trans - glm::vec3(
    camLookAt = camNextTrans - glm::vec3(
            cos(camAlpha) * cos(camBeta),
            sin(camAlpha),
            cos(camAlpha) * sin(camBeta));
}
