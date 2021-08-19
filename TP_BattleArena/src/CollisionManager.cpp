//
// Created by Administrator on 8/18/2021.
//

#include "CollisionManager.h"
CollisionManager::CollisionManager(const std::vector<Arbre *> &arbres, const std::vector<Champignon *> &champignons)
        : arbres(arbres), champignons(champignons) {}
bool CollisionManager::collisionCheck(Player *p) {
    bool collided = false;
    for (auto a : arbres) {
        if (p->getX() - p->getTaille() <= a->getX() + a->getRadius() &&
            p->getX() + p->getTaille() >= a->getX() - a->getRadius()
            && p->getZ() - p->getTaille() <= a->getZ() + a->getRadius() &&
            p->getZ() + p->getTaille() >= a->getZ() - a->getRadius()) {
            collided = true;
        }
    }
    for (auto c : champignons) {
        if (p->getX() - p->getTaille() <= c->getX() + c->getRadius() &&
            p->getX() + p->getTaille() >= c->getX() - c->getRadius()
            && p->getZ() - p->getTaille() <= c->getZ() + c->getRadius() &&
            p->getZ() + p->getTaille() >= c->getZ() - c->getRadius()) {
            collided = true;
        }
    }
    return collided;
}
bool CollisionManager::collisionBulletCheck(Player *playerThatShoot, Player *playerShot) {
    bool collided = false;
    for (auto b : playerThatShoot->getAbility0()->getBullets()) {
        if (playerShot->getX() - playerShot->getTaille() <= b->getX() + b->getRadius() &&
            playerShot->getX() + playerShot->getTaille() >= b->getX() - b->getRadius()
            && playerShot->getZ() - playerShot->getTaille() <= b->getZ() + b->getRadius() &&
            playerShot->getZ() + playerShot->getTaille() >= b->getZ() - b->getRadius()) {
            collided = true;
            b->setActive(false);
            playerShot->takeDamage(playerShot->getAbility0()->getDamage());
        }
        for (auto a : arbres) {
            if (b->getX() - b->getRadius() <= a->getX() + a->getRadius() &&
                b->getX() + b->getRadius() >= a->getX() - a->getRadius()
                && b->getZ() - b->getRadius() <= a->getZ() + a->getRadius() &&
                b->getZ() + b->getRadius() >= a->getZ() - a->getRadius()) {
                collided = true;
                b->setActive(false);
            }
        }
        for (auto c : champignons) {
            if (b->getX() - b->getRadius() <= c->getX() + c->getRadius() &&
                b->getX() + b->getRadius() >= c->getX() - c->getRadius()
                && b->getZ() - b->getRadius() <= c->getZ() + c->getRadius() &&
                b->getZ() + b->getRadius() >= c->getZ() - c->getRadius()) {
                collided = true;
                b->setActive(false);
            }
        }
    }
    return collided;
}

