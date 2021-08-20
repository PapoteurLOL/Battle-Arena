//
// Created by Administrator on 8/17/2021.
//

#include <iostream>
#include "Enemy.h"


Enemy::Enemy(GLUquadric *params, float x, float y, float z, float velocity) : direction(x,y,z){
    //x:0,y:20, z:-800

    this->enemyPosX = x;
    this->enemyPosY = y;
    this->enemyPosZ = z;
    this->velocity = velocity;

    enemyID = glGenLists(1);
    glNewList(enemyID, GL_COMPILE);
    glColor3ub(255, 5, 5);

    gluQuadricDrawStyle(params, GLU_FILL);
    glPushMatrix();
    glTranslatef(0, 20, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(10, 10, 10);
    gluSphere(params, 2, 6, 6);
    glPopMatrix();

    gluQuadricDrawStyle(params, GLU_FILL);
    glPushMatrix();
    glTranslatef(0, 50, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(10, 10, 10);
    gluSphere(params, 1, 6, 6);
    glPopMatrix();

    gluQuadricDrawStyle(params, GLU_FILL);
    glPushMatrix();
    glTranslatef(0, 50, 0);
    glRotatef(-90, 1, 0, 0);
    glScalef(10,10,10);
    glColor3ub(50, 50, 50);
    gluCylinder(params, 1, .01, 4, 10, 10);
    glPopMatrix();

    glEndList();
}


void Enemy::draw() {
    glPushMatrix();
    glTranslatef(enemyPosX, enemyPosY, enemyPosZ);
    glCallList(enemyID);
    glPopMatrix();

    for (Egg *egg : eggs) {
        egg->draw();
    }

}

void Enemy::trackPlayer(float x, float y, float z) {

    Vector *playerCoordinates = new Vector(x, y, z);
    direction = playerCoordinates->operator-(Vector(enemyPosX, enemyPosY, enemyPosZ));
    direction.normalize();

    float cosinus = direction.x / direction.magnitude();
    float sinus = direction.z / direction.magnitude();
    rotationAngle = acos(cosinus) * 180 / M_PI + 90;

    //glPushMatrix();
    //glRotatef(rotationAngle, 0, 1, 0);

    enemyPosX += velocity * direction.x;
    //enemyPosY += velocity * direction.y;
    enemyPosZ += velocity * direction.z;

    //glPopMatrix();

    setEggDirection(direction);
}

Enemy::~Enemy() {
    glDeleteLists(enemyID, 1);
}

void Enemy::spawnEgg(GLUquadric *params) {
    currentTime = SDL_GetTicks();
    if (currentTime - lastUpdate >= rand() % timeToSpawnEgg + 4000) {
        Egg *egg = new Egg(params, enemyPosX, enemyPosY + 10 , enemyPosZ, eggVelocity , direction.x, direction.y, direction.z);
        eggs.push_back(egg);
        lastUpdate = currentTime;
    }
}

float Enemy::getEnemyPosX() const {
    return enemyPosX;
}

float Enemy::getEnemyPosY() const {
    return enemyPosY;
}

float Enemy::getEnemyPosZ() const {
    return enemyPosZ;
}

void Enemy::setEggDirection(Vector direction) {
    if (!eggs.empty()) {
        for (Egg *e : eggs) {
            e->setDirection(direction);
            e->move();
//            if (abs(e->getEggPosX()) > 1000 && abs(e->getEggPosZ()) > 1000) {
//                e->setEggPosX(enemyPosX);
//                e->setEggPosY(enemyPosY);
//                e->setEggPosX(enemyPosZ);
//            }
        }
    }

    //std::cout<< enemyPosZ << std::endl;
}




