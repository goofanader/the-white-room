/* 
 * File:   Book2.cpp
 * Author: goofanader
 * 
 * Created on February 14, 2013, 6:32 AM
 */

#include "Book2.h"

Book2::Book2() {
    
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/bookshelf/Book2.obj",
            IBOlen, VBO, IBO, NBO, faceNBO, AABBmin, AABBmax);
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    color = vec3(1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    color = glm::vec3(0.f, 1.f, 0.f);
    isClicked = false;
    
    doScale(glm::vec3(2.f));
    doRotate(glm::vec3(0,1,0), 90);
    doTranslate(glm::vec3(-15.5f,-8.f - 0.f,3.f));
}

Book2::Book2(const Book2& orig) {
}

Book2::~Book2() {
}

std::string Book2::className() {
    return "Book2";
}

void Book2::onEvent(SoundPlayer* soundPlayer) {
    soundPlayer->playSound("TryBook");
    color = glm::vec3(0.f);
}