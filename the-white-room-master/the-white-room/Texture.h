#include <GL/glfw.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef struct {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
} Image;

typedef struct {
    GLubyte r, g, b;
} RGB;

static unsigned int getint(FILE *fp);
static unsigned int getshort(FILE *fp);

GLvoid LoadTexture(char *image_file, int texID);
GLvoid LoadNonMipmap(char *image_file, int texID);

int ImageLoad(char *filename, Image *image);
