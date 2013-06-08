/* 
 * File:   Letter.h
 * Author: goofanader
 *
 * Created on June 7, 2013, 10:16 AM
 */

#ifndef LETTER1_H
#define	LETTER1_H

#include "GameObject.h"
#include "MeshLoader.h"

class Letter1 : public GameObject {
public:
    Letter1();
    Letter1(const Letter1& orig);
    virtual ~Letter1();
    
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
private:

};

#endif	/* LETTER1_H */

