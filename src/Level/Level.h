#ifndef LEVEL_H
#define LEVEL_H
#include <GameObject.h>

#include "Cell.h"
#include "Block.h"
#include "ELayers.h"

class Level 
{
public:
    struct BlockDescription
    {
	glm::vec2 position;
	glm::vec4 color;
	
	BlockDescription(glm::vec2 position, glm::vec4 color) : position(position), color(color)
	{
	    
	}
    };
    void load(kte::GameObject* scene, kte::Resources* res)
    {
	
	blocks.clear();
	cells.clear();
	
	if(background.getGameObject() != nullptr)
	    scene->removeChild(background.getGameObject());
	
	//background image
	background = kte::GameSprite(scene, res->getTexture(Textures::background));
	background.setSize(800,600);
	background.setLayer(ELayers::background);
	
	//create the blocks
	std::map<std::string, glm::vec4> colors;
	colors["red"] = glm::vec4(1,0,0,1);
	colors["blue"] = glm::vec4(0,0,1,1);
	colors["green"] = glm::vec4(0,1,0,1);
	colors["yellow"] = glm::vec4(1,1,0,1);
	colors["purple"] = glm::vec4(1,0,1,1);
	colors["white"] = glm::vec4(1,1,1,1);
	
	
	//TODO: File/Random generated or with editor
	std::vector<BlockDescription> levelDescription;
	levelDescription.push_back(BlockDescription(glm::vec2(1,1) , colors["red"]));
	levelDescription.push_back(BlockDescription(glm::vec2(0,0) , colors["blue"]));
	levelDescription.push_back(BlockDescription(glm::vec2(0,2) , colors["green"]));
	levelDescription.push_back(BlockDescription(glm::vec2(2,2) , colors["purple"]));
	levelDescription.push_back(BlockDescription(glm::vec2(3,1) , colors["yellow"]));
	levelDescription.push_back(BlockDescription(glm::vec2(4,0) , colors["red"]));
	levelDescription.push_back(BlockDescription(glm::vec2(5,1), colors["green"]));
		
	
	
	
	int blockCounter = 0;
	blocks.resize(levelDescription.size());
	for(auto desc : levelDescription)
	{
	    glm::vec2 gridPosition = desc.position;
	    
	    glm::vec2 blockPosition;
	    blockPosition.x = blocks[blockCounter].BLOCK_SIZE * (2+gridPosition.x) * 0.5f - blocks[blockCounter].TILE_OFFSET; 
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
	blocks[0].rotate();
	//blocks[0].rotateSprite(45.0f);
	//shuffle
	/*for(int i = 0; i<1000 * blocks.size(); i++)
	{
	    int blockIndex = rand() % blocks.size();
	    int shuffleTimes = rand() % 4 + 1;
	    
	    for(int n = 0; n<shuffleTimes; n++)
		blocks[blockIndex].rotate();
	}*/
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
    
private:
    std::vector<Block> blocks;
    std::vector<Cell> cells;
    kte::GameSprite background;
};

#endif