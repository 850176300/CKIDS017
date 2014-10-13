//
//  TipLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-9-17.
//
//

#ifndef __CKIDS017__TipLayer__
#define __CKIDS017__TipLayer__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
enum {
    theNodeTag = 12121,
};
class TipLayer : public CCLayerColor{
public:
    static TipLayer* createWithNode(CCNode* pNode);
    bool initWithTipNode(CCNode* pNode);
    virtual void onEnter();
    virtual void onExit();
    void addToNode(CCNode* parent);
    void removeFromNode();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__CKIDS017__TipLayer__) */
