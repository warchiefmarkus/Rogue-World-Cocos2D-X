#include "Floor.h"


bool Floor::initialize(Layer layer, GameData* dat)
{
	this->type = flor;
	this->setLayer(layer);
	gameData = dat;
	//------------DEV VARS-----------
	float floor_num = 5;

	this->initWithTexture(gameData->SpriteSheet,CCRect((floor_num*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
	this->setAnchorPoint(ccp(0,0)); // Set Anchor point in bottom left


	return true;
}

void Floor::nextStep()
{
	std::cout << " FLOOR NEXT_STEP ";
}

