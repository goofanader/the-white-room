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
            IBOlen, VBO, IBO, NBO, faceNBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f);
    diffColor = vec3(0.1, 0.74, 0.32);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    doScale(glm::vec3(3.f));
    doTranslate(glm::vec3(0.f,-3.f,-7.f));
    //this->doScale(glm::vec3(3.f));
}

Plant6::Plant6(const Plant6& orig) {
}

Plant6::~Plant6() {
}

std::string Plant6::className() {
    return "Plant6";
}
