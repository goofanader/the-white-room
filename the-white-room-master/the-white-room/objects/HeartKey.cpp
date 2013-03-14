/* 
 * File:   HeartKey.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 6:34 AM
 */

#include "HeartKey.h"

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
            getRoomCeilHeight() - getAABBmax().y - 7.8f, -17.f));
    isVisible = false;
    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    LoadTexture((char *)"objects/meshes/keys/Key_HeartUV.bmp", texNum);
    hasTex = true;

    //doRotate(vec3(0,0,1), 90);
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
