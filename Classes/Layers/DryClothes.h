//
//  DryClothes.h
//  CKIDS017
//
//  Created by liuwei on 14-9-26.
//
//

#ifndef __CKIDS017__DryClothes__
#define __CKIDS017__DryClothes__

#include <iostream>
#include <sstream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "MovableItem.h"
#include "DragItemLayer.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
enum DryClothesTags{
    kClotheModelFirst = 3111,
    kClotheEntryFirst = 3333,
};

class LittleClothe: public CCNode{
private:
    CCSize clotheContentSize;
    CCSprite* clotheSprite;
public:
    static LittleClothe* createWithClothe(DryClothe clothe);
    bool initWithClothe(DryClothe clothe);
    CCRect getclotheBouning();
    void additem(MovableItem* pItem);
    void changetexture(MovableItem* pItem);
};

class DryClothes : public GameLayerBase, public MovableItemDelegate{
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(DryClothes);
    virtual void onEnterTransitionDidFinish();
    virtual void onEnter();
    virtual void onExit();
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void itemTouchDidBegan(ItemBase* pItem, CCTouch *pTouch);
private:
    CCNode* _littlecontainer;
    DragItemLayer* dragLayer;
    CCScrollView * littleClotheScrollView;
    int completeCount;//完成的个数
    void scrollClothes();
    void showWellDone();
};
#endif /* defined(__CKIDS017__DryClothes__) */
