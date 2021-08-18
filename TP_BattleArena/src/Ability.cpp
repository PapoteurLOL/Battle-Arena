//
// Created by Administrator on 8/18/2021.
//

#include "Ability.h"
Ability::Ability(float maxAmmo, float cd) {
    this->maxAmmo = maxAmmo;
    ammoLeft = maxAmmo;
    cooldown = cd;
    currentTime = SDL_GetTicks();
}
void Ability::use(GLUquadric *params, GLuint idTexture, float radius, Coord coord, float velocity, float angle) {
    if (SDL_GetTicks() - currentTime >= cooldown * 1000){
        Projectile *bullet = new Projectile(params, idTexture, radius, coord, velocity, angle);
        bullets.push_back(bullet);
        ammoLeft--;
        currentTime = SDL_GetTicks();
    }
}
void Ability::draw() {
    if (!bullets.empty()) {
        for (int i = 0; i < bullets.size(); i++) {
            bullets[i]->draw();
        }
    }
}
float Ability::getAmmoLeft() const {
    return ammoLeft;
}
void Ability::move() {
    if (ammoLeft < 0)
        ammoLeft = 0;
    if (!bullets.empty()) {
        for (int i = 0; i < bullets.size(); i++) {
            if (!bullets[i]->isActive())
                bullets.erase(bullets.begin() + i);
            bullets[i]->move();
        }
    }
}
