//
//  SortMuralsLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-11.
//
//

#ifndef __CKIDS017__SortMuralsLayer__
#define __CKIDS017__SortMuralsLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "MovableItem.h"
USING_NS_CC;

enum SortMuralsLayerTags{
    kMurals1Tag = 4441,
    kMurals2Tag,
    kMurals3Tag,
};
class SortMuralsLayer : public GameLayerBase, public MovableItemDelegate{
public:
    SortMuralsLayer(){_parent = NULL;};
    ~SortMuralsLayer(){CC_SAFE_RELEASE(_parent);};
    static CCScene* scene(CCObject* pObj);
    static SortMuralsLayer* createWithObj(CCObject* pObj);
    bool initWithObj(CCObject* pObj);
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch);
    virtual void onNextBtnClicked();
private:
    int count;//记录已经整理好的壁画数量
    CCObject *_parent;
    void updateCount();
    
};
#endif /* defined(__CKIDS017__SortMuralsLayer__) */
