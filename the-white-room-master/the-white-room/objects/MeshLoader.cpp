/* 
 * File:   MeshLoader.cpp
 * Author: goofanader
 * 
 * Created on February 3, 2013, 3:54 PM
 */
#if 1
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <string>
#include <streambuf>

#include "MeshLoader.h"

#define SCALE_SIZE 2 //1???
#define CENTER_SIZE 0
#define MAX_POINTS 4

class SColor {
public:

    float red, green, blue;

    SColor()
    : red(0.7f), green(0.7f), blue(0.7f) {
    }

};

class SVector3 {
public:

    float x, y, z;

    SVector3()
    : x(0), y(0), z(0) {
    }

    SVector3(float in)
    : x(in), y(in), z(in) {
    }

    SVector3(float in_x, float in_y, float in_z)
    : x(in_x), y(in_y), z(in_z) {
    }

    SVector3 crossProduct(SVector3 const & v) const {
        return SVector3(y * v.z - v.y*z, v.x * z - x * v.z, x * v.y - v.x * y);
    }

    float dotProduct(SVector3 const & v) const {
        return x * v.x + y * v.y + z * v.z;
    }

    float length() const {
        return sqrtf(x * x + y * y + z * z);
    }

    SVector3 operator +(SVector3 const & v) const {
        return SVector3(x + v.x, y + v.y, z + v.z);
    }

    SVector3 & operator +=(SVector3 const & v) {
        x += v.x;
        y += v.y;
        z += v.z;

        return * this;
    }

    SVector3 operator -(SVector3 const & v) const {
        return SVector3(x - v.x, y - v.y, z - v.z);
    }

    SVector3 & operator -=(SVector3 const & v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return * this;
    }

    SVector3 operator *(SVector3 const & v) const {
        return SVector3(x * v.x, y * v.y, z * v.z);
    }

    SVector3 & operator *=(SVector3 const & v) {
        x *= v.x;
        y *= v.y;
        z *= v.z;

        return * this;
    }

    SVector3 operator /(SVector3 const & v) const {
        return SVector3(x / v.x, y / v.y, z / v.z);
    }

    SVector3 & operator /=(SVector3 const & v) {
        x /= v.x;
        y /= v.y;
        z /= v.z;

        return * this;
    }

    SVector3 operator *(float const s) const {
        return SVector3(x*s, y*s, z * s);
    }

    SVector3 & operator *=(float const s) {
        x *= s;
        y *= s;
        z *= s;

        return * this;
    }

    SVector3 operator /(float const s) const {
        return SVector3(x / s, y / s, z / s);
    }

    SVector3 & operator /=(float const s) {
        x /= s;
        y /= s;
        z /= s;

        return * this;
    }

};

class SVertex {
public:

    SVector3 position;
    SColor color;

};

class CMesh {
    friend class CVertexBufferObject;
    friend class MeshLoader;

    struct STriangle {
        unsigned int vertexIndex1, vertexIndex2, vertexIndex3;
        unsigned int textureIndex1, textureIndex2, textureIndex3;
        unsigned int normalIndex1, normalIndex2, normalIndex3;
        SColor color;
    };

    std::vector<SVertex> vertices;
    std::vector<SVertex> textures;
    std::vector<SVertex> normals;
    std::vector<STriangle> vertexFaces;

    bool hasVertices, hasTextures, hasNormals;
    
    CMesh();

public:

    ~CMesh();

    void centerMeshByAverage(SVector3 const &centerLocation);
    void centerMeshByExtents(SVector3 const &centerLocation);

    void resizeMesh(SVector3 const &scale);

};
/*
bool MeshLoader::loadVertexBufferObjectFromMesh(std::string const &fileName,
        int &triangleCount, GLuint &positionBuff, GLuint &colorBuff,
        GLuint &vertexNormalBuff) {
    GLuint* temp = -1;
    return loadVertexBufferObjectFromMesh(fileName, triangleCount, positionBuff,
            colorBuff, vertexNormalBuff, *temp);
}*/

bool MeshLoader::loadVertexBufferObjectFromMesh(std::string const &fileName,
        int &triangleCount, GLuint &positionBuff, GLuint &indexBuff,
        GLuint &vertexNormalBuff, GLuint &textureBuff, glm::vec3 &AABBmin,
        glm::vec3 &AABBmax) {

    CMesh *mesh = loadObjMesh(fileName);
    if (!mesh)
        return false;

    //ADD code to resize the mesh and to reposition it at the origin
    mesh->resizeMesh(SVector3(SCALE_SIZE));
    mesh->centerMeshByAverage(SVector3(CENTER_SIZE));

    triangleCount = mesh->vertexFaces.size() * 3;// * 2;

    int count = 0;

    float posArr[mesh->vertexFaces.size() * 3 * 4];
    float normFaceArr[mesh->vertexFaces.size() * 3 * 4];
    float smoothArr[mesh->vertexFaces.size() * 3 * 4];
    float colArr[mesh->vertexFaces.size() * 3 * 4];

        if (/*!mesh->hasNormals*/false) {
        SVector3 normVertArr[mesh->vertices.size()];

        for (int i = 0; i < mesh->vertices.size(); i++) {
            normVertArr[i] = SVector3(0);
        }

        //build normals per vertex
        for (int i = 0; i < mesh->vertexFaces.size(); i++) {
            SVector3 a = mesh->vertices[
                mesh->vertexFaces[i].vertexIndex2].position -
                mesh->vertices[mesh->vertexFaces[i].vertexIndex1].position;
            SVector3 b = mesh->vertices[
                mesh->vertexFaces[i].vertexIndex3].position -
                mesh->vertices[mesh->vertexFaces[i].vertexIndex1].position;

            SVector3 cross = a.crossProduct(b);

            normVertArr[mesh->vertexFaces[i].vertexIndex1] += 
                cross / (float) cross.length();
            normVertArr[mesh->vertexFaces[i].vertexIndex2] += 
                cross / (float) cross.length();
            normVertArr[mesh->vertexFaces[i].vertexIndex3] += 
                cross / (float) cross.length();
        }


        //build the VBO and Normals (which is in the color buffer. I should change that)
        for (int i = 0; i < mesh->vertexFaces.size() * 3 * 4; i++) {
            SVector3 a = mesh->vertices[
              mesh->vertexFaces[count].vertexIndex2].position - 
              mesh->vertices[mesh->vertexFaces[count].vertexIndex1].position;
            SVector3 b = mesh->vertices[
              mesh->vertexFaces[count].vertexIndex3].position -
              mesh->vertices[mesh->vertexFaces[count].vertexIndex1].position;

            SVector3 cross = a.crossProduct(b);

            normFaceArr[i] = cross.x / (float) cross.length();
            smoothArr[i] = 
                normVertArr[mesh->vertexFaces[count].vertexIndex1].x;
            colArr[i] = mesh->vertexFaces.at(count).color.red;
            posArr[i++] = mesh->vertices.at(
                    mesh->vertexFaces.at(count).vertexIndex1).position.x;

            normFaceArr[i] = cross.y / (float) cross.length();
            smoothArr[i] = normVertArr[
                mesh->vertexFaces[count].vertexIndex1].y;
            colArr[i] = mesh->vertexFaces.at(count).color.green;
            posArr[i++] = mesh->vertices.at(
                    mesh->vertexFaces.at(count).vertexIndex1).position.y;

            normFaceArr[i] = cross.z / (float) cross.length();
            smoothArr[i] = normVertArr[
                mesh->vertexFaces[count].vertexIndex1].z;
            colArr[i] = mesh->vertexFaces.at(count).color.blue;
            posArr[i++] = mesh->vertices.at(
                    mesh->vertexFaces.at(count).vertexIndex1).position.z;

            normFaceArr[i] = smoothArr[i] = 0.0;
            colArr[i] = posArr[i++] = 1.0;


            normFaceArr[i] = cross.x / (float) cross.length();
            smoothArr[i] = normVertArr[
                mesh->vertexFaces[count].vertexIndex2].x;
            posArr[i++] = mesh->vertices.at(
                    mesh->vertexFaces.at(count).vertexIndex2).position.x;

            normFaceArr[i] = cross.y / (float) cross.length();
            smoothArr[i] = normVertArr[
                mesh->vertexFaces[count].vertexIndex2].y;
            posArr[i++] = mesh->vertices.at(
                mesh->vertexFaces.at(count).vertexIndex2).position.y;

            normFaceArr[i] = cross.z / (float) cross.length();
            smoothArr[i] = normVertArr[
                mesh->vertexFaces[count].vertexIndex2].z;
            posArr[i++] = mesh->vertices.at(
                mesh->vertexFaces.at(count).vertexIndex2).position.z;

            normFaceArr[i] = smoothArr[i] = 0.0;
            colArr[i] = posArr[i++] = 1.0;


            normFaceArr[i] = cross.x / (float) cross.length();
            smoothArr[i] = normVertArr[
                mesh->vertexFaces[count].vertexIndex3].x;
            posArr[i++] = mesh->vertices.at(
                    mesh->vertexFaces.at(count).vertexIndex3).position.x;

            normFaceArr[i] = cross.y / (float) cross.length();
            smoothArr[i] = normVertArr[
                mesh->vertexFaces[count].vertexIndex3].y;
            posArr[i++] = mesh->vertices.at(
                    mesh->vertexFaces.at(count).vertexIndex3).position.y;

            normFaceArr[i] = cross.z / (float) cross.length();
            smoothArr[i] = normVertArr[
                mesh->vertexFaces[count].vertexIndex3].z;
            posArr[i++] = mesh->vertices.at(
                mesh->vertexFaces.at(count++).vertexIndex3).position.z;

            normFaceArr[i] = smoothArr[i] = 0.0;
            colArr[i] = posArr[i] = 1.0;
        }
    }
    unsigned short indexArr[mesh->vertexFaces.size() * 3];
    float fixNormArr[mesh->vertexFaces.size() * 3 * 3];
    float fixVertexArr[mesh->vertexFaces.size() * 3 * 3];
    float texArr[mesh->vertexFaces.size() * 3 * 2];
    
    SVector3 min, max;
    
    //redo the IBO so the VBO and NBO are linked correctly
    int arrIndex = 0, indexCounter = 0, texIndex = 0;
    for (int i = 0; i < mesh->vertexFaces.size(); i++) {
        if (i == 0) {
            max.x = min.x = mesh->vertices[
                mesh->vertexFaces[i].vertexIndex1].position.x;
            max.y = min.y = mesh->vertices[
                mesh->vertexFaces[i].vertexIndex1].position.y;
            max.z = min.z = mesh->vertices[
                mesh->vertexFaces[i].vertexIndex1].position.z;
        }
        
        fixVertexArr[arrIndex] = 
            mesh->vertices[mesh->vertexFaces[i].vertexIndex1].position.x;
        if (min.x > fixVertexArr[arrIndex])
            min.x = fixVertexArr[arrIndex];
        if (max.x < fixVertexArr[arrIndex])
            max.x = fixVertexArr[arrIndex];
        texArr[texIndex++] = 
                mesh->textures[mesh->vertexFaces[i].textureIndex1].position.x;
        fixNormArr[arrIndex++] = 
            mesh->normals[mesh->vertexFaces[i].normalIndex1].position.x;
        
        fixVertexArr[arrIndex] = 
            mesh->vertices[mesh->vertexFaces[i].vertexIndex1].position.y;
        if (min.y > fixVertexArr[arrIndex])
            min.y = fixVertexArr[arrIndex];
        if (max.y < fixVertexArr[arrIndex])
            max.y = fixVertexArr[arrIndex];
        texArr[texIndex++] = mesh->textures[
            mesh->vertexFaces[i].textureIndex1].position.y;
        fixNormArr[arrIndex++] = 
            mesh->normals[mesh->vertexFaces[i].normalIndex1].position.y;
        
        fixVertexArr[arrIndex] = 
            mesh->vertices[mesh->vertexFaces[i].vertexIndex1].position.z;
        if (min.z > fixVertexArr[arrIndex])
            min.z = fixVertexArr[arrIndex];
        if (max.z < fixVertexArr[arrIndex])
            max.z = fixVertexArr[arrIndex];
        fixNormArr[arrIndex++] = 
            mesh->normals[mesh->vertexFaces[i].normalIndex1].position.z;
        indexArr[indexCounter++] = indexCounter;
        //-------------
        fixVertexArr[arrIndex] = 
            mesh->vertices[mesh->vertexFaces[i].vertexIndex2].position.x;
        if (min.x > fixVertexArr[arrIndex])
            min.x = fixVertexArr[arrIndex];
        if (max.x < fixVertexArr[arrIndex])
            max.x = fixVertexArr[arrIndex];
        texArr[texIndex++] = mesh->textures[
            mesh->vertexFaces[i].textureIndex2].position.x;
        fixNormArr[arrIndex++] = 
            mesh->normals[mesh->vertexFaces[i].normalIndex2].position.x;
        
        fixVertexArr[arrIndex] = 
            mesh->vertices[mesh->vertexFaces[i].vertexIndex2].position.y;
        if (min.y > fixVertexArr[arrIndex])
            min.y = fixVertexArr[arrIndex];
        if (max.y < fixVertexArr[arrIndex])
            max.y = fixVertexArr[arrIndex];
        texArr[texIndex++] = mesh->textures[
            mesh->vertexFaces[i].textureIndex2].position.y;
        fixNormArr[arrIndex++] = 
            mesh->normals[mesh->vertexFaces[i].normalIndex2].position.y;
        
        fixVertexArr[arrIndex] = 
            mesh->vertices[mesh->vertexFaces[i].vertexIndex2].position.z;
        if (min.z > fixVertexArr[arrIndex])
            min.z = fixVertexArr[arrIndex];
        if (max.z < fixVertexArr[arrIndex])
            max.z = fixVertexArr[arrIndex];
        fixNormArr[arrIndex++] = 
            mesh->normals[mesh->vertexFaces[i].normalIndex2].position.z;
        indexArr[indexCounter++] = indexCounter;
        //-------------
        fixVertexArr[arrIndex] = 
            mesh->vertices[mesh->vertexFaces[i].vertexIndex3].position.x;
        if (min.x > fixVertexArr[arrIndex])
            min.x = fixVertexArr[arrIndex];
        if (max.x < fixVertexArr[arrIndex])
            max.x = fixVertexArr[arrIndex];
        texArr[texIndex++] = mesh->textures[
            mesh->vertexFaces[i].textureIndex3].position.x;
        fixNormArr[arrIndex++] = 
            mesh->normals[mesh->vertexFaces[i].normalIndex3].position.x;
        
        fixVertexArr[arrIndex] = 
            mesh->vertices[mesh->vertexFaces[i].vertexIndex3].position.y;
        if (min.y > fixVertexArr[arrIndex])
            min.y = fixVertexArr[arrIndex];
        if (max.y < fixVertexArr[arrIndex])
            max.y = fixVertexArr[arrIndex];
        texArr[texIndex++] = 
                mesh->textures[mesh->vertexFaces[i].textureIndex3].position.y;
        fixNormArr[arrIndex++] = 
            mesh->normals[mesh->vertexFaces[i].normalIndex3].position.y;
        
        fixVertexArr[arrIndex] = 
            mesh->vertices[mesh->vertexFaces[i].vertexIndex3].position.z;
        if (min.z > fixVertexArr[arrIndex])
            min.z = fixVertexArr[arrIndex];
        if (max.z < fixVertexArr[arrIndex])
            max.z = fixVertexArr[arrIndex];
        fixNormArr[arrIndex++] = 
            mesh->normals[mesh->vertexFaces[i].normalIndex3].position.z;
        indexArr[indexCounter++] = indexCounter;
    }
    
    glGenBuffers(1, &positionBuff);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuff);
    glBufferData(
        GL_ARRAY_BUFFER, sizeof(fixVertexArr), fixVertexArr, GL_STATIC_DRAW);
    
    glGenBuffers(1, &indexBuff);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuff);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArr), indexArr, GL_STATIC_DRAW);
    
    glGenBuffers(1, &vertexNormalBuff);
    glBindBuffer(GL_ARRAY_BUFFER, vertexNormalBuff);
    glBufferData(
        GL_ARRAY_BUFFER, sizeof(fixNormArr), fixNormArr, GL_STATIC_DRAW);

    glGenBuffers(1, &textureBuff);
    glBindBuffer(GL_ARRAY_BUFFER, textureBuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texArr), texArr, GL_STATIC_DRAW);
    
    float buffer = 0.f;//.9f;
    AABBmin.x = min.x + buffer;
    AABBmin.y = min.y + buffer;
    AABBmin.z = min.z + buffer;
    
    AABBmax.x = max.x - buffer;
    AABBmax.y = max.y - buffer;
    AABBmax.z = max.z - buffer;
    
    return true;
}

CMesh * const MeshLoader::loadObjMesh(std::string const &fileName) {

    std::ifstream file;
    file.open(fileName.c_str());

    if (!file.is_open()) {
        std::cerr << "Unable to open mesh file: " << fileName << std::endl;
        return 0;
    }

    CMesh * mesh = new CMesh();

    bool hasVertices = false, hasTextures = false, hasNormals = false;
    
    while (file) {
        std::string readString;
        std::getline(file, readString);
        
        int stringLen = readString.size();
        
        if (readString[stringLen - 1] == ' ') {
            readString.resize(stringLen - 1);
        }

        std::stringstream stream(readString);

        std::string label;
        stream >> label;

        if (label.find("#") != std::string::npos) {
            // Comment, skip
            continue;
        }

        if ("g" == label) {
        }//don't do anything right now
        else if ("usemtl" == label) {
        }//don't do anything right now
        else if ("v" == label) //add vertices
        {
            hasVertices = true;
            mesh->hasVertices = true;

            SVector3 position;
            stream >> position.x;
            stream >> position.y;
            stream >> position.z;

            SVertex vertex;
            vertex.position = position;

            mesh->vertices.push_back(vertex);
        } else if ("vt" == label) {
            hasTextures = true;
            mesh->hasTextures = true;

            SVector3 texturePosition;
            stream >> texturePosition.x;
            stream >> texturePosition.y;

            SVertex texture;
            texture.position = texturePosition;

            mesh->textures.push_back(texture);
        } else if ("vn" == label) {
            //take normals from file, don't generate them here
            hasNormals = true;
            mesh->hasNormals = true;

            SVector3 normalPosition;
            stream >> normalPosition.x;
            stream >> normalPosition.y;
            stream >> normalPosition.z;

            SVertex normal;
            normal.position = normalPosition;

            mesh->normals.push_back(normal);
        } else if ("f" == label) //align faces
        {
            int vertex[MAX_POINTS + 1], texture[MAX_POINTS + 1],
                    normal[MAX_POINTS + 1];

            int number, numVertices;
            char slash;

            for (numVertices = 0; !stream.eof(); numVertices++) {
                if (hasVertices) {
                    stream >> number;
                    //std::cout << number;
                    vertex[numVertices] = number;
                }
                if (hasTextures || hasNormals) {
                    stream >> slash;
                    //std::cout << slash;
                }
                if (hasTextures) {
                    stream >> number;
                    //std::cout << number;
                    texture[numVertices] = number;
                }
                if (hasNormals) {
                    stream >> slash;
                    //std::cout << slash;
                    stream >> number;
                    //std::cout << number;
                    normal[numVertices] = number;
                }
                //std::cout << " ";
            }

            CMesh::STriangle triangle;
            CMesh::STriangle fixQuad;

            if (hasVertices) {
                triangle.vertexIndex1 = vertex[0] - 1;
                triangle.vertexIndex2 = vertex[1] - 1;
                triangle.vertexIndex3 = vertex[2] - 1;
            }
            if (hasTextures) {
                triangle.textureIndex1 = texture[0] - 1;
                triangle.textureIndex2 = texture[1] - 1;
                triangle.textureIndex3 = texture[2] - 1;
            }
            if (hasNormals) {
                triangle.normalIndex1 = normal[0] - 1;
                triangle.normalIndex2 = normal[1] - 1;
                triangle.normalIndex3 = normal[2] - 1;
            }

            mesh->vertexFaces.push_back(triangle);

            //if the .obj is in quads instead of triangles
            if (numVertices == MAX_POINTS) {
                if (hasVertices) {
                    fixQuad.vertexIndex1 = vertex[2] - 1;
                    fixQuad.vertexIndex2 = vertex[3] - 1;
                    fixQuad.vertexIndex3 = vertex[0] - 1;
                }
                if (hasTextures) {
                    fixQuad.textureIndex1 = texture[2] - 1;
                    fixQuad.textureIndex2 = texture[3] - 1;
                    fixQuad.textureIndex3 = texture[0] - 1;
                }
                if (hasNormals) {
                    fixQuad.normalIndex1 = normal[2] - 1;
                    fixQuad.normalIndex2 = normal[3] - 1;
                    fixQuad.normalIndex3 = normal[0] - 1;
                }

                mesh->vertexFaces.push_back(fixQuad);
            }

            //std::cout << std::endl;
        } else if ("" == label) {
            // Just a new line, carry on...
        } else {
            //std::cerr << "While parsing ASCII mesh: "
              //      "Expected .obj label, found '" << label << "'." << std::endl;
            //basically something I haven't handled yet.
        }
    }

    if (!mesh->vertexFaces.size() || !mesh->vertices.size()) {
        delete mesh;
        return 0;
    }

    return mesh;
}

CMesh::CMesh() {
}

CMesh::~CMesh() {
}

void CMesh::centerMeshByAverage(SVector3 const &centerLocation) {
    SVector3 average;

    for (int i = 0; i < vertices.size(); i++) {
        average += vertices.at(i).position;
    }

    average /= (float) vertices.size();
    SVector3 offset = centerLocation - average;

    for (int i = 0; i < vertices.size(); i++) {
        vertices.at(i).position += offset;
    }
}

void CMesh::centerMeshByExtents(SVector3 const &centerLocation) {
    //ADD
}

void CMesh::resizeMesh(SVector3 const &scale) {
    if (vertices.size() < 2)
        return;

    SVector3 min = vertices.at(0).position, max = vertices.at(0).position;

    for (int i = 0; i < vertices.size(); i++) {
        SVector3 temp = vertices.at(i).position;

        if (min.x > temp.x)
            min.x = temp.x;
        if (min.y > temp.y)
            min.y = temp.y;
        if (min.z > temp.z)
            min.z = temp.z;

        if (max.x < temp.x)
            max.x = temp.x;
        if (max.y < temp.y)
            max.y = temp.y;
        if (max.z < temp.z)
            max.z = temp.z;
    }

    SVector3 extent = (max - min);
    SVector3 resize = scale / std::max(extent.x, std::max(extent.y, extent.z));

    for (int i = 0; i < vertices.size(); i++) {
        vertices.at(i).position *= resize;
    }
}

#endif
