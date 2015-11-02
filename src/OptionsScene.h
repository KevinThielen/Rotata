#ifndef OPTIONS_SCENE_H
#define OPTIONS_SCENE_H

#include <GameEngine.h>
#include <IGameScene.h>
#include <Graphics/GameSprite.h>
#include <Audio/AudioSource.h>
#include <Components/Camera.h>

#include "GameData.h"
#include "GUI/GUIElement.h"
#include "GUI/GUISlider.h"
#include "GUI/GUICheckBox.h"
#include "GUI/GUIComboBox.h"


class OptionsScene : public kte::IGameScene
{
public:
    OptionsScene() : kte::IGameScene()
    {

    }
    
    virtual bool init()
    {
        loadData();

	background = kte::GameSprite(scene.get(), resources->getTexture(Textures::background));
	background.setSize(800,600);
	background.setLayer(1);
	
	gui = GUIElement(scene.get());
	slider = GUISlider(&gui, glm::vec2(50, 150));
	slider.setLeftPart(resources->getTexture(Textures::leftSlider), glm::vec2(2,3), glm::vec2(0,0)); 
	slider.setMiddlePart(resources->getTexture(Textures::middleSlider), glm::vec2(100,3), glm::vec2(2,0)); 
	slider.setRightPart(resources->getTexture(Textures::rightSlider), glm::vec2(2,3), glm::vec2(102,0)); 
	slider.setCursor(resources->getTexture(Textures::sliderCursor), glm::vec2(5,12), glm::vec2(2,-5));
	
	slider.setOnChange(
	    [this](int value)
	    {
		kte::Music::masterVolume = 0.01f * value;
	//	this->audioStream.play(resources->getAudio(Audio::menuHover));
	    }
	);
	
	checkBox = GUICheckBox(&gui, glm::vec2(160,142));
	checkBox.setCheckBox(resources->getTexture(Textures::guiCheckBox), glm::vec2(0,0), glm::vec2(32,32));
	checkBox.setCheckMark(resources->getTexture(Textures::guiCheckMark), glm::vec2(0,0), glm::vec2(32,32));
	checkBox.setOnChangeValue(
	    [](bool value)
	    {
		kte::Sound::muted = value;
	    }
	);
	checkBox.setLabel("Mute", resources->getFont(Fonts::smallFont28), glm::vec2(50,0));
	
	analyticsCheckBox = GUICheckBox(&gui, glm::vec2(80,200));
	analyticsCheckBox.setCheckBox(resources->getTexture(Textures::guiCheckBox), glm::vec2(0,0), glm::vec2(32,32));
	analyticsCheckBox.setCheckMark(resources->getTexture(Textures::guiCheckMark), glm::vec2(0,0), glm::vec2(32,32));
	analyticsCheckBox.setOnChangeValue(
	    [](bool value)
	    {
		kte::GameEngine::instance()->getContext()->setFullscreen(value);
	    }
	);
	analyticsCheckBox.setLabel("Fullscreen", resources->getFont(Fonts::smallFont28), glm::vec2(50,0));
	
	
	comboBox = GUIComboBox(&gui, 
			       resources->getTexture(Textures::comboBox),
			       resources->getTexture(Textures::comboBoxElement),
			       glm::vec2(400,200),
			       glm::vec2(150,25), 10);
	
	comboBox.setFont(resources->getFont(Fonts::smallFont28));
	comboBox.setFontColor(glm::vec4(1,1,1,1));
	comboBox.addElement("800x600");
	comboBox.addElement("801x601");
	comboBox.addElement("802x602");
	
	slider.setLayer(2);
	checkBox.setLayer(2);
	analyticsCheckBox.setLayer(2);
	
	
	std::vector<glm::vec2> resolutions = kte::GameEngine::instance()->getContext()->getScreenResolutions();
        kte::GameEngine::instance()->getContext()->setScreenResolution(glm::vec2(1024, 768));
//	kte::Camera::getMainCamera()->setViewMatrix(0, 1024, 768, 0);
	
	// 	
// 	for(auto resolution : resolutions) 
// 	    std::cout<<"Resolution: "<<resolution.x<<"x"<<resolution.y<<std::endl;
	
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
	if(kte::isKeyDown(GLFW_KEY_DOWN))
	{
	    kte::Camera::getMainCamera()->move(0, -dt*10);
	}
	if(kte::isKeyDown(GLFW_KEY_UP))
	{
	    kte::Camera::getMainCamera()->move(0, dt*10);
	}
	displayText(*checkBox.getLabel());
	displayText(*analyticsCheckBox.getLabel());
	
	if(comboBox.showElements())
	    displayText(comboBox.getTexts());
    }

    bool loadData()
    {
 	if(!resources->loadPackage("GUI"))
 	    return false;
	
	return true;
    }
    
private: 
    kte::GameSprite background;
    GUIElement gui;
    GUISlider slider;
    GUICheckBox checkBox;
    GUICheckBox analyticsCheckBox;
    GUIComboBox comboBox;
    
    kte::AudioSource audioStream;
};

#endif