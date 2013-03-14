/* 
 * File:   DiamondKey.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 6:34 AM
 */

#include "DiamondKey.h"

#define KEY_DISTANCE 2.f

DiamondKey::DiamondKey() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/keys/Key_Diamond.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);

    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f, 1.f, 1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    //Translate to hang from moose head horns
    doRotate(vec3(1, 0, 0), -90);
    initTranslate = glm::vec3(14.3f, getRoomCeilHeight() - getAABBmax().y - 3.f,
            ROOM_SIZE + getAABBmin().z - .5f);
    doTranslate(initTranslate);
    //doRotate(vec3(0,1,0), 90);
    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    LoadTexture((char *) "objects/meshes/keys/Key_DiamondUV.bmp", texNum);
    hasTex = true;

    isVisible = isHeld = isInKeyhole = false;
}

DiamondKey::DiamondKey(const DiamondKey& orig) {
}

DiamondKey::~DiamondKey() {
}

bool DiamondKey::doesCollide(GameObject* other) {
    return false; //never can collide
}

std::string DiamondKey::className() {
    return "DiamondKey";
}

void DiamondKey::onEvent(SoundPlayer* soundPlayer) {
    //soundPlayer->playSound("tryRadio");
}

void DiamondKey::update(float dt, GameObject* playerCamera, vec3 camLookAt) {
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
        rotate = mat4(1.f);
        trans = vec3(0.f);
        doRotate(vec3(1, 0, 0), -90);
        doTranslate(initTranslate);
    } else if (isInKeyhole) {
        trans = vec3(0.f);
        this->rotate = glm::mat4(1.f);
        doTranslate(vec3(-2.1f,-.45f,-ROOM_SIZE - getAABBmin().z + 2.5f));
    }
}
