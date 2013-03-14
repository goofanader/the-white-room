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
    isOpen = false;
    timeSpent = 0.f;
    
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

    body->depthMin = 0;
    body->depthMax = 1;

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

    body->doRotate(glm::vec3(0.f, 1.f, 0.f), -90.f);
    door->doRotate(glm::vec3(0.f, 1.f, 0.f), -90.f);

    body->doTranslate(glm::vec3(ROOM_SIZE + body->getAABBmin().x,
            getRoomFloorHeight().y - body->getAABBmin().y, 20.f));
    door->doTranslate(body->trans);
    door->doTranslate(glm::vec3(-2.f, -0.1f, 1.f));

    AABBmin = body->getAABBmin();
    AABBmax = body->getAABBmax();

    body->texNum = numTextures();
    body->textureEnum = GL_TEXTURE0 + body->texNum;
    LoadTexture((char *) "objects/meshes/safe/SafeBodyUV.bmp", body->texNum);
    body->hasTex = true;

    door->texNum = numTextures();
    door->textureEnum = GL_TEXTURE0 + door->texNum;
    LoadTexture((char *) "objects/meshes/safe/SafeDoor.bmp", door->texNum);
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

void Safe::drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc) {
    body->drawHighlight(cameraPos, lookAt, lightPos, lightColor, gc);
    if (isOpen)
        door->drawHighlight(cameraPos, lookAt, lightPos, lightColor, gc);
}

void Safe::update(float dt, GameObject* playerCamera) {
    if (isOpen && timeSpent < 90.f) {
        door->doRotate(glm::vec3(0, 1, 0), 1.f);
        float xMove = -.009f;
        float zMove = .01f; //-.3f;
        door->doTranslate(glm::vec3(xMove, 0.f, zMove));
        timeSpent++;
    }

    if (isHighlighted) {
        body->highlightColor = body->highlightColor + vec3(HIGHLIGHT_SPEED);
        if (isOpen)
            door->highlightColor = body->highlightColor + vec3(HIGHLIGHT_SPEED);

        if (body->highlightColor.x > 1.f) {
            body->highlightColor = vec3(1.f);
            if (isOpen)
                door->highlightColor = vec3(1.f);
        }

        body->highlightAlpha += HIGHLIGHT_SPEED;
        if (isOpen)
            door->highlightAlpha += HIGHLIGHT_SPEED;
        
        if (body->highlightAlpha > 1.f) {
            body->highlightAlpha = 1.f;
            
            if (isOpen)
                door->highlightAlpha = 1.f;
        }
    } else {
        isHighlightDisappearing = true;
        body->highlightColor = body->highlightColor - vec3(HIGHLIGHT_SPEED);
        if (isOpen)
            door->highlightColor = body->highlightColor - vec3(HIGHLIGHT_SPEED);

        if (body->highlightColor.x < 0.f) {
            body->highlightColor = vec3(0.f);
            if (isOpen)
                door->highlightColor = vec3(0.f);
        }

        body->highlightAlpha -= HIGHLIGHT_SPEED;
        if (isOpen)
            door->highlightAlpha -= HIGHLIGHT_SPEED;
        
        if (body->highlightAlpha < 0.f) {
            isHighlightDisappearing = false;
            body->highlightAlpha = 0.f;
            if (isOpen)
                door->highlightAlpha = 0.f;
        }
    }
}

bool Safe::doesCollide(GameObject* other) {
    if (!isOpen)
        return body->doesCollide(other);
    
    if (body->doesCollide(other)) return true;
    if (door->doesCollide(other)) return true;
    return false;
}

void Safe::onEvent(SoundPlayer *soundPlayer) {
    if (IS_SOUND_ON) {
        soundPlayer->playSound("TrySafe");
    }
}

std::string Safe::className() {
    return "Safe";
}
