#ifndef GUI_CHECKBOX_H
#define GUI_CHECKBOX_H

#include "GUIElement.h"
#include <Graphics/GameSprite.h>

class GUICheckBox : public GUIElement 
{
public:
    GUICheckBox() { }
    
    GUICheckBox(GUIElement* parent, glm::vec2 position, bool checked = false) : GUIElement(parent)
    {
	gameObject->getComponent<kte::TransformationComponent>()->x = position.x;
	gameObject->getComponent<kte::TransformationComponent>()->y = position.y;
	
	this->checked = checked;
    }

    void setLayer(unsigned int layer)
    {
	checkBox.setLayer(layer);
	checkMark.setLayer(layer+1);
    }
    void setCheckBox(kte::Texture* texture, glm::vec2 position, glm::vec2 size)
    {
	checkBox = kte::GameSprite(gameObject, texture);
	checkBox.setSize(size);
	checkBox.setPosition(position);
	
	checkBox.setOnClickEvent(
	    [this]()
	    {
		checked = !checked;

		checkMark.setActive(checked);
		onChange(checked);
	    }
	    
	);
    }
    
    void setCheckMark(kte::Texture* texture, glm::vec2 position, glm::vec2 size)
    {
	checkMark = kte::GameSprite(gameObject, texture);
	checkMark.setSize(size);
	checkMark.setPosition(position);
	checkMark.setLayer(checkBox.getLayer()+1);

	checkMark.setActive(checked);
    }
    
    bool getValue() { return checked; }
    void setOnChangeValue(std::function<void(bool)> onChange)
    {
	this->onChange = onChange;
    }
private:
    bool checked;
    std::function<void(bool)> onChange;
    
    kte::GameSprite checkBox;
    kte::GameSprite checkMark;
};


#endif