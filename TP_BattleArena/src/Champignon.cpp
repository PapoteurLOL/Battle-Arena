//
// Created by Administrator on 18/08/2021.
//

#include "Champignon.h"
Champignon::Champignon(float x, float y, float z, GLUquadric *params) : x(x), y(y), z(z) {
    idTexture = glGenLists(1);
    glNewList(idTexture, GL_COMPILE);
    //glPushMatrix();
    //corps champignon
    glColor3f(110.0 / 255.0, 40.0 / 255.0, 155.0 / 255.0);
    gluQuadricDrawStyle(params, GLU_FILL);
    glTranslatef(0, .01, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(params, 5, 2.5, 20, 10, 1);

    //tete champignon
    glTranslatef(0, 0, 20);
    glColor3f(1, 1, 0);
    glScalef(1, 1, .20);
    gluSphere(params, 10, 20, 20);
    //glPopMatrix();
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