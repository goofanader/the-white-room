/* 
 * File:   Safe.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 12:49 AM
 */

#include "Safe.h"
#include "GeometryCreator.h"
#include "MeshLoader.h"
#include <iostream>

Safe::Safe() {
    body = new GameObject();
    door = new GameObject();
    
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/safe/SafeBody.obj",
            body->IBOlen, body->VBO, body->IBO, body->NBO, body->TBO, 
            body->AABBmin, body->AABBmax);
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/safe/SafeDoor.obj",
            door->IBOlen, door->VBO, door->IBO, door->NBO, door->TBO, 
            door->AABBmin, door->AABBmax);
    
    body->dir = vec3(1.f, 0.f, 0.f);
    body->speed = 0.f;
    body->rotSpeed = 0.f;
    body->rotAxis = vec3(0.f, 1.f, 0.f);
    body->shininess = 5;
    body->specStrength = 0.f;
    body->scale = glm::vec3(1.f);
    body->ambColor = glm::vec3(1.f);
    body->diffColor = glm::vec3(0.5f);
    body->specColor = glm::vec3(0.5f);
    body->ambAlpha = 1.0f;
    body->diffAlpha = 1.0f;
    body->specAlpha = 1.0f;
    body->isClicked = false;
    
    door->dir = vec3(1.f, 0.f, 0.f);
    door->speed = 0.f;
    door->rotSpeed = 0.f;
    door->rotAxis = vec3(0.f, 1.f, 0.f);
    door->shininess = 5;
    door->specStrength = 0.f;
    door->scale = glm::vec3(1.f);
    door->ambColor = glm::vec3(1.f);
    door->diffColor = glm::vec3(.5f);
    door->specColor = glm::vec3(.5f);
    door->ambAlpha = 1.0f;
    door->diffAlpha = 1.0f;
    door->specAlpha = 1.0f;
    door->isClicked = false;
    
    body->doScale(glm::vec3(ROOM_SIZE / 10.f));
    door->doScale(1.f * body->scale);
    
    body->doTranslate(glm::vec3(0.f, 
            getRoomFloorHeight().y - body->getAABBmin().y, -ROOM_SIZE - body->getAABBmin().z));
    door->doTranslate(body->trans);
    door->doTranslate(glm::vec3(1.f, -0.1f, 2.f));
    
    AABBmin = body->getAABBmin();
    AABBmax = body->getAABBmax();

    body->texNum = numTextures();
    body->textureEnum = GL_TEXTURE0 + body->texNum;
    LoadTexture((char *)"objects/meshes/safe/SafeBodyUV.bmp", body->texNum);
    body->hasTex = true;

    door->texNum = numTextures();
    door->textureEnum = GL_TEXTURE0 + door->texNum;
    LoadTexture((char *)"objects/meshes/safe/SafeDoor.bmp", door->texNum);
    door->hasTex = true;
}

Safe::Safe(const Safe& orig) {
}

Safe::~Safe() {
}

void Safe::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc) {
    body->draw(cameraPos, lookAt, lightPos, lightColor, gc);
    door->draw(cameraPos, lookAt, lightPos, lightColor, gc);
}

void Safe::update(float dt, GameObject* playerCamera){
    if(this->ambColor != this->body->ambColor){
        this->body->ambColor = this->ambColor;
    }
}

bool Safe::doesCollide(GameObject* other) {
    return body->doesCollide(other);
}

void Safe::onEvent(SoundPlayer *soundPlayer){
    if (IS_SOUND_ON) {
    soundPlayer->playSound("TrySafe");
    }
}

std::string Safe::className() { return "Safe";}
