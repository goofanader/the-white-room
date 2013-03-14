/* 
 * File:   ClubKey.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 6:34 AM
 */

#include "ClubKey.h"

ClubKey::ClubKey() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/keys/Key_Club.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f, 1.f, 1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    //Translate to be inside safe
    doTranslate(vec3(ROOM_SIZE + getAABBmin().x - 2, 
            getRoomFloorHeight().y - getAABBmin().y + .5, 19.7f));

    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    LoadTexture((char *)"objects/meshes/keys/Key_ClubUV.bmp", texNum);
    hasTex = true;

    isVisible = false;
    doRotate(vec3(0,0,1), 90);
}

ClubKey::ClubKey(const ClubKey& orig) {
}

ClubKey::~ClubKey() {
}

bool ClubKey::doesCollide(GameObject* other) {
    return false;
}

std::string ClubKey::className() {
    return "ClubKey";
}

void ClubKey::onEvent(SoundPlayer* soundPlayer) {
}
