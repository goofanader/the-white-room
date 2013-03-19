/* 
 * File:   SpadeKey.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 6:34 AM
 */

#include "SpadeKey.h"

#define KEY_DISTANCE 2.f

SpadeKey::SpadeKey() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/keys/Key_Spade.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);

    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f, 1.f, 1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    depthMin = 0;
    depthMax = 1;
    
    highlightColor = vec3(0.f);
    highlightAlpha = 0.f;

    //Translate to be on top of armchair
    doRotate(vec3(0, 0, 1), 90);
    doScale(glm::vec3(.9f));
    doTranslate(glm::vec3(13.f, getRoomFloorHeight().y - getAABBmin().y + 3,
            -ROOM_SIZE + 10.f));
    isVisible = isHeld = isInKeyhole = false;

    glGenTextures(1, &texNum);
    LoadTexture((char *) "objects/meshes/keys/Key_SpadeUV.bmp", texNum);
    hasTex = true;
    ignore = false;
}

SpadeKey::SpadeKey(const SpadeKey& orig) {
}

SpadeKey::~SpadeKey() {
}

bool SpadeKey::doesCollide(GameObject* other) {
    return false;
}

std::string SpadeKey::className() {
    return "SpadeKey";
}

void SpadeKey::onEvent(SoundPlayer* soundPlayer) {
}

void SpadeKey::update(float dt, GameObject* playerCamera, vec3 camLookAt) {
    if (isHeld) {
        //move key to in front of player
        trans = vec3(0.f);
        doTranslate((camLookAt - playerCamera->trans) * vec3(KEY_DISTANCE) + playerCamera->trans);

        //make it so it always faces the player
        float rotY, rotA;
        vec3 up = glm::vec3(0.f, 1.f, 0.f);

        //get object location in room relative to player
        vec3 loc = playerCamera->trans - this->trans;

        //get a side axis for rotation up and down
        vec3 axis = glm::cross(up, loc);

        rotY = atan2(loc.x, loc.z) * 180.0 / 3.14;
        //rotY -= 90;

        rotA = asin(glm::length(axis) / (glm::length(loc))) * 180.0 / 3.14;
        rotA = 90 - rotA;

        if (loc.y > 0)
            rotA = -rotA;

        //reset rotation matrix
        this->rotate = glm::mat4(1.f);

        //doRotate(glm::cross(up,axis), rotating);
        doRotate(axis, rotA);
        doRotate(up, rotY);

        vec3 relative = glm::cross(axis, loc);
        relative = glm::normalize(relative);
        axis = glm::normalize(axis);
        loc = glm::normalize(loc);

        axis *= 2.1f;
        relative *= 1.5;

        doTranslate(relative);
        doTranslate(axis);

        loc = -loc;
        doTranslate(loc);

    } else if (!isInKeyhole) {
        trans = vec3(0.f);
        rotate = mat4(1.f);
        
        doRotate(vec3(0, 0, 1), 90);
        doTranslate(glm::vec3(13.f, getRoomFloorHeight().y - getAABBmin().y + 3,
                -ROOM_SIZE + 10.f));

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
    } else if (isInKeyhole) {
        trans = vec3(0.f);
        this->rotate = glm::mat4(1.f);
        doRotate(glm::vec3(0.f, 0.f, 1.f), 90.f);
        doTranslate(vec3(-4.1f,-.45f,-ROOM_SIZE - getAABBmin().z + 2.5f));
    }
}
