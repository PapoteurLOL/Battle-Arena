#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include "Arbre.h"
#include "Utils.h"
void playMusic(int channel, Mix_Chunk *chunk, int loops);
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
    Mix_Chunk *son1 = Mix_LoadWAV("./assets/Car-Theft-101.mp3");
    Mix_Chunk *son2 = Mix_LoadWAV("./assets/Nighttime-Escape.mp3");

    //precise la version d opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //creation du context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);
    //appelle la matrice de projection
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    GLuint idDesert = loadTexture("./assets/desert-skybox.png");
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
    float x = 50, y = 20, z = 50;
    const Uint8 *state = nullptr;
    std::vector<Arbre *> arbres;
    int nbArbres = 500;
    for (int nb = 0; nb < nbArbres; ++nb) {
        float xPositionArbres = rand() % 250;
        float yPositionArbres = rand() % 250;
        arbres.push_back(new Arbre(xPositionArbres * 5, .01, yPositionArbres * 5, params));
    }
    if (son1 == NULL || son2 == NULL) {
        SDL_Log("erreur chargement son");
    }
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
        if (state[SDL_SCANCODE_C] && event.type == SDL_KEYDOWN && event.key.repeat == 0) {
            Mix_PlayChannel(1, son1, -1);
        }

        //jouer son
        //        Mix_PlayChannel(1, son1, 0);
        //        if (Mix_Playing(1) != 0) {
        //        }
        //        Mix_PlayChannel(2, son2, 0);
        //        if (Mix_Playing(2) != 0) {
        //        }
        //        playMusic(1, son1, 0);
        //        playMusic(2, son2, 0);


        //dessin des différents objet dans la fenêtre

        //plateforme

        //dessiner skybox
        glPushMatrix();
        drawSkybox(250, 150, 250, idDesert);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(0, -10, 0);
        drawCube(250, .01, 250);
        //dessiner arbres
        for (auto arbre :arbres) {
            arbre->draw();
        }
        glPopMatrix();
        drawAxis(2);

        //mise a jour de l'écran
        glFlush();
        SDL_GL_SwapWindow(win);
        angleX += 0.5;
        angleZ += 0.5;
        //pause dans l'image
        SDL_Delay(1);
    }
    Mix_FreeChunk(son1);
    Mix_FreeChunk(son2);
    gluDeleteQuadric(params);
    glDeleteTextures(1, &idDesert);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
    return 0;
}
void playMusic(int channel, Mix_Chunk *chunk, int loops) {
    channel = Mix_PlayChannel(channel, chunk, loops);
    if (channel < 0) {
        return SDL_Log("Aucune chanson");
    }
    while (Mix_Playing(channel) != 0) {
        SDL_Delay(20);
    }
}
                        
