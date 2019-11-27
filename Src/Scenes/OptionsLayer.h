#ifndef OPTIONSLAYER_H
#define OPTIONSLAYER_H
#include "cocos2d.h"

USING_NS_CC;


class OptionsLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();

    void back(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_NODE_FUNC(OptionsLayer);
};

#endif // OPTIONSLAYER_H


