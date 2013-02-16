/* 
 * File:   Book3.h
 * Author: goofanader
 *
 * Created on February 14, 2013, 6:32 AM
 */

#ifndef BOOK3_H
#define	BOOK3_H

#include "GameObject.h"
#include "MeshLoader.h"

class Book3 : public GameObject {
public:
    Book3();
    Book3(const Book3& orig);
    virtual ~Book3();
    
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
private:

};

#endif	/* BOOK3_H */

