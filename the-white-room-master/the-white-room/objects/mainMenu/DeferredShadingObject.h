#ifndef DEFERRED_SHADING_OBJECT_H
#define	DEFERRED_SHADING_OBJECT_H

#include <GL/gl.h>
#include "../../GLSL_helper.h"
#include "../../GeometryCreator.h"
#include "../../audio/audio.h"
#include "../../Texture.h"

#include <string>

#define ROOM_SIZE 30.f
#define ROOM_HEIGHT_DIVISION 3.f
#define HIGHLIGHT_SPEED .03f

using glm::ivec2;
using glm::vec2;
using glm::vec3;
using glm::vec4;

using glm::mat2;
using glm::mat3;
using glm::mat4;

typedef struct DeferredShadingConstants {
    GLuint shader;
    float aspectRatio;
    glm::vec3 lightPos;
    glm::vec3 lightColor;
    float lightAlpha;
    GLuint h_aPosition;
    GLuint h_aNormal;
    GLuint h_aTexCoord;
    GLuint h_uAmbColor;
    GLuint h_uSpecColor;
    GLuint h_uDiffColor;
    GLuint h_uProjMatrix;
    GLuint h_uViewMatrix;
    GLuint h_uModelMatrix;
    GLuint h_uNormalMatrix;
    GLuint h_uLightPos;
    GLuint h_uTexUnit;
    GLuint h_uTexUnit2;
    GLuint h_uLightColor;
    GLuint h_uShininess;
    GLuint h_uSpecStrength;
    GLuint h_uCamTrans;
    GLuint h_uUseTex;
    GLuint h_uUseTex2;
    GLuint h_uTime;
    
    GLuint FramebufferName;
    GLuint diffuseTexture, PositionTexture, NormalsTexture;
    GLuint m_diffuseID, m_positionID, m_normalsID;
    GLuint quad_vertexbuffer;
} DeferredShadingConstants;

#include "../../Main.h"

class DeferredShadingObject {
public:
    //static float roomHeight = 0.f;
    //DeferredShadingObject(GLuint VBO, GLuint IBO, int IBOlen);
    DeferredShadingObject();
    virtual ~DeferredShadingObject();
    virtual void draw(glm::vec3 cameraPos, glm::vec3 lookAt,
            glm::vec3 lightPos, glm::vec3 lightColor, DeferredShadingConstants *gc);
    virtual void update(float dt, DeferredShadingObject* playerCamera, vec3 camLookAt);
    virtual std::string className();
    void doTranslate(glm::vec3 trans);
    void doRotate(glm::vec3 axis, float deg);
    void doScale(glm::vec3 scale);
    
    //void fixBoundingBoxes();
    
    virtual vec3 getAABBmin();
    virtual vec3 getAABBmax();

    void printTrans();
    unsigned int numTextures();
    
    glm::vec3 dir;
    float speed;
    glm::vec3 rotAxis;
    float rotSpeed;
    bool hasTex, hasTex2;

    // TODO: matrix transforms (orientation!)
    glm::vec3 AABBmin; //bounding box, I think
    glm::vec3 AABBmax;
    GLuint IBO;
    int IBOlen;
    GLuint VBO;
    GLuint NBO;
    GLuint TBO;
    GLuint texNum, texNum2;

    GLenum textureEnum;

    glm::vec3 ambColor;
    float ambAlpha;
    glm::vec3 initAmbColor;
    glm::vec3 specColor;
    float specAlpha;
    glm::vec3 diffColor;
    float diffAlpha;
    
    float shininess;
    float specStrength;
    int tag; //Misc information goes here

    //glm::mat4 scale;
    glm::vec3 scale;
    glm::mat4 rotate;
    glm::vec3 trans;
    //glm::mat4 trans;
    
    bool isVisible;
    
private:
    glm::vec3 getMinOrMax(bool isFindingMin);
};
#endif
