//
// Created by Administrator on 18/08/2021.
//

#ifndef TP_BATTLEARENA_CHAMPIGNON_H
#define TP_BATTLEARENA_CHAMPIGNON_H
#include <GL/gl.h>
#include <GL/glu.h>
#include "SDL2/SDL.h"
class Champignon {
private:
    float x, y, z, angleRotate = 0, deltaTime;
    GLuint idTexture;
    float radius;
    Uint32 endPosition;
public:
    float getX() const;
    float getY() const;
    float getZ() const;
    float getRadius() const;
public:
    Champignon(float x, float y, float z, GLUquadric *params, float radius, float deltaTime);
    void draw();
    void move(Uint32 startRotation);
    virtual ~Champignon();
};
#endif //TP_BATTLEARENA_CHAMPIGNON_H
