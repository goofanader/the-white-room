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
    ambColor = vec3(0.75f);
    diffColor = vec3(.32f, 0.17f, 0.08f);
    specColor = vec3(.5f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    isClicked = false;
    
    //doScale(glm::vec3(8.f));
    doScale(glm::vec3(ROOM_SIZE / 5.f));

    doRotate(glm::vec3(0,1,0), -270);
    //doTranslate(glm::vec3(-15.5f,-8.f,0.f));
    doTranslate(glm::vec3(-ROOM_SIZE + 3.0f, -2.f, 0.0f));
    
    hitTestAABBmin = AABBmin;
    hitTestAABBmax = AABBmax;
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
    return (this->hitTestAABBmin.x <= other->AABBmax.x &&
            //this->AABBmin.y <= other->AABBmax.y &&
            this->hitTestAABBmin.z <= other->AABBmax.z &&
            this->hitTestAABBmax.x >= other->AABBmin.x &&
            //this->AABBmax.y >= other->AABBmin.y &&
            this->hitTestAABBmax.z >= other->AABBmin.z);
}
