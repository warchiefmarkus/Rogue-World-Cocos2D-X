#ifndef FLOOR_H
#define FLOOR_H
#include <Object.h>
#include <cocos2d.h>
#include <GameData.h>
USING_NS_CC;

class Floor : public Object
{
public:
	bool initialize(Layer layer, GameData* dat);
	void nextStep();

	LAYER_NODE_FUNC(Floor);
};

#endif // WALL_H