//
//  SelectCarLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-13.
//
//

#ifndef __CKIDS017__SelectCarLayer__
#define __CKIDS017__SelectCarLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "ScrollMenu.h"
USING_NS_CC;

class SelectCar : public GameLayerBase{
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(SelectCar);

    virtual void onEnterTransitionDidFinish();
private:
    ScrollMenu* theScroll;
    bool hasPlayAnimation;
    float startx;
    void addScrollView();
    CCMenu* createMenu();
    void onItemClicked(CCObject* pObj);
};
#endif /* defined(__CKIDS017__SelectCarLayer__) */
