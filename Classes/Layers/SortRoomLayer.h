//
//  SortRoomLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-12.
//
//

#ifndef __CKIDS017__SortRoomLayer__
#define __CKIDS017__SortRoomLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "MovableItem.h"
USING_NS_CC;

enum SortRoomLayerTags{
    kBedTags = 5111,//床
    kForcerTags,//柜子
    kLightTags,//灯
    kLight1Tags = 5124,
    kPandaTags,//跳跳熊
    ktheMenuTags,
};


class SortRoomLayer : public GameLayerBase{
public:
    enum ForcerOrder{
        kRandom = 1,
        kSort,
        kSorted,
    };
public:
    static CCScene* scene();
    virtual bool init();
    virtual void onEnter();
    CREATE_FUNC(SortRoomLayer);
     ForcerOrder theOrder;
private:
    bool showShader;
    CCSprite* shaderSprite;
    void addAllSortItems();
    void onSortItemsClicked(CCObject* pObj);
    void onLightClicked();
};
#endif /* defined(__CKIDS017__SortRoomLayer__) */
