/* 
 * File:   WhiteDoor.cpp
 * Author: goofanader
 * 
 * Created on January 30, 2013, 11:04 PM
 */
#include <iostream>
#include "WhiteDoor.h"
#include "glm/gtx/integer.hpp"

#define GROUND_POS -0.5f

WhiteDoor::WhiteDoor() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/door/Door.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);

    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    shininess = 2.f;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    ambColor = glm::vec3(1.f);
    diffColor = glm::vec3(.8f);
    specColor = glm::vec3(.8f);
    ambAlpha = 1.0f;
    diffAlpha = 1.0f;
    specAlpha = 1.0f;
    isClicked = false;
    isClosed = true;
    timeSpent = 0.0;

    depthMin = 0;
    depthMax = 1;

    doorAngle = 180.f;
    doScale(glm::vec3(ROOM_SIZE / 5.f, ROOM_SIZE / 5.f - .45f, ROOM_SIZE / 5.f));

    doRotate(glm::vec3(0, 1, 0), doorAngle);
    doTranslate(glm::vec3(1.9f, getRoomFloorHeight().y - getAABBmin().y, ROOM_SIZE - .5f));
    prevAABBmin = getAABBmin();
    std::cout << "prevAABBmin: " << printVec3(prevAABBmin) << std::endl;

    glGenTextures(1, &texNum);
    LoadTexture((char *) "objects/meshes/door/DoorUV.bmp", texNum);
    hasTex = true;
    ignore = false;
    setNewBounds = false;
}

WhiteDoor::WhiteDoor(const WhiteDoor& orig) {
}

WhiteDoor::~WhiteDoor() {
}

void WhiteDoor::update(float dt, GameObject* playerCamera, vec3 camLookAt) {
    if (!isClosed) {
        if (timeSpent < 90) {
            //doTranslate(glm::vec3(2.f, 0.f, -2.f));
            doRotate(glm::vec3(0, 1, 0), 1.f);
            float xMove = -.075f;
            float zMove = -.065f; //-.3f;
            doTranslate(glm::vec3(xMove, 0.f, zMove));
            timeSpent ++;
            //setNewBounds = true;
        } else if (setNewBounds) {
            setNewBounds = false;
            //AABBmin.x = -7.1f;
            //AABBmax.x = -6.1f;
            AABBmin.z *= -1.f;
            AABBmax.z *= -1.f;
            AABBmin.z += -1.f;
            AABBmax.z += 6.f;
            AABBmin.x += 14.f;
            AABBmax.x += 10.f;

            AABBmin.x = -5.025f;
            AABBmax.x = -4.025f;
            AABBmin.z = 22.41f;
            AABBmax.z = 29.12f;
            this->fixBoundingBoxes();
            std::cout << "WhiteDoor newBound: AABBmin=" << printVec3(AABBmin);
            std::cout << "; AABBmax=" << printVec3(AABBmax) << std::endl;
        }

    } else {

        if (isHighlighted) {
            highlightColor = highlightColor + vec3(HIGHLIGHT_SPEED);

            if (highlightColor.x > 1.f) {
                highlightColor = vec3(1.f);
            }

            highlightAlpha += HIGHLIGHT_SPEED;
            if (highlightAlpha > 1.f) {
                highlightAlpha = 1.f;
            }
        } else {
            isHighlightDisappearing = true;
            highlightColor = highlightColor - vec3(HIGHLIGHT_SPEED);

            if (highlightColor.x < 0.f) {
                highlightColor = vec3(0.f);
            }

            highlightAlpha -= HIGHLIGHT_SPEED;
            if (highlightAlpha < 0.f) {
                isHighlightDisappearing = false;
                highlightAlpha = 0.f;
            }
        }
    }
}

void WhiteDoor::onEvent(SoundPlayer *soundPlayer) {
    if (hasWon()) {
        if (isClosed && IS_SOUND_ON) {
            soundPlayer->playSound("OpenDoor");
        }
        isClosed = false;
    } else if (IS_SOUND_ON) {
        soundPlayer->playSound("TryDoor");
    }
}

std::string WhiteDoor::className() {
    return "WhiteDoor";
}
