//
// Created by Administrator on 18/08/2021.
//

#include "Champignon.h"
Champignon::Champignon(float x, float y, float z, GLUquadric *params, float deltaTime) : x(x), y(y), z(z),
                                                                                         deltaTime(deltaTime) {
    idTexture = glGenLists(2);
    glNewList(idTexture, GL_COMPILE);
    //glPushMatrix();
    //corps champignon
    glColor3f(110.0 / 255.0, 40.0 / 255.0, 155.0 / 255.0);
    gluQuadricDrawStyle(params, GLU_FILL);
    glTranslatef(0, .01, 0);
    glRotatef(-90, 1, 0, 0);
    gluCylinder(params, 5, 2.5, 50, 20, 1);
    //glPopMatrix();

    // glPushMatrix();
    //tete champignon
    glTranslatef(0, 0, 50);
    glColor3f(1, 1, 0);
    glScalef(1, 1, .20);
    gluSphere(params, 10, 20, 20);
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
void Champignon::move(Uint32 startPosition) {
    y -= xVelocity;
    angleRotate += .01;
    if (startPosition - endPosition > deltaTime) {

//        if (angleRotate < 50 || angleRotate > 50) {
//            xVelocity *= -1;
//        }
        if ( y < 0 || y >0 ) {
            xVelocity *= -1;
//            x += sin(angleRotate * M_PI / 180) * xVelocity;
//            z += cos(angleRotate * M_PI / 180) * xVelocity;
        }
        endPosition = startPosition;
    }
}
Champignon::~Champignon() {
    glDeleteLists(idTexture, 2);
}