/* 
 * File:   Safe.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 12:49 AM
 */

#ifndef SAFE_H
#define	SAFE_H

#include "GameObject.h"

#define NUM_LEGS 4

class Safe : public GameObject {
public:
    bool isOpen;
    
    Safe();
    Safe(const Safe& orig);
    virtual ~Safe();
    void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    void update(float dt, GameObject* playerCamera, vec3 camLookAt);
    bool doesCollide(GameObject* other);

    void onEvent(SoundPlayer *soundPlayer);
    
    std::string className();
private:
    GameObject* body;
    GameObject* door;
    
    float timeSpent;
};

#endif	/* SAFE_H */

