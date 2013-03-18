/* 
 * File:   Bookshelf.cpp
 * Author: goofanader
 * 
 * Created on February 14, 2013, 6:06 AM
 */

#include "Bookshelf.h"

Bookshelf::Bookshelf() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/bookshelf/Bookshelf.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(0.75f);
    diffColor = vec3(.32f, 0.17f, 0.08f);
    specColor = vec3(.5f);
    ambAlpha = 1.f;
    diffAlpha = 1.f;
    specAlpha = 1.f;
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    isClicked = false;
    ignore = true;
    
    //doScale(glm::vec3(8.f));
    doScale(glm::vec3(ROOM_SIZE / 5.f));

    doRotate(glm::vec3(0,1,0), -270);
    //doTranslate(glm::vec3(-15.5f,-8.f,0.f));
    doTranslate(glm::vec3(-ROOM_SIZE + 3.0f, getRoomFloorHeight().y - getAABBmin().y, 0.0f));
    
    hitTestAABBmin = getAABBmin();
    hitTestAABBmax = getAABBmax();
    //AABBmin = glm::vec3(-200, -200, -200);
    //AABBmax = glm::vec3(-200, -200, -200);

    glGenTextures(1, &texNum);
    LoadTexture((char *)"objects/meshes/bookshelf/BookshelfUV.bmp", texNum);
    hasTex = true;
    
}

Bookshelf::Bookshelf(const Bookshelf& orig) {
}

Bookshelf::~Bookshelf() {
}

void Bookshelf::drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc) {
    //do nothing, we don't want a highlight for the Bookshelf. It's not selectable
}

void Bookshelf::onEvent(SoundPlayer *soundPlayer) {
    //color = glm::vec3(1.f, 0.f, 0.f);
}

std::string Bookshelf::className() {
    return "Bookshelf";
}
