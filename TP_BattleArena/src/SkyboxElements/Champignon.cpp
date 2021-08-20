//
// Created by Administrator on 18/08/2021.
//

#include "Champignon.h"
Champignon::Champignon(float x, float y, float z, GLUquadric *params, float radius, float deltaTime) : x(x), y(y), z(z),
                                                                                                       radius(radius),
                                                                                                       deltaTime(
                                                                                                               deltaTime) {
    idTexture = glGenLists(2);
    glNewList(idTexture, GL_COMPILE);
    //glPushMatrix();
    //corps champignon
    glColor3f(110.0 / 255.0, 40.0 / 255.0, 155.0 / 255.0);
    gluQuadricDrawStyle(params, GLU_FILL);
    glTranslatef(0, .01, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(params, this->radius, this->radius / 2, 25, 20, 1);

    //tete champignon
    glTranslatef(0, 0, 25);
    glColor3f(1, 1, 0);
    glScalef(1, 1, .20);
    gluSphere(params, this->radius * 2, 20, 20);
    //glPopMatrix();
    glEndList();
}
void Champignon::draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angleRotate, 0, angleRotate, 1);
    glCallList(idTexture);
    glPopMatrix();
}
void Champignon::move(Uint32 startRotation) {
    x += velocity;
    if (startRotation - endPosition > deltaTime) {
        angleRotate += .1;
        if (x < 50 || x > 50) {
            velocity *= -1;
        }
        endPosition = startRotation;
    }
}
Champignon::~Champignon() {
    glDeleteLists(idTexture, 2);
}
float Champignon::getX() const {
    return x;
}
float Champignon::getY() const {
    return y;
}
float Champignon::getZ() const {
    return z;
}
float Champignon::getRadius() const {
    return radius;
}
