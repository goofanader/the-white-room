/* 
 * File:   MainMenu.h
 * Author: goofanader
 *
 * Created on January 29, 2013, 10:19 PM
 */

#ifndef MAINMENU_H
#define	MAINMENU_H

#include <set>
#include <string>
#include <sstream>

#include "State.h"
#include "../objects/mainMenu/MenuObjects.h"

#include "../audio/audio.h"

class MainMenu : public State {
public:
    MainMenu();
    MainMenu(const MainMenu& orig);
    virtual ~MainMenu();
    
    void draw();
    void update(float dt);
    
    void mouseClicked(int button, int action);

    void pause();
    void resume();
private:
    DeferredShadingObject* playerCamera, *lightPos;
    std::set<DeferredShadingObject*> objects;
    SoundPlayer *soundPlayer;
    
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

