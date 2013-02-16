/* 
 * File:   State.cpp
 * Author: alex
 * 
 * Created on June 6, 2012, 12:07 PM
 */

#include "State.h"
#include "objects/GameObject.h"

State::State()
{
    paused = false;
}

State::State(const State& orig)
{
}

State::~State()
{
}

void State::draw()
{
    // do nothing
}

void State::update(float dt)
{
    // do nothing
}

void State::mouseClicked(int button, int action)
{
    // do nothing
}

void State::mouseMoved(int x, int y, float prevX, float prevY)
{
    // do nothing
}

void State::keyPressed(float dt, int keyDown[]) {
    
}

void State::wKeyPressed(glm::vec3 vecW)
{

}

void State::aKeyPressed(glm::vec3 vecU)
{

}

void State::sKeyPressed(glm::vec3 vecW)
{

}

void State::dKeyPressed(glm::vec3 vecU)
{

}

void State::pause()
{
    paused = true;
}

void State::resume()
{
    paused = false;
}

bool State::isPaused()
{
    return paused;
}

#if 0
void State::SetView(glm::vec3 camTrans, glm::vec3 camLookAt) {
    glm::mat4 View = glm::lookAt(camTrans, camLookAt, vec3(0.f, 1.f, 0.f));
    safe_glUniformMatrix4fv(gc.h_uViewMatrix, glm::value_ptr(View));
}
#endif
