//
// Created by Administrator on 8/17/2021.
//

#include <iostream>
#include "Enemy.h"
Enemy::Enemy(GLUquadric *params, float x, float y, float z, float velocity) : direction(x, y, z) {
    //x:0,y:20, z:-800
    dead = false;
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
    glScalef(10, 10, 10);
    glColor3ub(50, 50, 50);
    gluCylinder(params, 1, .01, 4, 10, 10);
    glPopMatrix();
    gluQuadricDrawStyle(params, GLU_FILL);
    glPushMatrix();
    glTranslatef(0, 110, 0);
    //glRotatef(-90, 1, 0, 0);
    glScalef(10, 10, 10);
    glColor3ub(255, 59, 59);
    gluCylinder(params, .75, .75, 10, 10, 10);
    glPopMatrix();
    glEndList();
    hpID = glGenLists(1);
    glNewList(hpID, GL_COMPILE);
    glColor3ub(51, 153, 0);
    gluQuadricDrawStyle(params, GLU_FILL);
    glPushMatrix();
    glTranslatef(0, 60, 0);
    //glRotatef(0, 1, 0, 0);
    glScalef(10, 10, 10);
    gluCylinder(params, 1, 1, 11, 10, 10);
    glPopMatrix();
    glEndList();
}
void Enemy::draw(std::vector<Projectile *> &p, std::vector<Arbre *> &a) {
    glPushMatrix();
    glTranslatef(enemyPosX, enemyPosY, enemyPosZ);
    glCallList(enemyID);
    glPopMatrix();
    if (this->isHitBy(p))
        HP -= .5;
    glPushMatrix();
    glTranslatef(enemyPosX, enemyPosY + 50, enemyPosZ);
    if (HP > 0) {
        glScalef(1, 1, HP / 100);
    } else {
        glScalef(0, 0, 0);
    }
    glCallList(hpID);
    glPopMatrix();
    for (Egg *egg : eggs) {
        if (egg) {
            egg->draw();
        }
        if (egg->collideWith(a)) {
            glDeleteLists(egg->getEggId(), 1);
        }
    }
}
void Enemy::trackPlayer(float x, float y, float z) {
    Vector *playerCoordinates = new Vector(x, y, z);
    direction = playerCoordinates->operator-(Vector(enemyPosX, enemyPosY, enemyPosZ));
    direction.normalize();
    float cosinus = direction.x / direction.magnitude();
    float sinus = direction.z / direction.magnitude();
    rotationAngle = acos(cosinus) * 180 / M_PI + 90;


    //glRotatef(rotationAngle, 0, 1, 0);

    if (HP > 0) {
        enemyPosX += velocity * direction.x;
        //enemyPosY += velocity * direction.y;
        enemyPosZ += velocity * direction.z;
        setEggDirection(direction);
    } else {
//        glDeleteLists(enemyID, 1);
        dead = true;
    }
}
Enemy::~Enemy() {
    glDeleteLists(enemyID, 1);
}
void Enemy::spawnEgg(GLUquadric *params) {
    currentTime = SDL_GetTicks();
    if (currentTime - lastUpdate >= rand() % timeToSpawnEgg + 4000) {
        Egg *egg = new Egg(params, enemyPosX, enemyPosY + 10, enemyPosZ, eggVelocity, direction.x, direction.y,
                           direction.z);
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
bool Enemy::isHitBy(std::vector<Projectile *> &p) {
    for (Projectile *projectile : p) {
        if ((projectile->getX() - projectile->getRadius() <= enemyPosX + 10
             && projectile->getX() + projectile->getRadius() >= enemyPosX - 10
             && projectile->getZ() - projectile->getRadius() <= enemyPosZ + 10
             && projectile->getZ() + projectile->getRadius() >= enemyPosZ - 10)) {
            return true;
        }
    }
    return false;
}
bool Enemy::isDead() const {
    return dead;
}
