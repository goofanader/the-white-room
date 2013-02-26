/* 
 * File:   Clock.h
 * Author: goofanader
 *
 * Created on February 14, 2013, 5:27 AM
 */

#ifndef CLOCK_H
#define	CLOCK_H

#include "GameObject.h"
#include "MeshLoader.h"
#include <iostream>
#include "../audio/audio.h"

class Clock : public GameObject {
public:
    Clock();
    Clock(const Clock& orig);
    virtual ~Clock();
    
    void draw(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    void update(float dt, GameObject* playerCamera);
    bool doesCollide(GameObject* other);
    std::string className();
    
    void onEvent(SoundPlayer *soundPlayer);
private:
    GameObject *body, *weight1, *weight2, *weight3;
    SoundPlayer *clockSoundPlayer;
    bool haveLoadedPlayer;
};

#endif	/* CLOCK_H */

