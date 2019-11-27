#include "Hero.h"


bool Hero::initialize(GameData* dat)
{
	gameData = dat;
	//------------DEV VARS-----------
	float hero_num = 1;
   
	this->initWithTexture(gameData->SpriteSheet,CCRect((hero_num*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
    this->setAnchorPoint(ccp(0,0)); // Set Anchor point in bottom left
	
	return true;
}

void Hero::MoveTo(int XCell, int YCell)
{
	//------------DEV VARS-----------	
	float hero_left_1 = 15;
	float hero_left_2 = 16;
	float hero_left_3 = 17;

	float hero_right_1 = 18;
	float hero_right_2 = 19;
	float hero_right_3 = 20;

	float hero_down_1 = 21;
	float hero_down_2 = 22;
	float hero_down_3 = 23;

	float hero_up_1 = 24;
	float hero_up_2 = 25;
	float hero_up_3 = 26;

	animMove = CCAnimation::animation();
	
	//--------Chose direction--------
	if (XCell<(int)(getPositionX()/32))
	{
		animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_left_1*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
		animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_left_2*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
		animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_left_3*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
	}	
	else
	{		
		if (XCell>(int)(getPositionX()/32))
		{
			animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_right_1*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
		    animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_right_2*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
		    animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_right_3*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
	    } 
	else
	{
		if (YCell>(int)(getPositionY()/32))
		{
			animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_up_1*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
		    animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_up_2*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
		    animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_up_3*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
		} 
		else
		{
			if (YCell<(int)(getPositionY()/32))
			{
				animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_down_1*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
		        animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_down_2*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));
		        animMove->addFrameWithTexture(gameData->SpriteSheet,CCRect((hero_down_3*CELL_WIDTH-CELL_WIDTH),0,CELL_WIDTH,CELL_WIDTH));		
		    }
	    }
	}
	}
	

	actAnimMove = CCAnimate::actionWithDuration(1.0f,animMove,true);

	actionMove = CCMoveTo::actionWithDuration(1.0,ccp(XCell*CELL_WIDTH,YCell*CELL_HEIGHT));
	
	this->runAction(CCSpawn::actions( actionMove, actAnimMove, NULL));

}

void Hero::Move(Direction dir)
{
    switch(dir)
    {
    case Up:
    {
		this->setPos(this->getPos().X,this->getPos().Y-1);					        
    }
    case Down:
    {
		this->setPos(this->getPos().X,this->getPos().Y+1);
    }
    case Left:
    {
		this->setPos(this->getPos().X-1,this->getPos().Y); 
    }
    case Right:
    {
		this->setPos(this->getPos().X+1,this->getPos().Y);
    }
    default:{}
    }
}
