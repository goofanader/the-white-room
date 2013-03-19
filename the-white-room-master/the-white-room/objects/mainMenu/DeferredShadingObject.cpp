#include <GL/gl.h>
#include <stdio.h>

#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#include "DeferredShadingObject.h"
#include <math.h>

#define HARDCODE_WALLS 0

/*DeferredShadingObject::DeferredShadingObject(GLuint VBO, GLuint IBO, int IBOlen) {
    this->IBO = IBO;
    this->IBOlen = IBOlen;
    this->VBO = VBO;
}*/

DeferredShadingObject::DeferredShadingObject() {
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

    texNum = texNum2 = -1;
    hasTex = false;
    hasTex2 = false;

    ambColor = glm::vec3(.75f);
    ambAlpha = 1.f;
    specColor = glm::vec3(.1f);
    specAlpha = 1.f;
    diffColor = glm::vec3(.1f);
    diffAlpha = 1.f;
    
    isVisible = true;
}

DeferredShadingObject::~DeferredShadingObject() {
}

void DeferredShadingObject::draw(glm::vec3 cameraPos, glm::vec3 lookAt,
        glm::vec3 lightPos, glm::vec3 lightColor, DeferredShadingConstants *gc) {
    if (VBO == -1 || IBO == -1 || IBOlen <= 0 || NBO == -1) {
        return;
    }

    //printOpenGLError();
    glUseProgram(gc->shader);
    //printOpenGLError();
    //TODO Set matrix stuff
    glm::mat4 projection = glm::perspective(80.0f, gc->aspectRatio, 0.1f, 100.f);
    safe_glUniformMatrix4fv(gc->h_uProjMatrix, glm::value_ptr(projection));
    
    //safe_glUniform1f(gc->h_uTime, glfwGetTime());

    glm::mat4 view = glm::lookAt(cameraPos, lookAt, glm::vec3(0.f, 1.f, 0.f));
    safe_glUniformMatrix4fv(gc->h_uViewMatrix, glm::value_ptr(view));

    glm::mat4 transMat = glm::translate(glm::mat4(), trans);
    glm::mat4 scaleMat = glm::scale(glm::mat4(), scale);

    glm::mat4 model = transMat * rotate * scaleMat;
    safe_glUniformMatrix4fv(gc->h_uModelMatrix, glm::value_ptr(model));
    safe_glUniformMatrix4fv(gc->h_uNormalMatrix,
            glm::value_ptr(glm::transpose(glm::inverse(model))));

    //Do transformations
    glActiveTexture(GL_TEXTURE1);
    safe_glEnableVertexAttribArray(gc->h_aPosition);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    safe_glVertexAttribPointer(gc->h_aPosition, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glActiveTexture(GL_TEXTURE2);
    safe_glEnableVertexAttribArray(gc->h_aNormal);
    glBindBuffer(GL_ARRAY_BUFFER, NBO);
    safe_glVertexAttribPointer(gc->h_aNormal, 3, GL_FLOAT, GL_TRUE, 0, 0);
    printOpenGLError();
    if (hasTex) {
        printOpenGLError();
        glEnable(GL_TEXTURE_2D);
        printOpenGLError();
        safe_glUniform1i(gc->h_uTexUnit, 0);
        printOpenGLError();
        safe_glEnableVertexAttribArray(gc->h_aTexCoord);
        printOpenGLError();
        glBindBuffer(GL_ARRAY_BUFFER, TBO);
        printOpenGLError();
        safe_glVertexAttribPointer(
                gc->h_aTexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
        printOpenGLError();
        glActiveTexture(GL_TEXTURE0);
        printOpenGLError();
        glBindTexture(GL_TEXTURE_2D, texNum);
        printOpenGLError();

        glDisable(GL_TEXTURE_2D);
    }
    printOpenGLError();
    safe_glUniform1i(gc->h_uUseTex, hasTex ? 1 : 0);
    //safe_glUniform1i(gc->h_uUseTex2, hasTex2 ? 1 : 0);
    printOpenGLError();
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    printOpenGLError();

    glDrawElements(GL_TRIANGLES, IBOlen, GL_UNSIGNED_SHORT, 0);
    printOpenGLError();

    safe_glDisableVertexAttribArray(gc->h_aNormal);
    safe_glDisableVertexAttribArray(gc->h_aPosition);
    safe_glDisableVertexAttribArray(gc->h_aTexCoord);
    glUseProgram(0);
    printOpenGLError();
}

void DeferredShadingObject::update(float dt, DeferredShadingObject* playerCamera, vec3 camLookAt) {
}

void DeferredShadingObject::doTranslate(glm::vec3 trans) {
    this->trans += trans;
}

void DeferredShadingObject::doRotate(glm::vec3 axis, float deg) {
    this->rotate = glm::rotate(this->rotate, deg, axis);
}

void DeferredShadingObject::doScale(glm::vec3 scale) {
    this->scale *= scale;
}

std::string DeferredShadingObject::className() {
    return "DeferredShadingObject";
}

void DeferredShadingObject::printTrans() {
    printf("(%lf, %lf, %lf)", trans.x, trans.y, trans.z);
}

unsigned int DeferredShadingObject::numTextures() {
    static int counter = 0;
    return counter++;
}

glm::vec3 DeferredShadingObject::getMinOrMax(bool isFindingMin) {
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

glm::vec3 DeferredShadingObject::getAABBmin() {
    return getMinOrMax(true);
}

glm::vec3 DeferredShadingObject::getAABBmax() {
    return getMinOrMax(false);
}
