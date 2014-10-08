//
//  SunSprite.h
//  CKIDS017
//
//  Created by liuwei on 14-9-19.
//
//

#ifndef __CKIDS017__SunSprite__
#define __CKIDS017__SunSprite__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class SunSprite : public CCSprite, public CCTouchDelegate{
public:
    static SunSprite* createOne();
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    void runAnimation();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    bool stopProduct;
private:
    void updateSun(float dt);
    void productSun();
};
#endif /* defined(__CKIDS017__SunSprite__) */
