/* 
 * File:   Event.cpp
 * Author: Phyllis Douglas
 * 
 * Created on January 29, 2013, 10:07 PM
 */

#include "Event.h"
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
    cout << "creating a new event" << endl;
    //read from event file
    eventNum = currentEventNum;
    soundPlayer = currSoundPlayer;

    initializeSwitches();

    readFromEventFile();
}

void Event::initializeSwitches() {
    for (int i = 0; i < MAX_SWITCHES; i++) {
        eventSwitches[i].setClassName("");
        eventSwitches[i].setIsEmpty(true);
        eventSwitches[i].setSwitch(false);
    }
}

void Event::reinitializeSwitches() {
    for (int i = 0; i < switchNum; i++) {
        eventSwitches[i].setIsEmpty(true);
        eventSwitches[i].setSwitch(false);
        eventSwitches[i].getGameObject()->resetEvent(soundPlayer);
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
    cout << "reading .evt file " << filepath << endl;
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
            }

            if (label == "ordered:") {
                std::string choice;
                stream >> choice;

                if (choice == "no") {
                    isEventOrdered = false;
                } else {
                    isEventOrdered = true;
                }
            } else if (label == "timed:") {
                std::string choice;
                stream >> choice;

                if (choice == "no")
                    isEventTimed = false;
                else
                    isEventTimed = true;
            }
            else if (label == "numItems:") {
                stream >> numSwitches;
                //sscanf(parsedString.c_str(), "%d", &numSwitches);
                switchNum = numSwitches;
                //would initialize array to the number of switches, but
                //that's a little difficult right now at 5:20AM...

                initializeSwitches();
            }
            else if (label == "create") {
                std::string item;
                stream >> item;
                
                eventSwitches[itemCount].setClassName(item);
                eventSwitches[itemCount].setSwitch(false);
                eventSwitches[itemCount++].setIsEmpty(true);
            } else if (label == "skipCreate") {
                std::string item;
                stream >> item;
                eventSwitches[itemCount].setClassName(item);
                eventSwitches[itemCount].setSwitch(true);
                eventSwitches[itemCount++].setIsEmpty(false);
                
                std::cout << "Line: " << item << std::endl;
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
                        reinitializeSwitches();
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