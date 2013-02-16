/* 
 * File:   Book3.cpp
 * Author: goofanader
 * 
 * Created on February 14, 2013, 6:32 AM
 */

#include "Book3.h"

Book3::Book3() {
    
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/bookshelf/Book3.obj",
            IBOlen, VBO, IBO, NBO, faceNBO, AABBmin, AABBmax);
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    color = vec3(1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    color = glm::vec3(0.f, 0.f, 1.f);
    isClicked = false;
    
    doScale(glm::vec3(2.f));
    doRotate(glm::vec3(0,1,0), 90);
    doTranslate(glm::vec3(-15.5f,-8.f + 4.5f,-1.f));
}

Book3::Book3(const Book3& orig) {
}

Book3::~Book3() {
}

std::string Book3::className() {
    return "Book3";
}

void Book3::onEvent(SoundPlayer* soundPlayer) {
    soundPlayer->playSound("TryBook");
    color = glm::vec3(0.f);
}