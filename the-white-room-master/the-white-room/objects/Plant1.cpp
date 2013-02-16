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
            IBOlen, VBO, IBO, NBO, faceNBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    color = vec3(1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    color = glm::vec3(1.f);
    
    doScale(glm::vec3(3.f));
    doTranslate(glm::vec3(0.f,-3.f,-7.f));
    //this->doScale(glm::vec3(3.f));
}

Plant1::Plant1(const Plant1& orig) {
}

Plant1::~Plant1() {
}

std::string Plant1::className() {
    return "Plant1";
}