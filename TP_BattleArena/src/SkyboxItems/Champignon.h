//
// Created by Administrator on 18/08/2021.
//

#ifndef TP_BATTLEARENA_CHAMPIGNON_H
#define TP_BATTLEARENA_CHAMPIGNON_H
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
class Champignon {
private:
    float x, y, z, angleRotate = 0, xVelocity = .5;
    float deltaTime;
    Uint32 endPosition;
    GLuint idTexture;
public:
    Champignon(float x, float y, float z, GLUquadric *params, float deltaTime);
    void draw();
    void move(Uint32 startPosition);
    virtual ~Champignon();
};
#endif //TP_BATTLEARENA_CHAMPIGNON_H
