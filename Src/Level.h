#ifndef GAMELAYER_H
#define GAMELAYER_H


#include "cocos2d.h"
USING_NS_CC;
#include "Utils.h"
#include <Object.h>
#include <iostream>
#include <DGenerator.h>
#include <CCSpriteBatchNode.h>
#include "GameData.h"
#include <Map.h>


class Level : public CCLayer
{
public:
    virtual bool init();

	//----------------Scroll map------------------//
	void ScrollToHero();

	//----------------Load Game Data------------------//
	void loadGameData();
	GameData* gameData;

	//----------------SpriteBatchNode----------------//
	CCSpriteBatchNode* batch;

	//----------------Game management------------------//
	void newGame();
	void loadGame(MMap map); // set current Map from map
	void loadGame(std::string filename); // set current Map from .savefile

	//-----------------Map management-----------------//
	DGenerator* dgenerator; // map generator
	Map* TMap; // map

	//void loadMap(std::string filename){} // load map from file
	//void saveMap(std::string filename){} // save map to file
	//void createMap(int width, int height){} // create new map

	int Width; // width of map in cells
	int Height; // Height of map in cells					

    Hero* MHero; // Main Hero object


	CCSprite* cellHighlight; // Highlight clicked cell

	
	// -------------- Controls ---------------//
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	void ccTouchesBegan(CCSet * touches, CCEvent * event);
	
	//bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);

    // -------------- Object Factory ---------------//
    Object* createObject(ObjectType type); // Create new Object and it to layer
	Hero* createHero();
	//Object* getObjByCell(int cellx, int celly, Layer layer); // wrapper of CCNode getChildByCell
	
	void nextStep(); // Next step function


    LAYER_NODE_FUNC(Level);

	

};

#endif // GAMELAYER_H
