#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <IGameScene.h>
#include "GameData.h"

#include "Level/Level.h"
#include <unistd.h>

class GameScene : public kte::IGameScene
{
public:
    GameScene() : kte::IGameScene()
    {

    }
    
    virtual bool init()
    {
        initDefaultSystem();
        if(!loadData())
	    return false;
	
	level.load(scene.get(), &resources);
	paused = false;
	pauseScreen = kte::GameSprite(scene.get(), glm::vec4(0,0,0,0.6f));
	pauseScreen.setSize(800,600);
	pauseScreen.setActive(false);
	pauseScreen.setLayer(ELayers::GUI-3);
	
	gameOverScreen = kte::GameSprite(pauseScreen.getGameObject(), resources.getTexture(Textures::gameOver));
	gameOverScreen.setSize(382, 210);
	gameOverScreen.setPosition((800 - 382)/2.0f, (600-210)/2.0f);
	gameOverScreen.setLayer(ELayers::GUI-2);
	
	restartButton = kte::GameSprite(gameOverScreen.getGameObject(), resources.getTexture(Textures::restart));
	restartButton.setSize(172, 46);
	restartButton.setPosition(10, 210 - 56);
	restartButton.setLayer(ELayers::GUI-1);
	
	nextLevelButton = kte::GameSprite(gameOverScreen.getGameObject(), resources.getTexture(Textures::next));
	nextLevelButton.setSize(172, 46);
	nextLevelButton.setPosition(382 - 182, 210 - 56);
	nextLevelButton.setLayer(ELayers::GUI-1);
	
	
	//onlcik callbacks
	restartButton.setOnClickEvent(
	   [this]()
	    {
		pauseScreen.setActive(false);
		paused = false;
		level.load(scene.get(), &resources);
	    }
	);
	
	pauseScreen.setActive(false);
        return true;
    }

    virtual void update(float dt)
    {
        IGameScene::update(dt);
	
	if(!paused)
	{
	    if(level.checkWinCondition())
	    {
		std::cout<<"GameOver"<<std::endl;
		paused = true;
		level.pause();
		pauseScreen.setActive(true);
	    }
	}
    }

    bool loadData()
    {
        if(!resources.loadTextureFromFile(Textures::overlay))
	    return false;
	if(!resources.loadTextureFromFile(Textures::cell))
	    return false;
	if(!resources.loadTextureFromFile(Textures::background))
	    return false;
	if(!resources.loadTextureFromFile(Textures::rotator))
	    return false;
	if(!resources.loadTextureFromFile(Textures::next))
	    return false;
	if(!resources.loadTextureFromFile(Textures::gameOver))
	    return false;
	if(!resources.loadTextureFromFile(Textures::restart))
	    return false;
	
	return true;
    
    }
    
private:
    Level level;
    bool paused;
    kte::GameSprite pauseScreen;
    kte::GameSprite gameOverScreen;
    kte::GameSprite restartButton;
    kte::GameSprite nextLevelButton;
};

#endif