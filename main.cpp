#include <GameEngine.h>
#include "GameScene.h"
#include "GameData.h"



int main()
{
    std::cout<<"jfdkbkdjfnbdnf,gbrk"<<std::endl;
    kte::GameEngine* gameEngine = kte::GameEngine::instance();
    gameEngine->run(new GameScene, kte::WindowDesc("Rubix"), true);

    return 0;
}

