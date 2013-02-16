/* 
 * File:   Radio.cpp
 * Author: goofanader
 * 
 * Created on February 12, 2013, 7:05 PM
 */

#include "Radio.h"

Radio::Radio() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/radio/Radio.obj",
            IBOlen, VBO, IBO, NBO, faceNBO, AABBmin, AABBmax);

    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    color = vec3(1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    color = glm::vec3(1.f);
    
    doScale(glm::vec3(3.f));
    doTranslate(glm::vec3(0.f,-3.f,7.f));
}

Radio::Radio(const Radio& orig) {
}

Radio::~Radio() {
}

void Radio::onEvent(SoundPlayer *soundPlayer){
    soundPlayer->playSound("radioAppear");
}

std::string Radio::className() {
    return "Radio";
}
