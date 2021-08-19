//
// Created by Administrator on 8/17/2021.
//

#include <iostream>
#include "Enemy.h"


Enemy::Enemy(GLUquadric *params, float x, float y, float z, float velocity) {
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
    glTranslatef(0, 0, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(10, 10, 10);
    gluSphere(params, 2, 6, 6);
    glPopMatrix();


    gluQuadricDrawStyle(params, GLU_FILL);
    glPushMatrix();
    glTranslatef(0, 20, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(10, 10, 10);
    gluSphere(params, 1, 6, 6);
    glPopMatrix();

//    gluQuadricDrawStyle(params, GLU_FILL);
//    glPushMatrix();
//    glTranslatef(0, 20, 0);
//    glRotatef(0, 1, 0, 0);
//    glScalef(10,10,10);
//    glColor3ub(50, 50, 50);
//    gluCylinder(params, 1, .01, 5, 10, 10);
//    glPopMatrix();

    glEndList();
}


void Enemy::draw() const {
    glPopMatrix();
    glTranslatef(enemyPosX, enemyPosY, enemyPosZ);
    //glCallList(enemyID);
    glPopMatrix();

    for (Egg* egg: eggs) {
        egg->draw();
    }
}

void Enemy::trackPlayer(float x, float y, float z) {

    Vector *playerCoordinates = new Vector(x, y, z);
    Vector direction = playerCoordinates->operator-(Vector(enemyPosX, enemyPosY, enemyPosZ));
    direction.normalize();

    float cosinus = direction.x / direction.magnitude();
    float sinus = direction.z / direction.magnitude();
    rotationAngle = acos(cosinus) * 180 / M_PI + 90;

    glPushMatrix();
    glRotatef(rotationAngle, 0, 1, 0);
    glCallList(enemyID);

    enemyPosX += velocity * direction.x;
    //enemyPosY += velocity * direction.y;
    enemyPosZ += velocity * direction.z;

    updateEggPosition();

    glPopMatrix();
}

Enemy::~Enemy() {
    glDeleteLists(enemyID, 1);
}

void Enemy::spawnEgg(GLUquadric *params) {
    currentTime = SDL_GetTicks();
    if (currentTime - lastUpdate >= 1000) {
        Egg *egg = new Egg(params, getEnemyPosX(), getEnemyPosY(), getEnemyPosZ(), 15);
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

void Enemy::updateEggPosition() {
    if (!eggs.empty()) {
        for (Egg *e : eggs) {
            e->move();
        }
    }
}

void Enemy::setEggReady(bool eggReady) {
    Enemy::eggReady = eggReady;
}

bool Enemy::isEggReady() const {
    return eggReady;
}



