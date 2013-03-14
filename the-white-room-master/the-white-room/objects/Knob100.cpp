/* 
 * File:   Knob100.cpp
 * Author: goofanader
 * 
 * Created on February 24, 2013, 6:44 PM
 */

#include "Knob100.h"
#include "GameObject.h"

Knob100::Knob100() {
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/radio/Knob.obj",
            IBOlen, VBO, IBO, NBO, TBO, AABBmin, AABBmax);
    dir = vec3(1.f, 0.f, 0.f);
    speed = 0.f;
    rotSpeed = 0.f;
    rotAxis = vec3(0.f, 1.f, 0.f);
    ambColor = vec3(1.7f);
    diffColor = vec3(0.1, 0.74, 0.32);
    specColor = vec3(.5f);
    shininess = 5;
    specStrength = 0.f;
    scale = glm::vec3(1.f);
    
    ambAlpha = 0.f;

    texNum = numTextures();
    textureEnum = GL_TEXTURE0 + texNum;
    printOpenGLError();
    LoadTexture((char *) "objects/meshes/radio/KnobUVbrass.bmp", texNum);
    printOpenGLError();
    hasTex = true;

    rotating = 18.f;
    rotAnim = 0.f;
    
    depthMin = .3;
    depthMax = 1.0;

    doScale(glm::vec3(0.75f));
    //doRotate(glm::vec3(1,0,0), rotating);
    doTranslate(glm::vec3(27.f, 0, -1.f));

    station = 1000;
    isClicked = isVisible = false;
    
    //Load in the select arrow
    arrow = new GameObject();
    MeshLoader::loadVertexBufferObjectFromMesh("objects/meshes/radio/Arrow.obj",
            arrow->IBOlen, arrow->VBO, arrow->IBO, arrow->NBO, arrow->TBO, 
            arrow->AABBmin, arrow->AABBmax);
    arrow->dir = vec3(1.f, 0.f, 0.f);
    arrow->speed = 0.f;
    arrow->rotSpeed = 0.f;
    arrow->rotAxis = vec3(0.f, 1.f, 0.f);
    arrow->ambColor = vec3(0.f);
    arrow->diffColor = vec3(1.f, 0.f, 0.f);
    arrow->specColor = vec3(.5f);
    arrow->shininess = 5;
    arrow->specStrength = 0.f;
    arrow->scale = glm::vec3(1.f);
    
    arrow->ambAlpha = 0.f;
    
    arrow->hasTex = false;
    
    arrow->doScale(vec3(.25f, .05f, .25f));
    arrow->doTranslate(this->trans);
    arrow->doTranslate(vec3(0.f, getAABBmax().y - arrow->getAABBmin().y + .5f, 0.f));
}

Knob100::Knob100(const Knob100& orig) {
}

Knob100::~Knob100() {
}

int Knob100::getStation() {
    return station;
}

void Knob100::update(float dt, GameObject *playerCamera) {
    if (isClicked) {
        if (ambAlpha < 1.0) {
            ambAlpha += HIGHLIGHT_SPEED;
            arrow->ambAlpha += HIGHLIGHT_SPEED;

            if (ambAlpha > 1.0) {
                ambAlpha = 1.0f;
                arrow->ambAlpha = 1.0f;
            }
        }
        
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
        doRotate(axis, rotA);
        
        
        doRotate(up, rotY);
        //doRotate(glm::vec3(1.f, 0.f, 0.f), rotating);
        
        if (rotAnim < rotating) { rotAnim += dt * 100; }
        doRotate(glm::vec3(1.f, 0.f, 0.f), rotAnim);
        
        arrow->rotate = glm::mat4(1.f);
        arrow->doRotate(up, rotY);
        arrow->doRotate(axis, rotA);
        arrow->doRotate(vec3(0,0,1), -90);
        
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
    } else if (!isClicked && ambAlpha > 0.f) {
        ambAlpha -= HIGHLIGHT_SPEED;
        arrow->ambAlpha -= HIGHLIGHT_SPEED;
        if (ambAlpha < 0.f) {
            ambAlpha = 0.f;
            arrow->ambAlpha = 0.f;
        }
        
        highlightAlpha = 0.f;
        highlightColor = vec3(0.f);
    }
}

void Knob100::onEvent(SoundPlayer *soundPlayer) {
    if (isClicked) {
        //soundPlayer->playSound("TryRadio");

        rotating += 36.f;

        station += 100;

        if (station > 1500) {
            station = 600;
        }
    }
}

std::string Knob100::className() {
    return "Knob100";
}

void Knob100::draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
        glm::vec3 lightColor, GameConstants* gc) {
    if (isClicked || (!isClicked && ambAlpha > 0.f)) {
        arrow->draw(cameraPos, lookAt, lightPos, lightColor, gc);
        
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
