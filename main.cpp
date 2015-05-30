#include <GameEngine.h>
#include "GameScene.h"
#include "GameData.h"


int main()
{
    kte::GameEngine* gameEngine = kte::GameEngine::instance();
    gameEngine->run(new GameScene, kte::WindowDesc("Rubix"));

    return 0;
}