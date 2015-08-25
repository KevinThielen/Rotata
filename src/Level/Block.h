#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <Graphics/GameSprite.h>
#include <Utility/Analytics.h>
/*
 * A block contains n*m Cells and can be rotated
 */

#include "ELayers.h"
#include "Resources.h"

class Cell;
class Level;

class Block 
{
public:
    const int BLOCK_SIZE = 128;
    const int TILE_OFFSET = 0;
    const glm::vec4 BACKGROUND_COLOR = glm::vec4(0.5f,0.5f,0.5f,0.0f);
    const int NUMBER_OF_CELLS = 2;
    const int TILE_SIZE = 64;//(BLOCK_SIZE-3*TILE_OFFSET) / 2.0f;
    
    Block();
    
    void load(kte::GameObject* scene, glm::vec2 position, glm::vec4 color, kte::Resources* res, Level* level, kte::Analytics* analytics = nullptr);
    void rotate();
    bool isFinished();
    
    void moveLayer(int i);
    
    void setCell(unsigned int x, unsigned int y, Cell* cell) { cells[x][y] = cell; } 
    Cell* getCell(unsigned int x, unsigned int y) { return cells[x][y];}
    glm::vec4 getColor() { return color; }
    kte::GameObject* getGameObject() { return background.getGameObject(); }
    
    
    void resetRotatorSize()
    {
	float rotatorPos = BLOCK_SIZE * 0.5f;
	rotator.setPosition(rotatorPos - 32 * 1.25f, rotatorPos -32 * 1.25f);
	rotator.setSize(1.25f*64, 1.25f*64);
    }

    bool contains(Cell* cell) 
    { 
	for(unsigned int x = 0; x<cells.size(); x++)
	    for(unsigned int y = 0; y<cells[x].size(); y++)
	    {
		if(cells[x][y] == cell)
		    return true;
	    }
	    
	return false;
    } 
    
    bool intersects(Cell* cell);
    glm::vec2 getCenter() { return background.getPosition() + (background.getSize() * 0.5f); }
    glm::vec2 getPosition() { return background.getPosition(); }
    void replaceCell(Cell* oldCell, Cell* newCell) 
    { 
	for(int x = 0; x<NUMBER_OF_CELLS; x++)
	    for(int y = 0; y<NUMBER_OF_CELLS; y++)
	    {
		if(cells[x][y] == oldCell)
		    cells[x][y] = newCell; 
	    }
	
    }
    
    void rotateSprite(float degrees);
    
    void pause(bool pause) { rotator.pauseOnClickListener(pause); }
private:
    std::vector<std::vector<Cell*>> cells;
    kte::Resources* res;
    kte::GameSprite background;
    kte::GameSprite cross;
    kte::GameSprite rotator;
    
    
    Level* level;
    glm::vec4 color;
    
   bool lockRotatorSize;
};

#endif