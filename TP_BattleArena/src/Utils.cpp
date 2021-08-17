//
// Created by Administrator on 8/13/2021.
//
#include "Utils.h"

void Utils::drawAxis(float taille) {
    glPushMatrix();
    glScaled(taille, taille, taille);
    glLineWidth(2);
    glBegin(GL_LINES);
    //axe des x
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    //axe des y
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    //axe des x
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
    glLineWidth(1);
    glPopMatrix();
}
void Utils::drawQuads(float height, float lenght, float red, float green, float blue) {
    glPushMatrix();
    glScaled(lenght, height, 1);
    glBegin(GL_QUADS);
    glColor3f(red, green, blue);
    glVertex2f(0, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0);
    glVertex2f(0, 0);
    glEnd();
    glEnd();
    glPopMatrix();
}
void Utils::drawQuadsHollow(float height, float lenght, float red, float green, float blue) {
    glPushMatrix();
    glScaled(lenght, height, 1);
    glBegin(GL_LINE_LOOP);
    glColor3f(red, green, blue);
    glVertex2f(0, 1);
    glVertex2f(1, 1);
    glVertex2f(1, 0);
    glVertex2f(0, 0);
    glEnd();
    glPopMatrix();
}
void Utils::drawCube(float tailleX, float tailleY, float tailleZ) {
    glPushMatrix();
    glScalef(tailleX, tailleY, tailleZ);
    glBegin(GL_QUADS);
    //face du bas
    glColor3f(0.1, 0.1, 0.1);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);

    //face du gauche
    glColor3f(0.2, 0.2, 0.2);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    //face du gauche
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);

    //face du droite
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    //face du droite
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);

    //face du droite
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glEnd();
    glPopMatrix();
}
void Utils::drawCube(float tailleX, float tailleY, float tailleZ, float red, float green, float blue) {
    glPushMatrix();
    glScalef(tailleX, tailleY, tailleZ);
    glBegin(GL_QUADS);
    //face du bas
    glColor3f(red, green, blue);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(-1, -1, -1);

    //face du gauche
    glColor3f(red, green, blue);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    //face du gauche
    glColor3f(red, green, blue);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);

    //face du droite
    glColor3f(red, green, blue);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);

    //face du droite
    glColor3f(red, green, blue);
    glVertex3f(1, -1, 1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);

    //face du droite
    glColor3f(red, green, blue);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, 1, -1);
    glEnd();
    glPopMatrix();
}
