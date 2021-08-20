#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include "SkyboxElements/Arbre.h"
#include "SkyboxElements/Champignon.h"
#include "Utils.h"
#include "Camera.h"
#include "Projectile.h"
#include "Enemy.h"
#include "CollisionManager.h"
void
drawsplitScreen(Player *p1, Player *p2, Enemy *enemy, int width, int height, Camera *c1, Camera *c2, const Uint8 *state,
                GLUquadric *params, GLuint idTextureBullet, GLuint idTextureSkybox, GLuint idTextureSol,
                std::vector<Arbre *> arbres,
                std::vector<Champignon *> champignons, int tailleMonde, CollisionManager *collmanag,
                Uint32 startPosition);
int main(int argc, char **args) {
    srand(time(NULL));
    SDL_Window *win;
    int width = 800, height = 600;
    int tailleMonde = 2000;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
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
    GLuint idSolSkybox = Utils::loadTexture("./assets/sol.jpg");
    glMatrixMode(GL_PROJECTION);
    //initialise la matrice de projection à 0
    glLoadIdentity();
    //modifie la matrice de projection pour avoir la perspective voulue
    gluPerspective(70, (double) (width / height), 1, tailleMonde * 3);
    glMatrixMode(GL_MODELVIEW);
    SDL_Event event;
    float angleX = 0;
    float angleZ = 0;
    float x = 10, y = 10, z = 10;
    float x2 = 15, y2 = 10, z2 = 15;
    const Uint8 *state = nullptr;
    Uint32 startRotation;
    //jouer son
    Mix_PlayChannel(2, son1, -1);
    GLUquadric *params = gluNewQuadric();
    GLuint idTankTexture = Utils::loadTexture("./assets/tanktexture.jpg");
    GLuint idBulletTexture = Utils::loadTexture("./assets/bullettexture.jpg");
    Player *p1 = new Player(params, idTankTexture, 10, 10, {0, 1, 0}, 0, 2, 0.5, 20, tailleMonde);
    Camera *c1 = new Camera(p1);
    Player *p2 = new Player(params, idTankTexture, 10, 10, {5, 1, 0}, 0, 1, 0.5, 20, tailleMonde);
    Camera *c2 = new Camera(p2);
    std::vector<Arbre *> arbres;
    std::vector<Champignon *> champignons;
    int nbArbres = 250;
    int nbChampignons = 100;
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
        arbres.push_back(new Arbre(xPositionArbres * 5, .01, zPositionArbres * 5, params, 5));
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
        champignons.push_back(new Champignon(xPositionChampignons * 5, .01, zPositionChampignons * 5, params, 5, 200));
    }
    if (son1 == NULL) {
        SDL_Log("erreur chargement son");
    }
    float enemyPosX = 0;
    float enemyPosY = 20;
    float enemyPosZ = -800;
    float enemyVelocity = .2;
    Enemy *enemy = new Enemy(params, enemyPosX, enemyPosY, enemyPosZ, enemyVelocity);
//    std::vector<Enemy *> enemies;
//    for (int i = 0; i < 5; i++) {
//        int sign = 1;
//        if (rand()%2 == 0)
//            sign = -1;
//        else
//            sign = 1;
//        enemies.push_back(new Enemy(params, sign * rand() % 700, 2, sign * rand() % 700, .2));
//    }

    CollisionManager *collisionManager = new CollisionManager(arbres, champignons);
    while (isRunning) {
        glLoadIdentity();
        //Nettoyer la fenêtre
        glClearColor(0.0f, 0.f, 0.f,
                     1.f); //permet d'expliquer avec quelle couleur on va remplir la memoire des couleurs
        glClear(GL_COLOR_BUFFER_BIT |
                GL_DEPTH_BUFFER_BIT); //permet de dire que la memoire des couleurs est prête à être modifié
        //gestion évènement
        SDL_PollEvent(&event);
        state = SDL_GetKeyboardState(NULL);
        startRotation = SDL_GetTicks();
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
        //OTHERCAMERA
        if (state[SDL_SCANCODE_A]) {
            x2 -= .1;
        }
        if (state[SDL_SCANCODE_D]) {
            x2 += .1;
        }
        if (state[SDL_SCANCODE_W]) {
            z2 -= .1;
        }
        if (state[SDL_SCANCODE_S]) {
            z2 += .1;
        }
        drawsplitScreen(p1, p2, enemy, width, height, c1, c2, state, params, idBulletTexture, idDesert, idSolSkybox,
                        arbres,
                        champignons, tailleMonde, collisionManager,startRotation);
        if (!p1->isActive() || !p2->isActive())
            isRunning = false;
        //mise a jour de l'écran
        glFlush();
        SDL_GL_SwapWindow(win);
        //pause dans l'image
        SDL_Delay(1);
    }
    delete p1;
    gluDeleteQuadric(params);
    glDeleteTextures(1, &idTankTexture);
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
void
drawsplitScreen(Player *p1, Player *p2, Enemy *enemy, int width, int height, Camera *c1, Camera *c2, const Uint8 *state,
                GLUquadric *params, GLuint idTextureBullet, GLuint idTextureSkybox, GLuint idTextureSol,
                std::vector<Arbre *> arbres,
                std::vector<Champignon *> champignons, int tailleMonde, CollisionManager *collmanag,
                Uint32 startPosition) {
    glViewport(0, 0, width, height);
    c1->move();
    if (!collmanag->collisionCheck(p1)) {
        p1->move(state, params, idTextureBullet);
    } else {
        p1->forceMoveBack();
    }
    collmanag->collisionBulletCheck(p1, p2);
    //dessiner skybox
    Utils::drawSkybox(tailleMonde, tailleMonde, tailleMonde, idTextureSkybox);
    //dessiner platforme
    Utils::drawCube(tailleMonde, .1, tailleMonde, idTextureSol);
    //dessiner arbres
    for (auto arbre : arbres) {
        arbre->draw();
    }
    //dessiner champignons
    for (auto champ : champignons) {
        champ->draw();
    }
    for (auto champ : champignons) {
        champ->move(startPosition);
    }
    //dessiner player
    p1->draw();
    p2->draw();
    //dessiner enemy
    enemy->draw();
    enemy->trackPlayer(p1->getX(), p1->getY(), p1->getZ());
    enemy->spawnEgg(params);

    //        for (Enemy *e : enemies) {
    //            e->draw();
    //        }
    //
    //        for (Enemy *e : enemies) {
    //            e->trackPlayer(p1->getX(), p1->getY(), p1->getZ());
    //        }

//    glViewport(0, height / 2, width, height);
//    glLoadIdentity();
//    c2->move();
//    Utils::drawCube(2000, .1, 2000);
//    p2->draw();
//    p1->draw();
//    enemy->draw();
//    enemy->trackPlayer(p1->getX(), p1->getY(), p1->getZ());
}
