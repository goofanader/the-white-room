/* 
 * File:   Clock.cpp
 * Author: goofanader
 * 
 * Created on February 14, 2013, 5:27 AM
 */

#include "Clock.h"

Clock::Clock() {
    GLuint faceNBO;
    body = new GameObject();
    weight1 = new GameObject();
    weight2 = new GameObject();
    weight3 = new GameObject();

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/clock/ClockBody.obj",
            body->IBOlen, body->VBO, body->IBO, body->NBO, faceNBO,
            body->AABBmin, body->AABBmax);
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/clock/ClockWeight1.obj",
            weight1->IBOlen, weight1->VBO, weight1->IBO, weight1->NBO, faceNBO,
            weight1->AABBmin, weight1->AABBmax);
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/clock/ClockWeight2.obj",
            weight2->IBOlen, weight2->VBO, weight2->IBO, weight2->NBO, faceNBO,
            weight2->AABBmin, weight2->AABBmax);
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/clock/ClockWeight3.obj",
            weight3->IBOlen, weight3->VBO, weight3->IBO, weight3->NBO, faceNBO,
            weight3->AABBmin, weight3->AABBmax);

    body->dir = vec3(1.f, 0.f, 0.f);
    body->speed = 0.f;
    body->rotSpeed = 0.f;
    body->rotAxis = vec3(0.f, 1.f, 0.f);
    body->shininess = 5;
    body->specStrength = 0.f;
    body->scale = glm::vec3(1.f);
    body->ambColor = glm::vec3(1.f);
    body->specColor = glm::vec3(.5f);
    body->diffColor = glm::vec3(.5f);
    body->isClicked = false;

    weight1->dir = vec3(1.f, 0.f, 0.f);
    weight1->speed = 0.f;
    weight1->rotSpeed = 0.f;
    weight1->rotAxis = vec3(0.f, 1.f, 0.f);
    weight1->shininess = 5;
    weight1->specStrength = 0.f;
    weight1->scale = glm::vec3(1.f);
    weight1->ambColor = glm::vec3(1.f, 0.f, 0.f);
    weight1->specColor = glm::vec3(.5f);
    weight1->diffColor = glm::vec3(.5f);
    weight1->isClicked = false;

    weight2->dir = vec3(1.f, 0.f, 0.f);
    weight2->speed = 0.f;
    weight2->rotSpeed = 0.f;
    weight2->rotAxis = vec3(0.f, 1.f, 0.f);
    weight2->shininess = 5;
    weight2->specStrength = 0.f;
    weight2->scale = glm::vec3(1.f);
    weight2->ambColor = glm::vec3(0.f, 1.f, 0.f);
    weight2->specColor = glm::vec3(.5f);
    weight2->diffColor = glm::vec3(.5f);
    weight2->isClicked = false;

    weight3->dir = vec3(1.f, 0.f, 0.f);
    weight3->speed = 0.f;
    weight3->rotSpeed = 0.f;
    weight3->rotAxis = vec3(0.f, 1.f, 0.f);
    weight3->shininess = 5;
    weight3->specStrength = 0.f;
    weight3->scale = glm::vec3(1.f);
    weight3->ambColor = glm::vec3(0.f, 0.f, 1.f);
    weight3->specColor = glm::vec3(.5f);
    weight3->diffColor = glm::vec3(.5f);
    weight3->isClicked = false;
    
    //body->doScale(glm::vec3(10.f));
    body->doScale(glm::vec3(ROOM_SIZE/5.f));
    weight1->scale = weight2->scale = weight3->scale = body->scale / 3.f;
    //body->doTranslate(glm::vec3(ROOM_SIZE - 5.f, -ROOM_SIZE + 14.5f,
            //ROOM_SIZE - AABBmax.z - 5));
    //body->doRotate(glm::vec3(0,1,0), 225);
    body->doRotate(glm::vec3(0,1,0), 180);
    body->doTranslate(glm::vec3(-3.25f - 8.f, -2.f, ROOM_SIZE - 2.f));
    
    weight1->doTranslate(body->trans);
    weight2->doTranslate(body->trans);
    weight2->doTranslate(glm::vec3(-1.f, 0.f, -0.5f));
    weight3->doTranslate(body->trans);
    weight3->doTranslate(glm::vec3(1.f, 0.f, 0.5f));
    //weight1->doTranslate(glm::vec3(-2,0,0) + body->trans);
    //weight2->trans += body->trans;
    //weight3->doTranslate(glm::vec3(2,0,0) + body->trans);
}

Clock::Clock(const Clock& orig) {
}

Clock::~Clock() {
}

void Clock::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc) {
    body->draw(cameraPos, lookAt, lightPos, lightColor, gc);
    weight1->draw(cameraPos, lookAt, lightPos, lightColor, gc);
    weight2->draw(cameraPos, lookAt, lightPos, lightColor, gc);
    weight3->draw(cameraPos, lookAt, lightPos, lightColor, gc);
}
void Clock::update(float dt) {
    
}
bool Clock::doesCollide(GameObject* other) {
    return body->doesCollide(other);
}

std::string Clock::className() {
    return "Clock";
}

void Clock::onEvent(SoundPlayer *soundPlayer) {
    body->ambColor = glm::vec3(1.f, 0.f, 0.f);
}
