#ifndef GAME_OBJECT_H
#define	GAME_OBJECT_H

#include <GL/gl.h>
#include "../GeometryCreator.h"
#include "../audio/audio.h"
#include "../Texture.h"


#include <string>

#define ROOM_SIZE 30.f
#define ROOM_HEIGHT_DIVISION 3.f

using glm::ivec2;
using glm::vec2;
using glm::vec3;
using glm::vec4;

using glm::mat2;
using glm::mat3;
using glm::mat4;


typedef struct GameConstants {
    GLuint shader;
    float aspectRatio;
    glm::vec3 lightPos;
    glm::vec3 lightColor;
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
    GLuint h_uLightColor;
    GLuint h_uShininess;
    GLuint h_uSpecStrength;
    GLuint h_uCamTrans;
    GLuint h_uUseTex;
} GameConstants;
#include "../Main.h"

class GameObject {
public:
    //static float roomHeight = 0.f;
    GameObject(GLuint VBO, GLuint IBO, int IBOlen);
    GameObject();
    ~GameObject();
    virtual void draw(glm::vec3 cameraPos, glm::vec3 lookAt,
            glm::vec3 lightPos, glm::vec3 lightColor, GameConstants *gc);
    virtual void update(float dt);
    virtual std::string className();
    virtual bool doesCollide(GameObject *other);
    void doTranslate(glm::vec3 trans);
    void doRotate(glm::vec3 axis, float deg);
    void doScale(glm::vec3 scale);

    void setTrans(glm::vec3 t);
    void changeColor(glm::vec3 c);
    void fixBoundingBoxes();

    virtual void onEvent(SoundPlayer *soundPlayer);
    virtual void resetEvent(SoundPlayer *soundPlayer);
    
    glm::vec3 dir;
    float speed;
    glm::vec3 rotAxis;
    float rotSpeed;
    bool hasTex;

    // TODO: matrix transforms (orientation!)
    glm::vec3 AABBmin; //bounding box, I think
    glm::vec3 AABBmax;
    GLuint IBO;
    int IBOlen;
    GLuint VBO;
    GLuint NBO;
    GLuint TBO;
    int texNum;

    GLenum textureMaps[39];

    glm::vec3 ambColor;
    glm::vec3 initAmbColor;
    glm::vec3 specColor;
    glm::vec3 diffColor;
    float shininess;
    float specStrength;
    int tag; //Misc information goes here

    GameObject *next;

    //glm::mat4 scale;
    glm::vec3 scale;
    glm::mat4 rotate;
    glm::vec3 trans;
    //glm::mat4 trans;

    bool isClicked;

    void printTrans();
    unsigned int numTextures();
};
#endif
