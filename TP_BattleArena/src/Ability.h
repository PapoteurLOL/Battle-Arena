//
// Created by Administrator on 8/18/2021.
//

#ifndef TP_BATTLEARENA_ABILITY_H
#define TP_BATTLEARENA_ABILITY_H
#include "Projectile.h"
class Ability {
protected:
    std::vector<Projectile*> bullets;
    float maxAmmo;
    float ammoLeft;
    float cooldown;
    Uint32 currentTime;
public:
    Ability(float maxAmmo, float cd);
    void use(GLUquadric *params, GLuint idTexture, float radius, Coord coord, float velocity, float angle);
    void draw();
    float getAmmoLeft() const;
    void move();
};
#endif //TP_BATTLEARENA_ABILITY_H
