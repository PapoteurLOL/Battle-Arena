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
#include <vector>

#include "Utilities/Point.h"
#include "Egg.h"

class Enemy {

private:
    GLuint enemyID;
    float enemyPosX = 0;
    float enemyPosY = 20;
    float enemyPosZ = -800;
    float velocity = .2;

    float rotationAngle = 0;

    std::vector <Egg*> eggs;
    Egg* anEgg;
    bool eggReady = false;

    Uint32 currentTime = 0;
    Uint32 lastUpdate = 0;
    int timeToEggReady = 5000; //ms

    Vector direction;

public:
    Enemy(GLUquadric *params, float x, float y, float z, float velocity);
    void draw();
    void trackPlayer(float x, float y, float z);

    void spawnEgg(GLUquadric *params);
    void setEggDirection(Vector direction);

    void setEggReady(bool eggReady);
    bool isEggReady() const;

    float getEnemyPosX() const;
    float getEnemyPosY() const;
    float getEnemyPosZ() const;


    virtual ~Enemy();
};


#endif //DEMOFIRSTSDL_ENEMY_H
