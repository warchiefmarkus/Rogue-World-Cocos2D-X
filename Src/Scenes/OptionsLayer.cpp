#include "OptionsLayer.h"



bool OptionsLayer::init()
{
    // Back item
    CCMenuItemImage *pBackItem = CCMenuItemImage::itemFromNormalImage(
                                        "quit.png",
                                        "quit-hover.png",
                                        this,
                                        menu_selector(OptionsLayer::back));
    pBackItem->setAnchorPoint( ccp(0.5, 0.5) );
    pBackItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, 50) );


    // Create menu
    CCMenu* pMenu = CCMenu::menuWithItems(pBackItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);


    // Label
    CCLabelTTF* pLabel = CCLabelTTF::labelWithString("About", "Arial", 24);
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    pLabel->setPosition( ccp(size.width / 2, size.height - 50) );
    this->addChild(pLabel, 1);

    return true;
}


void OptionsLayer::back(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}
