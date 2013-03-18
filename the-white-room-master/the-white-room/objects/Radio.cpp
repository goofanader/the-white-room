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

    doRotate(glm::vec3(0.f, 1.f, 0.f), 180.f);

    doTranslate(glm::vec3(0.f, -3.85f - getAABBmin().y, 0.f));

    doTranslate(glm::vec3(27.f, 0.f, 0.f));

    glGenTextures(1, &texNum);
    printOpenGLError();
    LoadTexture((char *) "objects/meshes/radio/RadioUVSmall.bmp", texNum);
    printOpenGLError();
    hasTex = true;
    ignore = false;

}

Radio::Radio(const Radio& orig) {
}

Radio::~Radio() {
}

void Radio::onEvent(SoundPlayer *soundPlayer) {
    if (isClicked) {
        soundPlayer->playSound("RadioStatic");
    }
}

std::string Radio::className() {
    return "Radio";
}

void Radio::drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos,
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

        printOpenGLError();
        safe_glUniform1i(gc->h_uUseTex, 0);
        printOpenGLError();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

        printOpenGLError();

        //pass colors, camera position, and light info to GPU
        glUniform4f(gc->h_uAmbColor, highlightColor.x, highlightColor.y,
                highlightColor.z, highlightAlpha);
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
}
