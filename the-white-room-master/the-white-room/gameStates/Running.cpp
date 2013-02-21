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

#define MAX_EVENTS 0

#define MOVE_SPEED 15.f
#define PI 3.14159f

#define MAX_FOOT_SPACE .4

Running::Running() {
    camAlpha = -0.545f;
    camBeta = -PI / 2.f - 1.f;
    camLookAt = glm::vec3(0.f);

    eventNum = 1;

    isFoot1 = true;
    timeSpent = 0;

    if (IS_SOUND_ON) {
        printf("try the sound\n");
        soundPlayer = new SoundPlayer("audio/sounds.txt");
        printf("loaded the sound player\n");
        footSounds = new SoundPlayer("audio/feetSounds.txt");
        printf("loaded foot sounds\n");
    }

    currEvent = new Event(eventNum, soundPlayer);
    loadObjectsFromEvent();

    //set mouse cursor to invisible
    glfwDisable(GLFW_MOUSE_CURSOR);

    initializeCamera();
    initializeLight();
}

void Running::initializeCamera() {
    //initialize camera
    playerCamera = new GameObject();
    playerCamera->AABBmin = glm::vec3(-0.5f, -7.0f, -0.5f);
    playerCamera->AABBmax = glm::vec3(0.5f, 7.0f, 0.5f);
    playerCamera->dir = vec3(0.f);
    playerCamera->speed = 0.f;
    playerCamera->rotAxis = vec3(0.f, 1.f, 0.f);
    playerCamera->rotSpeed = 0.f;
    playerCamera->trans = glm::vec3(0.f);
    playerCamera->scale = vec3(1.f);

    playerCamera->doTranslate(vec3(0.f,
            getRoomFloorHeight().y - playerCamera->AABBmin.y, 0.f));

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
    GameObject *clockSound;
    EventSwitch *arr = currEvent->getSwitches();

    for (int i = 0; i < currEvent->getSwitchNum(); i++, arr++) {
        GameObject* newObject = lookupAndCall(arr->getClassName());
        if (newObject) {
            objects.insert(newObject);
            arr->setGameObject(newObject);

            if (newObject->className() == "Clock") {
                clockSound = newObject;
            }
        }
    }

    if (clockSound) {
        clockSound->onEvent(soundPlayer);
    }
}

Running::Running(const Running& orig) {
}

Running::~Running() {
    delete soundPlayer;
}

void Running::draw() {
    GameObject *curr;
    for (std::set<GameObject*>::iterator iter = objects.begin();
            iter != objects.end(); iter++) {
        curr = (*iter);

        glm::vec3 objPos = (curr->AABBmax + curr->AABBmin)*0.5f - playerCamera->trans;
        glm::vec3 lookDir = camLookAt - playerCamera->trans;

        float objPoslen = sqrt(objPos.x * objPos.x + objPos.y * objPos.y + objPos.z * objPos.z);
        float lookAtlen = sqrt(lookDir.x * lookDir.x + lookDir.y * lookDir.y + lookDir.z * lookDir.z);
        float angle = acos(glm::dot(objPos, lookDir) / (objPoslen * lookAtlen)) * 180.0f / PI;

        //printf("lookAt: %lf %lf, %lf\n", lookAt.x - cameraPos.x, lookAt.y - cameraPos.y, lookAt.z - cameraPos.z);
        //printf("angle: %lf\n", angle);

        if (angle < 90.0f || curr->className() == "Room") {
            curr->draw(playerCamera->trans, camLookAt, getGC()->lightPos,
                    getGC()->lightColor, getGC());
        }
    }
    //====if you want to draw where the light is, uncomment code below.====//
    /*lightPos->draw(playerCamera->trans, camLookAt, getGC()->lightPos,
          getGC()->lightColor, getGC());*/
}

void Running::update(float dt) {
    if (!isPaused()) {
        playerCamera->AABBmin.x = playerCamera->trans.x - .5f;
        playerCamera->AABBmin.y = playerCamera->trans.y - 7.f;
        playerCamera->AABBmin.z = playerCamera->trans.z - .5f;
        playerCamera->AABBmax.x = playerCamera->trans.x + .5f;
        playerCamera->AABBmax.y = playerCamera->trans.y + 7.f;
        playerCamera->AABBmax.z = playerCamera->trans.z + .5f;

        timeSpent += dt;

        lightPos->trans = getGC()->lightPos;
        GameObject* curr;

        for (std::set<GameObject*>::iterator iter = objects.begin();
                iter != objects.end(); iter++) {
            curr = (*iter);

            curr->update(dt);

            if (curr->doesCollide(playerCamera)) {
                playerCamera->trans = camPrevTrans;
            }
        }
        camPrevTrans = playerCamera->trans;
    }

    if (playerCamera->trans.x > ROOM_SIZE || playerCamera->trans.x < -ROOM_SIZE ||
            playerCamera->trans.z > ROOM_SIZE || playerCamera->trans.z < -ROOM_SIZE) {
        printf("====\nYou exited the white room and won the game!\n");

        exit(EXIT_SUCCESS);
    }
}

void Running::mouseClicked(int button, int action) {
    std::cout << "alpha=" << camAlpha << ", beta=" << camBeta << std::endl;
    float x, y, z, mag;
    glm::vec3 translatedCam, reach;

    float nx, ny, nz,
            px, py, pz,
            ox, oy, oz,
            dx, dy, dz;

    float t;
    GameObject* curr;

    if (action == GLFW_RELEASE) {
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

            //set normals to planes we're checking against
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
                        reach.z >= curr->AABBmin.z && reach.z <= curr->AABBmax.z &&
                        (glm::dot(normalizedCam, reach)) > 0.f) {
                    //print out what got clicked on
                    std::cout << "clicked on... " << curr->className();
                    std::cout << ". AABBmin=" << printVec3(curr->AABBmin);
                    std::cout << ", AABBmax=" << printVec3(curr->AABBmax);
                    std::cout << std::endl;

                    currEvent->ifObjectSelected(curr);
                    break;
                }
            }
        }
    }
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
        // Camera movement
        glm::vec3 up = glm::vec3(0, 1, 0);
        glm::vec3 forward = glm::normalize(vec3(camLookAt.x - playerCamera->trans.x, 0.0,
                camLookAt.z - playerCamera->trans.z));
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

        //make feet-walking sounds (uncomment the code below if you wanna hear)
        if (IS_SOUND_ON && (keyDown['W'] || keyDown['S'] || keyDown['D'] || keyDown['A'])) {
            if (timeSpent >= MAX_FOOT_SPACE) {
                timeSpent = 0.0;
                if (isFoot1) {
                    //printf("foot1 sound\n");
                    //footSounds->playSound("Footstep1");
                    isFoot1 = false;
                } else {
                    //printf("foot2 sound\n");
                    //footSounds->playSound("Footstep2");
                    isFoot1 = true;
                }
            }
        } else {
            isFoot1 = true;
        }

        updateLookAt();
    } else if (keyDown['P'] && !isPaused()) {
        pause();
    } else if (keyDown['P'] && isPaused()) {
        resume();
    }
}

void Running::pause() {
    State::pause();
    glfwEnable(GLFW_MOUSE_CURSOR);
}

void Running::resume() {
    State::resume();
    glfwDisable(GLFW_MOUSE_CURSOR);
}

void Running::updateLookAt() {
    camLookAt = playerCamera->trans - glm::vec3(
            cos(camAlpha) * cos(camBeta),
            sin(camAlpha),
            cos(camAlpha) * sin(camBeta));
}