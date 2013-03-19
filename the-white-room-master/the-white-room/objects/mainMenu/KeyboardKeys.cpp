/* 
 * File:   KeyboardKeys.cpp
 * Author: goofanader
 * 
 * Created on March 18, 2013, 2:15 PM
 */

#include "KeyboardKeys.h"

KeyboardKeys::KeyboardKeys() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/mainMenu/meshes/keyboardKeys/KeyboardKeys.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);

    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f, 1.f, 1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    glGenTextures(1, &texNum);
    LoadTexture((char *) "objects/mainMenu/meshes/keyboardKeys/wasd.bmp", texNum);
    //glGenTextures(1, &altTexNum);
    //LoadTexture((char *) "objects/mainMenu/meshes/mouse/mouseUnselected.bmp", altTexNum);
    hasTex = true;
}

KeyboardKeys::KeyboardKeys(const KeyboardKeys& orig) {
}

KeyboardKeys::~KeyboardKeys() {
}

std::string KeyboardKeys::className() {
    return "KeyboardKeys";
}