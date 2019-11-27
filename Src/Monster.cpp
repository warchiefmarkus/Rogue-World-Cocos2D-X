#include "Monster.h"


bool Monster::initialize(Layer layer, GameData* dat)
{
	this->type = monster;
	this->setLayer(layer);
	gameData = dat;
	//------------DEV VARS-----------
	float monster_num = 7;

	this->initWithTexture(gameData->SpriteSheet,CCRect((monster_num*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
	this->setAnchorPoint(ccp(0,0)); // Set Anchor point in bottom left


	return true;
}

void Monster::nextStep()
{
	std::cout << " MONSTER NEXT_STEP ";
}







