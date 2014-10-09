//
//  CleanRoomLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-9.
//
//

#ifndef __CKIDS017__CleanRoomLayer__
#define __CKIDS017__CleanRoomLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "DaubSprite.h"
#include "DragItemLayer.h"
#include "MovableItem.h"
USING_NS_CC;
enum CleanRoomLayerTags{
    kBroomToolTags = 4111,//笤帚
    kVacuumToolTags,//吸尘器
    kRagToolTags,//喷壶
    kBroom2ToolTags,//扫把
    kMopToolTags,//拖把
};

class CleanRoomLayer : public GameLayerBase, public MovableItemDelegate{
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(CleanRoomLayer);
    virtual void itemTouchDidBegan(ItemBase* pItem, CCTouch *pTouch);
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
private:
    void showtoolLayer(MovableItem* pItem);
    /*添加所有的工具**/
    void addAlltools();
    DragItemLayer* toolsLayer;
    /*添加笤帚清除的灰尘图层**/
    DaubSprite* dust1;
    DaubSprite* dust2;
    DaubSprite* dust3;
    DaubSprite* dust4;
    void addallDust();
    /*吸尘器清除的灰尘**/
    DaubSprite* dust5;
    DaubSprite* dust6;
    
};
#endif /* defined(__CKIDS017__CleanRoomLayer__) */
