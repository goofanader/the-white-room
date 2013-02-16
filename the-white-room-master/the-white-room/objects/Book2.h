/* 
 * File:   Book2.h
 * Author: goofanader
 *
 * Created on February 14, 2013, 6:32 AM
 */

#ifndef BOOK2_H
#define	BOOK2_H

#include "GameObject.h"
#include "MeshLoader.h"

class Book2 : public GameObject {
public:
    Book2();
    Book2(const Book2& orig);
    virtual ~Book2();
    
    std::string className();
    void onEvent(SoundPlayer *soundPlayer);
private:

};

#endif	/* BOOK1_H */

