#ifndef WALL_H
#define WALL_H
#include <Object.h>
#include <cocos2d.h>
#include <GameData.h>
USING_NS_CC;

class Wall : public Object
{
public:
	bool initialize(Layer layer, GameData* dat);
	void nextStep();

	LAYER_NODE_FUNC(Wall);
};

#endif // WALL_H
