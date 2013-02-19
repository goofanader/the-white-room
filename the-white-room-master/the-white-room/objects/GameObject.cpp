#include <GL/gl.h>
#include <stdio.h>

#include "GLSL_helper.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GameObject.h"

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
    specColor = glm::vec3(.1f);
    diffColor = glm::vec3(.1f);

    textureMaps[0] = GL_TEXTURE0;
    textureMaps[1] = GL_TEXTURE1;
    textureMaps[2] = GL_TEXTURE2;
    textureMaps[3] = GL_TEXTURE3;
    textureMaps[4] = GL_TEXTURE4;
    textureMaps[5] = GL_TEXTURE5;
    textureMaps[6] = GL_TEXTURE6;
    textureMaps[7] = GL_TEXTURE7;
    textureMaps[8] = GL_TEXTURE8;
    textureMaps[9] = GL_TEXTURE9;
    textureMaps[10] = GL_TEXTURE10;
    textureMaps[11] = GL_TEXTURE11;
    textureMaps[12] = GL_TEXTURE12;
    textureMaps[13] = GL_TEXTURE13;
    textureMaps[14] = GL_TEXTURE14;
    textureMaps[15] = GL_TEXTURE15;
    textureMaps[16] = GL_TEXTURE16;
    textureMaps[17] = GL_TEXTURE17;

}

GameObject::~GameObject() {
}

void GameObject::draw(glm::vec3 cameraPos, glm::vec3 lookAt,
        glm::vec3 lightPos, glm::vec3 lightColor, GameConstants *gc) {
    if (VBO == -1 || IBO == -1 || IBOlen <= 0 || NBO == -1) {
        return;
    }

    glUseProgram(gc->shader);

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
        glEnable(GL_TEXTURE_2D);

        safe_glUniform1i(gc->h_uTexUnit, texNum);

        safe_glEnableVertexAttribArray(gc->h_aTexCoord);
        glBindBuffer(GL_ARRAY_BUFFER, TBO);
        safe_glVertexAttribPointer(
                gc->h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glActiveTexture(textureMaps[texNum]);
        glBindTexture(GL_TEXTURE_2D, texNum);

        glDisable(GL_TEXTURE_2D);
    }
    safe_glUniform1i(gc->h_uUseTex, hasTex ? 1 : 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    printOpenGLError();
    //pass colors, camera position, and light info to GPU
    glUniform3f(gc->h_uAmbColor, ambColor.x, ambColor.y, ambColor.z);
    glUniform3f(gc->h_uSpecColor, specColor.x, specColor.y, specColor.z);
    glUniform3f(gc->h_uDiffColor, diffColor.x, diffColor.y, diffColor.z);
    glUniform1f(gc->h_uShininess, shininess);
    glUniform1f(gc->h_uSpecStrength, specStrength);
    glUniform3f(gc->h_uLightPos, lightPos.x, lightPos.y, lightPos.z);
    glUniform3f(gc->h_uLightColor, lightColor.x, lightColor.y, lightColor.z);
    glUniform3f(gc->h_uCamTrans, cameraPos.x, cameraPos.y, cameraPos.z);
    printOpenGLError();

    glDrawElements(GL_TRIANGLES, IBOlen, GL_UNSIGNED_SHORT, 0);

    safe_glDisableVertexAttribArray(gc->h_aNormal);
    safe_glDisableVertexAttribArray(gc->h_aPosition);
    safe_glDisableVertexAttribArray(gc->h_aTexCoord);
    glUseProgram(0);
}

void GameObject::update(float dt) {
    //this needs to be generic
    //doTranslate(glm::vec3(dt * speed * dir));
#if HARDCODE_WALLS
    if (trans.x + AABBmin.x < -9.5) {
        trans.x = -9.5 - AABBmin.x;
        dir = -dir;
    } else if (trans.x + AABBmax.x > 9.5) {
        trans.x = 9.5 - AABBmax.x;
        dir = -dir;
    }
    if (trans.z + AABBmin.z < -9.5) {
        trans.z = -9.5 - AABBmin.z;
        dir = -dir;
    } else if (trans.z + AABBmax.z > 9.5) {
        trans.z = 9.5 - AABBmax.z;
        dir = -dir;
    }
#endif
    //doRotate(rotAxis, dt * rotSpeed);
    //doRotate(glm::vec3(0, 1, 0), 45);
    //TODO check for collisions
}

void GameObject::doTranslate(glm::vec3 trans) {
    this->trans += trans;
    this->AABBmin += trans;
    this->AABBmax += trans;

    fixBoundingBoxes();
}

void GameObject::doRotate(glm::vec3 axis, float deg) {
    this->rotate = glm::rotate(this->rotate, deg, axis);
    //this->AABBmin = vec3(this->rotate * vec4(this->AABBmin, 1.f));
    this->AABBmin = vec3(this->rotate * vec4(this->AABBmin, 1.f));
    //this->AABBmax = vec3(this->rotate * vec4(this->AABBmax, 1.f));
    this->AABBmax = vec3(this->rotate * vec4(this->AABBmax, 1.f));

    fixBoundingBoxes();
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
    this->AABBmin *= scale;
    this->AABBmax *= scale;

    fixBoundingBoxes();
}

bool GameObject::doesCollide(GameObject *other) {
    return (this->AABBmin.x <= other->AABBmax.x &&
            //this->AABBmin.y <= other->AABBmax.y &&
            this->AABBmin.z <= other->AABBmax.z &&
            this->AABBmax.x >= other->AABBmin.x &&
            //this->AABBmax.y >= other->AABBmin.y &&
            this->AABBmax.z >= other->AABBmin.z);
}

void GameObject::setTrans(glm::vec3 t) {
    this->trans = t;
    this->AABBmin += t;
    this->AABBmax += t;
}

void GameObject::changeColor(glm::vec3 c) {
    this->ambColor = c;
}

std::string GameObject::className() {
    return "GameObject";
}

void GameObject::printTrans() {
    printf("(%lf, %lf, %lf)", trans.x, trans.y, trans.z);
}

void GameObject::onEvent(SoundPlayer *soundPlayer) {
    //soundPlayer->playSound("GameStart");
}

void GameObject::resetEvent(SoundPlayer *soundPlayer) {
    this->ambColor = glm::vec3(1.f);
}

unsigned int GameObject::numTextures() {
    static int counter = 0;
    return counter++;
}
