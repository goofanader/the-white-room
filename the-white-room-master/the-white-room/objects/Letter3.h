/* 
 * File:   Letter3.h
 * Author: goofanader
 *
 * Created on June 7, 2013, 10:16 AM
 */

#ifndef LETTER3_H
#define	LETTER3_H

#include "GameObject.h"
#include "MeshLoader.h"

class Letter3 : public GameObject {
public:
    Letter3();
    Letter3(const Letter3& orig);
    virtual ~Letter3();
    
    std::string className();
private:

};

#endif	/* LETTER3_H */

