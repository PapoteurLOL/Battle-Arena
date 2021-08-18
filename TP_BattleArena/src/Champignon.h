//
// Created by Administrator on 18/08/2021.
//

#ifndef TP_BATTLEARENA_CHAMPIGNON_H
#define TP_BATTLEARENA_CHAMPIGNON_H
#include <GL/gl.h>
#include <GL/glu.h>
class Champignon {
private:
    float x, y, z, angleRotate = 0, xVelocity = 1;
    GLuint idTexture;
public:
    Champignon(float x, float y, float z, GLUquadric *params);
    void draw();
    void move();
    virtual ~Champignon();
};
#endif //TP_BATTLEARENA_CHAMPIGNON_H
