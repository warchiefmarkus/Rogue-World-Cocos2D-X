#ifndef MONSTER_H
#define MONSTER_H
#include <Object.h>
#include <cocos2d.h>
#include <GameData.h>
USING_NS_CC;

class Monster : public Object
{
public:
	bool initialize(Layer layer, GameData* dat);
	void nextStep();
	//--------------------Animations--------------------//
	CCAnimation* animMove;
	CCAnimate* actAnimMove;

	CCFiniteTimeAction* actionMove;


	LAYER_NODE_FUNC(Monster);


};

#endif // MONSTER_H
