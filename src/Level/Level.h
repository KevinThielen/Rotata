#ifndef LEVEL_H
#define LEVEL_H

#include <GameObject.h>
#include <Graphics/Text.h>
#include <IGameScene.h>
#include <Utility/Time.h>
#include <Audio/AudioSource.h>

#include "Cell.h"
#include "Block.h"
#include "ELayers.h"
#include "Colors.h"
#include "LevelData.h"

class Level 
{
public:
  
    void load(kte::GameObject* scene, kte::Resources* res, LevelData levelLayout, kte::Analytics* analytics)
    {
	this->res = res;
	rotatingBlock = nullptr;
	timer = 0.0f;
	rotations = 0;
	rotationTimer = 0.0f;
	
	audioStream.initialize();
   	audioStream2.initialize();
   	audioStream3.initialize();
	
	blocks.clear();
	cells.clear();
	
	if(background.getGameObject() != nullptr)
	    scene->removeChild(background.getGameObject());
	
	//background image
	background = kte::GameSprite(scene, res->getTexture(Textures::background));
	background.setSize(800,600);
	background.setLayer(ELayers::background);
	
	//level name
	levelText = kte::Text();
	levelText.setFont(res->getFont(Fonts::title86));
	levelText.setPosition(5,5);
	levelText.setString(levelLayout.name);
	    
	//timer
	timerText.setFont(res->getFont(Fonts::title86));
	timerText.setColor(Color::BLUE);
	timerText.setPosition(800-250,5);
	timerText.setString(std::to_string(timer));
	
	
	rotationText.setFont(res->getFont(Fonts::title86));
	rotationText.setColor(Color::BLUE);
	rotationText.setPosition(800-150, 100);
	rotationText.setString("0");
	
	//create the blocks
	int blockCounter = 0;
	blocks.resize(levelLayout.blocks.size());
	float xOffset = (800 - 6*blocks[blockCounter].BLOCK_SIZE) * 0.5f;
	
	std::vector<glm::vec4> usedColors;
	for(auto desc : levelLayout.blocks)
	{
	    glm::vec2 gridPosition = desc.position;
	    
	    glm::vec2 blockPosition;
	    blockPosition.x = blocks[blockCounter].BLOCK_SIZE * (gridPosition.x) * 0.5f - blocks[blockCounter].TILE_OFFSET + xOffset; 
	    blockPosition.y = blocks[blockCounter].BLOCK_SIZE * (2+gridPosition.y) * 0.5f- blocks[blockCounter].TILE_OFFSET;
	    
	    if(std::find(usedColors.begin(), usedColors.end(), desc.color) == usedColors.end())
		usedColors.push_back(desc.color);
	    
	    blocks[blockCounter++].load(background.getGameObject(), blockPosition, desc.color, res, this, analytics);
	}
	
	for(auto color : usedColors)
	{
	    levelText.addColor(color);
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
				    {
					cells.back().addOverlay(res, glm::vec2(newX,newY), checkBlock.getColor());
				    }
			    }
			}
		    }
		}
	   }
	}

	srand(3);
	//shuffle
	for(unsigned int i = 0; i<1000 * blocks.size(); i++)
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
	
	audioStream.play(res->getAudio(Audio::finished));
	return true;
    }
    void pause(bool pause)
    {
	for(auto& block : blocks)
	    block.pause(pause);
    }
    
    //needed for fancy animations, timer etc
    void update(kte::IGameScene* scene, float dt)
    {
	if(rotatingBlock)
	{

	    if(dt > 1.0f)
		dt = 1.0f;
	    
	
	    
	    rotationTimer -= dt;
	    float degrees = 90.f * dt / rotationDuration;
	    accumulatedRotation += degrees;
	    rotatingBlock->rotateSprite(degrees);
	    
	    if(rotationTimer <= 0.0f)
	{
	    rotatingBlock->rotate();

	    while(chainRotation > 0)
	    {
		rotatingBlock->rotate();
		chainRotation--;
	    }
	    audioStream2.play(res->getAudio(Audio::rotationEnd));
	    rotatingBlock->rotateSprite(-accumulatedRotation);
	    rotatingBlock->moveLayer(0);
	    rotatingBlock = nullptr;
	}
	}
	
	
	timer += dt;
	if(rotationScale > 1.0f)
	    rotationScale -= (2*dt);
	if(rotationScale < 1.0f) 
	    rotationScale = 1.0f;
	
	float fractionalDigits = (int)((timer-(int)timer)*10);


	//
//	rotationText.setString(std::to_string(rotations));
	//rotationText.setSize(rotationScale, rotationScale);
	scene->displayText(levelText);
	//scene->displayText(timerText);
    }
    
    float getTimer() 
    {
	int formattedTimer = (int)(timer*100);

	return formattedTimer/100.0f;
    }
    
    void rotate(Block* block)
    {
	if(rotatingBlock == nullptr)
	{
	    accumulatedRotation = 0.0f;
	    rotatingBlock = block;
	    rotationTimer = rotationDuration;
	    rotatingBlock->moveLayer(10);
	    chainRotation = 0;
	    rotations++;
	    rotationScale = 1.5f;
	    
	    audioStream.play(res->getAudio(Audio::rotatorClick));

	}
	else if(rotatingBlock == block && chainRotation <= 10)
	{
	    audioStream.play(res->getAudio(Audio::rotatorClick));
	    chainRotation++;
	    rotationTimer += rotationDuration;
	    rotations++;
	    rotationScale = 1.5f;
	}
    }
    
    bool isRotating()
    {
	return !(rotatingBlock == nullptr);
    }
    
    Block* getRotatingBlock()
    {
	return rotatingBlock;
    }
    
    unsigned int getRotations() { return rotations; }
    
private:
    std::vector<Block> blocks;
    std::vector<Cell> cells;
    kte::GameSprite background;
    kte::Text levelText;
    kte::Text rotationText;
    kte::Text timerText;

    kte::Resources* res;
    kte::AudioSource audioStream;
    kte::AudioSource audioStream2;
    kte::AudioSource audioStream3;
    
    
    Block* rotatingBlock;
    
    float rotationTimer;
    float accumulatedRotation;
    const float rotationDuration = 0.75f;
    float timer;
    float rotationScale = 1.0f;
    int chainRotation; 
    unsigned int rotations;
};

#endif