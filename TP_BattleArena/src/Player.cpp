//
// Created by Administrator on 8/17/2021.
//

#include "Player.h"
Player::Player(GLUquadric *params, GLuint idTexture, float taille, float radius, Coord coord,
               float angleRotation, float velocity, float velocityRotation, float hp, int widthWorld, int up, int down, int left, int right, int shoot) : coord(coord),
                                                                                                        angleRotation(
                                                                                                                angleRotation),
                                                                                                        velocityRotation(
                                                                                                                velocityRotation),
                                                                                                        velocity(
                                                                                                                velocity),
                                                                                                        hp(hp),
                                                                                                        taille(taille),
                                                                                                        radius(radius) {
    control = {up, down, left, right, shoot};
    ability0 = new Ability(120, 0.5);
    idPlayer = glGenLists(2);
    gluQuadricDrawStyle(params, GLU_FILL);
    glNewList(idPlayer, GL_COMPILE);
    glPushMatrix();
    glTranslatef(0, this->taille, 0);
    Utils::drawCube(this->taille, this->taille, this->taille, idTexture);
    glPopMatrix();
    glEndList();
    glNewList(idPlayer + 1, GL_COMPILE);
    glTranslatef(0, this->taille * 3 - this->radius, 0);
    glColor3f(25.0 / 255.0, 89.0 / 255.0, 2.0 / 255.0);
    glBindTexture(GL_TEXTURE_2D, idTexture);
    gluQuadricTexture(params, GL_TRUE);
    gluSphere(params, this->radius, 20, 20);
    glTranslatef(0, this->radius / 2, this->radius / 2);
    glColor3f(75.3 / 255.0, 200.0 / 255.0, 45.6 / 255.0);
    gluCylinder(params, this->radius / 6, this->radius / 6, this->radius * 1.5, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEndList();
    edgeWorld = widthWorld - taille - radius * 1.5;
    dead = false;
    sonHit = Mix_LoadWAV("./assets/hit.mp3");
    sonDead = Mix_LoadWAV("./assets/explosion.mp3");
    active = true;
    hpID = glGenLists(1);
    glNewList(hpID, GL_COMPILE);
    glColor3ub(51, 153, 0);
    gluQuadricDrawStyle(params, GLU_FILL);
    glPushMatrix();
    glTranslatef(0, 60, 0);
    //glRotatef(0, 1, 0, 0);
    glScalef(10, 10, 10);
    gluCylinder(params, 1, 1, 11, 10, 10);
    glPopMatrix();
    glEndList();
}
Player::~Player() {
    glDeleteLists(idPlayer, 1);
}
void Player::draw() {
    if(!dead){
        glPushMatrix();
        glTranslatef(coord.x, coord.y, coord.z);
        glCallList(idPlayer);
        glRotatef(this->angleRotation, 0, 1, 0);
        glCallList(idPlayer + 1);
        glTranslatef(0, 25, 0);
        if (hp > 0) {
            glScalef(1, 1, hp / 100);
        } else {
            glScalef(0, 0, 0);
        }
        glCallList(hpID);

        glPopMatrix();
        glPushMatrix();
        ability0->draw();

        glPopMatrix();
    } else {
        if(SDL_GetTicks() - timeOfDeath < timerDeathAnim * 1000){
            coord.x += 0.01;
            coord.z+=0.01;
            angleRotation+= 0.5;
            glPushMatrix();
            glTranslatef(coord.x, coord.y + taille, coord.z);
            glRotatef(this->angleRotation, 1, 0, 0);
            glRotatef(this->angleRotation, 0, 1, 0);
            glRotatef(this->angleRotation, 0, 0, 1);
            glCallList(idPlayer);
            glCallList(idPlayer + 1);
            glPopMatrix();
            glPushMatrix();
            ability0->draw();
            glPopMatrix();
        } else {
            active = false;
        }
    }
}
void Player::move(const Uint8 *state, GLUquadric *params, GLuint idTexture) {
    if (!dead){
        if (state[control.LEFT]) {
            angleRotation += velocityRotation;
        }
        if (state[control.RIGHT]) {
            angleRotation -= velocityRotation;
        }
        if (state[control.UP]) {
            coord.x += sin(angleRotation * M_PI / 180) * velocity;
            coord.z += cos(angleRotation * M_PI / 180) * velocity;
        }
        if (state[control.DOWN]) {
            coord.x -= sin(angleRotation * M_PI / 180) * velocity / 2;
            coord.z -= cos(angleRotation * M_PI / 180) * velocity / 2;
        }
        if (state[control.SHOOT] && ability0->getAmmoLeft() > 0) {
            ability0->use(params, idTexture, (radius / 4) - 1, {coord.x, coord.y + taille + radius / 2, coord.z}, 1,
                          angleRotation);
        }
        if (coord.x > edgeWorld)
            coord.x = edgeWorld;
        if (coord.z > edgeWorld)
            coord.z = edgeWorld;
        if (coord.x < edgeWorld * -1)
            coord.x = edgeWorld * -1;
        if (coord.z < edgeWorld * -1)
            coord.z = edgeWorld * -1;
        ability0->move();
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
void Player::forceMoveBack() {
    coord.x -= sin(angleRotation * M_PI / 180) * velocity / 2;
    coord.z -= cos(angleRotation * M_PI / 180) * velocity / 2;
}
void Player::takeDamage(float damage) {
    hp -= damage;
    if (hp < 0 && !dead){
        dead = true;
        timerDeathAnim = 15;
        timeOfDeath = SDL_GetTicks();
        Mix_PlayChannel(4, sonDead, 0);
    } else {
        Mix_PlayChannel(3, sonHit, 0);
    }

}
Ability *Player::getAbility0() const {
    return ability0;
}
bool Player::isDead() const {
    return dead;
}
bool Player::isActive() const {
    return active;
}

