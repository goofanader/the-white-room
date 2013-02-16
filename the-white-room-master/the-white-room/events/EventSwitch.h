/* 
 * File:   EventSwitch.h
 * Author: goofanader
 *
 * Created on January 31, 2013, 2:53 AM
 */

#ifndef EVENTSWITCH_H
#define	EVENTSWITCH_H

#include <string>

#include "../objects/GameObject.h"

class EventSwitch {
public:
    EventSwitch();
    EventSwitch(std::string newClassName, bool isItOn);
    EventSwitch(const EventSwitch& orig);
    virtual ~EventSwitch();
    
    bool isSwitchOn();
    void setSwitch(bool newSwitch);
    std::string getClassName();
    void setClassName(std::string newName);
    
    bool isUninitialized();
    void setIsEmpty(bool isItEmpty);
    
    GameObject* getGameObject();
    void setGameObject(GameObject* newObject);
private:
    std::string className;
    bool isOn;
    bool isEmpty;
    GameObject* roomObject;
};

#endif	/* EVENTSWITCH_H */

