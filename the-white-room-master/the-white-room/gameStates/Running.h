/* 
 * File:   Running.h
 * Author: goofanader
 *
 * Created on January 29, 2013, 10:19 PM
 */

#ifndef RUNNING_H
#define	RUNNING_H

#include <set>
#include <string>
#include <sstream>

#include "State.h"
#include "../objects/GameObject.h"
#include "../objects/Room.h"
#include "../objects/WhiteDoor.h"

#include "../events/Event.h"
#include "../events/EventSwitch.h"
#include "../audio/audio.h"

class Running : public State {
public:
    Running();
    Running(std::string saveFile);
    Running(const Running& orig);
    virtual ~Running();
    
    void draw();
    void update(float dt);

    void mouseClicked(int button, int action);
    void mouseMoved(int x, int y, float prevX, float prevY);
    void keyPressed(float dt, int keyDown[]);
    void wKeyPressed(glm::vec3 vecW);
    void aKeyPressed(glm::vec3 vecU);
    void sKeyPressed(glm::vec3 vecW);
    void dKeyPressed(glm::vec3 vecU);
    void handleFirstPersonMovement(int keyDown[], float dt);

    void pause();
    void resume();

    void printObjects();
private:
    GameObject* playerCamera, *lightPos;
    Room* room;
    WhiteDoor* door;
    std::set<GameObject*> objects;
    SoundPlayer *soundPlayer;
    SoundPlayer *footSounds;
    
    float camAlpha;
    float camBeta;
    glm::vec3 camLookAt;
    glm::vec3 camPrevTrans;
    
    int eventNum, mouseClicks;
    Event* currEvent;
    EventSwitch switches[MAX_SWITCHES];
    
    double timeSpent;
    bool isFoot1;
    
    void initializeCamera();
    void initializeLight();
    void updateLookAt();
    void loadObjectsFromEvent();
};

#endif	/* RUNNING_H */

