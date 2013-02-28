/* 
 * File:   Radio.cpp
 * Author: goofanader
 * 
 * Created on February 12, 2013, 7:05 PM
 */

#include "Radio.h"

Radio::Radio() {
    GLuint faceNBO;
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/radio/Radio3.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);

    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f);
    specColor = vec3(.5f);
    diffColor = vec3(.5f);
    ambAlpha = specAlpha = diffAlpha = 1.f;
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    doScale(glm::vec3(2.f));
    doTranslate(glm::vec3(0.f,-3.85f - getAABBmin().y,0.f));

    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    printOpenGLError();
    LoadTexture((char *)"objects/meshes/radio/RadioUVSmall.bmp", texNum);
    printOpenGLError();
    hasTex = true;

}

Radio::Radio(const Radio& orig) {
}

Radio::~Radio() {
}

void Radio::onEvent(SoundPlayer *soundPlayer){
    soundPlayer->playSound("RadioStatic");
}

std::string Radio::className() {
    return "Radio";
}
