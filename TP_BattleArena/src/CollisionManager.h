//
// Created by Administrator on 8/18/2021.
//

#ifndef TP_BATTLEARENA_COLLISIONMANAGER_H
#define TP_BATTLEARENA_COLLISIONMANAGER_H
#include "Player.h"
#include "Arbre.h"
class CollisionManager {
protected:
    std::vector<Arbre *> arbres;
public:
    CollisionManager(const std::vector<Arbre *> &arbres);
     bool collisionCheck(Player * p);
};
#endif //TP_BATTLEARENA_COLLISIONMANAGER_H
