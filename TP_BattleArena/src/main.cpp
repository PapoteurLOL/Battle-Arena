#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include "Arbre.h"
#include "Champignon.h"
#include "Utils.h"
int main(int argc, char **args) {
    srand(time(NULL));
    SDL_Window *win;
    int width = 1024, height = 800;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG);
    Mix_Init(MIX_INIT_MP3);
    win = SDL_CreateWindow("opengl Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                           SDL_WINDOW_OPENGL);

    //Preparer les differents sons
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    Mix_Chunk *son1 = Mix_LoadWAV("./assets/car.mp3");

    //precise la version d opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //creation du context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);
    //appelle la matrice de projection
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    GLuint idDesert = Utils::loadTexture("./assets/desert-skybox.png");
    GLUquadric *params = gluNewQuadric();
    glMatrixMode(GL_PROJECTION);
    //initialise la matrice de projection à 0
    glLoadIdentity();
    //modifie la matrice de projection pour avoir la perspective voulue
    gluPerspective(70, (double) 800 / 600, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    SDL_Event event;
    float angleX = 0;
    float angleZ = 0;
    float x = 50, y = 30, z = 50;
    const Uint8 *state = nullptr;
    std::vector<Arbre *> arbres;
    std::vector<Champignon *> champignons;
    int nbArbres = 1000;
    int nbChampignons = 500;
    for (int nb = 0; nb < nbArbres; ++nb) {
        int sign = 1;
        if (rand() % 2 == 0) {
            sign = -1;
        } else {
            sign = 1;
        }
        float xPositionArbres = sign * rand() % 250;
        if (rand() % 2 == 0) {
            sign = -1;
        } else {
            sign = 1;
        }
        float zPositionArbres = sign * rand() % 250;
        arbres.push_back(new Arbre(xPositionArbres * 5, .01, zPositionArbres * 5, params));
    }
    for (int nb = 0; nb < nbChampignons; ++nb) {
        int sign = 1;
        if (rand() % 2 == 0) {
            sign = -1;
        } else {
            sign = 1;
        }
        float xPositionChampignons = sign * rand() % 250;
        if (rand() % 2 == 0) {
            sign = -1;
        } else {
            sign = 1;
        }
        float zPositionChampignons = sign * rand() % 250;
        arbres.push_back(new Arbre(xPositionChampignons * 5, .01, zPositionChampignons * 5, params));
    }
    if (son1 == NULL) {
        SDL_Log("erreur chargement son");
    }
    //jouer son
    Mix_PlayChannel(2, son1, 0);
    while (isRunning) {
        glLoadIdentity();
        gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
        //Nettoyer la fenêtre
        glClearColor(0.0f, 0.f, 0.f,
                     1.f); //permet d'expliquer avec quelle couleur on va remplir la memoire des couleurs
        glClear(GL_COLOR_BUFFER_BIT |
                GL_DEPTH_BUFFER_BIT); //permet de dire que la memoire des couleurs est prête à être modifié
        //gestion évènement
        SDL_PollEvent(&event);
        state = SDL_GetKeyboardState(NULL);
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (state[SDL_SCANCODE_ESCAPE]) {
            isRunning = false;
        }
        if (state[SDL_SCANCODE_LEFT]) {
            x -= .1;
        }
        if (state[SDL_SCANCODE_RIGHT]) {
            x += .1;
        }
        if (state[SDL_SCANCODE_UP]) {
            z -= .1;
        }
        if (state[SDL_SCANCODE_DOWN]) {
            z += .1;
        }

        //dessin des différents objet dans la fenêtre

        //plateforme

        //dessiner skybox
        glPushMatrix();
        Utils::drawSkybox(250, 150, 250, idDesert);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, -10, 0);
        Utils::drawCube(250, .01, 250);
        //dessiner arbres
//        for (auto arbre :arbres) {
//            arbre->draw();
//        }
        for (auto champ :champignons) {
            champ->draw();
        }
        glPopMatrix();
        //glBindTexture(GL_TEXTURE_2D, NULL);
//        glPushMatrix();
//        //corps champignon
//        glColor3f(110.0 / 255.0, 40.0 / 255.0, 155.0 / 255.0);
//        gluQuadricDrawStyle(params, GLU_FILL);
//        glTranslatef(0, .01, 0);
//        glRotatef(-90, 1, 0, 0);
//        gluCylinder(params, 5, 2.5, 20, 10, 1);
//
//        //tete champignon
//        glTranslatef(0, 0, 20);
//        glColor3f(1, 1, 0);
//        glScalef(1, 1, .20);
//        gluSphere(params, 10, 20, 20);
//        Utils::drawAxis(10);
//        glPopMatrix();


        //mise a jour de l'écran
        glFlush();
        SDL_GL_SwapWindow(win);
        angleX += 1;
        angleZ += 1;
        //pause dans l'image
        SDL_Delay(1);
    }
    Mix_FreeChunk(son1);
    gluDeleteQuadric(params);
    glDeleteTextures(1, &idDesert);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    return 0;
}
                        
