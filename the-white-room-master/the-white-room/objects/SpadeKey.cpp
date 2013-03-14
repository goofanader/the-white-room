/* 
 * File:   SpadeKey.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 6:34 AM
 */

#include "SpadeKey.h"

SpadeKey::SpadeKey() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/keys/Key_Spade.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f, 1.f, 1.f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    //Translate to be on top of armchair
    doTranslate(glm::vec3(15.f,getRoomFloorHeight().y - getAABBmin().y + 10, -ROOM_SIZE + 10.f));
    isVisible = false;
    
    doRotate(vec3(0,0,1), 90);
}

SpadeKey::SpadeKey(const SpadeKey& orig) {
}

SpadeKey::~SpadeKey() {
}

bool SpadeKey::doesCollide(GameObject* other) {
    return false;
}

std::string SpadeKey::className() {
    return "SpadeKey";
}

void SpadeKey::onEvent(SoundPlayer* soundPlayer) {
}