#ifndef CELL_H
#define CELL_H
#include <Graphics/GameSprite.h>
#include <Resources/Resources.h>
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
	
	sideRight = true;
	hasSecondaryColor = false;
	toggleCounter = 0;
    }
    void setParent(kte::GameObject* parent) 
    { 
	sprite.setParent(parent); 
    }
    
    void moveLayer(int increment)
    {
	sprite.setLayer(ELayers::cells+increment);
	
	if(hasSecondaryColor)
	{
	    spriteOverlay.setLayer(ELayers::overlays+increment);
	}
	
    }
    void toggleSide()
    {
	if(sideRight)
	    leftSide();
	else
	    rightSide();
    }
    
    void toggle()
    {

	
	if(toggleCounter%2)
	{
	    toggleSide();
	}
	toggleCounter++;
	toggleCounter = toggleCounter%4;
	
	mirror();
    }
    void addOverlay(kte::Resources* res, glm::vec2 cellPos, glm::vec4 color) 
    {
	hasSecondaryColor = true;
	this->res = res;
	spriteOverlay = kte::GameSprite(sprite.getGameObject(), color);
	spriteOverlay.setTexture(res->getTexture(Textures::overlay));
	spriteOverlay.setSize(sprite.getSize());
	spriteOverlay.setLayer(ELayers::overlays);
	
	//orientation hack
	if((cellPos.x == 0 && cellPos.y == 0) || (cellPos.x == 1 && cellPos.y == 1))
	    toggleCounter =1;
	    
	if(sprite.isMirrored())
	    spriteOverlay.mirror();
    }
    
    void leftSide()
    {
	if(hasSecondaryColor)
	{
	    spriteOverlay.setTexture(res->getTexture(Textures::overlay));
	    sideRight = false;
	}
    }
    
    void rightSide()
    {
	if(hasSecondaryColor)
	{
	    spriteOverlay.setTexture(res->getTexture(Textures::overlayR));
	    sideRight = true;
	}
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
    
    void rotateSprite(float degrees, glm::vec2 center) 
    { 
	glm::vec2 offset = center - (glm::vec2(sprite.getWorldPosition().x, sprite.getWorldPosition().y) + sprite.getSize()*0.5f);
	
	sprite.rotateByDegrees(degrees, offset);
    }
      
      
private:
   std::vector<Block*> owners;
   kte::GameSprite sprite;
   kte::GameSprite spriteOverlay;
   kte::Resources* res;
   bool hasSecondaryColor;
   bool sideRight;
   unsigned int toggleCounter;
};

#endif