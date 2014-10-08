//
//  SnailLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-9-23.
//
//

#ifndef __CKIDS017__SnailLayer__
#define __CKIDS017__SnailLayer__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
USING_NS_CC;
class SnailLayer: public CCLayer{
public:
    SnailLayer();
    virtual bool init();
    CREATE_FUNC(SnailLayer);
    virtual void draw();
    void addSnail(CCPoint atPos, bool needFlip = false);
    CCRect getConfilctRect();
private:
    CCSprite* bottle;
    virtual void update(float dt);
    void addBottle();
    void initTheWorld();
    b2World* theWorld;
};
#endif /* defined(__CKIDS017__SnailLayer__) */
