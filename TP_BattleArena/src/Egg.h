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
#include "Utilities/Point.h"

class Egg {
private:
    GLuint eggID;

    float eggPosX;
    float eggPosY;
    float eggPosZ;

    float eggVelocity;
    float eggRadius = 10;

    Vector direction;

public:

    Egg(GLUquadric* params, float eggPosX, float eggPosY, float eggPosZ, float eggVelocity, float playerPosX, float playerPosY, float playerPosZ);

    void setEggPosX(float eggPosX);
    void setEggPosY(float eggPosY);
    void setEggPosZ(float eggPosZ);


    void draw();
    void draw(float x, float y, float z);
    void move();

    float getEggPosX() const;
    float getEggPosY() const;
    float getEggPosZ() const;

    void setDirection(Vector direction);

    virtual ~Egg();

};


#endif //TP_BATTLEARENA_EGG_H
