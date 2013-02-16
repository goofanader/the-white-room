/* 
 * File:   EventSwitch.cpp
 * Author: goofanader
 * 
 * Created on January 31, 2013, 2:53 AM
 */

#include "EventSwitch.h"

EventSwitch::EventSwitch() {
    className = "";
    isOn = false;
    isEmpty = true;
}

bool EventSwitch::isUninitialized() {
    return isEmpty;
}

EventSwitch::EventSwitch(std::string newClassName, bool isItOn) {
    className = newClassName;
    isOn = isItOn;
    isEmpty = false;
}

EventSwitch::EventSwitch(const EventSwitch& orig) {
}

EventSwitch::~EventSwitch() {
}

bool EventSwitch::isSwitchOn() {
    return isOn;
}

void EventSwitch::setSwitch(bool newSwitch) {
    isOn = newSwitch;
}

std::string EventSwitch::getClassName() {
    return className;
}

void EventSwitch::setClassName(std::string newName) {
    className = newName;
}

void EventSwitch::setIsEmpty(bool isItEmpty) {
    isEmpty = isItEmpty;
}

GameObject* EventSwitch::getGameObject() {
    return roomObject;
}

void EventSwitch::setGameObject(GameObject* newObject) {
    roomObject = newObject;
}