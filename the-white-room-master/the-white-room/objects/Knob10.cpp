/* 
 * File:   Knob10.cpp
 * Author: goofanader
 * 
 * Created on February 24, 2013, 6:44 PM
 */

#include "Knob10.h"
#include "GameObject.h"

Knob10::Knob10() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/radio/Knob.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(.75f);
    diffColor = vec3(0.1, 0.74, 0.32);
    specColor = vec3(.5f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);

    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    printOpenGLError();
    LoadTexture((char *) "objects/meshes/radio/Knob2UVbrass.bmp", texNum);
    printOpenGLError();
    hasTex = true;

    rotating = 18.f;

    doScale(glm::vec3(0.75f));
    //doRotate(glm::vec3(1.f,0,0), rotating);
    doTranslate(glm::vec3(27.f, 0, 1.f));

    station = 50;
    isClicked = false;
}

Knob10::Knob10(const Knob10& orig) {
}

Knob10::~Knob10() {
}

int Knob10::getStation() {
    return station;
}

void Knob10::update(float dt, GameObject *playerCamera) {
    if (isClicked) {
        //make it so it always faces the player
        float rotY, rotA;
        vec3 up = glm::vec3(0.f, 1.f, 0.f);

        vec3 loc = playerCamera->trans - this->trans;

        vec3 axis = glm::cross(up, loc);
        //vec3 axis = up * loc;

        if (loc.z == 0 && loc.x == 0)
            rotY = 0;
        else
            rotY = atan2(loc.x, loc.z) * 180.0 / 3.14 - 90;

        rotA = 90 - asin(glm::length(axis) / (glm::length(loc))) * 180.0 / 3.14;

        if (loc.y > 0)
            rotA = -rotA;

        this->rotate = glm::mat4(1.f);
        //doRotate(glm::cross(up,axis), rotating);
        doRotate(axis, rotA);

        doRotate(up, rotY);
        doRotate(glm::vec3(1.f, 0.f, 0.f), rotating);
        //doRotate(up, 90.f);

        if (isHighlighted) {
            highlightColor = highlightColor + vec3(HIGHLIGHT_SPEED);

            if (highlightColor.x > 1.f) {
                highlightColor = vec3(1.f);
            }

            highlightAlpha += HIGHLIGHT_SPEED;
            if (highlightAlpha > 1.f) {
                highlightAlpha = 1.f;
            }
        } else {
            isHighlightDisappearing = true;
            highlightColor = highlightColor - vec3(HIGHLIGHT_SPEED);

            if (highlightColor.x < 0.f) {
                highlightColor = vec3(0.f);
            }

            highlightAlpha -= HIGHLIGHT_SPEED;
            if (highlightAlpha < 0.f) {
                isHighlightDisappearing = false;
                highlightAlpha = 0.f;
            }
        }
    }
}

void Knob10::onEvent(SoundPlayer *soundPlayer) {
    if (isClicked) {
        soundPlayer->playSound("TryRadio");

        rotating += 36.f;

        station += 10;

        if (station > 90) {
            station = 0;
        }
    }
}

std::string Knob10::className() {
    return "Knob10";
}

void Knob10::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc) {
    if (isClicked) {
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
            glActiveTexture(textureEnum);
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
        glUniform4f(gc->h_uAmbColor, ambColor.x + highlightColor.x,
                ambColor.y + highlightColor.y, ambColor.z + highlightColor.z, ambAlpha);
        glUniform4f(gc->h_uSpecColor, specColor.x + highlightColor.x,
                specColor.y + highlightColor.y, specColor.z + highlightColor.z, specAlpha);
        glUniform4f(gc->h_uDiffColor, diffColor.x + highlightColor.x,
                diffColor.y + highlightColor.y, diffColor.z + highlightColor.z, diffAlpha);
        printOpenGLError();
        glUniform1f(gc->h_uShininess, shininess);
        glUniform1f(gc->h_uSpecStrength, specStrength);
        printOpenGLError();
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
}