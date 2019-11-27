#include "Object.h"


bool Object::initialize(GameData* dat)
{
	type = empty;
	Cost = 0;
	gameData = dat;
	//------------------DEV VARS--------------------//
	float hero_num = 1;

	this->initWithTexture(gameData->SpriteSheet,CCRect((hero_num*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
	this->setAnchorPoint(ccp(0,0)); // Set Anchor point in bottom left	
	return true;
}

void Object::setPos(int CellX, int CellY)
{
	setCellX(CellX);
	setCellY(CellY);
    setPosition(ccp(CellX*CELL_WIDTH,CellY*CELL_HEIGHT));	
}

Point Object::getPos()
{
	return Point(getCellX(),getCellY());
}

//---------------------Next step function----------------/
void Object::nextStep()
{
	std::cout << " NEXT STEP " << getPos().X;
	setPosition(CCPoint(getPosition().x+1,getPosition().y));
	
}

void Object::MoveTo(int XCell, int YCell)
{

}