#include "Box.h"


bool Box::initialize(Layer layer, GameData* dat)
{
	this->type = box;
	this->setLayer(layer);
	gameData = dat;
	//------------DEV VARS-----------
	float box_num = 6;

	this->initWithTexture(gameData->SpriteSheet,CCRect((box_num*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
	this->setAnchorPoint(ccp(0,0)); // Set Anchor point in bottom left


	return true;
}

void Box::nextStep()
{
	std::cout << " BOX NEXT_STEP ";
}

