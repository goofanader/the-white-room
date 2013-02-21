/* 
 * File:   Table.h
 * Author: goofanader
 *
 * Created on February 21, 2013, 12:15 PM
 */

#ifndef TABLE_H
#define	TABLE_H

#include "GameObject.h"
#include "MeshLoader.h"

class Table : public GameObject {
public:
    Table();
    Table(const Table& orig);
    virtual ~Table();
    
    std::string className();
private:

};

#endif	/* TABLE_H */

