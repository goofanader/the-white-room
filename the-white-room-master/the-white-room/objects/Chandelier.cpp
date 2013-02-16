/* 
 * File:   Chandelier.cpp
 * Author: goofanader
 * 
 * Created on February 13, 2013, 12:35 PM
 */

#include "Chandelier.h"

Chandelier::Chandelier() {
    
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/chandelier/Chandelier.obj",
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

Chandelier::Chandelier(const Chandelier& orig) {
}

Chandelier::~Chandelier() {
}

std::string Chandelier::className() {
    return "Chandelier";
}