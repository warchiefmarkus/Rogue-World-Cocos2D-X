#ifndef OBJECT_H
#define OBJECT_H
#include <cocos2d.h>
#include <Utils.h>
#include "GameData.h"

USING_NS_CC;

//--------------------------Object--------------------------//
class Object : public CCSprite
{
 
public:    
    LAYER_NODE_FUNC(Object);

	int Cost; // walk coast, default walkable

	char* datas;

	bool initialize(GameData* dat); // create simple object

	virtual void nextStep(); // Next Step
	void MoveTo(int XCell, int YCell); // Move to cells x, y
    void setPos(int CellX, int CellY); // Overloaded function for set object position on map in cells
	Point getPos();

	void findPath(int XCell, int YCell){};

	ObjectType type;
	GameData* gameData;
};

#endif // OBJECT_H
