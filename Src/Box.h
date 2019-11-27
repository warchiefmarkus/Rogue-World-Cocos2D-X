#ifndef BOX_H
#define BOX_H
#include <Object.h>
#include <cocos2d.h>
#include <GameData.h>
USING_NS_CC;

class Box : public Object
{
public:
	bool initialize(Layer layer, GameData* dat);
	void nextStep();

	LAYER_NODE_FUNC(Box);
};

#endif // BOX_H
