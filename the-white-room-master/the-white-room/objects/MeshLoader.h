/* 
 * File:   MeshLoader.h
 * Author: goofanader
 *
 * Created on February 3, 2013, 3:54 PM
 */

#ifndef MESHLOADER_H
#define	MESHLOADER_H

#ifdef __APPLE__
#include "GLUT/glut.h"
#include <OPENGL/gl.h>
#endif

#ifdef __unix__
#include <GL/glut.h>
#endif

#ifdef _WIN32
#include <GL\glew.h>
#include <GL\glut.h>
#endif

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class CMesh;

class MeshLoader {
    
public:
    static CMesh * const loadObjMesh(std::string const &fileName);
    /*static bool loadVertexBufferObjectFromMesh(std::string const &fileName,
            int &triangleCount, GLuint &positionBuff, GLuint &colorBuff, 
            GLuint &vertexNormalBuff);*/

    static bool loadVertexBufferObjectFromMesh(std::string const &fileName,
            int &triangleCount, GLuint &positionBuff, GLuint &indexBuff,
            GLuint &vertexNormalBuff, GLuint &textureBuff, glm::vec3 &AABBmin,
            glm::vec3 &AABBmax);
};

#endif	/* MESHLOADER_H */

