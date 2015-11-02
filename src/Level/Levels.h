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


	levelLayouts[1] = LevelData("Intro II", blocks);
	}
	
	
		{
	std::vector<BlockDescription> blocks;
	
	blocks.push_back(BlockDescription(glm::vec2(3,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(4,4) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(4,2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(2,2) , Color::YELLOW));
	
	


	levelLayouts[2] = LevelData("Glider", blocks);
	
	}
	
		
	{
	std::vector<BlockDescription> blocks;
	
	
	blocks.push_back(BlockDescription(glm::vec2(4,1) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(6,1) , Color::GREEN));

	blocks.push_back(BlockDescription(glm::vec2(5,0) , Color::WHITE));

	levelLayouts[3] = LevelData("Hanoi", blocks);
	
	}
	
	{

	std::vector<BlockDescription> blocks;
	
	blocks.push_back(BlockDescription(glm::vec2(2,2) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(4,2) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(3,3) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(3,1) , Color::YELLOW));
	
	


	levelLayouts[4] = LevelData("Together", blocks);
	
	}
	
	
	
	{
	std::vector<BlockDescription> blocks;
	blocks.push_back(BlockDescription(glm::vec2(4,3) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(3,4) , Color::BLUE));  
	blocks.push_back(BlockDescription(glm::vec2(4,5) , Color::YELLOW));  
	blocks.push_back(BlockDescription(glm::vec2(3,2) , Color::ORANGE));  
	blocks.push_back(BlockDescription(glm::vec2(2,3) , Color::WHITE));  


	levelLayouts[5] = LevelData("Intro III", blocks);
	}
	
	
	
		{
	std::vector<BlockDescription> blocks;
	


	blocks.push_back(BlockDescription(glm::vec2(3,2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(5, 2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(7,2) , Color::BLUE));

	blocks.push_back(BlockDescription(glm::vec2(4,1) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(6,1) , Color::GREEN));

	blocks.push_back(BlockDescription(glm::vec2(5,0) , Color::WHITE));

	levelLayouts[6] = LevelData("Hanoi II", blocks);
	
	}
	
	{
	std::vector<BlockDescription> blocks;
	
	blocks.push_back(BlockDescription(glm::vec2(1,1) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(3,3) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(2,2) , Color::BLACK));
	blocks.push_back(BlockDescription(glm::vec2(3,1) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(1,3) , Color::PINK));


	levelLayouts[7] = LevelData("Extra", blocks);
	
	}
	
	

	{

	std::vector<BlockDescription> blocks;
	
	blocks.push_back(BlockDescription(glm::vec2(3,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(2,2) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(4,2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(1,1) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(5,1) , Color::PINK));
	
	


	levelLayouts[8] = LevelData("Together", blocks);
	
	}
	{

	std::vector<BlockDescription> blocks;
	
	blocks.push_back(BlockDescription(glm::vec2(4,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(5,2) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(6,1) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(6,3) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(6,5) , Color::PINK));
	blocks.push_back(BlockDescription(glm::vec2(5,4) , Color::PURPLE));
	
	


	levelLayouts[9] = LevelData("Triangle", blocks);
	
	}
	{

	std::vector<BlockDescription> blocks;
	
	blocks.push_back(BlockDescription(glm::vec2(3,3) , Color::RED));
 
	blocks.push_back(BlockDescription(glm::vec2(2,2) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(2,4) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(1,3) , Color::YELLOW));

	blocks.push_back(BlockDescription(glm::vec2(4,4) , Color::PINK));
	blocks.push_back(BlockDescription(glm::vec2(4,2) , Color::PURPLE));
	blocks.push_back(BlockDescription(glm::vec2(5,3) , Color::WHITE));
	
	


	levelLayouts[10] = LevelData("Hexagon", blocks);
	
	}
	{

	std::vector<BlockDescription> blocks;
	
	blocks.push_back(BlockDescription(glm::vec2(3,3) , Color::RED));
 
	blocks.push_back(BlockDescription(glm::vec2(2,2) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(2,4) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(1,3) , Color::YELLOW));

	blocks.push_back(BlockDescription(glm::vec2(4,4) , Color::PINK));
	blocks.push_back(BlockDescription(glm::vec2(4,2) , Color::PURPLE));
	blocks.push_back(BlockDescription(glm::vec2(5,3) , Color::WHITE));
	
	blocks.push_back(BlockDescription(glm::vec2(3,1) , Color::ORANGE));
	blocks.push_back(BlockDescription(glm::vec2(3,5) , Color::GRAY));
	
	


	levelLayouts[11] = LevelData("Octagon", blocks);
	
	}
	{

	std::vector<BlockDescription> blocks;
	
 
	blocks.push_back(BlockDescription(glm::vec2(2,2) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(2,4) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(1,3) , Color::YELLOW));

	blocks.push_back(BlockDescription(glm::vec2(4,4) , Color::PINK));
	blocks.push_back(BlockDescription(glm::vec2(4,2) , Color::PURPLE));
	blocks.push_back(BlockDescription(glm::vec2(5,3) , Color::WHITE));
	
	blocks.push_back(BlockDescription(glm::vec2(3,1) , Color::ORANGE));
	blocks.push_back(BlockDescription(glm::vec2(3,5) , Color::GRAY));
	
	


	levelLayouts[12] = LevelData("Donut", blocks);
	
	}


	{
	std::vector<BlockDescription> blocks;
	blocks.push_back(BlockDescription(glm::vec2(4,3) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(4,5) , Color::YELLOW));  
	
	blocks.push_back(BlockDescription(glm::vec2(3,4) , Color::BLUE));  
	blocks.push_back(BlockDescription(glm::vec2(3,2) , Color::ORANGE));  
	blocks.push_back(BlockDescription(glm::vec2(2,3) , Color::WHITE));  
	
	blocks.push_back(BlockDescription(glm::vec2(5,4) , Color::BLUE));  
	blocks.push_back(BlockDescription(glm::vec2(5,2) , Color::ORANGE));  
	blocks.push_back(BlockDescription(glm::vec2(6,3) , Color::WHITE));  
	

	levelLayouts[13] = LevelData("Victory", blocks);
	}
	
	{
	std::vector<BlockDescription> blocks;
	blocks.push_back(BlockDescription(glm::vec2(4,3) , Color::RED));  
	blocks.push_back(BlockDescription(glm::vec2(4,5) , Color::YELLOW));  
	
	blocks.push_back(BlockDescription(glm::vec2(3,4) , Color::BLUE));  
	blocks.push_back(BlockDescription(glm::vec2(3,2) , Color::ORANGE));  
	blocks.push_back(BlockDescription(glm::vec2(2,3) , Color::WHITE));  
	blocks.push_back(BlockDescription(glm::vec2(1,2) , Color::PINK));  
	blocks.push_back(BlockDescription(glm::vec2(2,1) , Color::PURPLE));  
	
	blocks.push_back(BlockDescription(glm::vec2(5,4) , Color::BLUE));  
	blocks.push_back(BlockDescription(glm::vec2(5,2) , Color::ORANGE));  
	blocks.push_back(BlockDescription(glm::vec2(6,3) , Color::WHITE));  
	blocks.push_back(BlockDescription(glm::vec2(7,2) , Color::PINK));  
	blocks.push_back(BlockDescription(glm::vec2(6,1) , Color::PURPLE));  
	

	levelLayouts[14] = LevelData("Victory II", blocks);
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

	levelLayouts[15] = LevelData("Germany", blocks);
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

	levelLayouts[16] = LevelData("X-Stream", blocks);
	
	}
	

	

	

		{
	std::vector<BlockDescription> blocks;
	

	
	blocks.push_back(BlockDescription(glm::vec2(2,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(4,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(6,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(8,3) , Color::RED));

	blocks.push_back(BlockDescription(glm::vec2(3,2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(5, 2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(7,2) , Color::BLUE));

	blocks.push_back(BlockDescription(glm::vec2(4,1) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(6,1) , Color::GREEN));

	blocks.push_back(BlockDescription(glm::vec2(5,0) , Color::WHITE));

	levelLayouts[17] = LevelData("Hanoi III", blocks);
	
	}
		{
	std::vector<BlockDescription> blocks;
	

	blocks.push_back(BlockDescription(glm::vec2(1,4) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(3,4) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(5,4) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(7,4) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(9,4) , Color::YELLOW));
	
	blocks.push_back(BlockDescription(glm::vec2(2,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(4,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(6,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(8,3) , Color::RED));

	blocks.push_back(BlockDescription(glm::vec2(3,2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(5, 2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(7,2) , Color::BLUE));

	blocks.push_back(BlockDescription(glm::vec2(4,1) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(6,1) , Color::GREEN));

	blocks.push_back(BlockDescription(glm::vec2(5,0) , Color::WHITE));

	levelLayouts[18] = LevelData("Hanoi IV", blocks);
	
	}
	
			{
	std::vector<BlockDescription> blocks;
	
	blocks.push_back(BlockDescription(glm::vec2(0,5) , Color::PINK));
	blocks.push_back(BlockDescription(glm::vec2(2,5) , Color::PINK));
	blocks.push_back(BlockDescription(glm::vec2(4,5) , Color::PINK));
	blocks.push_back(BlockDescription(glm::vec2(6,5) , Color::PINK));
	blocks.push_back(BlockDescription(glm::vec2(8,5) , Color::PINK));
	blocks.push_back(BlockDescription(glm::vec2(10,5) , Color::PINK));
	
	
	blocks.push_back(BlockDescription(glm::vec2(1,4) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(3,4) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(5,4) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(7,4) , Color::YELLOW));
	blocks.push_back(BlockDescription(glm::vec2(9,4) , Color::YELLOW));
	
	blocks.push_back(BlockDescription(glm::vec2(2,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(4,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(6,3) , Color::RED));
	blocks.push_back(BlockDescription(glm::vec2(8,3) , Color::RED));

	blocks.push_back(BlockDescription(glm::vec2(3,2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(5, 2) , Color::BLUE));
	blocks.push_back(BlockDescription(glm::vec2(7,2) , Color::BLUE));

	blocks.push_back(BlockDescription(glm::vec2(4,1) , Color::GREEN));
	blocks.push_back(BlockDescription(glm::vec2(6,1) , Color::GREEN));

	blocks.push_back(BlockDescription(glm::vec2(5,0) , Color::WHITE));

	levelLayouts[19] = LevelData("Hanoi V", blocks);
	
	}
    }
    
    LevelData getLevel(unsigned int index) { 
	if(index<levelLayouts.size()) 
	return levelLayouts[index]; 
	
	else return levelLayouts[levelLayouts.size()-1];
    }
    
    std::vector<glm::vec4> getColorList(unsigned int levelIndex)
    {
	std::vector<glm::vec4> colors;
	LevelData level =getLevel(levelIndex);
	
	for(auto block : level.blocks)
	{
	    if(std::find(colors.begin(), colors.end(), block.color) == colors.end())
		colors.push_back(block.color);
	}
	
	return colors;
    }
    
    unsigned int getNumberOfLevels() { return levelLayouts.size(); }
    
private:
    std::map<unsigned int, LevelData> levelLayouts;
};


#endif