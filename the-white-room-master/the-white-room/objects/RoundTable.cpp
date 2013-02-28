/* 
 * File:   RoundTable.cpp
 * Author: goofanader
 * 
 * Created on February 21, 2013, 12:15 PM
 */

#include "RoundTable.h"

RoundTable::RoundTable() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/table/RoundTable.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f);
    diffColor = vec3(.5f);
    specColor = vec3(.5f);
    ambAlpha = 1.0f;
    diffAlpha = 1.0f;
    specAlpha = 1.0f;
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    rotate = glm::mat4(1.f);
    
    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    LoadTexture((char *)"objects/meshes/table/tableUV.bmp", texNum);
    hasTex = true;

    isClicked = false;
    doRotate(glm::vec3(0,1,0), 90);
    doScale(glm::vec3(ROOM_SIZE / 5.f, ROOM_SIZE / 5.f, ROOM_SIZE / 5.f));
    doTranslate(glm::vec3(-ROOM_SIZE - getAABBmin().x, 
            getRoomFloorHeight().y - getAABBmin().y, ROOM_SIZE - getAABBmax().z - 5.f));
    //doTranslate(glm::vec3(27.f, 0.f, 0.f));
}

RoundTable::RoundTable(const RoundTable& orig) {
}

RoundTable::~RoundTable() {
}

void RoundTable::drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc) {
    //do nothing, we don't want a highlight for the table. It's not selectable
}

std::string RoundTable::className() {
    return "RoundTable";
}
