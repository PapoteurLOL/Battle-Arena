//
// Created by Administrator on 8/17/2021.
//

#include "Camera.h"
Camera::Camera(Player *p) : p(p) {
}
void Camera::move() {
    float deltaPosX = sin(p->getAngleRotation() * M_PI / 180) * p->getRadius();
    float posY = this->p->getTaille() * 2 + this->p->getRadius();
    float deltaPosZ =  cos(p->getAngleRotation() * M_PI / 180) * p->getRadius();
    gluLookAt(this->p->getX() + deltaPosX, this->p->getY() + posY,
              this->p->getZ() + deltaPosZ, this->p->getX() + deltaPosX * 1000,
              this->p->getY(), this->p->getZ() + deltaPosZ * 1000, 0, 1, 0);
}
