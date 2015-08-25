#ifndef OPTIONS_SCENE_H
#define OPTIONS_SCENE_H

#include <GameEngine.h>
#include <IGameScene.h>
#include <Graphics/GameSprite.h>
#include <Audio/AudioSource.h>

#include "GameData.h"
#include "GUI/GUIElement.h"
#include "GUI/GUISlider.h"
#include "GUI/GUICheckBox.h"


class OptionsScene : public kte::IGameScene
{
public:
    OptionsScene() : kte::IGameScene()
    {

    }
    
    virtual bool init()
    {
        initDefaultSystem();
        loadData();

	audioStream.initialize();
	
	gui = GUIElement(scene.get());
	slider = GUISlider(&gui, glm::vec2(50, 150));
	slider.setLeftPart(resources.getTexture(Textures::leftSlider), glm::vec2(2,3), glm::vec2(0,0)); 
	slider.setMiddlePart(resources.getTexture(Textures::middleSlider), glm::vec2(100,3), glm::vec2(2,0)); 
	slider.setRightPart(resources.getTexture(Textures::rightSlider), glm::vec2(2,3), glm::vec2(102,0)); 
	slider.setCursor(resources.getTexture(Textures::sliderCursor), glm::vec2(5,12), glm::vec2(2,-5));
	slider.setOnChange(
	    [this](int value)
	    {
		kte::Audio::masterVolume = 0.01f * value;
		this->audioStream.play(resources.getAudio(Audio::menuHover));
	    }
	);
	
	checkBox = GUICheckBox(&gui, glm::vec2(160,142));
	checkBox.setCheckBox(resources.getTexture(Textures::guiCheckBox), glm::vec2(0,0), glm::vec2(32,32));
	checkBox.setCheckMark(resources.getTexture(Textures::guiCheckMark), glm::vec2(0,0), glm::vec2(32,32));
	checkBox.setOnChangeValue(
	    [](bool value)
	    {
		kte::Audio::muted = value;
	    }
	);
	
	analyticsCheckBox = GUICheckBox(&gui, glm::vec2(80,200));
	analyticsCheckBox.setCheckBox(resources.getTexture(Textures::guiCheckBox), glm::vec2(0,0), glm::vec2(32,32));
	analyticsCheckBox.setCheckMark(resources.getTexture(Textures::guiCheckMark), glm::vec2(0,0), glm::vec2(32,32));
	analyticsCheckBox.setOnChangeValue(
	    [](bool value)
	    {
		kte::Analytics::enable(value);
	    }
	);
	
	
	kte::GameEngine::instance()->getContext()->setFullscreen(true	);
	std::vector<glm::vec2> resolutions = kte::GameEngine::instance()->getContext()->getScreenResolutions();
	
	for(auto resolution : resolutions) 
	    std::cout<<"Resolution: "<<resolution.x<<"x"<<resolution.y<<std::endl;
	

	return true;
    }

    virtual void update(float dt)
    {
        IGameScene::update(dt);
	
	if(kte::isKeyDown(GLFW_KEY_ESCAPE))
	{
	    kte::GameEngine* engine = kte::GameEngine::instance();
	    engine->popScene();   
	}
    }

    bool loadData()
    {
	if(!resources.loadTextureFromFile(Textures::leftSlider))
	    return false;
	if(!resources.loadTextureFromFile(Textures::middleSlider))
	    return false;
	if(!resources.loadTextureFromFile(Textures::rightSlider))
	    return false;
	if(!resources.loadTextureFromFile(Textures::sliderCursor))
	    return false;
	if(!resources.loadTextureFromFile(Textures::guiCheckMark))
	    return false;
	if(!resources.loadTextureFromFile(Textures::guiCheckBox))
	    return false;

	if(!resources.loadAudioFromFile(Audio::menuHover))
	    return false;

	
    return true;
    }
    
private: 
    GUIElement gui;
    GUISlider slider;
    GUICheckBox checkBox;
    GUICheckBox analyticsCheckBox;
    
    
    kte::AudioSource audioStream;
};

#endif