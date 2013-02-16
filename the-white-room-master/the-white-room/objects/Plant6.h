/* 
 * File:   Plant6.h
 * Author: goofanader
 *
 * Created on February 13, 2013, 12:36 PM
 */

#ifndef PLANT6_H
#define	PLANT6_H

#include "GameObject.h"
#include "MeshLoader.h"

class Plant6 : public GameObject {
public:
    Plant6();
    Plant6(const Plant6& orig);
    virtual ~Plant6();
    std::string className();
private:

};

#endif	/* PLANT6_H */

