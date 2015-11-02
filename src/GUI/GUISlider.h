#ifndef GUI_SLIDER_H
#define GUI_SLIDER_H

#include "GUIElement.h"
#include <Graphics/GameSprite.h>

class GUISlider : public GUIElement 
{
public:
    GUISlider() { }
    
    GUISlider(GUIElement* parent, glm::vec2 position, unsigned int steps = 100, int increment = 1) : GUIElement(parent)
    {
	gameObject->getComponent<kte::TransformationComponent>()->x = position.x;
	gameObject->getComponent<kte::TransformationComponent>()->y = position.y;
	
	currentStep = 0;
	this->increment = increment;
	this->steps = steps;	
    }

    void setLayer(unsigned int layer)
    {
	left.setLayer(layer);
	middle.setLayer(layer);
	right.setLayer(layer);
	cursor.setLayer(middle.getLayer()+1);
    }
    void setLeftPart(kte::Texture* texture, glm::vec2 size, glm::vec2 position)
    {
	left = kte::GameSprite(gameObject, texture);
	left.setSize(size);
	left.setPosition(position);
    }
    
    
    void setMiddlePart(kte::Texture* texture, glm::vec2 size, glm::vec2 position)
    {
	middle = kte::GameSprite(gameObject, texture);
	middle.setSize(size);
	middle.setPosition(position);
    }
    
    
    void setRightPart(kte::Texture* texture, glm::vec2 size, glm::vec2 position)
    {
	right = kte::GameSprite(gameObject, texture);
	right.setSize(size);
	right.setPosition(position);
    }
    
    void setCursor(kte::Texture* texture, glm::vec2 size, glm::vec2 position)
    {
	cursor = kte::GameSprite(gameObject, texture);
	cursor.setSize(size);
	cursor.setPosition(position);
	cursor.setLayer(middle.getLayer()+1);
	startX = position.x;
	
	cursor.setOnDragEvent(
	    [this](float deltaX, float deltaY)
	    {
		glm::vec2 position = cursor.getPosition();
		
		int currentValue = getValue();
		if(position.x + deltaX < startX)
		{
		    currentStep = 0;
		    cursor.setPosition(startX, position.y);
		}
		else if(position.x + deltaX > startX+steps)
		{
		    currentStep = steps;
		    cursor.setPosition(startX+steps, position.y);
		}
		else 
		{
		    this->cursor.move(deltaX, 0);
		    currentStep += (int)deltaX;	      
		}	      
		
		if(currentValue != getValue())
		    onChange(getValue());
		
		currentValue = getValue();
	    }
	);
    }
    void setOnChange(std::function<void(int)> onChange)
    {
	this->onChange = onChange;
    }
    
    int getValue() { return currentStep * increment; }
private:
    //the slider is seperated in the middle part and the start/end for aesthetical reasons 
    kte::GameSprite left;
    kte::GameSprite middle;
    kte::GameSprite right;
    
    kte::GameSprite cursor;
    std::function<void(int)> onChange;
    
    float startX;
    
    unsigned int steps;
    int increment;
  
    int currentStep;
};


#endif