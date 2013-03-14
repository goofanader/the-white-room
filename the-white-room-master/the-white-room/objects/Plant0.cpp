/* 
 * File:   Plant0.cpp
 * Author: goofanader
 * 
 * Created on February 13, 2013, 12:36 PM
 */

#include "Plant0.h"

Plant0::Plant0() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/plants/Plant0.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    glGenTextures(1, &texNum);
    printOpenGLError();
    //Plant0 is able to use Plant1 or Plant6's UV
    LoadTexture((char *)"objects/meshes/plants/Plant1UV.bmp", texNum);
    printOpenGLError();
    hasTex = true;
    
    rotating = 90.f;
    
    doScale(glm::vec3(3.f));
    doTranslate(glm::vec3(-ROOM_SIZE - getAABBmin().x + 1.f,-3.4745f - getAABBmin().y,
            ROOM_SIZE - getAABBmax().z - 14.f));
    //this->doScale(glm::vec3(3.f));
}

Plant0::Plant0(const Plant0& orig) {
}

Plant0::~Plant0() {
}

void Plant0::update(float dt, GameObject* playerCamera, vec3 camLookAt) {
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

std::string Plant0::className() {
    return "Plant0";
}

void Plant0::onEvent(SoundPlayer *soundPlayer) {
    if (rotating >= 90.f) {
        rotating = 0.f;
    } else {
    }

     soundPlayer->playSound("RotatePlant");

}
