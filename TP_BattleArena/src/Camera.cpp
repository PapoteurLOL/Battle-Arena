//
// Created by Administrator on 8/17/2021.
//

#include "Camera.h"
Camera::Camera(Player *p) : p(p) {
}
void Camera::move() {
    gluLookAt(this->p->getX() + sin(p->getAngleRotation() * M_PI / 180) * p->getRadius() / 2, this->p->getY() + this->p->getTaille() + this->p->getRadius() / 2 + cos(p->getAngleRotation() * M_PI / 180) * p->getRadius() / 2,
              this->p->getZ() + this->p->getRadius(), this->p->getX() + sin(p->getAngleRotation() * M_PI / 180) * 1000,
              this->p->getY(), this->p->getZ() + cos(p->getAngleRotation() * M_PI / 180) * 1000, 0, 1, 0);
}
