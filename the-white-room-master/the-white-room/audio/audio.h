#ifndef AUDIO_H
#define AUDIO_H

#include "FMOD/api/inc/fmod.hpp"
#include "FMOD/api/inc/fmod_errors.h"
#include "wincompat.h"
#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

void ERRCHECK(FMOD_RESULT result);

class SoundObject {
    public:
        FMOD::Sound *sound;
        virtual ~SoundObject();
        FMOD_RESULT loadSound(FMOD::System *soundSystem, string fileName);
};
class SoundPlayer {
    private:
        map<string, SoundObject*> soundMap;

        FMOD::System *soundSystem;
        FMOD::Channel *channel;
        SoundObject *object;

        vector<string> tokenize(const string &str, const string &delim);
        void fillMap(std::string listOfSounds);

    public:
        SoundPlayer(std::string listOfSounds);
        virtual ~SoundPlayer();

        void playSound(string sName);
        void playContinuous(string sName);
        void debug();
};

#endif
