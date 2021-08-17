//
// Created by Administrator on 8/17/2021.
//

#ifndef TP_BATTLEARENA_PLAYER_H
#define TP_BATTLEARENA_PLAYER_H
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "iostream"
struct Coord {
    float x, y, z;
};
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
public:
    Player(GLUquadric *params, GLuint idTexture, float taille, float radius, Coord coord, float angleRotation, float velocity, float velocityRotation, float hp);
    void draw();
    float getTaille() const;
    float getRadius() const;
    virtual ~Player();
    void move(const Uint8 *state);
    float getX() const;
    float getY() const;
    float getZ() const;
    float getAngleRotation() const;
};
#endif //TP_BATTLEARENA_PLAYER_H
