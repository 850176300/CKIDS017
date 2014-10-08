//
//  LittleSun.h
//  CKIDS017
//
//  Created by liuwei on 14-9-20.
//
//

#ifndef __CKIDS017__LittleSun__
#define __CKIDS017__LittleSun__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class LittleSun: public CCSprite, public CCTouchDelegate{
public:
    static LittleSun* createWithFile(const char* file);
    bool initWithFile(const char* file);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
private:
    void addParticle();
    void addSunParticles();
};
#endif /* defined(__CKIDS017__LittleSun__) */
