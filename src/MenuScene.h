#ifndef MENU_SCENE_H
#define MENU_SCENE_H

#include <IGameScene.h>
#include <GameEngine.h>
#include <Graphics/GameSprite.h>
#include <Audio/AudioSource.h>
#include <Utility/Serializer.h>
#include "GameData.h"
#include "GameScene.h"
#include "Level/Levels.h"
#include "OptionsScene.h"
#include <X11/X.h>


#include <fstream>

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
	//initDefaultSystem();
	if(!loadData())
	    return false;
	
	
	
//  	kte::GameEngine::instance()->getContext()->setWireframe();
	audioStream.initialize();
	audioStream2.initialize();
	
	//read save file
	serializer.read("save.dat");
	
	background = kte::GameSprite(scene.get(), resources->getTexture(Textures::background));
	background.setSize(800,600);
	background.setLayer(ELayers::background);
	
	float leftOffset = 75.0f;
	
	titleText.resize(5);

	titleText[0] = kte::Text();
	titleText[0].setFont(resources->getFont(Fonts::title118));
	titleText[0].setPosition((800-300)*0.5f-leftOffset, 20);
	titleText[0].setString("R");
	titleText[0].setColor(Color::RED);
	
	titleText[1] = kte::Text();
	titleText[1].setFont(resources->getFont(Fonts::title118));
	titleText[1].setPosition((800-300)*0.5f+100-leftOffset+25, 20);
	titleText[1].setString("u");
	titleText[1].setColor(Color::BLUE);
	
	titleText[2] = kte::Text();
	titleText[2].setFont(resources->getFont(Fonts::title118));
	titleText[2].setPosition((800-300)*0.5f+180-leftOffset+50, 20);
	titleText[2].setString("b");
	titleText[2].setColor(Color::GREEN);
	
	titleText[3] = kte::Text();
	titleText[3].setFont(resources->getFont(Fonts::title118));
	titleText[3].setPosition((800-300)*0.5f+255-leftOffset+75, 20);
	titleText[3].setString("i");
	titleText[3].setColor(Color::PURPLE);
	
	titleText[4] = kte::Text();
	titleText[4].setFont(resources->getFont(Fonts::title118));
	titleText[4].setPosition((800-300)*0.5f+300-leftOffset+80, 20);
	titleText[4].setString("x");
	titleText[4].setColor(Color::YELLOW);
	
	//stateNodes
	levelSelectNode = background.getGameObject()->addChild();
	menuNode = background.getGameObject()->addChild();
	
	levelDescriptionNode = scene.get()->addChild();
	
	levelPanel = kte::GameSprite(levelDescriptionNode, resources->getTexture(Textures::levelDescription));
	levelPanel.setSize(250, 150);
	levelPanel.setPosition(800-levelPanel.getSize().x, 110);
        levelPanel.setLayer(ELayers::background+1);
	
	levelDescription.resize(2);
	levelDescription[0].setFont(resources->getFont(Fonts::font));
	levelDescription[0].setColor(glm::vec4(1,1,1,1));
	levelDescription[0].setString("");
	levelDescription[0].setPosition(levelPanel.getPosition().x+5, levelPanel.getPosition().y+5);

	
	levelDescription[1].setFont(resources->getFont(Fonts::smallFont28));
	levelDescription[1].setColor(glm::vec4(1,1,1,1));
	levelDescription[1].setString("");
	levelDescription[1].setPosition(levelPanel.getPosition().x+5, levelPanel.getPosition().y+50);
	
	levelDescriptionNode->setActive(false);
	{
	    kte::GameSprite widget = kte::GameSprite(menuNode, resources->getTexture(Textures::menuWidget));
	    widget.setPosition(550,160);
	    widget.setSize(127,127);
	    widget.setLayer(ELayers::background+2);
	    widget.setColor(glm::vec4(1,1,1,0.5f));
	    menuWidgets.push_back(widget);
	}
	
	{
	    kte::GameSprite widget = kte::GameSprite(menuNode, resources->getTexture(Textures::menuWidget));
	    widget.setPosition(600,400);
	    widget.setSize(127,127);
	    widget.setLayer(ELayers::background+2);
	    widget.setColor(glm::vec4(1,1,1,0.5f));
	    menuWidgets.push_back(widget);
	}
	
	{
	    kte::GameSprite widget = kte::GameSprite(menuNode, resources->getTexture(Textures::menuWidget));
	    widget.setPosition(125,270);
	    widget.setSize(127,127);
	    widget.setLayer(ELayers::background+2);
	    widget.setColor(glm::vec4(1,1,1,0.5f));
	    menuWidgets.push_back(widget);
	}
	
	//MENU
	const int START_BUTTON = 0;
	const int OPTION_BUTTON = 1;
	const int EXIT_BUTTON = 2;
	

	
	for(unsigned int i = 0; i<3; i++)
	{
	   kte::GameSprite button =  kte::GameSprite(menuNode, resources->getTexture(Textures::menuButton));
	   button.setSize(175,60);
	   button.setPosition((800 - 175)*0.5f, 75*i + 200);
	   button.setLayer(ELayers::background+2);
	   button.setColor(glm::vec4(1,1,1,0.6f));
	   menuButtons.push_back(button);
	   
	   kte::Text buttonText;
	   buttonText.setFont(resources->getFont(Fonts::buttonFont));
	   buttonText.setPosition(button.getPosition().x+10, button.getPosition().y+15);
	   buttonTexts.push_back(buttonText);
	   
	   button.setOnMouseOverEvent(
		[this, i]() 
		{
		    this->menuButtons[i].setColor(Color::YELLOW);
		}  
	   );
	   
	   button.setOnMouseLeaveEvent(
		[this, i]() 
		{
		    this->menuButtons[i].setColor(glm::vec4(1,1,1,0.6f));
		}
	   );
	}
	
	
	buttonTexts[0].setString("PLAY");
	buttonTexts[0].setColor(Color::GREEN);
	menuButtons[START_BUTTON].setOnReleaseEvent(
	    [this](){
		changeState(EMenuState::LEVEL_SELECT);
		    this->audioStream2.play(resources->getAudio(Audio::menuSelect));
	    }
	);
	
	buttonTexts[1].setFont(resources->getFont(Fonts::optionsFont));
	buttonTexts[1].setString("Options");
	buttonTexts[1].setColor(Color::BLUE);
	menuButtons[OPTION_BUTTON].setOnReleaseEvent(
	    [this](){
	
		    IGameScene* scene = new OptionsScene();
	
		    kte::GameEngine::instance()->pushScene(scene);
	    }
	);
	
	buttonTexts[2].setString("Exit");
	buttonTexts[2].setColor(Color::RED);
	menuButtons[EXIT_BUTTON].setOnReleaseEvent(
	    [this](){
		changeState(EMenuState::EXIT);
	    }    
	);
	
	
	
	//LEVEL SELECT
	unsigned int xCounter = 0;
	unsigned int yCounter = 0;
	const float tileSize = 96;
	const float xOffset = 25.0f;
	const float yOffset = 110.0f;
	int lastFinishedLevel = 0;
	
	for(int i = 0; i<levels.getNumberOfLevels(); i++)
	{

	    if(xCounter>=5)
	    {
		xCounter = 0;
		yCounter++;
	    }
	    
	    bool playable = true;
	    kte::GameSprite tile = kte::GameSprite(levelSelectNode, resources->getTexture(Textures::levelSelect));
	    tile.setSize(tileSize,tileSize);
	    tile.setPosition(xCounter * tileSize + xOffset, yCounter * tileSize + yOffset);
	    tile.setLayer(ELayers::background+1);

	    if(!serializer[levels.getLevel(i).name].empty())
	    {
		kte::GameSprite flag = kte::GameSprite(tile.getGameObject(), resources->getTexture(Textures::checkMark));
		flag.setSize(tileSize, tileSize);
		flag.setLayer(ELayers::background+3);
		completionFlags.push_back(flag);
		
		lastFinishedLevel++;
	    }
	    else if(lastFinishedLevel < i)
	    {
		kte::GameSprite flag = kte::GameSprite(tile.getGameObject(), resources->getTexture(Textures::lock));
		flag.setSize(tileSize, tileSize);
		flag.setLayer(ELayers::background+3);
		completionFlags.push_back(flag);
		
		tile.setOnMouseOverEvent(
		[this, i]()
		{
		    this->showLevelDescription();
		    this->levelTiles[i].setColor(Color::YELLOW);
		}  
	        );
	   
		tile.setOnMouseLeaveEvent(
		[this, i]() 
		{
		   this->levelTiles[i].setColor(glm::vec4(1,1,1,1));
		   if(!this->newDescrption)
		   {
		       showDescription = false;
		    levelDescriptionNode->setActive(false);
		   }
		}
	        );
		
		playable = false;
	    }
	    else
	    {
		kte::GameSprite flag = kte::GameSprite(tile.getGameObject(), glm::vec4(0,0,0,0));
		flag.setSize(tileSize, tileSize);
		flag.setLayer(ELayers::background+3);
		completionFlags.push_back(flag);
	    }
	    if(playable  || CHEAT_MODE)
	    {
		tile.setOnReleaseEvent(
		[this, i]()
		{
		    kte::GameEngine* engine = kte::GameEngine::instance();
		    this->audioStream2.play(resources->getAudio(Audio::menuSelect));
		    
		    GameScene* scene = new GameScene(levels, i);
	
		    engine->pushScene(scene);
		});
		
		tile.setOnMouseOverEvent(
		[this, i]()
		{
		    this->showLevelDescription(i);
		    this->levelTiles[i].setColor(Color::YELLOW);
		    this->audioStream.play(resources->getAudio(Audio::menuHover));
		}  
	        );
	   
		 tile.setOnMouseLeaveEvent(
		[this, i]() 
		{
		    this->levelTiles[i].setColor(glm::vec4(1,1,1,1));
		   if(!this->newDescrption)
		   {
		       showDescription = false;
		       levelDescriptionNode->setActive(false);
		   }
		}
	        );
	    }
	    
	    levelTiles.push_back(tile);
	    
	    kte::Text text;
	    text.setFont(resources->getFont(Fonts::font));
	    text.setString(std::to_string(i+1));
	    text.setColor(glm::vec4(1,1,1,1));
	    text.setPosition(tile.getPosition().x, tile.getPosition().y);
	    texts.push_back(text);

	    xCounter++;	    
	}
	
	state = EMenuState::INTRO;
	changeState(EMenuState::MAIN);
	
	
	subTitleText = kte::Text();
	subTitleText.setPosition(5,5);
	subTitleText.setFont(resources->getFont(Fonts::subTitle));
	subTitleText.addColor(Color::RED);
	subTitleText.addColor(Color::BLUE);
	subTitleText.addColor(Color::GREEN);
	subTitleText.addColor(Color::YELLOW);
	subTitleText.addColor(Color::PURPLE);
	subTitleText.addColor(Color::WHITE);
	subTitleText.addColor(Color::BLACK);

	
        return true;
    }

    void refresh()
    {
	//clear old informations
	for(auto& flag : completionFlags)
	{
	    flag.setColor(glm::vec4(0,0,0,0));
	}
	
	for(auto& tile : levelTiles)
	{
	    tile.setOnReleaseEvent(
		[]()
		{
		}
	    );
	}
	
	//reload the GameData
	serializer.read("save.dat");
	unsigned int lastFinishedLevel  = 0;
	bool playable = false;
	for(int i = 0; i<levelTiles.size(); i++)
	{
	    playable = false;
	    //level already played?
	    if(!serializer[levels.getLevel(i).name].empty())
	    {
		lastFinishedLevel++;
		completionFlags[i].setColor(glm::vec4(1,1,1,1));
		completionFlags[i].setTexture(resources->getTexture(Textures::checkMark));
		playable = true;
	    }
	    //check if level is the not the next playable level
	    else if(lastFinishedLevel < i && !CHEAT_MODE)
	    {
		completionFlags[i].setColor(glm::vec4(1,1,1,1));
		completionFlags[i].setTexture(resources->getTexture(Textures::lock));
		
		levelTiles[i].setOnMouseOverEvent(
		[this, i]()
		{
		    this->showLevelDescription();
		    this->levelTiles[i].setColor(Color::YELLOW);
		}  
	        );
	    }
	    else
		playable = true;
	    
	    if(playable  || CHEAT_MODE)
	    {
		levelTiles[i].setOnReleaseEvent(
		[this, i]()
		{
		    kte::GameEngine* engine = kte::GameEngine::instance();
		  
		    GameScene* scene = new GameScene(levels, i);
	
		    engine->pushScene(scene);
		    
		    this->audioStream2.play(resources->getAudio(Audio::menuSelect));
		});
		
		levelTiles[i].setOnMouseOverEvent(
		[this, i]()
		{
		    this->showLevelDescription(i);
		    this->levelTiles[i].setColor(Color::YELLOW);
		}  
	        );
	    }
	}
	
    }
    void changeState(EMenuState state)
    {
	if(this->state != state)
	{
	    switch (state)
	    {
		case EMenuState::LEVEL_SELECT: 
		{
		    subTitleText.setString("Select a Level");
		    menuNode->setActive(false);
		    levelSelectNode->setActive(true);
		    this->state = state;
		    
		    break;
		}
		case EMenuState::MAIN:
		{
		    menuNode->setActive(true);
		    levelSelectNode->setActive(false);
		    this->state = state;
		    
		    break;   
		}
		default: {kte::GameEngine::instance()->exit();}
	    }
	}
	
    }
    
    
   
    virtual void update(float dt)
    {
        
	
	static float timer = 0.0f;

	
	if(state == EMenuState::LEVEL_SELECT)
	{
	    
	    if(showDescription)
		displayText(levelDescription);
	 
	    displayText(texts);
	    displayText(subTitleText);
	}
	else if(state == EMenuState::MAIN)
	{
	    for(auto& widget : menuWidgets)
	    {
		widget.rotateByDegrees(5*dt);
	    }
	    displayText(buttonTexts);
	    displayText(titleText);
	}
	newDescrption = false;

    }

    bool loadData()
    {
	if(!resources->loadAudioFromFile(Audio::menuHover))
	    return false;
	
	if(!resources->loadAudioFromFile(Audio::menuSelect))
	    return false;
	
	
	if(!resources->loadPackage("Game"))
	    return false;
 	if(!resources->loadPackage("General"))
 	    return false;
	
	return true;
    }
    
    void showLevelDescription(unsigned int levelId)
    {
	newDescrption = true;
	showDescription = true;

	levelDescription[0].setColors(levels.getColorList(levelId));
	levelDescription[1].setColor(Color::GREEN);
	levelDescription[0].setString("");
	levelDescription[1].setString("");
	levelDescription[0].setString(levels.getLevel(levelId).name);

	if (!serializer[levels.getLevel(levelId).name].empty())
	{
	    float timer = serializer[levels.getLevel(levelId).name].asFloat();
	    float fractionalDigits = (int)((timer-(int)timer)*100);
	    std::string timerText = std::to_string((int)timer) + "." + std::to_string((int)fractionalDigits);
	    
	    levelDescription[1].setString("Best Time: "+timerText);
	}
	levelDescriptionNode->setActive(true);
    }
    
     void showLevelDescription()
    {
	newDescrption = true;
	showDescription = true;
	levelDescription[0].setString("");
	levelDescription[1].setString("");
	
	levelDescription[0].setString("LOCKED");
	levelDescription[0].setColor(Color::BLACK);
	levelDescriptionNode->setActive(true);
    }
    

    
    
private:
    std::vector<kte::Text> titleText;
    
    kte::Text subTitleText;
    std::vector<kte::GameSprite> menuWidgets;
    std::vector<kte::GameSprite> menuButtons;
    std::vector<kte::Text> buttonTexts;
    std::vector<kte::GameSprite> levelTiles;
    std::vector<kte::GameSprite> completionFlags;
    kte::GameSprite background;
    kte::GameSprite levelPanel;
    std::vector<kte::Text> levelDescription;
    
    Levels levels;
    std::vector<kte::Text> texts;
    kte::GameObject* levelSelectNode;
    kte::GameObject* menuNode;
    kte::GameObject* levelDescriptionNode;
    
    kte::AudioSource audioStream;
    kte::AudioSource audioStream2;
   
    bool showDescription;
    const bool CHEAT_MODE = true;
    bool newDescrption;
    kte::Serializer serializer;
    
    EMenuState state;
};

#endif