/* 
 * File:   Book1.cpp
 * Author: goofanader
 * 
 * Created on February 14, 2013, 6:32 AM
 */

#include "Book1.h"

Book1::Book1() {
    
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/bookshelf/Book1.obj",
            IBOlen, VBO, IBO, NBO, faceNBO, AABBmin, AABBmax);
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    color = vec3(1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    color = glm::vec3(1.f, 0.f, 0.f);
    
    doScale(glm::vec3(2.f));
    doRotate(glm::vec3(0,1,0), 90);
    doTranslate(glm::vec3(-15.5f,-8.f - 6.f,0.f));
}

Book1::Book1(const Book1& orig) {
}

Book1::~Book1() {
}

std::string Book1::className() {
    return "Book1";
}

void Book1::onEvent(SoundPlayer* soundPlayer) {
    soundPlayer->playSound("TryBook");
    color = glm::vec3(0.f);
}