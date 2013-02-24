#include <GL/gl.h>
#include <stdio.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GameObject.h"
#include <math.h>

#define HARDCODE_WALLS 0

GameObject::GameObject(GLuint VBO, GLuint IBO, int IBOlen) {
    this->IBO = IBO;
    this->IBOlen = IBOlen;
    this->VBO = VBO;
}

GameObject::GameObject() {
    this->IBO = -1; //NULL;
    dir = glm::vec3(0.f);
    speed = 0.f;
    rotAxis = glm::vec3(0.f, 1.f, 0.f);
    rotSpeed = 0.f;
    AABBmin = glm::vec3(-1.f);
    AABBmax = glm::vec3(1.f);
    IBO = -1;
    IBOlen = -1;
    VBO = -1;
    NBO = -1;
    TBO = -1;
    scale = glm::vec3(1.f);
    rotate = glm::mat4(1.f);
    this->doRotate(vec3(0, 1, 0), 0);
    trans = glm::vec3(0.f);
    tag = 0;
    isClicked = false;

    texNum = -1;
    hasTex = false;

    ambColor = glm::vec3(.75f);
    ambAlpha = 1.f;
    specColor = glm::vec3(.1f);
    specAlpha = 1.f;
    diffColor = glm::vec3(.1f);
    diffAlpha = 1.f;

    for (int i = 0; i < MAX_TEXTURES; i++) {
        textureMaps[i] = GL_TEXTURE0 + i;
    }
}

GameObject::~GameObject() {
}

void GameObject::draw(glm::vec3 cameraPos, glm::vec3 lookAt,
        glm::vec3 lightPos, glm::vec3 lightColor, GameConstants *gc) {
    if (VBO == -1 || IBO == -1 || IBOlen <= 0 || NBO == -1) {
        return;
    }
    
    printOpenGLError();
    glUseProgram(gc->shader);
    printOpenGLError();
    //TODO Set matrix stuff
    glm::mat4 projection = glm::perspective(80.0f, gc->aspectRatio, 0.1f, 100.f);
    safe_glUniformMatrix4fv(gc->h_uProjMatrix, glm::value_ptr(projection));

    glm::mat4 view = glm::lookAt(cameraPos, lookAt, glm::vec3(0.f, 1.f, 0.f));
    safe_glUniformMatrix4fv(gc->h_uViewMatrix, glm::value_ptr(view));

    glm::mat4 transMat = glm::translate(glm::mat4(), trans);
    glm::mat4 scaleMat = glm::scale(glm::mat4(), scale);

    glm::mat4 model = transMat * rotate * scaleMat;
    safe_glUniformMatrix4fv(gc->h_uModelMatrix, glm::value_ptr(model));
    safe_glUniformMatrix4fv(gc->h_uNormalMatrix,
            glm::value_ptr(glm::transpose(glm::inverse(model))));

    //Do transformations
    safe_glEnableVertexAttribArray(gc->h_aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    safe_glVertexAttribPointer(gc->h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    safe_glEnableVertexAttribArray(gc->h_aNormal);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    safe_glVertexAttribPointer(gc->h_aNormal, 3, GL_FLOAT, GL_TRUE, 0, 0);

    if (hasTex) {
        printOpenGLError();
        glEnable(GL_TEXTURE_2D);
        printOpenGLError();
        safe_glUniform1i(gc->h_uTexUnit, texNum);
        printOpenGLError();
        safe_glEnableVertexAttribArray(gc->h_aTexCoord);
        printOpenGLError();
        glBindBuffer(GL_ARRAY_BUFFER, TBO);
        printOpenGLError();
        safe_glVertexAttribPointer(
                gc->h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
        printOpenGLError();
        glActiveTexture(textureMaps[texNum]);
        printOpenGLError();
        glBindTexture(GL_TEXTURE_2D, texNum);
        printOpenGLError();
        glDisable(GL_TEXTURE_2D);
    }
    printOpenGLError();
    safe_glUniform1i(gc->h_uUseTex, hasTex ? 1 : 0);
    printOpenGLError();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    printOpenGLError();
    //pass colors, camera position, and light info to GPU
    glUniform4f(gc->h_uAmbColor, ambColor.x, ambColor.y, ambColor.z, ambAlpha);
    glUniform4f(gc->h_uSpecColor, specColor.x, specColor.y, specColor.z, specAlpha);
    glUniform4f(gc->h_uDiffColor, diffColor.x, diffColor.y, diffColor.z, diffAlpha);
    glUniform1f(gc->h_uShininess, shininess);
    glUniform1f(gc->h_uSpecStrength, specStrength);
    glUniform3f(gc->h_uLightPos, lightPos.x, lightPos.y, lightPos.z);
    glUniform4f(gc->h_uLightColor, lightColor.x, lightColor.y, lightColor.z, gc->lightAlpha);
    glUniform3f(gc->h_uCamTrans, cameraPos.x, cameraPos.y, cameraPos.z);
    printOpenGLError();

    glDrawElements(GL_TRIANGLES, IBOlen, GL_UNSIGNED_SHORT, 0);

    safe_glDisableVertexAttribArray(gc->h_aNormal);
    safe_glDisableVertexAttribArray(gc->h_aPosition);
    safe_glDisableVertexAttribArray(gc->h_aTexCoord);
    glUseProgram(0);
}

void GameObject::update(float dt) {
    //default: do nothing.
}

void GameObject::doTranslate(glm::vec3 trans) {
    this->trans += trans;
}

void GameObject::doRotate(glm::vec3 axis, float deg) {
    this->rotate = glm::rotate(this->rotate, deg, axis);
}

void GameObject::fixBoundingBoxes() {
    if (AABBmin.x > AABBmax.x) {
        float temp = AABBmin.x;
        AABBmin.x = AABBmax.x;
        AABBmax.x = temp;
    }
    if (AABBmin.y > AABBmax.y) {
        float temp = AABBmin.y;
        AABBmin.y = AABBmax.y;
        AABBmax.y = temp;
    }
    if (AABBmin.z > AABBmax.z) {
        float temp = AABBmin.z;
        AABBmin.z = AABBmax.z;
        AABBmax.z = temp;
    }
}

void GameObject::doScale(glm::vec3 scale) {
    this->scale *= scale;
}

bool GameObject::doesCollide(GameObject *other) {
    vec3 thisMin = getAABBmin();
    vec3 thisMax = getAABBmax();
    vec3 otherMin = other->getAABBmin();
    vec3 otherMax = other->getAABBmax();

    return (thisMin.x <= otherMax.x &&
            thisMin.y <= otherMax.y &&
            thisMin.z <= otherMax.z &&
            thisMax.x >= otherMin.x &&
            thisMax.y >= otherMin.y &&
            thisMax.z >= otherMin.z);
}

void GameObject::setTrans(glm::vec3 t) {
    this->trans = t;
}

void GameObject::changeColor(glm::vec3 c, float alpha) {
    this->ambColor = c;
    ambAlpha = alpha;
}

std::string GameObject::className() {
    return "GameObject";
}

void GameObject::printTrans() {
    printf("(%lf, %lf, %lf)", trans.x, trans.y, trans.z);
}

void GameObject::onClick(SoundPlayer *soundPlayer) {
}

void GameObject::onEvent(SoundPlayer *soundPlayer) {
}

void GameObject::resetEvent(SoundPlayer *soundPlayer) {
}

unsigned int GameObject::numTextures() {
    static int counter = 0;
    return counter++;
}

glm::vec3 GameObject::getMinOrMax(bool isFindingMin) {
    glm::mat4 transMat = glm::translate(glm::mat4(), trans);
    glm::mat4 scaleMat = glm::scale(glm::mat4(), scale);

    glm::mat4 model = transMat * rotate * scaleMat;

    vec3 min = vec3(model * vec4(AABBmin, 1.0));
    vec3 max = vec3(model * vec4(AABBmax, 1.0));

    if (min.x > max.x) {
        float temp = min.x;
        min.x = max.x;
        max.x = temp;
    }
    if (min.y > max.y) {
        float temp = min.y;
        min.y = max.y;
        max.y = temp;
    }
    if (min.z > max.z) {
        float temp = min.z;
        min.z = max.z;
        max.z = temp;
    }
    
    if (isFindingMin)
        return min;
    else
        return max;
}

glm::vec3 GameObject::getAABBmin() {
    return getMinOrMax(true);
}

glm::vec3 GameObject::getAABBmax() {
    return getMinOrMax(false);
}