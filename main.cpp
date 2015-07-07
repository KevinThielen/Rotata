#if defined(EMSCRIPTEN)
    #include <emscripten/emscripten.h>
#endif

#include <GameEngine.h>
#include "MenuScene.h"
#include "GameData.h"
#include <Utility/Analytics.h>


/*
void update()
{
    static kte::GameEngine* g = kte::GameEngine::instance();
    
    g->update();
}*/
 
int main()
{
  
    kte::Analytics::enable(false);
    kte::GameEngine* gameEngine = kte::GameEngine::instance();
    
#if defined(EMSCRIPTEN)
    gameEngine->run(new MenuScene, kte::WindowDesc("Emscripten"), false);
   
    emscripten_set_main_loop(update, 0, 1);
    while(1)
    {
	update();
    }
#else
    gameEngine->run(new MenuScene, kte::WindowDesc("Rubix"), true);  
#endif
    
    return 0;
}


