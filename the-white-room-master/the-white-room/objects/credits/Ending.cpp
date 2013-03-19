/* 
 * File:   Ending.cpp
 * Author: goofanader
 * 
 * Created on March 18, 2013, 2:15 PM
 */

#include "Ending.h"

Ending::Ending() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/mainMenu/meshes/FrameBuffer.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);

    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f, 1.f, 1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);//glm::vec3(getWindowWidth() / 2.f, getWindowHeight() / 2.f, 1.f);
    //doTranslate(vec3(1.f));
    
    doScale(glm::vec3(6.3f, 5.f, 5.f));
    doRotate(glm::vec3(0,0,1), 180);
    doRotate(glm::vec3(1,0,0), 17);
    //doRotate(glm::vec3(0,1,0), -1);
    doTranslate(glm::vec3(0,3.5f,10.f));

    glGenTextures(1, &texNum);
    LoadTexture((char *) "objects/credits/credits.bmp", texNum);
    //glGenTextures(1, &altTexNum);
    //LoadTexture((char *) "objects/mainMenu/meshes/FakeLoadingUV.bmp", altTexNum);
    //hasTex = true;
    hasTex = true;
    
    isLoading = false;
    
    ambAlpha = 0.f;
}

Ending::Ending(const Ending& orig) {
}

Ending::~Ending() {
}

std::string Ending::className() {
    return "Ending";
}

bool Ending::isItLoading() {
    return isLoading;
}

void Ending::setIsLoading(bool loading) {
    isLoading = loading;
    
    if (isLoading) {
        //texNum = altTexNum;
    }
}

void Ending::update(float dt, GameObject* playerCamera, vec3 camLookAt) {
    float ambAlphaChange = .05f;
    if (!isLoading) {
    if (ambAlpha < 1.0f) {
    this->ambAlpha += ambAlphaChange;
    }
    
    if (ambAlpha > 1.0f) {
        ambAlpha = 1.0f;
    }
    } else {
        if (ambAlpha > 0.f) {
            ambAlpha -= ambAlphaChange;
            
            if (ambAlpha < 0.f) {
                ambAlpha = 0.f;
                isLoading = false;
            }
        }
    }
}