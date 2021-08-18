//
// Created by Administrator on 8/17/2021.
//

#ifndef TP_BATTLEARENA_PROJECTILE_H
#define TP_BATTLEARENA_PROJECTILE_H
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "iostream"
#include "Utils.h"

struct Coord {
    float x, y, z;
};
class Projectile {
protected:
    float radius;
    Coord coord;
    float velocity;
    const float MAX_TRAVELING = 500;
    GLuint idProjectile;
    float angleTrajectoire;
    float traveled;
    bool active;
public:
    Projectile(GLUquadric *params, GLuint idTexture, float radius, const Coord &coord, float velocity, float angle);
    virtual void draw();
    virtual ~Projectile();
    bool isActive() const;
    virtual  void move();
};

#endif //TP_BATTLEARENA_PROJECTILE_H
