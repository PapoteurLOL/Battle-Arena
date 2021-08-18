//
// Created by PAPOTEUR on 2021-08-17.
//

#include "Arbre.h"
Arbre::Arbre(float x, float y, float z, GLUquadric *params) : x(x), y(y), z(z) {
    idTexture = glGenLists(1);
    glNewList(idTexture, GL_COMPILE);
    glColor3f(143.0 / 255.0, 89.0 / 255.0, 2.0 / 255.0);
    gluQuadricDrawStyle(params, GLU_FILL);
    glTranslatef(0, 2, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(params, 1, .5, 4, 4, 4);
    glTranslatef(0, 0, 4);
    glColor3f(0, 1, 0);
    gluQuadricDrawStyle(params, GLU_FILL);
    gluSphere(params, 2, 5, 5);
    glEndList();
}
void Arbre::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glCallList(idTexture);
    glPopMatrix();
}
void Arbre::move() {
    angleRotate += .1;
}
Arbre::~Arbre() {
    glDeleteLists(idTexture, 1);
}
