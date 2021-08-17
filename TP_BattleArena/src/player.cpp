//
// Created by Administrator on 8/17/2021.
//

#include "player.h"
#include "Utils.h"
Player::Player(GLUquadric *params, GLuint idTexture, float taille, float radius, float x, float y, float z,
               float angleRotation, float velocity, float hp) : x(x), y(y), z(z),
                                                                angleRotation(angleRotation),
                                                                velocity(velocity), hp(hp) {
    idPlayer = glGenLists(1);
    glNewList(idPlayer, GL_COMPILE);
    glPushMatrix();
    Utils::drawCube(taille, taille, taille, idTexture);
    glTranslatef(this->x, this->y + taille, this->z);
    gluQuadricDrawStyle(params, GLU_FILL);
    glColor3f(25.0 / 255.0, 89.0 / 255.0, 2.0 / 255.0);
    gluSphere(params, radius, 20, 20);
    glTranslatef(x, radius / 2, radius / 2);
    glColor3f(75.3 / 255.0, 200.0 / 255.0, 45.6 / 255.0);
    gluCylinder(params, radius / 4, radius / 4, radius * 2, 20, 20);
    glPopMatrix();
    glEndList();
}
Player::~Player() {
    glDeleteLists(idPlayer, 1);
}
void Player::Draw() {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(this->angleRotation, 0, 1, 0);
    Utils::drawAxis(50);
    glCallList(idPlayer);
    glPopMatrix();
}
void Player::Move(const Uint8 *state) {
    if (state[SDL_SCANCODE_A]) {
        angleRotation += velocity;
    }
    if (state[SDL_SCANCODE_D]) {
        angleRotation -= velocity;
    }
    if (state[SDL_SCANCODE_W]) {
        x += sin(angleRotation * M_PI / 180);
        z += cos(angleRotation * M_PI / 180);
    }
    if (state[SDL_SCANCODE_S]) {
        x -= sin(angleRotation * M_PI / 180);
        z -= cos(angleRotation * M_PI / 180);
    }
}
