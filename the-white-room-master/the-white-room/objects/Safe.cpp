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
#if 0
    //cube for the room/floor
    Mesh *cubeMesh = GeometryCreator::CreateCube(vec3(1.f));

    body = new GameObject();
    body->VBO = cubeMesh->PositionHandle;
    body->IBO = cubeMesh->IndexHandle;
    body->IBOlen = cubeMesh->IndexBufferLength;
    body->NBO = cubeMesh->NormalHandle;
    body->dir = vec3(1.f, 0.f, 0.f);
    body->speed = 0.f;
    body->rotSpeed = 0.f;
    body->rotAxis = vec3(0.f, 1.f, 0.f);
    body->color = vec3(1.f, 1.f, 1.f);
    body->shininess = 5;
    body->specStrength = 0.f;
    body->scale = glm::vec3(2.f, 3.f, 2.f);

    for (int i = 0; i < NUM_LEGS; i++) {
        feet[i].VBO = cubeMesh->PositionHandle;
        feet[i].IBO = cubeMesh->IndexHandle;
        feet[i].IBOlen = cubeMesh->IndexBufferLength;
        feet[i].NBO = cubeMesh->NormalHandle;
        feet[i].dir = vec3(1.f, 0.f, 0.f);
        feet[i].speed = 0.f;
        feet[i].rotSpeed = 0.f;
        feet[i].rotAxis = vec3(0.f, 1.f, 0.f);
        feet[i].color = vec3(1.f, 1.f, 1.f);
        feet[i].shininess = 5;
        feet[i].specStrength = 0.f;
        feet[i].scale = glm::vec3(.5f);
    }
    
    body->AABBmin = glm::vec3(-1.5f, -2.f, -1.5f);
    body->AABBmax = glm::vec3(1.f, 1.5f, 1.f);

    body->doTranslate(vec3(-8.5f, -.5f - 2.5f, 0.f));
    feet[0].doTranslate(vec3(.75f, -1.75f, .75f) + body->trans);
    feet[1].doTranslate(vec3(-.75f, -1.75f, -.75f) + body->trans);
    feet[2].doTranslate(vec3(-.75f, -1.75f, .75f) + body->trans);
    feet[3].doTranslate(vec3(.75f, -1.75f, -.75f) + body->trans);

    this->AABBmin = body->AABBmin;
    this->AABBmax = body->AABBmax;

    //setTrans(vec3(-8.5f, -.5f - 2.5f, 0.f));
#endif
    body = new GameObject();
    door = new GameObject();
    
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/safe/SafeBody.obj",
            body->IBOlen, body->VBO, body->IBO, body->NBO, faceNBO, 
            body->AABBmin, body->AABBmax);
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/safe/SafeDoor.obj",
            door->IBOlen, door->VBO, door->IBO, door->NBO, faceNBO, 
            door->AABBmin, door->AABBmax);
    
    body->dir = vec3(1.f, 0.f, 0.f);
    body->speed = 0.f;
    body->rotSpeed = 0.f;
    body->rotAxis = vec3(0.f, 1.f, 0.f);
    body->shininess = 5;
    body->specStrength = 0.f;
    body->scale = glm::vec3(1.f);
    body->ambColor = glm::vec3(1.f);
    body->isClicked = false;
    
    door->dir = vec3(1.f, 0.f, 0.f);
    door->speed = 0.f;
    door->rotSpeed = 0.f;
    door->rotAxis = vec3(0.f, 1.f, 0.f);
    door->shininess = 5;
    door->specStrength = 0.f;
    door->scale = glm::vec3(1.f);
    door->ambColor = glm::vec3(1.f);
    door->isClicked = false;
    
    AABBmin = body->AABBmin;
    AABBmax = body->AABBmax;
    
    std::cout << "body: min=(" << AABBmin.x << ", " << AABBmin.y << ", ";
    std::cout << AABBmin.z << "). max=(" << AABBmax.x << ", " << AABBmax.y;
    std::cout << ", " << AABBmax.z << ")" << std::endl;
    
    //body->doScale(glm::vec3(ROOM_SIZE / 2.f));
    body->doScale(glm::vec3(ROOM_SIZE / 10.f));
    door->doScale(1.f * body->scale);
    
    //doRotate(glm::vec3(0, 1, 0), 180);
    //body->doTranslate(glm::vec3(0.f, -ROOM_SIZE / 2.f + 3, -ROOM_SIZE));
    body->doTranslate(glm::vec3(0.f, -5.f, -ROOM_SIZE + 3.f));
    //door->doTranslate(glm::vec3(3.5f,0.f,7.f) + body->trans);
    door->doTranslate(body->trans);
    door->doTranslate(glm::vec3(1.f, -0.1f, 2.f));
    
    AABBmin = body->AABBmin;
    AABBmax = body->AABBmax;
    
    std::cout << "body: min=(" << AABBmin.x << ", " << AABBmin.y << ", ";
    std::cout << AABBmin.z << "). max=(" << AABBmax.x << ", " << AABBmax.y;
    std::cout << ", " << AABBmax.z << ")" << std::endl;
}

Safe::Safe(const Safe& orig) {
}

Safe::~Safe() {
}
#if 1
void Safe::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc) {
    body->draw(cameraPos, lookAt, lightPos, lightColor, gc);
    door->draw(cameraPos, lookAt, lightPos, lightColor, gc);
}

void Safe::update(float dt){
    if(this->ambColor != this->body->ambColor){
        this->body->ambColor = this->ambColor;
    }
}

bool Safe::doesCollide(GameObject* other) {
    return body->doesCollide(other);
}
#endif
void Safe::onEvent(SoundPlayer *soundPlayer){
    soundPlayer->playSound("TrySafe");
   // soundPlayer->playContinuous("Tick");
    
    body->ambColor = glm::vec3(1.f, 0.f, 0.f);
    door->ambColor = body->ambColor;
    ambColor = glm::vec3(1.f, 0.f, 0.f);
}

std::string Safe::className() { return "Safe";}
