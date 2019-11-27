#ifndef __MENU_LAYER_H__
#define __MENU_LAYER_H__


#include "cocos2d.h"
#include <Game.h>
USING_NS_CC;

class Game;

// Input Layer
class MenuLayer : public CCLayer
{
public:

    Game* game;

	virtual bool init();  

    // Menu items functions
    void NewGame(CCObject* pSender);
    void LoadGame(CCObject* pSender);
    void Instructions(CCObject* pSender);
    void Options(CCObject* pSender);
    void About(CCObject* pSender);
    virtual void menuCloseCallback(CCObject* pSender);

    LAYER_NODE_FUNC(MenuLayer);
};



#endif // __MENU_LAYER_H__
