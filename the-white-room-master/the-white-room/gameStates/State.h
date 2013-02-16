/* 
 * File:   State.h
 * Author: alex
 *
 * Created on June 6, 2012, 12:07 PM
 */

#ifndef STATE_H
#define	STATE_H

#include <GL/glfw.h>
#include "glm/glm.hpp"
#include "Main.h"

class State
{
public:
    State();
    State(const State& orig);
    virtual ~State();

    virtual void draw();
    virtual void update(float dt);

    virtual void mouseClicked(int button, int action);
    virtual void mouseMoved(int x, int y, float prevX, float prevY);

    virtual void keyPressed(float dt, int keyDown[]);
    virtual void wKeyPressed(glm::vec3 vecW);
    virtual void aKeyPressed(glm::vec3 vecU);
    virtual void sKeyPressed(glm::vec3 vecW);
    virtual void dKeyPressed(glm::vec3 vecU);

    virtual void pause();
    virtual void resume();
    bool isPaused();
    
    void SetView(glm::vec3 camTrans, glm::vec3 camLookAt);
private:
    bool paused;
};

#endif	/* STATE_H */

