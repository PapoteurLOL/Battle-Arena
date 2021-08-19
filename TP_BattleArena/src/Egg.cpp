//
// Created by Administrator on 8/18/2021.
//

#include "Egg.h"

Egg::Egg(GLUquadric *params, float eggPosX, float eggPosY, float eggPosZ, float eggVelocity) {

    this->eggPosX = eggPosX;
    this->eggPosY = eggPosY;
    this->eggPosZ = eggPosZ;
    this->eggVelocity = eggVelocity;


    eggID = glGenLists(1);
    glNewList(eggID, GL_COMPILE);
    glColor3ub(0, 255, 0);

    gluQuadricDrawStyle(params, GLU_FILL);
    glPushMatrix();
    glTranslatef(eggPosX, eggPosY, eggPosZ);
    glRotatef(90, 1, 0, 0);
    gluSphere(params, 25, 20, 20);
    glPopMatrix();

    glEndList();
}

void Egg::draw() {
    glPushMatrix();
    glTranslatef(eggPosX, eggPosY, eggPosZ);
    glCallList(eggID);
    glPopMatrix();
}

void Egg::move() {
    //eggPosX++;
}

Egg::~Egg() {
    glDeleteLists(eggID, 1);
}

float Egg::getEggPosX() const {
    return eggPosX;
}

float Egg::getEggPosY() const {
    return eggPosY;
}

float Egg::getEggPosZ() const {
    return eggPosZ;
}
