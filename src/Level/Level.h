#ifndef LEVEL_H
#define LEVEL_H
#include <GameObject.h>
#include <Graphics/Text.h>
#include <IGameScene.h>

#include "Cell.h"
#include "Block.h"
#include "ELayers.h"
#include "Colors.h"
#include "LevelData.h"

class Level 
{
public:
  
    void load(kte::GameObject* scene, kte::Resources* res, LevelData levelLayout)
    {
	
	blocks.clear();
	cells.clear();
	
	if(background.getGameObject() != nullptr)
	    scene->removeChild(background.getGameObject());
	
	//background image
	background = kte::GameSprite(scene, res->getTexture(Textures::background));
	background.setSize(800,600);
	background.setLayer(ELayers::background);
	
	//level name
	levelText.setFont(res->getFont(Fonts::font));
	levelText.setColor(glm::vec4(1,1,1,1));
	levelText.setPosition(25,25);
	levelText.setString(levelLayout.name);
	    
	//timer
	timerText.setFont(res->getFont(Fonts::font));
	timerText.setColor(glm::vec4(1,1,1,1));
	timerText.setPosition(800-300,25);
	timerText.setString(std::to_string(timer));
	
	
	//create the blocks
	int blockCounter = 0;
	blocks.resize(levelLayout.blocks.size());
	float xOffset = (800 - 6*blocks[blockCounter].BLOCK_SIZE) * 0.5f;
	for(auto desc : levelLayout.blocks)
	{
	    glm::vec2 gridPosition = desc.position;
	    
	    glm::vec2 blockPosition;
	    blockPosition.x = blocks[blockCounter].BLOCK_SIZE * (gridPosition.x) * 0.5f - blocks[blockCounter].TILE_OFFSET + xOffset; 
	    blockPosition.y = blocks[blockCounter].BLOCK_SIZE * (2+gridPosition.y) * 0.5f- blocks[blockCounter].TILE_OFFSET;
	    
	    blocks[blockCounter++].load(background.getGameObject(), blockPosition, desc.color, res);
	}
	
	cells.reserve(blocks.size()*4);
	
	//fill block with single color cells, check if overlapping then mixed color

	for(auto& block : blocks)
	{
	   for(int x = 0; x<block.NUMBER_OF_CELLS; x++)
	   {
		for(int y = 0; y<block.NUMBER_OF_CELLS; y++)
		{
		    //cell empty
		    if(!block.getCell(x,y))
		    {
			Cell cell;
			glm::vec2 size = glm::vec2(block.TILE_SIZE, block.TILE_SIZE);
			glm::vec2 position = block.getPosition() + glm::vec2(x*block.TILE_SIZE + (1+x) * block.TILE_OFFSET,y*block.TILE_SIZE + (y+1) * block.TILE_OFFSET);
			cell.load(background.getGameObject(), position, size, block.getColor(), res);
			
			if((x+y)%2)
			    cell.mirror();

			
			cells.push_back(cell);
			
			glm::vec2 center = block.getCenter();
		
			//assign cell to all overlapped blocks
			
			/* The algorithm to find the coordinate of the cell in the other block is:
			*  Cell pos in origin block - Normalized difference between centers
			*/
			cells.back().addOwner(&block);
			for(auto& checkBlock : blocks)
			{
			    if(!checkBlock.contains(&cells.back()) && checkBlock.intersects(&cells.back()))
			    {
				glm::vec2 otherCenter = checkBlock.getCenter();
				
				int xDiff = (otherCenter.x - center.x);
				if(xDiff != 0)
				    xDiff /= abs(otherCenter.x - center.x);
				
				int yDiff = (otherCenter.y - center.y); 
				if(yDiff != 0)
				    yDiff /= abs(otherCenter.y - center.y);
				
			
			
				    int newX = x-xDiff;
				    int newY = y-yDiff;

				    checkBlock.setCell(newX, newY, &cells.back());
				    cells.back().addOwner(&checkBlock);
				    if(checkBlock.getColor() != block.getColor())
					cells.back().addOverlay(res, checkBlock.getColor());
			    }
			}
		    }
		}
	   }
	}

	srand(5);
	//shuffle
	for(int i = 0; i<1000 * blocks.size(); i++)
	{
	    int blockIndex = rand() % blocks.size();
	    int shuffleTimes = rand() % 4 + 1;
	    
	    for(int n = 0; n<shuffleTimes; n++)
		blocks[blockIndex].rotate();
	}
    }
    
    bool checkWinCondition()
    {
	for(auto block : blocks)
	{
	    if(!block.isFinished())
		return false;
	}
	return true;
    }
    void pause()
    {
	for(auto& block : blocks)
	    block.pause();
    }
    
    //needed for fancy animations, timer etc
    void update(kte::IGameScene* scene, float dt)
    {
	timer += dt;
	
	float fractionalDigits = (int)((timer-(int)timer)*100);
	
	timerText.setString(std::to_string((int)timer) + "." + std::to_string((int)fractionalDigits));
	
	scene->displayText(levelText);
	scene->displayText(timerText);
    }
    
    float getTimer() 
    {
	int formattedTimer = (int)(timer*100);

	return formattedTimer/100.0f;
    }
private:
    std::vector<Block> blocks;
    std::vector<Cell> cells;
    kte::GameSprite background;
    kte::Text levelText;
    
    kte::Text timerText;
    float timer;
};

#endif