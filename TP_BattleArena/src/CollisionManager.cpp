//
// Created by Administrator on 8/18/2021.
//

#include "CollisionManager.h"
CollisionManager::CollisionManager(const std::vector<Arbre *> &arbres) : arbres(arbres) {}
bool CollisionManager::collisionCheck(Player *p) {
    bool collided = false;
    for (auto a : arbres) {
        glPushMatrix();
        glTranslatef(a->getX(), 1, a->getZ());
        Utils::drawAxis(15);
        glPopMatrix();
        if (((p->getX() - p->getTaille() <= a->getX() + a->getRadius()) && (p->getX() + p->getTaille() >= a->getX() - a->getRadius()))
            || ((p->getZ() - p->getTaille() <= a->getZ() + a->getRadius()) && (p->getZ() + p->getTaille() >= a->getZ() - a->getRadius()))) {
            collided = true;
        }
    }
    std::string s = std::to_string(p->getZ());
    SDL_Log(s.c_str());
    return collided;
}

