//
// Created by Administrator on 8/17/2021.
//

#ifndef TP_BATTLEARENA_CAMERA_H
#define TP_BATTLEARENA_CAMERA_H
#include "Player.h"
class Camera {
protected:
    Player * p;
public:
    Camera(Player *p);
    void move();
};
#endif //TP_BATTLEARENA_CAMERA_H
