#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H

#include <GameObject.h>
#include <Graphics/Text.h>

class GUIElement
{
public:
    GUIElement() { gameObject = nullptr; }
    GUIElement(kte::GameObject* parent) 
    {
	gameObject = parent->addChild();
    }
   
   void setLabel(std::string text, kte::FontTexture* font, glm::vec2 offset = glm::vec2(50,10), glm::vec4 color = glm::vec4(1,1,1,1))
   {
       kte::TransformationComponent* trans = gameObject->getComponent<kte::TransformationComponent>();
       label.setFont(font);
       label.setString(text);
       label.setPosition(offset.x + trans->x, offset.y + trans->y);
       label.setColor(color);
   }
   
   kte::Text* getLabel() { return &label; }
   
    GUIElement(GUIElement* parent)
    {
	gameObject = parent->getGameObject()->addChild();
    }

    virtual void setLayer(unsigned int layer)
    {
    }
    
  kte::GameObject* getGameObject() { return gameObject; }
  
protected:
    kte::GameObject* gameObject;
    kte::Text label;
};

#endif