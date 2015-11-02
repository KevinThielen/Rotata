#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "GUIElement.h"
#include <Graphics/GameSprite.h>

class GUIComboBox : public GUIElement 
{
public:
    GUIComboBox() { }
    GUIComboBox(GUIElement* parent, kte::Texture* boxTexture, kte::Texture* elementTexture, glm::vec2 position, glm::vec2 size, int layer) : GUIElement(parent), elementTexture(elementTexture)
    {
	box = kte::GameSprite(parent->getGameObject(), boxTexture);
	box.setSize(size);
	box.setPosition(position);
	box.setLayer(layer);
	
	elementPanel = parent->getGameObject()->addChild();
	elementPanel->getComponent<kte::TransformationComponent>()->x = position.x;
	elementPanel->getComponent<kte::TransformationComponent>()->y = position.y;
	elementPanel->setActive(false);
	
	showElements(false);
    }
    
    
    void setFont(kte::FontTexture* font) 
    {
	this->font = font;
    }
    
    void setFontColor(glm::vec4 color) { fontColor = color; }
    void addElement(std::string element)
    {
	if(!font)
	{
	    std::cout<<"WARNING: Combobox Font not set!"<<std::endl;
	    return;
	}
	
	if(!elements.size())
	{
	    box.setOnReleaseEvent(
		[this]()
		{
		    showElements(true);
		}
	    );
	}
	
	kte::GameSprite e = kte::GameSprite(elementPanel, elementTexture);
	e.setPosition(0, elements.size()*box.getSize().y);
	e.setSize(box.getSize());
	e.setActive(false);
	e.setLayer(box.getLayer()+1);
	e.setOnReleaseEvent(
	    [this]()
	    {
		showElements(false);
	    }
	);
	int index = elements.size();
	e.setOnMouseOverEvent(
	    [this, index]()
	    {
		elements[index].setColor(glm::vec4(0,1,0,1));
	    }
	);
	e.setOnMouseLeaveEvent(
	    [this, index]()
	    {
		elements[index].setColor(glm::vec4(1,1,1,1));
	    }
	);
	elements.push_back(e);
	
	kte::Text text;
	text.setFont(font);
	text.setPosition(e.getWorldPosition().x,e.getWorldPosition().y);
	text.setString(element);
	text.setColor(fontColor);
	texts.push_back(text);
    }
    
    
    void selectElement(unsigned int index) 
    {
    }
    
    void showElements(bool show)
    {
	box.setActive(!show);
	elementPanel->setActive(show);
	this->show = show;
    }
    
    bool showElements() { return show; }
    std::vector<kte::Text> getTexts() { return texts; }
private:
    kte::Texture* elementTexture;
    kte::GameSprite box;
    std::vector<kte::Text> texts;
    std::vector<kte::GameSprite> elements;
    kte::GameObject* elementPanel;
    bool show;
    kte::FontTexture* font;
    glm::vec4 fontColor;
};

#endif