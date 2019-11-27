#ifndef INSTRUCTIONSLAYER_H
#define INSTRUCTIONSLAYER_H
#include "cocos2d.h"

USING_NS_CC;


class InstructionsLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();

    void back(CCObject* pSender);

    LAYER_NODE_FUNC(InstructionsLayer);
};

#endif // INCTUCTIONSLAYER_H


