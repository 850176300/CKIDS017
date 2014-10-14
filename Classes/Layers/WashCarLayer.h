//
//  WashCarLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#ifndef __CKIDS017__WashCarLayer__
#define __CKIDS017__WashCarLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "MovableItem.h"
USING_NS_CC;
class WashCar: public GameLayerBase, public MovableItemDelegate{
    enum ItemTags{
        kTripTag = 6111,
        
    };
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(WashCar);
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void onEnterTransitionDidFinish();
private:
    void playHandTip();
    void setTouchItemCanTouch(MovableItem* pItem);//设置移动的元素可以被移动
    bool hasShowHandTip;
    CCSprite* garageDoor;//车库的门
    float maxDeltaY;//链子最大的y偏移
};
#endif /* defined(__CKIDS017__WashCarLayer__) */
