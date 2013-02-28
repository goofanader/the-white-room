/* 
 * File:   Plant6.cpp
 * Author: goofanader
 * 
 * Created on February 13, 2013, 12:36 PM
 */

#include "Plant6.h"

Plant6::Plant6() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/plants/Plant6New.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(.75f);
    specColor = vec3(.5f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/plants/Plant6UV.bmp", texNum);
    printOpenGLError();
    hasTex = true;
    
    rotating = 90.f;
    
    doScale(glm::vec3(3.f));
    doRotate(glm::vec3(0,1,0), 180);
    doTranslate(glm::vec3(-ROOM_SIZE - getAABBmin().x + 6.f,-3.1158f - getAABBmin().y,
            ROOM_SIZE - getAABBmax().z - 8.f));
}

Plant6::Plant6(const Plant6& orig) {
}

Plant6::~Plant6() {
}

void Plant6::update(float dt, GameObject* playerCamera) {
    if (rotating < 90.f) {
        rotating++;
        doRotate(vec3(0,1,0), 1.f);
    }
    
    if (isHighlighted) {
        highlightColor = highlightColor + vec3(HIGHLIGHT_SPEED);

        if (highlightColor.x > 1.f) {
            highlightColor = vec3(1.f);
        }
        
        highlightAlpha += HIGHLIGHT_SPEED;
        if (highlightAlpha > 1.f) {
            highlightAlpha = 1.f;
        }
    } else {
        isHighlightDisappearing = true;
        highlightColor = highlightColor - vec3(HIGHLIGHT_SPEED);
        
        if (highlightColor.x < 0.f) {
            highlightColor = vec3(0.f);
        }
        
        highlightAlpha -= HIGHLIGHT_SPEED;
        if (highlightAlpha < 0.f) {
            isHighlightDisappearing = false;
            highlightAlpha = 0.f;
        }
    }
}

std::string Plant6::className() {
    return "Plant6";
}

void Plant6::onEvent(SoundPlayer *soundPlayer) {
    if (rotating >= 90.f) {
        rotating = 0.f;
    } else {
    }
}
