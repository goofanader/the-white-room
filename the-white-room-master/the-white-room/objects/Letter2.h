/* 
 * File:   Letter2.h
 * Author: goofanader
 *
 * Created on June 7, 2013, 10:16 AM
 */

#ifndef LETTER2_H
#define	LETTER2_H

#include "GameObject.h"
#include "MeshLoader.h"

class Letter2 : public GameObject {
public:
    Letter2();
    Letter2(const Letter2& orig);
    virtual ~Letter2();
    
    std::string className();
private:

};

#endif	/* LETTER2_H */

