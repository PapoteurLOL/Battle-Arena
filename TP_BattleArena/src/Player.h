//
// Created by Administrator on 8/17/2021.
//

#ifndef TP_BATTLEARENA_PLAYER_H
#define TP_BATTLEARENA_PLAYER_H
#include "Ability.h"
class Player {
protected:
    Coord coord;
    float angleRotation;
    float velocityRotation;
    float velocity;
    float hp;
    GLuint idPlayer;
    float taille;
    float radius;
    Ability *ability0;
public:
    Player(GLUquadric *params, GLuint idTexture, float taille, float radius, Coord coord, float angleRotation,
           float velocity, float velocityRotation, float hp);
    void draw();
    float getTaille() const;
    float getRadius() const;
    virtual ~Player();
    void move(const Uint8 *state, GLUquadric *params, GLuint idTexture);
    float getX() const;
    float getY() const;
    float getZ() const;
    float getAngleRotation() const;
};
#endif //TP_BATTLEARENA_PLAYER_H
