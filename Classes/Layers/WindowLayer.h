//
//  WindowLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-10.
//
//

#ifndef __CKIDS017__WindowLayer__
#define __CKIDS017__WindowLayer__

#include <iostream>
#include "GameLayerBase.h"
#include "cocos2d.h"
#include "Scribble.h"
#include "DaubSprite.h"
#include "MovableItem.h"
USING_NS_CC;

class WindowLayer : public GameLayerBase, public MovableItemDelegate{
public:
    WindowLayer(){_scribble = NULL;};
    ~WindowLayer(){CC_SAFE_DELETE(_scribble); CC_SAFE_RELEASE(_parent);};
    static CCScene* scene(CCObject* pObj);
    static WindowLayer* createWithObj(CCObject* pObj);
    bool initWithobj(CCObject* pObj);

    virtual void itemTouchDidBegan(ItemBase* pItem, CCTouch *pTouch);
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void onNextBtnClicked();
private:
    CCObject* _parent;
    Scribble* _scribble;
    DaubSprite* dust;
    void addDust();
    void addMopTool();
};
#endif /* defined(__CKIDS017__WindowLayer__) */
