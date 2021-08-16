//
// Created by jlidou on 2021-08-12.
//

#ifndef DEMOFIRSTSDL_UTILS_H
#define DEMOFIRSTSDL_UTILS_H
#include <GL/gl.h>

class Utils {
public:
    static void drawAxis(float taille);
    static void drawQuads(float height, float lenght, float red, float green, float blue);
    static void drawQuadsHollow(float height, float lenght, float red, float green, float blue);
    static void drawCube(float tailleX, float tailleY, float tailleZ);
};
#endif //DEMOFIRSTSDL_UTILS_H