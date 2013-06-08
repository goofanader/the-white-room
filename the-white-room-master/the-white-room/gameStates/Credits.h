/* 
 * File:   Credits.h
 * Author: goofanader
 *
 * Created on January 29, 2013, 10:19 PM
 */

#ifndef CREDITS_H
#define	CREDITS_H

#include <set>
#include <string>
#include <sstream>

#include "State.h"
#include "../objects/credits/Ending.h"

#include "../audio/audio.h"

class Credits : public State {
public:
    Credits();
    Credits(const Credits& orig);
    virtual ~Credits();
    
    void draw();
    void update(float dt);
    
    void mouseClicked(int button, int action);
    void keyPressed(float dt, int keyDown[]);

    void pause();
    void resume();
private:
    GameObject* playerCamera, *lightPos;
    Ending *frame;
    //std::set<GameObject*> objects;
    SoundPlayer *soundPlayer;
    int waitCounter;
    
    bool isReadingStory;
    int storyCounter;
    
    float camAlpha, camBeta;
    float prevAlpha, prevBeta;
    glm::vec3 camLookAt;
    glm::vec3 camPrevTrans, camNextTrans;
    
    double timeSpent;
    
    void initializeCamera();
    void initializeLight();
    void updateLookAt();
};

#endif	/* RUNNING_H */

