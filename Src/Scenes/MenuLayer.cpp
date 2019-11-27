#include "MenuLayer.h"
#include <iostream>





//--------------------------------------Main menu--------------------------------------//
bool MenuLayer::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}
	
	// Tiled background
    CCSprite* background = CCSprite::spriteWithFile("Resources//background.png", CCRectMake(0,0, CCDirector::sharedDirector()->getWinSize().width, CCDirector::sharedDirector()->getWinSize().height));
    background->setAnchorPoint(ccp(0,0));
    background->setPosition(ccp(0,0));
    ccTexParams params = {GL_LINEAR,GL_LINEAR,GL_REPEAT,GL_REPEAT};
    background->getTexture()->setTexParameters(&params);
    this->addChild(background);


	CCSprite* spr = CCSprite::spriteWithFile("Resources//void.png");
	

    // New game item
	CCMenuItemImage *pNewGame = CCMenuItemImage::itemFromNormalImage(
                                        "Resources//new-game.png",
                                        "Resources//new-game-hover.png",
                                        this,
                                        menu_selector(MenuLayer::NewGame) );

    pNewGame->setAnchorPoint( ccp(0.5, 0.5) );
    pNewGame->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-50) );

    // Load item
    CCMenuItemImage *pLoadGame = CCMenuItemImage::itemFromNormalImage(
                                        "Resources//load-game.png",
                                        "Resources//load-game-hover.png",
                                        this,
                                        menu_selector(MenuLayer::LoadGame) );
    pLoadGame->setAnchorPoint( ccp(0.5, 0.5) );
    pLoadGame->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-125) );

    // Instructions item
    CCMenuItemImage *pInstructions = CCMenuItemImage::itemFromNormalImage(
                                        "Resources//instruction.png",
                                        "Resources//instruction-hover.png",
                                        this,
                                        menu_selector(MenuLayer::Instructions) );
    pInstructions->setAnchorPoint( ccp(0.5, 0.5) );
    pInstructions->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-200) );

    // Options item
    CCMenuItemImage *pOptions = CCMenuItemImage::itemFromNormalImage(
                                        "Resources//options.png",
                                        "Resources//options-hover.png",
                                        this,
                                        menu_selector(MenuLayer::Options) );
    pOptions->setAnchorPoint( ccp(0.5, 0.5) );
    pOptions->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-275) );

    // About item
    CCMenuItemImage *pAbout = CCMenuItemImage::itemFromNormalImage(
                                        "Resources//about.png",
                                        "Resources//about-hover.png",
                                        this,
                                        menu_selector(MenuLayer::About) );
    pAbout->setAnchorPoint( ccp(0.5, 0.5) );
    pAbout->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-350) );

    // Quit item
    CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
                                        "Resources//quit.png",
                                        "Resources//quit-hover.png",
										this,
                                        menu_selector(MenuLayer::menuCloseCallback) );
    pCloseItem->setAnchorPoint( ccp(0.5, 0.5) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height-425) );

    // Create menu
    CCMenu* pMenu = CCMenu::menuWithItems(pNewGame, pLoadGame, pInstructions, pOptions, pAbout, pCloseItem, NULL);
	pMenu->setPosition( CCPointZero );
	this->addChild(pMenu, 1);

	return true;
}

//------------------New Game----------------//
void MenuLayer::NewGame(CCObject* pSender)
{
    game->NewGame();
}

//-----------------Load Game-----------------//
void MenuLayer::LoadGame(CCObject* pSender)
{
	game->LoadGame();
}

//-----------------Instructions---------------//
void MenuLayer::Instructions(CCObject* pSender)
{
	game->showInstructions();
}

//-------------------Options-------------------//
void MenuLayer::Options(CCObject* pSender)
{
	game->showOptions();
}

//-------------------About---------------------//
void MenuLayer::About(CCObject* pSender)
{
    game->showAbout();
}

//--------------------Quit Game------------------//
void MenuLayer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
