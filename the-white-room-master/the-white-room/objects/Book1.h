/* 
 * File:   Book1.h
 * Author: goofanader
 *
 * Created on February 14, 2013, 6:32 AM
 */

#ifndef BOOK1_H
#define	BOOK1_H

#include "GameObject.h"
#include "MeshLoader.h"

class Book1 : public GameObject {
public:
    Book1();
    Book1(const Book1& orig);
    virtual ~Book1();
    
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
private:

};

#endif	/* BOOK1_H */

