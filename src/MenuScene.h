#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include <IGameScene.h>
#include <GameEngine.h>
#include <Graphics/GameSprite.h>
#include <Utility/Serializer.h>
#include "GameData.h"
#include "GameScene.h"
#include "Level/Levels.h"

class MenuScene : public kte::IGameScene
{
public:
    enum class EMenuState
    {
	INTRO,
	MAIN,
	LEVEL_SELECT,
	EXIT
    };
    
    MenuScene() : kte::IGameScene()
    {

    }
    
    virtual bool init()
    {
	initDefaultSystem();
	if(!loadData())
	    return false;
	
	//read save file
	serializer.read("save.dat");
	
	//stateNodes
	levelSelectNode = scene.get()->addChild();
	menuNode = scene.get()->addChild();
	
	levelDescriptionNode = scene.get()->addChild();
	
	levelPanel = kte::GameSprite(levelDescriptionNode, glm::vec4(0,0,0.6f, 0.6f));
	levelPanel.setSize(300, 250);
	levelPanel.setPosition(800-levelPanel.getSize().x, 0);
    
	
	levelDescription.resize(2);
	levelDescription[0].setFont(resources.getFont(Fonts::font));
	levelDescription[0].setColor(glm::vec4(1,1,1,1));
	levelDescription[0].setString("");
	levelDescription[0].setPosition(levelPanel.getPosition().x, levelPanel.getPosition().y);
	
	
	levelDescription[1].setFont(resources.getFont(Fonts::font));
	levelDescription[1].setColor(glm::vec4(1,1,1,1));
	levelDescription[1].setString("");
	levelDescription[1].setPosition(levelPanel.getPosition().x, levelPanel.getPosition().y+25);
	
	
	levelDescriptionNode->setActive(false);
	
	//MENU
	const int START_BUTTON = 0;
	const int OPTION_BUTTON = 1;
	const int EXIT_BUTTON = 2;
	
	for(unsigned int i = 0; i<3; i++)
	{
	   kte::GameSprite button =  kte::GameSprite(menuNode, glm::vec4(1,0,0,1));
	   button.setSize(150,50);
	   button.setPosition(328, 150*i);
	   menuButtons.push_back(button);
	}
	
	menuButtons[START_BUTTON].setOnClickEvent(
	    [this](){
		changeState(EMenuState::LEVEL_SELECT);
	    }
	);
	menuButtons[OPTION_BUTTON].setOnClickEvent(
	    [this](){
		//changeState(EMenuState::LEVEL_SELECT);
	    }
	);
	
	menuButtons[EXIT_BUTTON].setOnClickEvent(
	    [this](){
		changeState(EMenuState::EXIT);
	    }    
	);
	
	
	
	//LEVEL SELECT
	unsigned int xCounter = 0;
	unsigned int yCounter = 0;
	const float tileSize = 96;
	const float xOffset = 25.0f;
	const float yOffset = 100.0f;
	
	for(int i = 0; i<levels.getNumberOfLevels(); i++)
	{
	    xCounter++;
	    if(xCounter>=5)
	    {
		xCounter = 0;
		yCounter++;
	    }
	    
	    kte::GameSprite tile = kte::GameSprite(levelSelectNode, resources.getTexture(Textures::levelSelect));
	    tile.setSize(tileSize,tileSize);
	    tile.setPosition(xCounter * tileSize + xOffset, yCounter * tileSize + yOffset);
	    

	    if(!serializer[levels.getLevel(i).name].empty())
	    {
		kte::GameSprite flag = kte::GameSprite(tile.getGameObject(), resources.getTexture(Textures::medal));
		flag.setSize(16,16);
		flag.setPosition(tileSize-20, tileSize-20);
		completionFlags.push_back(flag);
	    }
	    
	    
	    tile.setOnClickEvent(
		[this, i]()
		{
		    kte::GameEngine* engine = kte::GameEngine::instance();
		    GameScene* scene = new GameScene(levels, i);
		    engine->pushScene(scene);
		}
	    );
	    
	    tile.setOnMouseOverEvent(
		[this, i]()
		{
		    this->showLevelDescription(i);
		}	
	    );
	    
	    levelTiles.push_back(tile);
	    
	kte::Text text;
	text.setFont(resources.getFont(Fonts::font));
	text.setString(std::to_string(i+1));
	text.setColor(glm::vec4(1,1,1,1));
	text.setPosition(tile.getPosition().x, tile.getPosition().y);
	texts.push_back(text);
	    
	}
	
	state = EMenuState::INTRO;
	changeState(EMenuState::MAIN);
	
        return true;
    }

    void changeState(EMenuState state)
    {
	if(this->state != state)
	{
	    switch (state)
	    {
		case EMenuState::LEVEL_SELECT: 
		{
		    this->state = state;
		    menuNode->setActive(false);
		    levelSelectNode->setActive(true);
		    break;
		}
		case EMenuState::MAIN:
		{
		    menuNode->setActive(true);
		    levelSelectNode->setActive(false);
		    
		    break;   
		}
		default: {kte::GameEngine::instance()->exit();}
		    
	    }
	}
	
    }
    virtual void update(float dt)
    {
        IGameScene::update(dt);
	
	if(state == EMenuState::LEVEL_SELECT)
	{
	    if(showDescription)
		displayText(levelDescription);
	    
	    displayText(texts);
	}
    }

    bool loadData()
    {
	if(!resources.loadTextureFromFile(Textures::levelSelect))
	    return false;
	if(!resources.loadTextureFromFile(Textures::medal))
	    return false;
	
	//if(!resources.loadFontFromFile(Fonts::font, 96))
	//    return false;
	
	if(!resources.loadFontFromFile(Fonts::font, 24))
	    return false;

	return true;
    }
    
    void showLevelDescription(unsigned int levelId)
    {
	showDescription = true;

	levelDescription[0].setString("");
	levelDescription[1].setString("");
	levelDescription[0].setString(levels.getLevel(levelId).name);

	if (!serializer[levels.getLevel(levelId).name].empty())
	{
	  //  float time = serializer[levels.getLevel(levelId).name].asFloat();
	    levelDescription[1].setString("Time: "+serializer[levels.getLevel(levelId).name].asString());
	}
	levelDescriptionNode->setActive(true);
    }
    
private:
    std::vector<kte::GameSprite> menuButtons;
    std::vector<kte::GameSprite> levelTiles;
    std::vector<kte::GameSprite> completionFlags;
    kte::GameSprite levelPanel;
    std::vector<kte::Text> levelDescription;
    
    Levels levels;
    std::vector<kte::Text> texts;
    kte::GameObject* levelSelectNode;
    kte::GameObject* menuNode;
    kte::GameObject* levelDescriptionNode;
    
    bool showDescription;
    
    kte::Serializer serializer;
    
    EMenuState state;
    
};

#endif