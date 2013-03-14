/* 
 * File:   HeartKey.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 6:34 AM
 */

#include "HeartKey.h"

#define KEY_DISTANCE 2.f

HeartKey::HeartKey() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/keys/Key_Heart.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f, 0.f, 0.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    //Translate to sit on the picture frame
    doTranslate(vec3(-ROOM_SIZE - getAABBmin().x + .25, 
            getRoomCeilHeight() - getAABBmax().y - 7.9f, -15.f));
    isVisible = false;
    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    LoadTexture((char *)"objects/meshes/keys/Key_HeartUV.bmp", texNum);
    hasTex = true;
    
    isHeld = isInKeyhole = false;
}

HeartKey::HeartKey(const HeartKey& orig) {
}

HeartKey::~HeartKey() {
}

bool HeartKey::doesCollide(GameObject* other) {
    return false;
}

std::string HeartKey::className() {
    return "HeartKey";
}

void HeartKey::onEvent(SoundPlayer* soundPlayer) {
    //soundPlayer->playSound("tryRadio");
}

void HeartKey::update(float dt, GameObject* playerCamera, vec3 camLookAt) {
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
        rotY -= 90;

        rotA = asin(glm::length(axis) / (glm::length(loc))) * 180.0 / 3.14;
        rotA = 90 - rotA;

        //rotA = atan2(loc.y, loc.z) * 180.0 / 3.14;
        //rotA = 90 - rotA;

        //reset rotation matrix
        this->rotate = glm::mat4(1.f);

        //doRotate(glm::cross(up,axis), rotating);
        doRotate(axis, rotA);
        doRotate(up, rotY);
    } else if (!isInKeyhole) {
        trans = vec3(0.f);
        doTranslate(vec3(-ROOM_SIZE - getAABBmin().x + .25, 
            getRoomCeilHeight() - getAABBmax().y - 7.9f, -15.f));
    } else if (isInKeyhole) {
        isVisible = false;
    }
}