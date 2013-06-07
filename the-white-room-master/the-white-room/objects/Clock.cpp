/* 
 * File:   Clock.cpp
 * Author: goofanader
 * 
 * Created on February 14, 2013, 5:27 AM
 */

#include "Clock.h"

Clock::Clock() {
    ignore = false;

    body = new GameObject();
    weight1 = new GameObject();
    weight2 = new GameObject();
    weight3 = new GameObject();

    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/clock/ClockBody.obj",
            body->IBOlen, body->VBO, body->IBO, body->NBO, body->TBO,
            body->AABBmin, body->AABBmax);
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/clock/ClockWeight1.obj",
            weight1->IBOlen, weight1->VBO, weight1->IBO, weight1->NBO, 
            weight1->TBO, weight1->AABBmin, weight1->AABBmax);
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/clock/ClockWeight2.obj",
            weight2->IBOlen, weight2->VBO, weight2->IBO, weight2->NBO, 
            weight2->TBO, weight2->AABBmin, weight2->AABBmax);
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/clock/ClockWeight3.obj",
            weight3->IBOlen, weight3->VBO, weight3->IBO, weight3->NBO, 
            weight3->TBO, weight3->AABBmin, weight3->AABBmax);

    body->dir = vec3(1.f, 0.f, 0.f);
    body->speed = 0.f;
    body->rotSpeed = 0.f;
    body->rotAxis = vec3(0.f, 1.f, 0.f);
    body->shininess = 5;
    body->specStrength = 0.f;
    body->scale = glm::vec3(1.f);
    body->ambColor = glm::vec3(.25f);
    body->specColor = glm::vec3(.42f, .22f, .08f);
    //body->diffColor = glm::vec3(.5f);
    body->diffColor = glm::vec3(.42f, .22f, .08f);
    body->ambAlpha = 1.f;
    body->diffAlpha = 1.f;
    body->specAlpha = 1.f;
    body->isClicked = false;
    
    body->depthMin = 0;
    body->depthMax = 1;

    glGenTextures(1, &(body->texNum));
    LoadTexture((char *)"objects/meshes/clock/ClockUV.bmp", body->texNum);
    body->hasTex = true;

    weight1->dir = vec3(1.f, 0.f, 0.f);
    weight1->speed = 0.f;
    weight1->rotSpeed = 0.f;
    weight1->rotAxis = vec3(0.f, 1.f, 0.f);
    weight1->shininess = 5;
    weight1->specStrength = 0.f;
    weight1->scale = glm::vec3(1.f);
    weight1->ambColor = glm::vec3(0.94f, .90f, .55f)/ 5.f;
    weight1->specColor = glm::vec3(.94f, 0.90f, 0.55f);
    weight1->diffColor = glm::vec3(0.32f, 0.16f, 0.00f);
    weight1->ambAlpha = 1.f;
    weight1->diffAlpha = 1.f;
    weight1->specAlpha = 1.f;

    weight1->isClicked = false;

    weight2->dir = vec3(1.f, 0.f, 0.f);
    weight2->speed = 0.f;
    weight2->rotSpeed = 0.f;
    weight2->rotAxis = vec3(0.f, 1.f, 0.f);
    weight2->shininess = 5;
    weight2->specStrength = 0.f;
    weight2->scale = glm::vec3(1.f);
    weight2->ambColor = glm::vec3(1.0f, 0.85, 0.0f)/5.f;
    weight2->specColor = glm::vec3(1.0f, 0.85, 0.0f);
        weight2->isClicked = false;
    weight2->diffColor = glm::vec3(1.0f, 0.85f, 0.0f);
    weight2->ambAlpha = 1.f;
    weight2->diffAlpha = 1.f;
    weight2->specAlpha = 1.f;


    weight3->dir = vec3(1.f, 0.f, 0.f);
    weight3->speed = 0.f;
    weight3->rotSpeed = 0.f;
    weight3->rotAxis = vec3(0.f, 1.f, 0.f);
    weight3->shininess = 5;
    weight3->specStrength = 0.f;
    weight3->scale = glm::vec3(1.f);
    weight3->ambColor = glm::vec3(.93f, .93f, .88f)/5.f;
    weight3->specColor = glm::vec3(.93f, .93f, .88f);
    weight3->diffColor = glm::vec3(0.93f, 0.93f, 0.88f);
    weight3->ambAlpha = 1.f;
    weight3->diffAlpha = 1.f;
    weight3->specAlpha = 1.f;

    weight3->isClicked = false;
    
    body->doScale(glm::vec3(ROOM_SIZE/5.f));
    weight1->scale = weight2->scale = weight3->scale = body->scale / 3.f;
    body->doRotate(glm::vec3(0,1,0), 180);
    body->doTranslate(glm::vec3(-3.25f - 8.f, 
            getRoomFloorHeight().y - body->getAABBmin().y, ROOM_SIZE - 2.f));
    
    weight1->doTranslate(body->trans);
    weight2->doTranslate(body->trans);
    weight2->doTranslate(glm::vec3(1.f, 0.f, 0.5f));
    weight3->doTranslate(body->trans);
    weight3->doTranslate(glm::vec3(-1.f, 0.f, -0.5f));
    
    AABBmin = body->getAABBmin();
    AABBmax = body->getAABBmax();
    haveLoadedPlayer = false;
    
    timePassed = 5.f;
}

Clock::Clock(const Clock& orig) {
}

Clock::~Clock() {
    delete body;
    delete weight1;
    delete weight2;
    delete weight3;
}

void Clock::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc, int shouldDarkenScreen) {
    body->draw(cameraPos, lookAt, lightPos, lightColor, gc, shouldDarkenScreen);
    weight1->draw(cameraPos, lookAt, lightPos, lightColor, gc, shouldDarkenScreen);
    weight2->draw(cameraPos, lookAt, lightPos, lightColor, gc, shouldDarkenScreen);
    weight3->draw(cameraPos, lookAt, lightPos, lightColor, gc, shouldDarkenScreen);
}
void Clock::drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc) {
    body->drawHighlight(cameraPos, lookAt, lightPos, lightColor, gc);
}
void Clock::update(float dt, GameObject* playerCamera, vec3 camLookAt) {
    timePassed += dt;
    if (isHighlighted) {
        body->highlightColor = body->highlightColor + vec3(HIGHLIGHT_SPEED);

        if (highlightColor.x > 1.f) {
            body->highlightColor = vec3(1.f);
        }
        
        body->highlightAlpha += HIGHLIGHT_SPEED;
        if (body->highlightAlpha > 1.f) {
            body->highlightAlpha = 1.f;
        }
    } else {
        isHighlightDisappearing = true;
        body->highlightColor = body->highlightColor - vec3(HIGHLIGHT_SPEED);
        
        if (body->highlightColor.x < 0.f) {
            body->highlightColor = vec3(0.f);
        }
        
        body->highlightAlpha -= HIGHLIGHT_SPEED;
        if (body->highlightAlpha < 0.f) {
            isHighlightDisappearing = false;
            body->highlightAlpha = 0.f;
        }
    }
}
bool Clock::doesCollide(GameObject* other) {
    return body->doesCollide(other);
}

std::string Clock::className() {
    return "Clock";
}

void Clock::onEvent(SoundPlayer *soundPlayer) {
    if (IS_SOUND_ON) {
        if (timePassed >= 5) {
                soundPlayer->playSound("BellTones");
                timePassed = 0.f;
        }
    }
    if (!haveLoadedPlayer) {
        if (IS_SOUND_ON) {
        printf("putting a sound player into clock\n");
        clockSoundPlayer = soundPlayer;
        clockSoundPlayer->playContinuous("TickTock");
        }
        haveLoadedPlayer = true;
    }
}
