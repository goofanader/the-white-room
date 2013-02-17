/* 
 * File:   Armchair.cpp
 * Author: goofanader
 * 
 * Created on February 12, 2013, 5:32 PM
 */

#include "Armchair.h"

Armchair::Armchair() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/armchair/chair.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f);
    diffColor = vec3(.5f);
    specColor = vec3(.5f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    isClicked = false;
    
    doScale(glm::vec3(3.f));
    doTranslate(glm::vec3(0.f,-3.f,-7.f));
    //this->doScale(glm::vec3(3.f));


 texNum = numTextures++;
    LoadTexture((char *)"objects/meshes/armchair/ChairTexture.bmp", texNum);
    hasTex = true;
   
}

Armchair::Armchair(const Armchair& orig) {
}

Armchair::~Armchair() {
}

std::string Armchair::className() {
    return "Armchair";
}