/* 
 * File:   Radio.h
 * Author: goofanader
 *
 * Created on February 12, 2013, 7:05 PM
 */

#ifndef RADIO_H
#define	RADIO_H

#include "GameObject.h"
#include "MeshLoader.h"

class Radio : public GameObject {
public:
    Radio();
    Radio(const Radio& orig);
    virtual ~Radio();
    void onEvent(SoundPlayer *soundPlayer);
    std::string className();
private:

};

#endif	/* RADIO_H */

