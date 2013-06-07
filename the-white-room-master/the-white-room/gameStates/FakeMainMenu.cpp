/* 
 * File:   FakeMainMenu.cpp
 * Author: goofanader
 * 
 * Created on January 29, 2013, 10:19 PM
 */

#include "FakeMainMenu.h"
#include "../objects/MeshLoader.h"
#include "../GeometryCreator.h"
//#include "../objects/mainMenu/MenuObjects.h"
//#include "objects/mainMenu/MenuObjects.h"

#define MOVE_SPEED 15.f
#define PI 3.14159f

FakeMainMenu::FakeMainMenu() {
    camAlpha = -0.545f;
    camBeta = -PI / 2.f - 1.f;
    camLookAt = glm::vec3(0.f);
    timeSpent = 0;

    if (IS_SOUND_ON) {
        soundPlayer = new SoundPlayer("audio/menuSounds.txt"); //change what sounds are accessed
        printf("loaded the menu's sound player\n");
    }

    initializeCamera();
    initializeLight();

    //objects.insert(new Mouse());
    //objects.insert();
    frame = new FakeOpening();
    
    soundPlayer->playContinuous("MenuSong");
    
    waitCounter = 0;
    
    setStartRunning(1000);
}

void FakeMainMenu::initializeCamera() {
    //initialize camera
    playerCamera = new GameObject();
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
            0.f - playerCamera->getAABBmin().y, 20.f));

    camPrevTrans = camNextTrans = playerCamera->trans;

    prevAlpha = camAlpha;
    prevBeta = camBeta;
    
    //updateLookAt();
}

void FakeMainMenu::initializeLight() {
    Mesh *globe = GeometryCreator::CreateSphere(glm::vec3(1), 32, 32);
    lightPos = new GameObject();
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

FakeMainMenu::FakeMainMenu(const FakeMainMenu& orig) {
}

FakeMainMenu::~FakeMainMenu() {
    //std::cout << "Deleting FakeMainMenu" << std::endl;
    /*for (std::set<GameObject*>::iterator iter = objects.begin();
            iter != objects.end(); iter++) {
        GameObject* curr = (*iter);
        //std::cout << "Deleting " << curr->className() << "..." << std::endl;
        delete curr;
    }*/

    //objects.clear();

    delete frame;
    delete playerCamera;
    delete lightPos;
    delete soundPlayer;
}

void FakeMainMenu::draw() {
   vec3 lightPosition = vec3(0.f,5.f,20.f);
    frame->draw(playerCamera->trans, camLookAt, lightPosition, 
            getGC()->lightColor, getGC(), 0);
    
    if (frame->isItLoading() && waitCounter < 1) {
        waitCounter++;
        glfwSetMousePos(getWindowWidth() / 2, getWindowHeight() / 2);
        //setIsNextState("FakeMainMenu");
    } else if (waitCounter >= 1) {
        setIsNextState("FakeMainMenu");
    }
    //====if you want to draw where the light is, uncomment code below.====//
    //lightPos->draw(playerCamera->trans, camLookAt, getGC()->lightPos,
    //      getGC()->lightColor, getGC());
}

void FakeMainMenu::update(float dt) {
    if (!isPaused()) {
        timeSpent += dt;

        lightPos->trans = getGC()->lightPos;
        //GameObject* curr;

        camPrevTrans = playerCamera->trans;
        playerCamera->trans = camNextTrans;

        /*for (std::set<GameObject*>::iterator iter = objects.begin();
                iter != objects.end(); iter++) {
            curr = (*iter);

            curr->update(dt, playerCamera, camLookAt);
        }*/
        
        frame->update(dt, playerCamera, camLookAt);
        
        camPrevTrans = playerCamera->trans;
        prevAlpha = camAlpha;
        prevBeta = camBeta;
    }
}

void FakeMainMenu::mouseClicked(int button, int action) {
    //GameObject* curr;

    if (action == GLFW_RELEASE) {
        //switch to the loading screen, and then start Running.cpp
        frame->setIsLoading(true);
        setCanMoveMouse(false);
        //glfwDisable(GLFW_MOUSE_CURSOR);
        glDepthFunc(GL_LEQUAL);
    }
}

void FakeMainMenu::keyPressed(float dt, int keyDown[]) {
    float frameBuffMoveSpeed = .3f;

    /*if (keyDown[GLFW_KEY_LEFT]) {
        frame->doTranslate(vec3(-frameBuffMoveSpeed, 0.f, 0.f));
    }
    if (keyDown[GLFW_KEY_RIGHT]) {
        frame->doTranslate(vec3(frameBuffMoveSpeed, 0.f, 0.f));
    }
    if (keyDown[GLFW_KEY_DOWN]) {
        frame->doTranslate(vec3(0.f, -frameBuffMoveSpeed, 0.f));
    }
    if (keyDown[GLFW_KEY_UP]) {
        frame->doTranslate(vec3(0.f, frameBuffMoveSpeed, 0.f));
    }
    if (keyDown['I']) {
        frame->doTranslate(vec3(0.f, 0.f, frameBuffMoveSpeed));
    }
    if (keyDown['K']) {
        frame->doTranslate(vec3(0.f, 0.f, -frameBuffMoveSpeed));
    }*/
    
    //std::cout << "Frame Trans: " << printVec3(frame->trans) << std::endl;
}

void FakeMainMenu::pause() {
    State::pause();
}

void FakeMainMenu::resume() {
    State::resume();
}

void FakeMainMenu::updateLookAt() {
    //camLookAt = playerCamera->trans - glm::vec3(
    camLookAt = camNextTrans - glm::vec3(
            cos(camAlpha) * cos(camBeta),
            sin(camAlpha),
            cos(camAlpha) * sin(camBeta));
}
