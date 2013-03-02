#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

FMOD_RESULT       result;

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf(
          "FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}


SoundObject::~SoundObject() {
    result = sound->release();
    ERRCHECK(result);
}

FMOD_RESULT SoundObject::loadSound(
        FMOD::System *soundSystem, string fileName) {
    return soundSystem->createSound(fileName.c_str(), FMOD_3D, 0,
            &sound);
}

    
//let C++ hold our hands and essentially cut the string for us...
//C++ coders don't have to deal with char ** or even char *** for
//tokenizing....makes me sad. Though, the code is a lot cleaner
vector<string> SoundPlayer::tokenize(const string &str, const string &delim) {
    vector<string> tokens;
    size_t p0 = 0, p1 = string::npos;

    while(p0 != string::npos) {
        //set p1 to the offset of the first occurence of the 
        //delim pattern in str, starting from offset p0
        p1 = str.find_first_of(delim, p0);
        if (p1 != p0) {
            //create a string from p0 to p1
            string token = str.substr(p0, p1-p0);
            tokens.push_back(token);
        }

        //set p0 to the offset of the first character not in a 
        //series of delim patterns
        p0 = str.find_first_not_of(delim, p1);
    }

    return tokens;
}


void SoundPlayer::fillMap(std::string listOfSounds) {
    ifstream soundFile;
    string in;
    soundFile.open(listOfSounds.c_str());

    if (soundFile.is_open()) {
        while (soundFile.good()) {
            vector<string> tokens;
            getline(soundFile, in);
            if (in != "") {
                tokens = tokenize(in, ":");
                cout << tokens[0] << endl << tokens[1] << endl;
                object = new SoundObject();
                result = object->loadSound(soundSystem, tokens[1]);
                ERRCHECK(result);

                soundMap[tokens[0]] = object;
            }
        }

        soundFile.close();
    }
    else cout << "Unable to open file\n";
}

SoundPlayer::SoundPlayer(std::string listOfSounds) {
    int               key;
    unsigned int      version;

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&soundSystem);
    ERRCHECK(result);

    result = soundSystem->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        printf("Error! You are using an old version of FMOD %08x."
          " This program requires %08x\n", version, FMOD_VERSION);
        getch();
        return;
    }

    //result = soundSystem->setOutput(FMOD_OUTPUTTYPE_ALSA);
    //ERRCHECK(result);
    
    result = soundSystem->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);
    
    fillMap(listOfSounds);
}

SoundPlayer::~SoundPlayer() {
    for (std::map<string, SoundObject*>::iterator it = soundMap.begin();
        it != soundMap.end(); ++it) {
        delete it->second;
    }
    soundMap.clear();

    result = soundSystem->close();
    ERRCHECK(result);
    result = soundSystem->release();
    ERRCHECK(result);
}


void SoundPlayer::playSound(string sName) {
    if(soundMap.find(sName) != soundMap.end()) {
        //the "true" variable pauses the sound and prevents it from playing
        //we use this to set up the channel
        result = soundSystem->playSound(FMOD_CHANNEL_FREE, 
                soundMap[sName]->sound, true, &channel);
        ERRCHECK(result);
        ERRCHECK(channel->setPaused(false));
    }
}

void SoundPlayer::playContinuous(string sName) {
    if(soundMap.find(sName) != soundMap.end()) {
        soundMap[sName]->sound->setMode(FMOD_LOOP_NORMAL);
        result = soundSystem->playSound(FMOD_CHANNEL_FREE, 
                soundMap[sName]->sound, true, &channel);
        ERRCHECK(result);
        ERRCHECK(channel->setPaused(false));
    }
}


void SoundPlayer::debug() {
    for(map<string, SoundObject*>::iterator it = soundMap.begin();
            it != soundMap.end(); ++it) {
        cout << it->first << endl;
    }
}
