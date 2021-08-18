//
// Created by jlidou on 2021-08-12.
//

#ifndef DEMOFIRSTSDL_UTILS_H
#define DEMOFIRSTSDL_UTILS_H
#include <GL/gl.h>
#include <string>
#include <SDL2/SDL_image.h>

class Utils {
public:
    static void drawAxis(float taille);
    static void drawQuads(float height, float lenght, float red, float green, float blue);
    static void drawQuadsHollow(float height, float lenght, float red, float green, float blue);
    static void drawCube(float tailleX, float tailleY, float tailleZ);
    static void drawSkybox(float tailleX, float tailleY, float tailleZ, GLuint idTexture) {
        float v1_3 = 1.0 / 3.0;
        float v1_4 = 1.0 / 4.0;
        float v1_2 = 1.0 / 2.0;
        float v2_3 = 2.0 / 3.0;
        float v3_4 = 3.0 / 4.0;
        float v0 = 0.0;
        float v1 = 1.0;
        glPushMatrix();
        glScalef(tailleX, tailleY, tailleZ);
        glBindTexture(GL_TEXTURE_2D, idTexture);
        glBegin(GL_QUADS);

        //face avant
        glColor3f(1, 1, 1);
        glTexCoord2f(v1_4, v1_3);glVertex3f(-1, -1, 1);
        glTexCoord2f(v1_2, v1_3);glVertex3f(1, -1, 1);
        glTexCoord2f(v1_2, v2_3);glVertex3f(1, 1, 1);
        glTexCoord2f(v1_4, v2_3);glVertex3f(-1, 1, 1);

        //face du gauche
        glColor3f(1, 1, 1);
        glTexCoord2f(v1_4, v1_3);glVertex3f(-1, -1, 1);
        glTexCoord2f(v0, v1_3);glVertex3f(-1, -1, -1);
        glTexCoord2f(0, v2_3);glVertex3f(-1, 1, -1);
        glTexCoord2f(v1_4, v2_3);glVertex3f(-1, 1, 1);

        //face du droite
        glColor3f(1, 1, 1);
        glTexCoord2f(v1_2, v1_3);
        glVertex3f(1, -1, 1);
        glTexCoord2f(v3_4, v1_3);
        glVertex3f(1, -1, -1);
        glTexCoord2f(v3_4, v2_3);
        glVertex3f(1, 1, -1);
        glTexCoord2f(v1_2, v2_3);
        glVertex3f(1, 1, 1);

        //face du arriere
        glColor3f(1, 1, 1);
        glTexCoord2f(v1, v1_3);
        glVertex3f(1, -1, -1);
        glTexCoord2f(v1, v2_3);
        glVertex3f(1, 1, -1);
        glTexCoord2f(v3_4, v2_3);
        glVertex3f(-1, 1, -1);
        glTexCoord2f(v3_4, v1_3);
        glVertex3f(-1, -1, -1);

        //face du haut
        glColor3f(1, 1, 1);
        glTexCoord2f(v1_2,v2_3);glVertex3f(1, 1, 1);
        glTexCoord2f(v1_2,v1);glVertex3f(1, 1, -1);
        glTexCoord2f(v1_4,v1);glVertex3f(-1, 1, -1);
        glTexCoord2f(v1_4,v2_3);glVertex3f(-1, 1, 1);

        //face du bas
        glColor3f(1, 1, 1);
        glTexCoord2f(v1_4,v0);glVertex3f(-1, -1, 1);
        glTexCoord2f(v1_2,v0);glVertex3f(1, -1, 1);
        glTexCoord2f(v1_2,v1_3);glVertex3f(1, -1, -1);
        glTexCoord2f(v1_4,v1_3);glVertex3f(-1, -1, -1);
        glEnd();
        //glBindTexture(GL_TEXTURE_2D, NULL);
        glPopMatrix();
    }
    GLuint loadTexture(std::string path) {
        GLuint idTexture = 0;
        SDL_Surface *surfaceTemp1 = IMG_Load(path.c_str());
        if (surfaceTemp1 == nullptr) {
            SDL_Log("file not load");
            exit(404);
        }
        SDL_Surface *surfaceTemp2 = flipSurface(surfaceTemp1);
        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);
        int Mode = GL_RGB;
        if (surfaceTemp2->format->BytesPerPixel == 4) {
            Mode = GL_RGBA;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, Mode, surfaceTemp2->w, surfaceTemp2->h, 0, Mode, GL_UNSIGNED_BYTE,
                     surfaceTemp2->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(surfaceTemp1);
        SDL_FreeSurface(surfaceTemp2);
        glBindTexture(GL_TEXTURE_2D, 0);
        return idTexture;
    }
    SDL_Surface *flipSurface(SDL_Surface *surface) {
        int current_line, pitch;
        SDL_Surface *fliped_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                                           surface->w, surface->h,
                                                           surface->format->BitsPerPixel,
                                                           surface->format->Rmask,
                                                           surface->format->Gmask,
                                                           surface->format->Bmask,
                                                           surface->format->Amask);
        SDL_LockSurface(surface);
        SDL_LockSurface(fliped_surface);
        pitch = surface->pitch;
        for (current_line = 0; current_line < surface->h; current_line++) {
            memcpy(&((unsigned char *) fliped_surface->pixels)[current_line * pitch],
                   &((unsigned char *) surface->pixels)[(surface->h - 1 -
                   current_line) * pitch],
                   pitch);
        }
        SDL_UnlockSurface(fliped_surface);
        SDL_UnlockSurface(surface);
        return fliped_surface;
    }
};
#endif //DEMOFIRSTSDL_UTILS_H