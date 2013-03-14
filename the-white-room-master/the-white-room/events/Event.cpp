/* 
 * File:   Event.cpp
 * Author: Phyllis Douglas
 * 
 * Created on January 29, 2013, 10:07 PM
 */

#include "Event.h"
#include "ObjectCreation.h"
#include "objects/Knob100.h"
#include "objects/Knob10.h"
#include "objects/Safe.h"
#include "objects/HeartKey.h"
#include <iostream>
#include <sstream>
#include <stdio.h>

using namespace std;

/**
 * reminder to future Phyllis & other future selves:
 * this class should actually be the one to build the items in the room,
 * not the state class. The state class will keep track of which event is
 * currently underway, but not the items.
 * @param currentEventNum
 */
Event::Event(int currentEventNum, SoundPlayer *currSoundPlayer) {
    //cout << "creating a new event" << endl;
    //read from event file
    //eventNum = currentEventNum;
    soundPlayer = currSoundPlayer;

    initializeIndices();
    initializeSwitches();

    //readFromEventFile();
    readFile("events/loadObjects.txt");
}

void Event::initializeSwitches() {
    for (int i = 0; i < MAX_SWITCHES; i++) {
        eventSwitches[i].setClassName("");
        eventSwitches[i].setIsEmpty(true);
        eventSwitches[i].setSwitch(false);
    }
}

void Event::reinitializeSwitches(int start, int end) {
    for (int i = start; i < end; i++) {
        //eventSwitches[i].setIsEmpty(true);
        eventSwitches[i].setSwitch(false);
        //eventSwitches[i].getGameObject()->resetEvent(soundPlayer);
    }
}

void Event::readFromEventFile() {
    string dir, filepath;
    int num;
    DIR *dp;
    struct dirent *dirp;
    struct stat filestat;

    //cout << "dir to get files of: " << flush;
    //getline(cin, dir); // gets everything the user ENTERs

    dp = opendir("events/eventFiles");
    if (dp == NULL) {
        cout << "couldn't open folder" << endl;
        //cout << "Error(" << errno << ") opening " << dir << endl;
        //return errno;
    } else {

        bool isCorrectFile = false;

        while ((dirp = readdir(dp)) && !isCorrectFile) {
            filepath = dir + "/" + dirp->d_name;
            //cout << "dirp->d_name: " << dirp->d_name << endl;

            // If the file is a directory (or is in some way invalid) we'll skip it 
            //if (stat(filepath.c_str(), &filestat)) continue;
            //if (S_ISDIR(filestat.st_mode)) continue;
            //cout << "hello" << endl;

            string fileEventNum = "";

            for (int i = 0; (dirp->d_name[i] != '\0'); i++) {
                if (dirp->d_name[i] == '-') {
                    //istringstream convert(fileEventNum);

                    sscanf(fileEventNum.c_str(), "%d", &num);
                    //cout << "num: " << num << endl;

                    if (num == eventNum) {
                        isCorrectFile = true;
                        //printf("woof\n");
                        break;
                    }
                } else {
                    if (dirp->d_name[i] != '0')
                        fileEventNum += dirp->d_name[i];
                    //cout << "current fileNum: " << fileEventNum << endl;
                }
            }

            // Endeavor to read a single number from the file and display it
            //fin.open(filepath.c_str());
            //if (fin >> num)
            //  cout << filepath << ": " << num << endl;
            //fin.close();
        }

        if (isCorrectFile)
            readFile("events/eventFiles" + filepath);
        closedir(dp);

    }
}

void Event::readFile(std::string filepath) {
    cout << "reading " << filepath << endl;
    ifstream fin;
    int numSwitches = 0, itemCount = 0;
    std::string parsedString;

    fin.open(filepath.c_str());

    if (fin.is_open()) {
        //while (fin.good()) {
        while (fin) {
            getline(fin, parsedString);
            std::stringstream stream(parsedString);

            std::string label;
            stream >> label;

            if (label.find("#") != std::string::npos) {
                // Comment, skip
                continue;
            } else if (label == "numItems:") {
                stream >> numSwitches;
                //sscanf(parsedString.c_str(), "%d", &numSwitches);
                switchNum = numSwitches;
                //would initialize array to the number of switches, but
                //that's a little difficult right now at 5:20AM...

                //initializeSwitches();
            } else if (label == "create") {
                std::string item;
                stream >> item;

                setObjectIndex(item, itemCount);
                eventSwitches[itemCount].setClassName(item);
                eventSwitches[itemCount].setSwitch(false);
                eventSwitches[itemCount++].setIsEmpty(false);
            }
        }
        fin.close();
    } else
        cout << "Couldn't load file :(" << endl;
}

Event::Event(const Event& orig) {
}

Event::~Event() {
}

EventSwitch* Event::getSwitches() {
    return eventSwitches;
}

int Event::getSwitchNum() {
    return switchNum;
}

void Event::ifObjectSelected(GameObject *curr) {
    std::string name = curr->className();
    eventSwitches[BOOK1].setSwitch(true);
    eventSwitches[BOOK2].setSwitch(true);
    eventSwitches[BOOK3].setSwitch(true);
    eventSwitches[RADIO].setSwitch(true);

    eventSwitches[HEART].getGameObject()->isVisible = true;
    eventSwitches[SPADE].getGameObject()->isVisible = true;
    eventSwitches[DIAMOND].getGameObject()->isVisible = true;
    eventSwitches[CLUB].getGameObject()->isVisible = true;
    
    if (name != "Book1" && name != "Book2" && name != "Book3") {
        curr->onEvent(soundPlayer);
    }

    /*==================================================================
     * PUZZLE 1 LOGIC
     *==================================================================*/
    if (name == "Book3") {
        printf("clicked on Book3, index %d\n", BOOK3);
        eventSwitches[BOOK3].setSwitch(true);
        curr->isClicked = true;
        curr->onEvent(soundPlayer);
    } else if (name == "Book2" && eventSwitches[BOOK3].isSwitchOn()) {
        printf("clicked on Book2 in order, index %d\n", BOOK2);
        eventSwitches[BOOK2].setSwitch(true);
        curr->isClicked = true;
        curr->onEvent(soundPlayer);
    }//Got it in order! Move to the next puzzle.
    else if (name == "Book1" && eventSwitches[BOOK3].isSwitchOn() &&
            eventSwitches[BOOK2].isSwitchOn()) {
        printf("clicked on Book1 in order, index %d\n", BOOK1);

        if (!eventSwitches[BOOK1].isSwitchOn())
            soundPlayer->playSound("RadioAppear2");


        eventSwitches[BOOK1].setSwitch(true);
        curr->isClicked = true;
        curr->onEvent(soundPlayer);

        eventSwitches[KNOB10].getGameObject()->isClicked = true;
        eventSwitches[KNOB10].getGameObject()->isVisible = true;
        eventSwitches[KNOB100].getGameObject()->isClicked = true;
        eventSwitches[KNOB100].getGameObject()->isVisible = true;
        eventSwitches[RADIO].getGameObject()->isClicked = true;
    }//Got the book order wrong, reset.
    else if ((name == "Book2" && !eventSwitches[BOOK3].isSwitchOn()) ||
            (name == "Book1" && !(eventSwitches[BOOK3].isSwitchOn() &&
            eventSwitches[BOOK2].isSwitchOn()))) {
        curr->onEvent(soundPlayer);

        reinitializeSwitches(BOOK1, BOOK1 + 1);
        reinitializeSwitches(BOOK2, BOOK2 + 1);
        reinitializeSwitches(BOOK3, BOOK3 + 1);
        reinitializeSwitches(WHITE_DOOR, WHITE_DOOR + 1);
        printf("oh no! out of order :(\n");
    }

    /*==================================================================
     * PUZZLE 2 LOGIC
     *==================================================================*/
    if (eventSwitches[BOOK1].isSwitchOn() && !eventSwitches[RADIO].isSwitchOn()) {
        if (name == "Knob100" || name == "Knob10") {
            Knob100 *bigKnob = (Knob100*) eventSwitches[KNOB100].getGameObject();
            Knob10 *smallKnob = (Knob10*) eventSwitches[KNOB10].getGameObject();

            int station = bigKnob->getStation() + smallKnob->getStation();

            printf("station=%d\n", station);
            if (station == 610) {
                eventSwitches[RADIO].setSwitch(true);

                eventSwitches[KNOB100].getGameObject()->isClicked = false;
                eventSwitches[KNOB10].getGameObject()->isClicked = false;

                eventSwitches[HEART].getGameObject()->isVisible = true;
                eventSwitches[SPADE].getGameObject()->isVisible = true;
                eventSwitches[DIAMOND].getGameObject()->isVisible = true;
                eventSwitches[CLUB].getGameObject()->isVisible = true;

                Safe *temp = (Safe*) (eventSwitches[SAFE].getGameObject());
                temp->isOpen = true;
            }
        }
    }

    /*==================================================================
     * PUZZLE 3 LOGIC
     *==================================================================*/
    if (eventSwitches[BOOK1].isSwitchOn() && eventSwitches[RADIO].isSwitchOn()) {
        if (curr->className() == "HeartKey") {
            HeartKey *temp = (HeartKey *)curr;
            
            temp->isHeld = true;
        }
#if 0
        setIfWon(true);
        //cause the white door to open
        if (!eventSwitches[WHITE_DOOR].isSwitchOn()) {
            eventSwitches[WHITE_DOOR].getGameObject()->onEvent(soundPlayer);
            eventSwitches[WHITE_DOOR].setSwitch(true);
        }
#endif
    }
}

bool Event::setSwitch(std::string className) {
    bool classExists = false;

    for (int i = 0; i < switchNum; i++) {
        if (eventSwitches[i].getClassName() == className) {
            classExists = true;
            break;
        }
    }

    if (classExists) {
        if (isEventOrdered) {
            for (int i = 0; i < switchNum; i++) {
                if (eventSwitches[i].isUninitialized()) {
                    if (eventSwitches[i].getClassName() != className) {
                        reinitializeSwitches(0, switchNum);
                        return false;
                    } else if (eventSwitches[i].getClassName() == className) {
                        eventSwitches[i].setSwitch(true);
                        eventSwitches[i].setIsEmpty(false);
                        eventSwitches[i].getGameObject()->onEvent(soundPlayer);

                        return checkIfAllSwitchesSet();
                    }
                    return false;
                } else if (!eventSwitches[i].isUninitialized() &&
                        eventSwitches[i].getClassName() == className) {
                    return false;
                }
            }
        } else {
            for (int i = 0; i < switchNum; i++) {
                if (eventSwitches[i].getClassName() == className) {
                    //something
                    eventSwitches[i].setSwitch(true);
                    eventSwitches[i].setIsEmpty(false);
                    eventSwitches[i].getGameObject()->onEvent(soundPlayer);

                    return checkIfAllSwitchesSet();
                }
            }
        }
    }

    //cout << "switch class name fail" << endl;

    return false;
}

bool Event::checkIfAllSwitchesSet() {
    for (int i = 0; i < switchNum; i++) {
        if (!eventSwitches[i].isSwitchOn()) {
            return false;
        }
    }

    return true;
}

int Event::getEventNum() {
    return eventNum;
}
