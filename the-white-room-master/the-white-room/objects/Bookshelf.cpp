/* 
 * File:   Bookshelf.cpp
 * Author: goofanader
 * 
 * Created on February 14, 2013, 6:06 AM
 */

#include "Bookshelf.h"

Bookshelf::Bookshelf() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/bookshelf/Bookshelf.obj",
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
    isClicked = false;
    
    doScale(glm::vec3(8.f));
    doRotate(glm::vec3(0,1,0), -270);
    doTranslate(glm::vec3(-15.5f,-8.f,0.f));
    
    AABBmin = glm::vec3(-200, -200, -200);
    AABBmax = glm::vec3(-200, -200, -200);
}

Bookshelf::Bookshelf(const Bookshelf& orig) {
}

Bookshelf::~Bookshelf() {
}

void Bookshelf::onEvent(SoundPlayer *soundPlayer) {
    //color = glm::vec3(1.f, 0.f, 0.f);
}

std::string Bookshelf::className() {
    return "Bookshelf";
}

bool Bookshelf::doesCollide(GameObject *other) {
    //don't do anything, lol
    return false;
}