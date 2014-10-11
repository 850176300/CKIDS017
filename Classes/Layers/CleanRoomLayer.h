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

enum WindowStatues{
    kDirty = 41,
    kClean,
    kCleaned,
};

enum MuralsStatues{
    kRandom = 411,
    kSort,
    kSorted,
};

class CleanRoomLayer : public GameLayerBase, public MovableItemDelegate{
public:
    CleanRoomLayer(){_scribble = NULL;};
    ~CleanRoomLayer(){CC_SAFE_DELETE(_scribble);};
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(CleanRoomLayer);
    void setWindowStatues(WindowStatues state);
    void setMuralsStatues(MuralsStatues state);
    virtual void itemTouchDidBegan(ItemBase* pItem, CCTouch *pTouch);
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void onEnter();
private:
    WindowStatues _winState;
    MuralsStatues _muralState;
    Scribble*  _scribble;//涂抹功能的图案
    void showtoolLayer(MovableItem* pItem);
    /*添加所有的工具**/
    void addAlltools();
    DragItemLayer* toolsLayer;
    /*添加笤帚清除的灰尘图层**/
    DaubSprite* dust1;
    DaubSprite* dust2;
    DaubSprite* dust3;
    DaubSprite* dust4;
    CCSprite* spider1;
    CCSprite* spider2;
    CCSprite* spider3;
    void addallDust();
    /*吸尘器清除的灰尘**/
    CCSprite* dust5;
    CCSprite* dust6;
    CCSprite* dust7;//沙发上面的
    void addCleanerDust();
    /*扫把清除的飞尘和纸屑**/
    CCSprite* paper1;
    CCSprite* paper2;
    CCSprite* paper3;
    DaubSprite* dust8;
    void addBroom2Items();//添加扫把清除物品
    /*拖把清除的污水**/
    CCSprite* water1;
    CCSprite* water2;
    void addModItems();//添加拖把清除物品
    /*窗户的污渍**/
    CCSprite* dustonWind;
    /*位置错乱的壁画**/
    MyItemSprite* item1;
    MyItemSprite* item2;
    MyItemSprite* item3;
    void addAllMurals();//添加所有壁画
    
    void addWindowDust();
    void onPaintClicked();
    
    int doneCount;
    void checkisDone();
    void addtip();
};
#endif /* defined(__CKIDS017__CleanRoomLayer__) */
