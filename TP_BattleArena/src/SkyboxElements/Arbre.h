//
// Created by PAPOTEUR on 2021-08-17.
//

#ifndef SKYBOX_ARBRE_H
#define SKYBOX_ARBRE_H
#include <GL/gl.h>
#include <GL/glu.h>
class Arbre {
private:
    float x, y, z, angleRotate = 0;
    GLuint idTexture;
    float radius;
public:
    Arbre(float x, float y, float z, GLUquadric *params, float radius);
    void draw();
    void move();
    virtual ~Arbre();
    float getX() const;
    float getZ() const;
    float getRadius() const;
};
#endif //SKYBOX_ARBRE_H
