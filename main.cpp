#include "myGame.h"

int main()
{
    SceneManager sceneManager(1920, 1080, "Tahiti Shooter");
    myGame game(sceneManager);

    game.exec();

    return 0;
}