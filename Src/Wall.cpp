#include "Wall.h"


bool Wall::initialize(Layer layer, GameData* dat)
{
	this->type = wall;
	this->setLayer(layer);
	gameData = dat;
	//------------DEV VARS-----------
	float wall_num = 8;

	this->initWithTexture(gameData->SpriteSheet,CCRect((wall_num*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
	this->setAnchorPoint(ccp(0,0)); // Set Anchor point in bottom left


	return true;
}

void Wall::nextStep()
{
	std::cout << " WALL NEXT_STEP ";
}

