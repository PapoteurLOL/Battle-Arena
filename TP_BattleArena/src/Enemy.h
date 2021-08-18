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
    float enemyPosY = 0;
    float enemyPosZ = 0;
    float velocity = 0.01;

    float rotationAngle = 0;

public:
    Enemy(GLUquadric *params);
    void draw() const;
    void trackPlayer(float x, float y, float z);
    virtual ~Enemy();
};


#endif //DEMOFIRSTSDL_ENEMY_H
