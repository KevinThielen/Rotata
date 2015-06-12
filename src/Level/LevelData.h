#ifndef LEVEL_LAYOUT_H
#define LEVEL_LAYOUT_H

struct BlockDescription
{
    glm::vec2 position;
    glm::vec4 color;
	    
    BlockDescription(glm::vec2 position, glm::vec4 color) : position(position), color(color)
    {
	
    }
};
    
struct LevelData 
{
    std::vector<BlockDescription> blocks;
    std::string name;
    
    LevelData(){}
    LevelData(std::string name, std::vector<BlockDescription> blocks) : name(name), blocks(blocks) {}
};

#endif