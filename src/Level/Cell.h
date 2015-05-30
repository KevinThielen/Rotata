#ifndef CELL_H
#define CELL_H
#include <Graphics/GameSprite.h>
#include <Resources.h>
#include "Block.h"
#include "GameData.h"
#include "ELayers.h"

class Cell 
{
public:
    void updateOwners()
    {
	
    }
    
    void load(kte::GameObject* parent, glm::vec2 position, glm::vec2 size, glm::vec4 color, kte::Resources* res)
    {
	sprite = kte::GameSprite(parent, res->getTexture(Textures::cell));
	sprite.setColor(color);
	sprite.setSize(size);
	sprite.setPosition(position);	   
	sprite.setLayer(ELayers::cells);
	
	hasSecondaryColor = false;
    }
    void setParent(kte::GameObject* parent) 
    { 
	sprite.setParent(parent); 
    }
    
    void addOverlay(kte::Resources* res, glm::vec4 color) 
    {
	hasSecondaryColor = true;
	spriteOverlay = kte::GameSprite(sprite.getGameObject(), color);
	spriteOverlay.setTexture(res->getTexture(Textures::overlay));
	spriteOverlay.setSize(sprite.getSize());
	spriteOverlay.setLayer(ELayers::overlays);
	if(sprite.isMirrored())
	    spriteOverlay.mirror();
    }
    void setPosition(glm::vec2 position) { sprite.setPosition(position); }
    glm::vec2 getPosition() { return sprite.getPosition(); }
    glm::vec3 getWorldPosition() { return sprite.getWorldPosition(); }
    std::vector<Block*> getOwners() { return owners; }
    void setOwners( std::vector<Block*> owners) { this->owners = owners; } 
    void addOwner(Block* owner) { owners.push_back(owner); }
    glm::vec4 getPrimaryColor() { return sprite.getColor(); }
    glm::vec4 getSecondaryColor() 
    { 
	if(hasSecondaryColor)
	    return spriteOverlay.getColor(); 
	else
	    return glm::vec4(0,0,0,0);
    }
    
    void mirror()
    {
	sprite.mirror();
	if(hasSecondaryColor)
	    spriteOverlay.mirror();
    }
    
    bool containsColor(glm::vec4 color)
    {
	return (color == getPrimaryColor() || color == getSecondaryColor());
    }
private:
   std::vector<Block*> owners;
   kte::GameSprite sprite;
   kte::GameSprite spriteOverlay;
   bool hasSecondaryColor;
};

#endif