//
// Created by Administrator on 8/18/2021.
//

#ifndef TP_BATTLEARENA_COLLISIONMANAGER_H
#define TP_BATTLEARENA_COLLISIONMANAGER_H
#include "Player.h"
#include "SkyboxElements/Arbre.h"
#include "SkyboxElements/Champignon.h"
class CollisionManager {
protected:
    std::vector<Arbre *> arbres;
    std::vector<Champignon *> champignons;
public:
    CollisionManager(const std::vector<Arbre *> &arbres, const std::vector<Champignon *> &champignons);
    bool collisionCheck(Player * p);
    bool collisionBulletCheck(Player * playerThatShoot, Player * playerShot);
};
#endif //TP_BATTLEARENA_COLLISIONMANAGER_H
