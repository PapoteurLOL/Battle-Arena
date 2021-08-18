//
// Created by Administrator on 8/17/2021.
//

#include "Player.h"

Player::Player(GLUquadric *params, GLuint idTexture, float taille, float radius,Coord coord,
               float angleRotation, float velocity, float velocityRotation, float hp) : coord(coord),
                                                                angleRotation(angleRotation),
                                                                velocityRotation(velocityRotation), velocity(velocity), hp(hp),
                                                                taille(taille), radius(radius){
    maxAmmo = 500000000;
    ammoLeft = maxAmmo;
    idPlayer = glGenLists(2);
    glNewList(idPlayer, GL_COMPILE);
    glPushMatrix();
    Utils::drawCube(this->taille, this->taille, this->taille, idTexture);
    glTranslatef(this->coord.x, this->taille * 2 - this->radius, this->coord.z);
    glEndList();
    glNewList(idPlayer + 1, GL_COMPILE);
    gluQuadricDrawStyle(params, GLU_FILL);
    glColor3f(25.0 / 255.0, 89.0 / 255.0, 2.0 / 255.0);
    glBindTexture(GL_TEXTURE_2D,idTexture);
    gluQuadricTexture(params,GL_TRUE);
    gluSphere(params, this->radius, 20, 20);
    glTranslatef(this->coord.x, this->radius / 2, this->radius / 2);
    glColor3f(75.3 / 255.0, 200.0 / 255.0, 45.6 / 255.0);
    gluCylinder(params, this->radius / 4, this->radius / 4, this->radius, 20, 20);
    glBindTexture(GL_TEXTURE_2D,0);
    glPopMatrix();
    glEndList();
}
Player::~Player() {
    glDeleteLists(idPlayer, 1);
}
void Player::draw() {
    glPushMatrix();
    glTranslatef(coord.x, coord.y, coord.z);
    glCallList(idPlayer);
    glRotatef(this->angleRotation, 0, 1, 0);
    glCallList(idPlayer + 1);
    glPopMatrix();
    if (!bullets.empty()){
        for (int i = 0; i < bullets.size(); i++){
            bullets[i]->draw();
        }
    }
}
void Player::move(const Uint8 *state, GLUquadric *params, GLuint idTexture) {
    if (state[SDL_SCANCODE_A]) {
        angleRotation += velocityRotation;
    }
    if (state[SDL_SCANCODE_D]) {
        angleRotation -= velocityRotation;
    }
    if (state[SDL_SCANCODE_W]) {
        coord.x += sin(angleRotation * M_PI / 180) * velocity;
        coord.z += cos(angleRotation * M_PI / 180) * velocity;
    }
    if (state[SDL_SCANCODE_S]) {
        coord.x -= sin(angleRotation * M_PI / 180) * velocity / 2;
        coord.z -= cos(angleRotation * M_PI / 180) * velocity / 2;
    }
    if (state[SDL_SCANCODE_SPACE] && ammoLeft > 0) {
        Projectile *bullet = new Projectile(params, idTexture, (radius / 4) - 1,
                                            {coord.x, coord.y + taille+ radius / 2, coord.z}, 1 , angleRotation);
        bullets.push_back(bullet);
        ammoLeft--;
    }
    if (ammoLeft < 0)
        ammoLeft = 0;
    if (!bullets.empty()){
        for (int i = 0; i < bullets.size(); i++){
            if(!bullets[i]->isActive())
                bullets.erase(bullets.begin() + i);

            bullets[i]->move();
        }
    }
}
float Player::getX() const {
    return coord.x;
}
float Player::getY() const {
    return coord.y;
}
float Player::getZ() const {
    return coord.z;
}
float Player::getTaille() const {
    return taille;
}
float Player::getRadius() const {
    return radius;
}
float Player::getAngleRotation() const {
    return angleRotation;
}
