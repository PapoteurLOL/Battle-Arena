//
// Created by Administrator on 8/17/2021.
//

#ifndef TP_BATTLEARENA_PLAYER_H
#define TP_BATTLEARENA_PLAYER_H
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL2/SDL.h>
#include "iostream"
class Player {
protected:
    float x, y, z;
    float angleRotation;
    float velocity;
    float hp;
    GLuint idPlayer;
public:
    Player(GLUquadric *params, GLuint idTexture, float taille, float radius, float x, float y, float z, float angleRotation, float velocity, float hp);
    void Draw();
    virtual ~Player();
    void Move(const Uint8 *state);
};
#endif //TP_BATTLEARENA_PLAYER_H
