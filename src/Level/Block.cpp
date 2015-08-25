#include "Block.h"
#include "Cell.h"
#include "ELayers.h"
#include "Level.h"

Block::Block()
{
    
}

void Block::load(kte::GameObject* scene, glm::vec2 position, glm::vec4 color, kte::Resources* res, Level* level, kte::Analytics* analytics)
{
    this->level = level;
    this->color = color;
    this->res = res;
    color = glm::vec4(0,0,0,0);
    background = kte::GameSprite(scene, color);
    background.setSize(BLOCK_SIZE, BLOCK_SIZE);
    background.setPosition(position);
    background.setLayer(ELayers::blocks);
	
    cross = kte::GameSprite(background.getGameObject(), color);
    cross.setSize(BLOCK_SIZE-2*TILE_OFFSET, BLOCK_SIZE-2*TILE_OFFSET);
    cross.setPosition(glm::vec2(TILE_OFFSET, TILE_OFFSET));
    cross.setLayer(ELayers::cross);
	
    int rotatorPos = BLOCK_SIZE*0.5f;
    rotator = kte::GameSprite(background.getGameObject(), res->getTexture(Textures::rotator));
    rotator.setSize(64, 64);
    rotator.setPosition(glm::vec2(rotatorPos-32,rotatorPos-32));
    rotator.setLayer(ELayers::rotators);

    
    cells.clear();
    for(int x = 0; x<NUMBER_OF_CELLS; x++)
    {
	cells.push_back(std::vector<Cell*>());
	for(int y = 0; y<NUMBER_OF_CELLS; y++)
	{
	    cells[x].push_back(nullptr);
	}
    }
 
     rotator.setOnReleaseEvent
    (
	[this, analytics, rotatorPos]()
	{
	    //rotate();
	    rotator.setPosition(rotatorPos - 32 * 1.25f, rotatorPos -32 * 1.25f);
	    rotator.setSize(1.25f*64, 1.25f*64);

	    this->level->rotate(this);
	    
	    if(analytics)
	    {
		auto& analyticsRef = *analytics;
		if(analyticsRef["numberOfRotations"].empty())
		    analyticsRef["numberOfRotations"] = 0;
		
		analyticsRef["numberOfRotations"] = 1 + analyticsRef["numberOfRotations"].asInt(); 
	    }
	}
    );
    
    
    rotator.setOnClickEvent
    (
	[this, analytics, rotatorPos, level]()
	{
	    if(!level->isRotating() || level->getRotatingBlock() == this)
	    {
		//rotate();
		rotator.setPosition(rotatorPos - 32 * 1.1f, rotatorPos -32 * 1.1f);
		rotator.setSize(1.1f*64, 1.1f*64);
	    }
	}
    );
    
    rotator.setOnMouseOverEvent(
	[this, rotatorPos]()
	{
	    rotator.setPosition(rotatorPos - 32 * 1.25f, rotatorPos -32 * 1.25f);
	    rotator.setSize(1.25f*64, 1.25f*64);
	}
    );
    
    rotator.setOnMouseLeaveEvent(
	[this, rotatorPos]()
	{
	    rotator.setPosition(rotatorPos - 32, rotatorPos -32);
	    rotator.setSize(1.0f*64, 1.0f*64);
	}
    );

}



void Block::rotate()
{
    
    int xIndex = 0;
    int yIndex = 0;
    glm::vec2 increment = glm::vec2(1,0);
    bool rotationComplete = false;
    int stepCounter = 0;
    
    glm::vec2 tempPositions[2][2];
    std::vector<Block*> tempOwners[2][2];
    
    for(int x = 0; x<NUMBER_OF_CELLS; x++)
    {
	for(int y = 0; y<NUMBER_OF_CELLS; y++)
	{
	    tempPositions[x][y] = cells[x][y]->getPosition();
	    tempOwners[x][y] = cells[x][y]->getOwners();
	}
    }
    
    do 
    {
	stepCounter++;
	
	Cell* oldCell = cells[xIndex][yIndex]; 
	
	
	xIndex += increment.x;
	yIndex += increment.y;

	oldCell->toggle();

	oldCell->setPosition(tempPositions[xIndex][yIndex]);
	oldCell->setOwners(tempOwners[xIndex][yIndex]);
	
	//change ownerchip of tiles
	for(auto& owner : oldCell->getOwners())
	{
	    if(owner != this)
		owner->replaceCell(cells[xIndex][yIndex], oldCell);
	}
	
	
	
	//continue
	if(xIndex +increment.x > NUMBER_OF_CELLS-1)
	{
	    increment.x = 0;
	    increment.y = 1;
	}
	else if(yIndex+increment.y > NUMBER_OF_CELLS-1)
	{    
	    increment.x = -1;
	    increment.y = 0;
	}
	else if(xIndex + increment.x < 0)
	{
	    increment.x = 0;
	    increment.y = -1;
	}
	else if(yIndex + increment.y < 0)
	{
	    rotationComplete = true;
	    increment.x = 0;
	    increment.y *= -1;
	}
    }while(!rotationComplete);
}

bool Block::intersects(Cell* cell)
{
    glm::vec3 position = cell->getWorldPosition()  + TILE_SIZE/2.0f;
    return background.contains(glm::vec2(position.x, position.y));
}

bool Block::isFinished()
{
    glm::vec4 color = cells[0][0]->getPrimaryColor();
    glm::vec4 secondaryColor = cells[0][0]->getSecondaryColor();
    
    
    for(int x = 0; x<NUMBER_OF_CELLS; x++)
	for(int y = 0; y<NUMBER_OF_CELLS; y++)
	{
	    if(!cells[x][y]->containsColor(color))
		if(secondaryColor.a == 0 || !cells[x][y]->containsColor(secondaryColor))
		    return false;
		else if(secondaryColor.a != 0)
		    color = secondaryColor;
	}
	
    return true;
}

void Block::moveLayer(int increment)
    {

	background.setLayer(ELayers::blocks+ increment);
	cross.setLayer(ELayers::cross  + increment);
	
	rotator.setLayer(ELayers::rotators  + increment);
	
	for(auto& cellRow : cells)
	{
	    for(auto& cell : cellRow)
	    {
		cell->moveLayer(increment);   
	    }
	}  
    }

void Block::rotateSprite(float degrees)
{
    background.rotateByDegrees(degrees);
  
    for(auto& cellRow : cells)
    {
	for(auto& cell : cellRow)
	{
	    cell->rotateSprite(degrees, getCenter());    
	}
    }
}

