//
// Created by Administrator on 8/17/2021.
//

#ifndef DEMOFIRSTSDL_ENEMY_H
#define DEMOFIRSTSDL_ENEMY_H


#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <time.h>

#include "Utilities/Point.h"

class Enemy {

private:
    GLuint enemyID;

    float enemyPosX = 0;
    float enemyPosY = 20;
    float enemyPosZ = -800;
    float velocity = .2;

    float rotationAngle = 0;

public:
    Enemy(GLUquadric *params, float x, float y, float z, float velocity);
    void draw() const;
    void trackPlayer(float x, float y, float z);
    virtual ~Enemy();
};


#endif //DEMOFIRSTSDL_ENEMY_H
