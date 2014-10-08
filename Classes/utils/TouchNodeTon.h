//
//  TouchNodeTon.h
//  CKIDS017
//
//  Created by liuwei on 14-9-15.
//
//

#ifndef CKIDS017_TouchNodeTon_h
#define CKIDS017_TouchNodeTon_h

#include "cocos2d.h"
USING_NS_CC;
class TouchNode : public CCSprite, public CCTouchDelegate{
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){return true;};
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {CC_UNUSED_PARAM(pTouch); CC_UNUSED_PARAM(pEvent);}
};


#endif
