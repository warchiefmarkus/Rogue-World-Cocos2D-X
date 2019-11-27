#include "Npc.h"


bool Npc::initialize(Layer layer, GameData* dat)
{
	this->type = npc;
	this->setLayer(layer);
	gameData = dat;
	//------------DEV VARS-----------
	float npc_num = 9; 

	this->initWithTexture(gameData->SpriteSheet,CCRect((npc_num*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
	this->setAnchorPoint(ccp(0,0)); // Set Anchor point in bottom left
    
	
	return true;
}

void Npc::nextStep()
{
	std::cout << " NPC NEXT_STEP ";
}
	
	
	




