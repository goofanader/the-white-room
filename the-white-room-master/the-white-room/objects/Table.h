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
    void drawHighlight(glm::vec3 cameraPos, glm::vec3 lookAt, glm::vec3 lightPos, 
        glm::vec3 lightColor, GameConstants* gc);
    std::string className();
private:

};

#endif	/* TABLE_H */

