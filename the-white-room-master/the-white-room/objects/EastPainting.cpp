/* 
 * File:   EastPainting.cpp
 * Author: goofanader
 * 
 * Created on March 13, 2013, 9:12 PM
 */

#include "EastPainting.h"

EastPainting::EastPainting() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/paintings/TallPainting.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.f);
    diffColor = vec3(.5f);
    specColor = vec3(.5f);
    ambAlpha = 1.f;
    diffAlpha = 1.f;
    specAlpha = 1.f;
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    isClicked = false;
    isVisible = true;
    
    doScale(vec3(3.5f));
    doRotate(vec3(0,1,0), 90);
    doTranslate(vec3(-ROOM_SIZE - getAABBmin().x, 
            getRoomCeilHeight() - getAABBmax().y - 2.f, -17.f));

    glGenTextures(1, &texNum);
    LoadTexture((char *)"objects/meshes/paintings/TallPaintingUV.bmp", texNum);
    hasTex = true;
    ignore = true;
    //printf("%d\n", texNum);
}

EastPainting::EastPainting(const EastPainting& orig) {
}

EastPainting::~EastPainting() {
}

std::string EastPainting::className() {
    return "EastPainting";
}

void EastPainting::drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc) {
    //do nothing, we don't want a highlight for the armchair. It's not selectable
}
