#ifndef GUI_ELEMENT_H
#define GUI_ELEMENT_H
#include <Audio/AudioData.h>

#include <GameObject.h>

class GUIElement
{
public:
    GUIElement() { gameObject = nullptr; }
    GUIElement(kte::GameObject* parent) 
    {
	gameObject = parent->addChild();
    }
   
    GUIElement(GUIElement* parent)
    {
	gameObject = parent->getGameObject()->addChild();
    }

    
    
  kte::GameObject* getGameObject() { return gameObject; }
protected:
    kte::GameObject* gameObject;
};

#endif