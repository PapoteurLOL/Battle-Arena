//
// Created by Administrator on 8/20/2021.
//

#include "GameFlow.h"
GameFlow::GameFlow(int widthScreen, int heightScreen, GLdouble zfar, float wSize) : widthScreen(widthScreen),
                                                                                    heightScreen(heightScreen),
                                                                                    zFar(zfar), worldSize(wSize) {
    init();
    createObject();
}
void GameFlow::init() {
    isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG || IMG_INIT_PNG);
    Mix_Init(MIX_INIT_MP3);
    win = SDL_CreateWindow("opengl Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, widthScreen, heightScreen,
                           SDL_WINDOW_OPENGL);

    //Preparer les differents sons
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    sonBG = Mix_LoadWAV("./assets/car.mp3");


    //precise la version d opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //creation du context
    context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);
    //appelle la matrice de projection
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    //initialisation de texture
    idDesert = Utils::loadTexture("./assets/desert-skybox.png");
    idSolSkybox = Utils::loadTexture("./assets/sol.jpg");
    idTankTexture = Utils::loadTexture("./assets/tanktexture.jpg");
    idBulletTexture = Utils::loadTexture("./assets/bullettexture.jpg");
    glMatrixMode(GL_PROJECTION);
    //initialise la matrice de projection à 0
    glLoadIdentity();
    //modifie la matrice de projection pour avoir la perspective voulue
    gluPerspective(70, (double) (widthScreen / heightScreen), 1, worldSize * 3);
    glMatrixMode(GL_MODELVIEW);
    state = nullptr;
}
void GameFlow::loop() {
    while (isRunning) {
        glLoadIdentity();
        //Nettoyer la fenêtre
        glClearColor(0.0f, 0.f, 0.f,
                     1.f); //permet d'expliquer avec quelle couleur on va remplir la memoire des couleurs
        glClear(GL_COLOR_BUFFER_BIT |
                GL_DEPTH_BUFFER_BIT); //permet de dire que la memoire des couleurs est prête à être modifié
        move();
        draw();
        //check game end
        if (!p1->isActive() || !p2->isActive())
            isRunning = false;
        //mise a jour de l'écran
        glFlush();
        SDL_GL_SwapWindow(win);
        //pause dans l'image
        SDL_Delay(5);
    }
}
void GameFlow::clean() {
    delete p1;
    gluDeleteQuadric(params);
    glDeleteTextures(1, &idTankTexture);
    Mix_FreeChunk(sonBG);
    gluDeleteQuadric(params);
    glDeleteTextures(1, &idDesert);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    IMG_Quit();
    Mix_Quit();
    SDL_Quit();
}
void GameFlow::createObject() {
    //jouer son
    Mix_PlayChannel(2, sonBG, -1);
    if (sonBG == NULL) {
        SDL_Log("erreur chargement son");
    }
    //param pour quad
    params = gluNewQuadric();
    //creation player et cam
    p1 = new Player(params, idTankTexture, 10, 10, {0, 1, 0}, 0, 0.5, 0.5, 100, worldSize, SDL_SCANCODE_W,
                    SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_SPACE);
    c1 = new Camera(p1);
    p2 = new Player(params, idTankTexture, 10, 10, {5, 1, 0}, 0, 0.5, 0.5, 100, worldSize, SDL_SCANCODE_UP,
                    SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_P);
    c1 = new Camera(p1);
    c2 = new Camera(p2);
    //creation arbre et champignons
    nbArbres = 250;
    nbChampignons = 100;
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
    //creation enemies
    for (int i = 0; i < 5; i++) {
        enemies.push_back(new Enemy(params, rand() % 3000 - 1000, 4, rand() % 3000 - 1000, .2));
    }
    //creation du manager de collision
    collisionManager = new CollisionManager(arbres, champignons);
}
void GameFlow::move() {
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
}
void GameFlow::draw() {
    //UI PLAYER 1
    glViewport(0, heightScreen - heightScreen / 8, widthScreen, heightScreen / 8);
    glLoadIdentity();
    drawUi();
    //        GAMESCREEN PLAYER 1
    glViewport(0, heightScreen / 2, widthScreen, heightScreen * 3 / 8);
    glLoadIdentity();
    if (!p1->isDead())
        c1->move();
    drawsplitScreen();
    //UI PLAYER 2
    glViewport(0, heightScreen * 5 / 8, widthScreen, heightScreen / 8);
    glLoadIdentity();
    //GAMESCREEN PLAYER 2
    glViewport(0, 0, widthScreen, heightScreen * 3 / 8);
    glLoadIdentity();
    if (!p2->isDead())
        c2->move();
    drawsplitScreen();
}
void GameFlow::drawsplitScreen() {
    //verifier collision pour les 2 player
    //p1
    if (!collisionManager->collisionCheck(p1)) {
        p1->move(state, params, idBulletTexture);
    } else {
        p1->forceMoveBack();
    }
    collisionManager->collisionBulletCheck(p1, p2);
    //p2
    if (!collisionManager->collisionCheck(p2)) {
        p2->move(state, params, idBulletTexture);
    } else {
        p2->forceMoveBack();
    }
    collisionManager->collisionBulletCheck(p2, p1);
    //dessiner skybox
    Utils::drawSkybox(worldSize, worldSize, worldSize, idDesert);
    //dessiner platforme
    Utils::drawCube(worldSize, .1, worldSize, idSolSkybox);
    //dessiner arbres
    for (auto arbre : arbres) {
        arbre->draw();
    }
    //dessiner champignons
    for (auto champ : champignons) {
        champ->draw();
    }
    for (auto champ : champignons) {
        champ->move(0);
    }
    //dessiner player
    p1->draw();
    p2->draw();
    //dessiner enemy
    for (Enemy *e : enemies) {
        e->draw(const_cast<std::vector<Projectile *> &>(p1->getAbility0()->getBullets()));
        e->trackPlayer(p1->getX(), p1->getY(), p1->getZ());
        e->spawnEgg(params);
    }
}
void GameFlow::drawUi() {
    Utils::drawQuads(100, 100, 1, 0, 0);
}
