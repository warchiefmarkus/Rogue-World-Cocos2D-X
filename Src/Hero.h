#ifndef HERO_H
#define HERO_H
#include "Object.h"
#include <cocos2d.h>
#include <GameData.h>
USING_NS_CC;

class Hero : public Object
{
public:
	virtual bool initialize(GameData* dat);

	void MoveTo(int XCell, int YCell);
	
	//--------------------Animations--------------------//
	CCAnimation* animMove;
	CCAnimate* actAnimMove;

	CCFiniteTimeAction* actionMove;


    LAYER_NODE_FUNC(Hero);

	
    void Move(Direction dir); // Move in direction


};

#endif // HERO_H
