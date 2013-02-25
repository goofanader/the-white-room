/* 
 * File:   Plant1.cpp
 * Author: goofanader
 * 
 * Created on February 13, 2013, 12:36 PM
 */

#include "Plant1.h"

Plant1::Plant1() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/plants/Plant1.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    texNum = numTextures();
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/plants/Plant1UV.bmp", texNum);
    printOpenGLError();
    hasTex = true;
    
    rotating = 90.f;
    
    doScale(glm::vec3(3.f));
    doTranslate(glm::vec3(0.f,-3.85f - getAABBmin().y,4.5f));
    //this->doScale(glm::vec3(3.f));
}

Plant1::Plant1(const Plant1& orig) {
}

Plant1::~Plant1() {
}

void Plant1::update(float dt) {
    if (rotating < 90.f) {
        rotating++;
        doRotate(vec3(0,1,0), 1.f);
    }
}

std::string Plant1::className() {
    return "Plant1";
}

void Plant1::onEvent(SoundPlayer *soundPlayer) {
    if (rotating >= 90.f) {
        rotating = 0.f;
    } else {
    }
}