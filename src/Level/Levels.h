#ifndef LEVELS_H
#define LEVELS_H

#include "LevelData.h"
#include "Colors.h"
#include <Graphics/Text.h>

class Levels 
{
public:
    Levels() 
    {
	//TODO: File loading?
	{
	std::vector<BlockDescription> blocks;
	blocks.push_back(BlockDescription(glm::vec2(2,0) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(1,1) , Color::BLUE));  


	levelLayouts[0] = LevelData("Intro", blocks);
	}
	
	{
	std::vector<BlockDescription> blocks;
	blocks.push_back(BlockDescription(glm::vec2(2,0) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(1,1) , Color::BLUE));  
	blocks.push_back(BlockDescription(glm::vec2(2,2) , Color::YELLOW));  


	levelLayouts[1] = LevelData("Intro 2", blocks);
	}
	
	{
	std::vector<BlockDescription> blocks;
	blocks.push_back(BlockDescription(glm::vec2(1,0) , Color::BLACK));  
	blocks.push_back(BlockDescription(glm::vec2(3,0) , Color::BLACK));  
	blocks.push_back(BlockDescription(glm::vec2(5,0) , Color::BLACK));  

	blocks.push_back(BlockDescription(glm::vec2(0,1) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(2,1) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(4,1) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(6,1) , Color::RED));  

	
	blocks.push_back(BlockDescription(glm::vec2(1,2) , Color::YELLOW));  
	blocks.push_back(BlockDescription(glm::vec2(3,2) , Color::YELLOW));  
	blocks.push_back(BlockDescription(glm::vec2(5,2) , Color::YELLOW));  

	levelLayouts[2] = LevelData("Germany", blocks);
	}
	
	{
	std::vector<BlockDescription> blocks;
	blocks.push_back(BlockDescription(glm::vec2(5,2) , Color::RED));
	
	blocks.push_back(BlockDescription(glm::vec2(4,1) , Color::YELLOW));  
	blocks.push_back(BlockDescription(glm::vec2(4,3) , Color::GREEN));  
	blocks.push_back(BlockDescription(glm::vec2(6,3) , Color::BLACK));  
	blocks.push_back(BlockDescription(glm::vec2(6,1) , Color::WHITE));  

	blocks.push_back(BlockDescription(glm::vec2(3,0) , Color::PURPLE));  
	blocks.push_back(BlockDescription(glm::vec2(3,4) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(7,4) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(7,0) , Color::GREEN));  

	levelLayouts[3] = LevelData("X-Stream", blocks);
	
	
	
	//add level number prefix
	for(int i = 0; i<levelLayouts.size(); i++)
	    levelLayouts[i].name = std::to_string(i+1) + " " + levelLayouts[i].name; 
	
	
	
	
	}
    }
    
    LevelData getLevel(unsigned int index) { 
	if(index<levelLayouts.size()) 
	return levelLayouts[index]; 
	
	else return levelLayouts[levelLayouts.size()-1];
    }
    
    
    unsigned int getNumberOfLevels() { return levelLayouts.size(); }
    
private:
    std::map<unsigned int, LevelData> levelLayouts;
};


#endif