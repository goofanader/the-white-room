/* 
 * File:   Book1.cpp
 * Author: goofanader
 * 
 * Created on February 14, 2013, 6:32 AM
 */

#include "Book1.h"

Book1::Book1() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/bookshelf/Book1.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    //ambColor = glm::vec3(1.f, 0.f, 0.f);
    ambColor = glm::vec3(0.75f);
    initAmbColor = ambColor;
    diffColor = vec3(0.93f, 0.93f, 0.88f);
    specColor = vec3(.5f);
    
    isClicked = false;
    
    doScale(glm::vec3(1.25f));
    //doScale(glm::vec3(ROOM_SIZE / 5.f));

    doRotate(glm::vec3(0,1,0), 90);

    //doTranslate(glm::vec3(-15.5f,-8.f - 6.f,0.f));
    doTranslate(glm::vec3(-ROOM_SIZE + 3.0f, -2.f, 0.0f));

    texNum = numTextures();
    LoadTexture((char *)"objects/meshes/bookshelf/book1UV.bmp", texNum);
    hasTex = true;
    AABBmin.x -= 1.f;
    AABBmax.x += 1.f;
    AABBmin.z -= 1.f;
    AABBmax.z += 1.f;
}

Book1::Book1(const Book1& orig) {
}

Book1::~Book1() {
}

std::string Book1::className() {
    return "Book1";
}

void Book1::onEvent(SoundPlayer* soundPlayer) {
    soundPlayer->playSound("Bell3");
    if (isClicked) {
        ambColor = glm::vec3(0.f);
    }
}
