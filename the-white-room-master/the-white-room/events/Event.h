/* 
 * File:   Event.h
 * Author: goofanader
 *
 * Created on January 29, 2013, 10:07 PM
 */

#ifndef EVENT_H
#define	EVENT_H

#include <fstream>
#include <iostream>
#include <string>

#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "EventSwitch.h"
#include "ObjectCreation.h"
#include "../audio/audio.h"

#define MAX_SWITCHES 35

using namespace std;

class Event {
public:
    Event(int currentEventNum, SoundPlayer *currSoundPlayer);
    Event(const Event& orig);
    virtual ~Event();
    EventSwitch* getSwitches();
    int getSwitchNum();
    void ifObjectSelected(GameObject *curr);
    bool setSwitch(std::string className);
    int getEventNum();
private:
    std::string fileName;
    int eventNum;
    EventSwitch eventSwitches[MAX_SWITCHES];
    int switchNum;
    bool isEventOrdered;
    bool isEventTimed;
    SoundPlayer *soundPlayer;
    
    void readFromEventFile();
    void readFile(std::string filepath);
    bool checkIfAllSwitchesSet();
    void initializeSwitches();
    void reinitializeSwitches(int start, int end);
};

#endif	/* EVENT_H */

