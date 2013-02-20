/* 
 * File:   MooseHead.h
 * Author: goofanader
 *
 * Created on February 19, 2013, 6:32 PM
 */

#ifndef MOOSEHEAD_H
#define	MOOSEHEAD_H

#include "GameObject.h"
#include "MeshLoader.h"

class MooseHead : public GameObject {
public:
    MooseHead();
    MooseHead(const MooseHead& orig);
    virtual ~MooseHead();
    std::string className();
private:

};

#endif	/* MOOSEHEAD_H */

