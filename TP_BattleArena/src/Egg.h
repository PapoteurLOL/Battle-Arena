//
// Created by Administrator on 8/18/2021.
//

#ifndef TP_BATTLEARENA_EGG_H
#define TP_BATTLEARENA_EGG_H

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>

class Egg {
private:
    GLuint eggID;

    float eggPosX;
    float eggPosY;
    float eggPosZ;

    float eggVelocity;

public:

    Egg(GLUquadric* params, float eggPosX, float eggPosY, float eggPosZ, float eggVelocity);

    void draw();

    void move();

    float getEggPosX() const;
    float getEggPosY() const;
    float getEggPosZ() const;

    virtual ~Egg();

};


#endif //TP_BATTLEARENA_EGG_H
