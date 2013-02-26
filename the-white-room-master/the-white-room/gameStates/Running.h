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

    void pause();
    void resume();
private:
    GameObject* playerCamera, *lightPos;
    std::set<GameObject*> objects;
    SoundPlayer *soundPlayer, *footSounds;
    
    float camAlpha;
    float camBeta;
    float prevAlpha, prevBeta;
    glm::vec3 camLookAt;
    glm::vec3 camPrevTrans;
    
    int eventNum;
    Event* currEvent;
    
    double timeSpent;
    bool isFoot1;
    
    void initializeCamera();
    void initializeLight();
    void updateLookAt();
    void loadObjectsFromEvent();
};

#endif	/* RUNNING_H */

