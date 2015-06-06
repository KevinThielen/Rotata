#if defined(EMSCRIPTEN)
    #include <emscripten/emscripten.h>
#endif

#include <GameEngine.h>
#include "GameScene.h"
#include "GameData.h"




void update()
{
    static kte::GameEngine* g = kte::GameEngine::instance();
    
    g->update();
}
 
int main()
{
    kte::GameEngine* gameEngine = kte::GameEngine::instance();
    
#if defined(EMSCRIPTEN)
    gameEngine->run(new GameScene, kte::WindowDesc("Emscripten"), false);
   
    emscripten_set_main_loop(update, 0, 1);
    while(1)
    {
	update();
    }
#else
    gameEngine->run(new GameScene, kte::WindowDesc("Rubix"), true);  
#endif
    
 
    
    return 0;
}


