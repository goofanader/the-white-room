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
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    //ambColor = glm::vec3(0.f, 1.f, 0.f);
    ambColor = glm::vec3(0.75f);
    diffColor = glm::vec3(0.94f, 0.90f, 0.55f); 
    specColor = vec3(.5f);
    isClicked = false;
    
    doScale(glm::vec3(1.25f));

    doRotate(glm::vec3(0,1,0), 90);

    //doTranslate(glm::vec3(-15.5f,-8.f - 0.f,3.f));
    //translate to Book1's pos
    doTranslate(glm::vec3(-ROOM_SIZE + 3.0f, -2.f, 0.0f));
    //translate to its own pos
    doTranslate(glm::vec3(0.f, -4.f, 3.f));
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
    ambColor = glm::vec3(0.f);
}
