#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <IGameScene.h>
#include <Utility/Serializer.h>
#include <Utility/Analytics.h>

#include "GameData.h"

#include "Level/Level.h"
#include "Level/Levels.h"

#include "MenuScene.h"
class GameScene : public kte::IGameScene
{
public:
    GameScene(Levels levels, unsigned int startLevel = 0) : kte::IGameScene(), analytics(kte::Analytics("localhost", 8080))
    {
	this->levels = levels;
	currentLevel = startLevel;
    }
    
    GameScene() : kte::IGameScene(), analytics(kte::Analytics("localhost", 8080))
    {
	currentLevel = 0;
    }
    
    virtual bool init()
    {
        initDefaultSystem();
        if(!loadData())
	    return false;
	
	popScene = false;

	
	level.load(scene.get(), &resources, levels.getLevel(currentLevel), &analytics);
	paused = false;
	pauseScreen = kte::GameSprite(scene.get(), glm::vec4(0,0,0,0.4f));
	pauseScreen.setSize(800,600);
	pauseScreen.setActive(false);
	pauseScreen.setLayer(ELayers::GUI-3);
	
	gameOverScreen = kte::GameSprite(pauseScreen.getGameObject(), resources.getTexture(Textures::gameOver));
	gameOverScreen.setSize(400,210);
	gameOverScreen.setPosition((800-400)*0.5f, (600-210)*0.5f);
	gameOverScreen.setLayer(ELayers::GUI-2);
	
	gameOverText.setFont(resources.getFont(Fonts::smallFont));
	gameOverText.setPosition(gameOverScreen.getPosition().x +5, gameOverScreen.getPosition().y +5);
	gameOverText.setColor(Color::WHITE);
	
	newBestText.setFont(resources.getFont(Fonts::smallFont));
	newBestText.setPosition(gameOverText.getPosition().x, gameOverText.getPosition().y + 75);
	newBestText.setColor(Color::YELLOW);
	
	gameOverButtons.resize(3);
	buttontexts.resize(3);
	
	for(int i =0; i<3; i++)
	{
	    gameOverButtons[i] = kte::GameSprite(gameOverScreen.getGameObject(), resources.getTexture(Textures::menuButton));
	    gameOverButtons[i].setSize((gameOverScreen.getSize().x - 40) / 3.0f, 60);
	    gameOverButtons[i].setPosition(gameOverButtons[i].getSize().x * i +  10 + i*10, gameOverScreen.getSize().y - 70);
	    gameOverButtons[i].setLayer(ELayers::GUI-1);
	        
	    buttontexts[i] = kte::Text();
	    buttontexts[i].setFont(resources.getFont(Fonts::smallFont));

	    buttontexts[i].setColor(Color::WHITE);
	    
	    gameOverButtons[i].setOnMouseOverEvent(
		 [this, i]()
		 {
		     this->gameOverButtons[i].setColor(Color::YELLOW);
		     this->buttontexts[i].setColor(Color::YELLOW);
		 }
	    );
	    
	      gameOverButtons[i].setOnMouseLeaveEvent(
		 [this, i]()
		 {
		     this->gameOverButtons[i].setColor(Color::WHITE);
		     this->buttontexts[i].setColor(Color::WHITE);
		 }
	    );
	}
	
	buttontexts[0].setString("Retry");
	buttontexts[0].setPosition(gameOverButtons[0].getWorldPosition().x + 5, gameOverButtons[0].getWorldPosition().y + 15);
	
	buttontexts[1].setString("Select\nLevel");
	buttontexts[1].setSize(0.6f, 0.6f);
	buttontexts[1].setPosition(gameOverButtons[1].getWorldPosition().x + 5, gameOverButtons[1].getWorldPosition().y + 5);
	
	buttontexts[2].setString("Next");
	buttontexts[2].setPosition(gameOverButtons[2].getWorldPosition().x + 10, gameOverButtons[2].getWorldPosition().y + 15);

	
	//onlcik callbacks
	gameOverButtons[0].setOnReleaseEvent(
	   [this]()
	    {
		pauseScreen.setActive(false);
		paused = false;
		gameOver = false;
		pausedPressed = false;
		level.load(scene.get(), &resources, levels.getLevel(currentLevel), &analytics);
	    }
	);
	
	gameOverButtons[1].setOnReleaseEvent(
	[this]()
	  {
	    popScene = true;
	  }
	);    
	gameOverButtons[2].setOnReleaseEvent(
	   [this]()
	    {
		pauseScreen.setActive(false);
		paused = false;
		gameOver = false;
		pausedPressed = false;
		level.load(scene.get(), &resources, levels.getLevel(++currentLevel), &analytics);
	    }
	    );
	
	
	pauseNode = pauseScreen.getGameObject()->addChild();	
	pauseButtons.resize(3);
	pauseTexts.resize(3);
	for(int i =0; i<3; i++)
	{
	    pauseButtons[i] = kte::GameSprite(pauseNode, resources.getTexture(Textures::menuButton));
	    pauseButtons[i].setSize(160, 60);
	    pauseButtons[i].setPosition((800 - 160)*0.5f , (600 - 3*70)*0.5f + i*70);
	    
	    std::cout<<"Button Position: "<<pauseButtons[i].getPosition().x<<"/"<<pauseButtons[i].getPosition().y<<std::endl;
	    pauseButtons[i].setLayer(ELayers::GUI-1);
	        
	    pauseTexts[i] = kte::Text();
	    pauseTexts[i].setFont(resources.getFont(Fonts::smallFont));

	    pauseTexts[i].setColor(Color::WHITE);
	    
	    pauseButtons[i].setOnMouseOverEvent(
		 [this, i]()
		 {
		     this->gameOverButtons[i].setColor(Color::YELLOW);
		     this->pauseButtons[i].setColor(Color::YELLOW);
		 }
	    );
	    
	      pauseButtons[i].setOnMouseLeaveEvent(
		 [this, i]()
		 {
		     this->gameOverButtons[i].setColor(Color::WHITE);
		     this->pauseButtons[i].setColor(Color::WHITE);
		 }
	    );
	}
	
	pauseTexts[0].setString("Continue");
	pauseTexts[0].setPosition(pauseButtons[0].getWorldPosition().x + 5, pauseButtons[0].getWorldPosition().y + 15);
	
	pauseTexts[1].setString("Restart");
	pauseTexts[1].setPosition(pauseButtons[1].getWorldPosition().x + 10, pauseButtons[1].getWorldPosition().y + 15);
	
	pauseTexts[2].setString("Select\nLevel");
	pauseTexts[2].setSize(0.6f, 0.6f);
	pauseTexts[2].setPosition(pauseButtons[2].getWorldPosition().x + 15, pauseButtons[2].getWorldPosition().y + 5);

	
	//onlcik callbacks
	pauseButtons[0].setOnReleaseEvent(
	   [this]()
	    {
		pause();
	    }
	);
	
	pauseButtons[1].setOnReleaseEvent(
	[this]()
	  {
	    pauseScreen.setActive(false);
	    paused = false;
	    level.load(scene.get(), &resources, levels.getLevel(currentLevel), &analytics);
	  }
	);    
	pauseButtons[2].setOnReleaseEvent(
	   [this]()
	    {		
		popScene = true;
	    }
	    );
		
	
	pauseScreen.setActive(false);
	gameOver = false;
	pausedPressed = false;
	
        return true;
    }

    virtual void update(float dt)
    {
        IGameScene::update(dt);
	
	if(kte::isKeyDown(GLFW_KEY_ESCAPE) && !pausedPressed)
	    pausedPressed = true;
	else if(pausedPressed && !kte::isKeyDown(GLFW_KEY_ESCAPE) )
	{
	    pausedPressed = false;
	    pause();
	}
	
	if(popScene)
	{
	     kte::GameEngine* engine = kte::GameEngine::instance();
	     engine->popScene();

	}
	else if(!paused)
	{
	    level.update(this, dt);
	    if(level.checkWinCondition())
	    {
		//save progress
		kte::Serializer serializer;
		serializer.read("save.dat");
		
		float timer = level.getTimer();
		int rotations = level.getRotations();
		
		float fractionalDigits = (int)((timer-(int)timer)*100);
		std::string formattedTimer =  std::to_string((int)timer) + "." + std::to_string((int)fractionalDigits);
		
		bool bestTime = false;
		bool bestTurns = false;
		
		std::string gameOverString = "Congratulations!\nYou finished the level.\n\n”";
		std::string  newBestString = "";
		if(serializer[levels.getLevel(currentLevel).name].empty() || serializer[levels.getLevel(currentLevel).name] > timer)		
		{
		    serializer[levels.getLevel(currentLevel).name] = timer;
		    bestTime = true;
		}
	
		if(serializer[levels.getLevel(currentLevel).name+"_rotations"].empty() || serializer[levels.getLevel(currentLevel).name+"_rotations"] > rotations)
		{
		    serializer[levels.getLevel(currentLevel).name+"_rotations"] = rotations;
		    bestTurns = true;
		    
		}

		
		if(bestTime)
		    newBestString += "New Best Time: "+formattedTimer+"\n";
		    
		serializer.persist("save.dat");
		
		gameOverText.setString(gameOverString);
		newBestText.setString(newBestString);

		analytics["LevelID"] = currentLevel+1;
		analytics["finishTime"] = timer;
		
		
		analytics.sendData();
		analytics.resetData();
		
		paused = true;
		level.pause(true);
		pauseScreen.setActive(true);
		pauseNode->setActive(false);
		gameOver  =true;
	    }
	}
	else
	{
	    level.update(this, 0);
	    	
	    if(gameOver)
	    {
		displayText(newBestText);
		displayText(gameOverText);
		displayText(buttontexts);
	    }
	    else
	    {
		   displayText(pauseTexts);
	    }
	}
    }

    bool loadData()
    {
        if(!resources.loadTextureFromFile(Textures::overlay))
	    return false;
        if(!resources.loadTextureFromFile(Textures::overlayR))
	    return false;
	if(!resources.loadTextureFromFile(Textures::cell))
	    return false;
	if(!resources.loadTextureFromFile(Textures::background))
	    return false;
	if(!resources.loadTextureFromFile(Textures::rotator))
	    return false;
	if(!resources.loadTextureFromFile(Textures::next))
	    return false;
	if(!resources.loadTextureFromFile(Textures::menuButton))
	    return false;
	if(!resources.loadTextureFromFile(Textures::gameOver))
	    return false;
	if(!resources.loadTextureFromFile(Textures::restart))
	    return false;
	if(!resources.loadTextureFromFile(Textures::levelSelect))
	    return false;
	if(!resources.loadFontFromFile(Fonts::title, 86))
	    return false;
	if(!resources.loadFontFromFile(Fonts::smallFont, 38))
	    return false;
	if(!resources.loadAudioFromFile(Audio::rotation, true))
	    return false;
	if(!resources.loadAudioFromFile(Audio::rotationEnd))
	    return false;
	if(!resources.loadAudioFromFile(Audio::rotatorClick))
	    return false;
	if(!resources.loadAudioFromFile(Audio::finished))
	    return false;
	
	return true;
    
    }
    
    void pause()
    {
	if(!gameOver)
	{
	    if(!paused)
	    {
		level.pause(true);
		paused = true;
		pauseScreen.setActive(true);
		gameOverScreen.setActive(false);
		pauseNode->setActive(true);
	    }
	    else
	    {
		level.pause(false);
		paused = false;
		pauseScreen.setActive(false);
		gameOverScreen.setActive(false);
		pauseNode->setActive(false);
	    }
	}
    }
    
private:
    Level level;
    bool paused;
    bool gameOver;
    bool pausedPressed = true;
    kte::GameSprite pauseScreen;
    kte::GameSprite gameOverScreen;
    kte::GameObject* pauseNode;
    std::vector<kte::GameSprite> gameOverButtons;
    std::vector<kte::GameSprite> pauseButtons;
    std::vector<kte::Text> buttontexts;
    std::vector<kte::Text> pauseTexts;
    

    kte::Text gameOverText;
    kte::Text newBestText;
    kte::Analytics analytics;
    
    bool popScene;
    Levels levels;
    unsigned int currentLevel;
};

#endif