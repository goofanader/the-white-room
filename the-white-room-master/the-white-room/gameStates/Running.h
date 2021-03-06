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

#define ARRAYMULTIPLIER 4.f
#define ARRAYDIVISOR 0.5f

class Running : public State {
public:
    Running();
    Running(std::string saveFile);
    Running(const Running& orig);
    virtual ~Running();
    
    void draw();
    void update(float dt);

    bool isMouseOverObject(GameObject *curr);
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
    glm::vec3 camPrevTrans, camNextTrans;
    
    int eventNum;
    Event* currEvent;
    
    double timeSpent;
    bool isFoot1;
   
    //GameObject* objectArray[(int) (ROOM_SIZE * ARRAYDIVISOR * ARRAYMULTIPLIER)][(int) ((ROOM_SIZE/ROOM_HEIGHT_DIVISION) * ARRAYDIVISOR * ARRAYMULTIPLIER)][(int) (ROOM_SIZE * ARRAYDIVISOR * ARRAYMULTIPLIER)];

    void initializeCamera();
    void initializeLight();
    void updateLookAt();
    void loadObjectsFromEvent();
};

#endif	/* RUNNING_H */

