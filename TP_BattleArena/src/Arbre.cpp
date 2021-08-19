//
// Created by PAPOTEUR on 2021-08-17.
//

#include "Arbre.h"
Arbre::Arbre(float x, float y, float z, GLUquadric *params, float radius) : x(x), y(y), z(z), radius(radius) {
    idTexture = glGenLists(1);
    glNewList(idTexture, GL_COMPILE);
    glColor3f(143.0 / 255.0, 89.0 / 255.0, 2.0 / 255.0);
    gluQuadricDrawStyle(params, GLU_FILL);
    glTranslatef(0, 2, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(params, this->radius, 1, 100, 20, 4);
    glTranslatef(0, 0, 100);
    glColor3f(0, 1, 0);
    gluQuadricDrawStyle(params, GLU_FILL);
    gluSphere(params, this->radius * 5, 5, 5);
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
float Arbre::getX() const {
    return x;
}
float Arbre::getZ() const {
    return z;
}
float Arbre::getRadius() const {
    return radius;
}
