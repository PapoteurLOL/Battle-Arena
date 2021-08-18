//
// Created by Administrator on 18/08/2021.
//

#include "Champignon.h"
Champignon::Champignon(float x, float y, float z, GLUquadric *params) : x(x), y(y), z(z) {
    idTexture = glGenLists(1);
    glNewList(idTexture, GL_COMPILE);
    glColor3f(150.0 / 255.0, 0, 0);
    gluQuadricDrawStyle(params, GLU_FILL);
    glTranslatef(0, 2, 0);
    glRotatef(-90, .5, 0, 0);
    gluCylinder(params, 1, .5, 4, 4, 4);
    glTranslatef(0, 0, 4);
//    glColor3f(0, 1, 0);
//    gluQuadricDrawStyle(params, GLU_FILL);
//    gluSphere(params, 5, 20, 20);
//    glTranslatef(2, 0, 1);
//    gluSphere(params, 1, 20, 20);
    glEndList();
}
void Champignon::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glCallList(idTexture);
    glPopMatrix();
}
void Champignon::move() {
    angleRotate += .1;
}
Champignon::~Champignon() {
    glDeleteLists(idTexture, 1);
}