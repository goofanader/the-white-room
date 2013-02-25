/* 
 * File:   Plant6.cpp
 * Author: goofanader
 * 
 * Created on February 13, 2013, 12:36 PM
 */

#include "Plant6.h"

Plant6::Plant6() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/plants/Plant6.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(.75f);
    diffColor = vec3(0.1, 0.74, 0.32);
    specColor = vec3(.5f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/plants/Plant6UV.bmp", texNum);
    printOpenGLError();
    hasTex = true;
    
    rotating = 90.f;
    
    doScale(glm::vec3(3.f));
    doRotate(glm::vec3(0,1,0), rotating);
    doTranslate(glm::vec3(/*getAABBmax().x / 2.f*/0.f,-3.85f - getAABBmin().y,-4.f));
    //this->doScale(glm::vec3(3.f));
    
    std::cout << "Plant6 AABBmin=" << printVec3(getAABBmin());
    std::cout << ", AABBmax=" << printVec3(getAABBmax()) << std::endl;
    std::cout << "Plant6 realMin=" << printVec3(AABBmin);
    std::cout << ", realMax=" << printVec3(AABBmax) << std::endl;
}

Plant6::Plant6(const Plant6& orig) {
}

Plant6::~Plant6() {
}

void Plant6::update(float dt) {
    if (rotating < 90.f) {
        rotating++;
        doRotate(vec3(0,1,0), 1.f);
    }
}

std::string Plant6::className() {
    return "Plant6";
}

void Plant6::onEvent(SoundPlayer *soundPlayer) {
    if (rotating >= 90.f) {
        rotating = 0.f;
    } else {
    }
}
