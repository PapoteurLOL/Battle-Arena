#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Utils.h"
#include "Camera.h"
void splitScreen(Player *p1,Player *p2,int width, int height, Camera *c1,Camera *c2,const Uint8 *state);
int main(int argc, char **args) {
    SDL_Window *win;
    int width = 800, height = 600;
    bool isRunning = true;
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_JPG);
    win = SDL_CreateWindow("opengl Template", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                           SDL_WINDOW_OPENGL);

    //precise la version d opengl
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    //creation du context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(0);
    //appelle la matrice de projection
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    //initialise la matrice de projection à 0
    glLoadIdentity();
    //modifie la matrice de projection pour avoir la perspective voulue
    gluPerspective(70, (double) (width / height), 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    SDL_Event event;
    float angleX = 0;
    float angleZ = 0;
    float x = 10, y = 10, z = 10;
    float  x2 = 15,y2 = 10,z2 = 15;
    const Uint8 *state = nullptr;
    GLUquadric *params = gluNewQuadric();
    GLuint idTankTexture = Utils::loadTexture("./assets/tanktexture.jpg");
    Player *p1 = new Player(params, idTankTexture, 18, 16, {0, 1, 0}, 0, 0.5, 0.5, 20);
    Camera *c1 = new Camera(p1);
    GLUquadric *params2 = gluNewQuadric();
   Player *p2 = new Player(params2,idTankTexture,18,16,{5,1,0},0,0.5,0.5,20);
   Camera *c2 = new Camera(p2);
    while (isRunning) {
        glLoadIdentity();
//        glPushMatrix();
//        gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
      //  c1->move();
//        glPopMatrix();
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
        //OTHERCAMERA
        if (state[SDL_SCANCODE_A]) {
            x2-= .1;
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
        //p1->move(state);
        //dessin des différents objet dans la fenêtre

       /* glViewport(0,0,width,height/2);
        gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
        Utils::drawCube(10,.1,10);

        glViewport(0, height/2, width,height);
        glLoadIdentity();
        gluLookAt(x2, y2, z2, 0, 0, 0, 0, 1, 0);
        glTranslatef(15,1,10);
        Utils::drawCube(10, .1, 10);*/


        //Player
        //p1->draw();
        splitScreen(p1,p2,width,height,c1,c2,state);


        //mise a jour de l'écran
        glFlush();
        SDL_GL_SwapWindow(win);
       // angleX += 0.1;
       // angleZ += 0.05;
        //pause dans l'image
        SDL_Delay(1);
    }
    //delete p1;
    gluDeleteQuadric(params);
    glDeleteTextures(1, &idTankTexture);
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
    return 0;
}

void splitScreen(Player *p1,Player *p2,int width, int height, Camera *c1, Camera *c2, const Uint8 *state){
    glViewport(0,0,width,height/2);
    c1->move();
    p1->move(state);
    Utils::drawCube(10, .1, 10);
    p1->draw();
    p2->draw();
    glViewport(0, height/2, width,height);
    glLoadIdentity();
    c1->move();
    c2->move();
    Utils::drawCube(10, .1, 10);
    p2->draw();
    p1->draw();

}
