
#include "GameFlow.h"

int main(int argc, char **args) {
    srand(time(NULL));
    GameFlow * j = new GameFlow(1200, 800, 5000, 2000);
    j->loop();
    j->clean();
    return 0;
}


