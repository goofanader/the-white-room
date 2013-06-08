/* 
 * File:   Letter.h
 * Author: goofanader
 *
 * Created on June 7, 2013, 10:16 AM
 */

#ifndef LETTER_H
#define	LETTER_H

#include "GameObject.h"
#include "MeshLoader.h"

class Letter4 : public GameObject {
public:
    Letter4();
    Letter4(const Letter4& orig);
    virtual ~Letter4();
    
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
private:

};

#endif	/* LETTER_H */

