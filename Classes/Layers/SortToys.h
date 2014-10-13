//
//  SortToys.h
//  CKIDS017
//
//  Created by liuwei on 14-10-13.
//
//

#ifndef __CKIDS017__SortToys__
#define __CKIDS017__SortToys__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "MovableItem.h"
USING_NS_CC;

enum SortToysTags{
    kBlocksTagAtOne = 51001,
    kDollsTagAtOne = 51101,
    kCarsTagAtOne = 50111,
};
class SortToys : public GameLayerBase, public MovableItemDelegate{
public:
    ~SortToys(){CC_SAFE_RELEASE(_parent);};
    static CCScene* scene(CCObject* pObj);
    static SortToys* createWithObj(CCObject* pObj);
    bool initWithObj(CCObject* pObj);
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch);
    virtual void onNextBtnClicked();
    virtual void onResetBtnClicked();
    virtual void onEnterTransitionDidFinish();
private:
    CCObject* _parent;
    CCRect blockRect;
    CCRect carRect;
    CCRect dollsRect;
    void addblocks();
    void addcars();
    void adddolls();
    void checkToyCount();
    int allToyCount;
    void setZorderforItem(MovableItem* pItem);
    void resetpItems(int tag, int count);
};
#endif /* defined(__CKIDS017__SortToys__) */
