/* 
 * File:   Book3.cpp
 * Author: goofanader
 * 
 * Created on February 14, 2013, 6:32 AM
 */

#include "Book3.h"

Book3::Book3() {
    
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/bookshelf/Book3.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    //ambColor = glm::vec3(0.f, 0.f, 1.f);
    ambColor = glm::vec3(0.75f);
    initAmbColor = ambColor;
    diffColor = vec3(1.0f, 0.85f, 0.0f);
    specColor = vec3(.5f);
    ambAlpha = 1.f;
    diffAlpha = 1.f;
    specAlpha = 1.f;
    isClicked = false;
    
    doScale(glm::vec3(1.25f));

    doRotate(glm::vec3(0,1,0), 90);

    //doTranslate(glm::vec3(-15.5f,-8.f + 4.5f,-1.f));
    //translate to Book1's pos
    doTranslate(glm::vec3(-ROOM_SIZE + 3.0f, -2.5f, 0.0f));
    //translate to its own pos
    doTranslate(glm::vec3(0.f, 3.f, -1.f));

    texNum = numTextures();
    LoadTexture((char *) "objects/meshes/bookshelf/book3UV.bmp", texNum);
    hasTex = true;
    
    std::cout << "Book3: AABBmin=" << printVec3(getAABBmin());
    std::cout <<"; AABBmax=" << printVec3(getAABBmax()) << std::endl;
    /*AABBmin.x -= 1.f;
    AABBmax.x += 1.f;
    AABBmin.z -= 1.f;
    AABBmax.z += 1.f;*/
}

Book3::Book3(const Book3& orig) {
}

Book3::~Book3() {
}

std::string Book3::className() {
    return "Book3";
}

void Book3::onEvent(SoundPlayer* soundPlayer) {
    if (IS_SOUND_ON) {
    soundPlayer->playSound("Bell1");
    }
    if (isClicked) {
        ambColor = glm::vec3(0.f);
    }
}
