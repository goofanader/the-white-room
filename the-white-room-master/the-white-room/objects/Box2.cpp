/* 
 * File:   Box2.cpp
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
    cube->ambColor = vec3(1.f, 0.f, 0.f);
    cube->shininess = 5;
    cube->specStrength = 0.f;
    cube->scale = glm::vec3(1.f);
    
    cube->AABBmin = vec3(1.f) / 2.f * -1.f;
    cube->AABBmax = vec3(1.f) / 2.f;
    cube->doTranslate(vec3(-2.f,-.6f,-ROOM_SIZE - cube->getAABBmin().z + 2.f));
    
    AABBmin = cube->getAABBmin();
    AABBmax = cube->getAABBmax();
    //setTrans(vec3(4.f,-1.f,4.f));
    
    this->ambColor = cube->ambColor;
    
    hasTex = false;
    ignore = false;
    
    delete cubeMesh;
}

Box2::Box2(const Box2& orig) {
}

Box2::~Box2() {
    delete cube;
}

void Box2::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc, int shouldDarkenScreen) {
    if (false)
        cube->draw(cameraPos, lookAt, lightPos, lightColor, gc, shouldDarkenScreen);
}

void Box2::update(float dt, GameObject* playerCamera, vec3 camLookAt){
}

bool Box2::doesCollide(GameObject* other) {
    return false;
}

std::string Box2::className() {
    return "Box2";
}

void Box2::onEvent(SoundPlayer* soundPlayer) {
}
