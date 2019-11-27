#ifndef ABOUTLAYER_H
#define ABOUTLAYER_H
#include "cocos2d.h"

USING_NS_CC;


class AboutLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();

    void back(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_NODE_FUNC(AboutLayer);
};

#endif // ABOUTLAYER_H


