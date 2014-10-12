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
    kLight1Tags,
    kPandaTags,//跳跳熊
};


class SortRoomLayer : public GameLayerBase{
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(SortRoomLayer);
private:
    void addAllSortItems();
    void onSortItemsClicked(CCObject* pObj);
};
#endif /* defined(__CKIDS017__SortRoomLayer__) */
