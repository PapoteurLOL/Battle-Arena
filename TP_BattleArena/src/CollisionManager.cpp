//
// Created by Administrator on 8/18/2021.
//

#include "CollisionManager.h"
CollisionManager::CollisionManager(const std::vector<Arbre *> &arbres, const std::vector<Champignon *> &champignons) : arbres(arbres), champignons(champignons) {}
bool CollisionManager::collisionCheck(Player *p) {
    bool collided = false;
    for (auto a : arbres) {
        glPopMatrix();
        if (p->getX() - p->getTaille() <= a->getX() + a->getRadius() && p->getX() + p->getTaille() >= a->getX() - a->getRadius()
            && p->getZ() - p->getTaille() <= a->getZ() + a->getRadius() && p->getZ() + p->getTaille() >= a->getZ() - a->getRadius()) {
            collided = true;
        }
    }
    for (auto c : champignons) {
        glPopMatrix();
        if (p->getX() - p->getTaille() <= c->getX() + c->getRadius() && p->getX() + p->getTaille() >= c->getX() - c->getRadius()
            && p->getZ() - p->getTaille() <= c->getZ() + c->getRadius() && p->getZ() + p->getTaille() >= c->getZ() - c->getRadius()) {
            collided = true;
        }
    }
    return collided;
}

