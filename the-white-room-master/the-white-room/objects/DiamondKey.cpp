/* 
 * File:   DiamondKey.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 6:34 AM
 */

#include "DiamondKey.h"

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
    
    doRotate(vec3(1,0,0), 90);
    //doRotate(vec3(0,1,0), 90);
    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    LoadTexture((char *)"objects/meshes/keys/Key_DiamondUV.bmp", texNum);
    hasTex = true;

    isVisible = false;
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
