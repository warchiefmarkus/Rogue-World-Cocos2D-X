#ifndef NPC_H
#define NPC_H
#include <Object.h>
#include <cocos2d.h>
#include <GameData.h>
USING_NS_CC;

class Npc : public Object
{
public:
	bool initialize(Layer layer, GameData* dat);
	void nextStep();
	//--------------------Animations--------------------//
	CCAnimation* animMove;
	CCAnimate* actAnimMove;

	CCFiniteTimeAction* actionMove;


	LAYER_NODE_FUNC(Npc);


};

#endif // NPC_H
