//
//  HouseLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-9-15.
//
//

#ifndef __CKIDS017__HouseLayer__
#define __CKIDS017__HouseLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
USING_NS_CC;
class HouseLayer : public GameLayerBase{
public:
    static CCScene* scene(bool LorR);
    static HouseLayer* create(bool LorR);
    bool init(bool LorR);
    virtual void onEnterTransitionDidFinish();
    virtual void onEnter();
    virtual void onExit();
private:
    CCSprite* houseSprite;
    bool LorR;
    void addHouse();
    void onTypdeItemClicked(CCObject* pObj);
    
};
#endif /* defined(__CKIDS017__HouseLayer__) */
