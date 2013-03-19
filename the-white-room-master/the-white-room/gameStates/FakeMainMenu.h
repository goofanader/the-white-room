/* 
 * File:   FakeMainMenu.h
 * Author: goofanader
 *
 * Created on January 29, 2013, 10:19 PM
 */

#ifndef FAKEMAINMENU_H
#define	FAKEMAINMENU_H

#include <set>
#include <string>
#include <sstream>

#include "State.h"
#include "../objects/mainMenu/FakeOpening.h"

#include "../audio/audio.h"

class FakeMainMenu : public State {
public:
    FakeMainMenu();
    FakeMainMenu(const FakeMainMenu& orig);
    virtual ~FakeMainMenu();
    
    void draw();
    void update(float dt);
    
    void mouseClicked(int button, int action);
    void keyPressed(float dt, int keyDown[]);

    void pause();
    void resume();
private:
    GameObject* playerCamera, *lightPos;
    FakeOpening *frame;
    //std::set<GameObject*> objects;
    SoundPlayer *soundPlayer;
    int waitCounter;
    
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

