//
// Created by Administrator on 8/17/2021.
//

#include "Projectile.h"
Projectile::Projectile(GLUquadric *params, GLuint idTexture, float radius, const Coord &coord, float velocity,
                       float angle) : radius(radius), coord(coord),
                                      velocity(velocity),
                                      angleTrajectoire(angle) {
    traveled = 0;
    idProjectile = glGenLists(1);
    active = true;
    glNewList(idProjectile, GL_COMPILE);
    glPushMatrix();
    gluQuadricDrawStyle(params, GLU_FILL);
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, idTexture);
    gluQuadricTexture(params, GL_TRUE);
    gluSphere(params, this->radius, 20, 20);
    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    glEndList();

}
void Projectile::draw() {
    glPushMatrix();
    glTranslatef(coord.x, coord.y, coord.z);
    glCallList(idProjectile);
    glPopMatrix();
}
Projectile::~Projectile() {
    glDeleteLists(idProjectile, 1);
}
void Projectile::move() {
    coord.x += sin(angleTrajectoire * M_PI / 180) * velocity;
    coord.z += cos(angleTrajectoire * M_PI / 180) * velocity;
    traveled += velocity;
    if(traveled >= MAX_TRAVELING)
        active = false;
//        delete this;
}
bool Projectile::isActive() const {
    return active;
}
float Projectile::getRadius() const {
    return radius;
}
float Projectile::getX() const {
    return coord.x;
}
float Projectile::getY() const {
    return coord.y;
}
float Projectile::getZ() const {
    return coord.z;
}
void Projectile::setActive(bool active) {
    Projectile::active = active;
}

