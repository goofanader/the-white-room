/* 
 * File:   Running.cpp
 * Author: goofanader
 * 
 * Created on January 29, 2013, 10:19 PM
 */

#include "Running.h"
#include "objects/AllObjects.h"
#include "objects/MeshLoader.h"
#include "GeometryCreator.h"
#include "events/ObjectCreation.h"

#define HARDCODE_OBJECTS_IN 0
#define MAX_EVENTS 0

#define MOVE_SPEED 20.f
#define PI 3.14159f

#define MAX_MOUSE_CLICKS 0

Running::Running() {
    initializeCamera();
    initializeLight();
    camAlpha = 0.f;
    camBeta = PI;
    camLookAt = glm::vec3(0.f);

    eventNum = 1;

    //objects.insert(new Room());

    printf("try the sound\n");
    soundPlayer = new SoundPlayer();
    printf("loaded the sound player\n");
    
    switches[0].setClassName("Book1");
    switches[1].setClassName("Book2");
    switches[2].setClassName("Book3");
    for (int i = 0; i < 3; i++) {
        switches[i].setIsEmpty(false);
        switches[i].setSwitch(false);
    }
    
    currEvent = new Event(eventNum, soundPlayer);
    loadObjectsFromEvent();

    //set mouse cursor to invisible
    //glfwDisable(GLFW_MOUSE_CURSOR);

    mouseClicks = MAX_MOUSE_CLICKS;

    //printf("woof\n");

    //printf("nya\n");
}

void Running::initializeCamera() {
    //initialize camera
    playerCamera = new GameObject();
    playerCamera->AABBmin = glm::vec3(-0.5f, -0.5f, -0.5f);
    playerCamera->AABBmax = glm::vec3(0.5f, 0.5f, 0.5f);
    playerCamera->dir = vec3(0.f);
    playerCamera->speed = 0.f;
    playerCamera->rotAxis = vec3(0.f, 1.f, 0.f);
    playerCamera->rotSpeed = 0.f;
    playerCamera->doTranslate(vec3(-8.f, -.7f, 0.f));
    playerCamera->scale = vec3(1.f);

    camPrevTrans = playerCamera->trans;
}

void Running::initializeLight() {
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
}

void Running::loadObjectsFromEvent() {
    EventSwitch *arr = currEvent->getSwitches();

    for (int i = 0; i < currEvent->getSwitchNum(); i++, arr++) {
        GameObject* newObject = lookupAndCall(arr->getClassName());
        if (newObject) {
            objects.insert(newObject);
            arr->setGameObject(newObject);
            
            if (newObject->className() == "Book1") {
                switches[0].setGameObject(newObject);
            }
            if (newObject->className() == "Book2") {
                switches[1].setGameObject(newObject);
            }
            if (newObject->className() == "Book3") {
                switches[2].setGameObject(newObject);
            }
        }
    }
}

Running::Running(const Running& orig) {
}

Running::~Running() {
    delete soundPlayer;
}

void Running::draw() {
    for (std::set<GameObject*>::iterator iter = objects.begin();
            iter != objects.end(); iter++) {
        (*iter)->draw(playerCamera->trans, camLookAt, getGC()->lightPos,
                getGC()->lightColor, getGC());
    }
    //camBeta += .1;
    lightPos->draw(playerCamera->trans, camLookAt, getGC()->lightPos,
            getGC()->lightColor, getGC());
}

void Running::update(float dt) {
    if (!isPaused()) {
        playerCamera->update(dt);
        playerCamera->AABBmin = playerCamera->trans - .5f;
        playerCamera->AABBmax = playerCamera->trans + .5f;

        lightPos->trans = getGC()->lightPos;
        GameObject* curr;

        for (std::set<GameObject*>::iterator iter = objects.begin();
                iter != objects.end(); iter++) {
            curr = (*iter);

            curr->update(dt);

            /*std::cout << "Item " << curr->className() << ": AABBmin = (";
            std::cout << curr->AABBmin.x << ", " << curr->AABBmin.y << ", " << curr->AABBmin.z;
            std::cout << "). AABBmax=(" << curr->AABBmax.x << ", " << curr->AABBmax.y;
            std::cout << ", " << curr->AABBmax.z << ")\n==============" << std::endl;*/

            if (curr->doesCollide(playerCamera)) {
                //we need to stop player movement as well AKA
                //don't go through objects :<
                playerCamera->trans = camPrevTrans;

                //cout << "colliding with " << curr->className() << endl;
            } else {
                //cout << "not colliding with " << curr->className() << endl;
            }
        }
        camPrevTrans = playerCamera->trans;
    }
}

void Running::mouseClicked(int button, int action) {
    float x, y, z, mag;
    glm::vec3 translatedCam, reach;

    float nx, ny, nz,
            px, py, pz,
            ox, oy, oz,
            dx, dy, dz;

    float t;

    int sound = 0;

    GameObject* curr;

    if (action == GLFW_RELEASE && mouseClicks >= MAX_MOUSE_CLICKS) {
        mouseClicks = 0;
        //Sound code
        //soundPlayer->playSound("Click");

        for (std::set<GameObject*>::iterator iter = objects.begin();
                iter != objects.end(); iter++) {
            curr = (*iter);

            glm::vec3 normalizedCam = camLookAt - playerCamera->trans;

            dx = normalizedCam.x;
            dy = normalizedCam.y;
            dz = normalizedCam.z;

            ox = playerCamera->trans.x;
            oy = playerCamera->trans.y;
            oz = playerCamera->trans.z;

            x = playerCamera->trans.x - curr->trans.x;
            y = playerCamera->trans.y - curr->trans.y;
            z = playerCamera->trans.z - curr->trans.z;

            //distance from current object

            //printf("mag = %f\n",mag);

            mag = sqrt(x * x + y * y + z * z);

            //intersection b/n view vector and planes

            for (int i = 0; i < 6; i++) {
                if (i == 0) {
                    nx = 0.f;
                    ny = 0.f;
                    nz = 1.f;

                    px = curr->AABBmax.x;
                    py = curr->AABBmax.y;
                    pz = curr->AABBmax.z;
                } else if (i == 1) {
                    nx = 1.f;
                    ny = 0.f;
                    nz = 0.f;

                    px = curr->AABBmax.x;
                    py = curr->AABBmax.y;
                    pz = curr->AABBmax.z;
                } else if (i == 2) {
                    nx = 0.f;
                    ny = 1.f;
                    nz = 0.f;

                    px = curr->AABBmax.x;
                    py = curr->AABBmax.y;
                    pz = curr->AABBmax.z;
                } else if (i == 3) {
                    nx = 0.f;
                    ny = 0.f;
                    nz = -1.f;

                    px = curr->AABBmin.x;
                    py = curr->AABBmin.y;
                    pz = curr->AABBmin.z;
                } else if (i == 4) {
                    nx = -1.f;
                    ny = 0.f;
                    nz = 0.f;

                    px = curr->AABBmin.x;
                    py = curr->AABBmin.y;
                    pz = curr->AABBmin.z;
                } else if (i == 5) {
                    nx = 0.f;
                    ny = -1.f;
                    nz = 0.f;

                    px = curr->AABBmin.x;
                    py = curr->AABBmin.y;
                    pz = curr->AABBmin.z;
                }

                t = (nx * px + ny * py + nz * pz - nx * ox - ny * oy - nz * oz) /
                        (nx * dx + ny * dy + nz * dz);

                reach.x = ox + dx * t;
                reach.y = oy + dy * t;
                reach.z = oz + dz * t;

                //printf("reach = %f, %f, %f\n",reach.x, reach.y, reach.z);


                if (reach.x >= curr->AABBmin.x && reach.x <= curr->AABBmax.x &&
                        reach.y >= curr->AABBmin.y && reach.y <= curr->AABBmax.y &&
                        reach.z >= curr->AABBmin.z && reach.z <= curr->AABBmax.z) {

                    //curr->onEvent(soundPlayer);
                    sound = 1;
                    //curr->changeColor(glm::vec3(1.0f, 0.f, 0.f));
                    //curr->update(0.f);
#if 0
                    //if true, want to switch out to the next event
                    if (eventNum <= MAX_EVENTS && currEvent->getEventNum() == eventNum &&
                            currEvent->setSwitch(curr->className())) {
                        //cout << "deleted old event" << endl;
                        //delete currEvent;

                        if ((++eventNum) <= MAX_EVENTS) {
                            currEvent = new Event(eventNum, soundPlayer);
                            loadObjectsFromEvent();
                            break;
                        }
                    }
#endif
                    if (curr->className() == "Book1") {
                        printf("clicked on Book1\n");
                        switches[0].setSwitch(true);
                        curr->onEvent(soundPlayer);
                    } else if (curr->className() == "Book2" && switches[0].isSwitchOn()) {
                        printf("clicked on Book2 in order\n");
                        switches[1].setSwitch(true);
                        curr->onEvent(soundPlayer);
                    } else if (curr->className() == "Book3" && switches[0].isSwitchOn() &&
                            switches[1].isSwitchOn()) {
                        printf("clicked on Book3 in order\n");
                        switches[2].setSwitch(true);
                        curr->onEvent(soundPlayer);
                        
                        
                    } else if ((curr->className() == "Book2" && !switches[0].isSwitchOn()) ||
                            curr->className() == "Book3" && !(switches[0].isSwitchOn() &&
                            switches[1].isSwitchOn())) {
                        for (int i = 0; i < 3; i++) {
                            switches[i].setSwitch(false);
                            switches[i].getGameObject()->changeColor(switches[i].getGameObject()->initAmbColor);
                        }
                        printf("oh no! out of order :(\n");
                    }
                }

            }

            if (!sound) {
                //soundPlayer->playSound("Click");
            } else {
                sound = 0;
            }


            /*
            printf("AABBmins = %f, %f, %f\n",
            curr->AABBmin.x, curr->AABBmin.y, curr->AABBmin.z);

            printf("AABBmaxes = %f, %f, %f\n",
            curr->AABBmax.x, curr->AABBmax.y, curr->AABBmax.z);
             */

        }
    } else mouseClicks++;
}

void Running::mouseMoved(int x, int y, float prevX, float prevY) {
    if (!isPaused()) {
        camAlpha += (float) (y - prevY) / getWindowHeight() * 1;
        const float threshold = 3.14159f / 2.f;
        if (camAlpha < -threshold)
            camAlpha = -threshold;
        else if (camAlpha > threshold)
            camAlpha = threshold;
        camBeta += (float) (x - prevX) / getWindowWidth() * 2;
        updateLookAt();
        //printf("A: %lf, B: %lf\n", camAlpha, camBeta);
    }
}

void Running::keyPressed(float dt, int keyDown[]) {
    if (!keyDown['P'] && !isPaused()) {
        //handleFirstPersonMovement(dt, keyDown);
        // Camera movement
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 forward = glm::normalize(camLookAt - playerCamera->trans);
        glm::vec3 right = glm::normalize(glm::cross(forward, up));

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
        //if (playerCamera->trans.y <= 0.f)
        //  playerCamera->trans.y = 0.f;
        updateLookAt();
    } else if (keyDown['P'] && !isPaused()) {
        pause();
        glfwEnable(GLFW_MOUSE_CURSOR);
    } else if (keyDown['P'] && isPaused()) {
        resume();
        //glfwDisable(GLFW_MOUSE_CURSOR);
    }
}

void Running::wKeyPressed(glm::vec3 vecW) {
}

void Running::aKeyPressed(glm::vec3 vecU) {
}

void Running::sKeyPressed(glm::vec3 vecW) {
}

void Running::dKeyPressed(glm::vec3 vecU) {
}

void Running::pause() {
    State::pause();
}

void Running::resume() {
    State::resume();
}

void Running::printObjects() {
}

void Running::updateLookAt() {
    camLookAt = playerCamera->trans - glm::vec3(
            cos(camAlpha) * cos(camBeta),
            sin(camAlpha),
            cos(camAlpha) * sin(camBeta));
}

void Running::handleFirstPersonMovement(int keyDown[], float dt) {

}
