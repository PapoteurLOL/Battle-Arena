//
// Created by Administrator on 8/18/2021.
//

#include "CollisionManager.h"
CollisionManager::CollisionManager(const std::vector<Arbre *> &arbres) : arbres(arbres) {}
bool CollisionManager::collisionCheck(Player *p) {
    bool collided = true;
    for (auto a : arbres) {
        if ((p->getX() - p->getTaille() >= a->getX() + a->getRadius())
            || (p->getX() + p->getTaille() <= a->getX() - a->getRadius())
            || (p->getZ() - p->getTaille() >= a->getZ() + a->getRadius())
            || (p->getZ() + p->getTaille() <= a->getZ() - a->getRadius())) {
            collided = false;
        }
    }
    return collided;
}

