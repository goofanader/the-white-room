/* 
 * File:   Box1.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 6:34 AM
 */

#include "Box2.h"

Box2::Box2() {
    Mesh *cubeMesh = GeometryCreator::CreateCube(vec3(1.f));

    cube = new GameObject();
    cube->VBO = cubeMesh->PositionHandle;
    cube->IBO = cubeMesh->IndexHandle;
    cube->IBOlen = cubeMesh->IndexBufferLength;
    cube->NBO = cubeMesh->NormalHandle;
    cube->dir = vec3(1.f, 0.f, 0.f);
    cube->speed = 0.f;
    cube->rotSpeed = 0.f;
    cube->rotAxis = vec3(0.f, 1.f, 0.f);
    cube->ambColor = vec3(1.f, 1.f, 1.f);
    cube->shininess = 5;
    cube->specStrength = 0.f;
    cube->scale = glm::vec3(1.f);
        cube->AABBmin = vec3(1.f) / 2.f * -1.f;
    cube->AABBmax = vec3(1.f) / 2.f;
    cube->doTranslate(vec3(4.f,-1.f,-4.f));
    //setTrans(vec3(4.f,-1.f,-4.f));
AABBmin = cube->AABBmin;
    AABBmax = cube->AABBmax;
    
    this->ambColor = cube->ambColor;
}

Box2::Box2(const Box2& orig) {
}

Box2::~Box2() {
}

void Box2::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc) {
    cube->draw(cameraPos, lookAt, lightPos, lightColor, gc);
}

void Box2::update(float dt, GameObject* playerCamera){
    if(this->ambColor != this->cube->ambColor){
        this->cube->ambColor = vec3(0.f, 1.f, 0.f);
        this->ambColor = this->cube->ambColor;
    }
}

bool Box2::doesCollide(GameObject* other) {
    return cube->doesCollide(other);
}

std::string Box2::className() {
    return "Box2";
}

void Box2::onEvent(SoundPlayer* soundPlayer) {
    soundPlayer->playSound("tryRadio");
    this->cube->ambColor = vec3(0.f, 1.f, 0.f);
    this->ambColor = this->cube->ambColor;
}

void Box2::resetEvent(SoundPlayer *soundPlayer) {
    this->cube->ambColor = vec3(1.f);
    this->ambColor = this->cube->ambColor;
}