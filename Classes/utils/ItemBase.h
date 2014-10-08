//
//  ItemBase.h
//  Doctor
//
//  Created by tanshoumei on 13-8-14.
//
//

#ifndef __Doctor__ItemBase__
#define __Doctor__ItemBase__
#include <iostream>
#include "cocos2d.h"
#include "Collsion.h"
#include <vector>
#include <algorithm>
USING_NS_CC;
using namespace std;

class ItemBase;
/*
 item touch delegate.
 **/
class ItemTouchDelegate
{
public:
    //touch did begin.
    virtual void itemTouchDidBegan(ItemBase* pItem, CCTouch *pTouch) {};
    //touch did move
    virtual void itemTouchDidMoved(ItemBase* pItem, CCTouch *pTouch) {};
    //touch did end
    virtual void itemTouchDidEnded(ItemBase* pItem, CCTouch *pTouch) {};
    //touch did cancel
    virtual void itemTouchDidCancel(ItemBase* pItem, CCTouch *pTouch) {};
};

/*
 ���������������������������������������������������
 1.������������touch did begin or touch did end������������������������������
 2.������������������touch did moved���������������item������������
 3.���������������������������������������������=���=
 **/
class ItemBase: public CCSprite, public CCTouchDelegate
{
public:
    //static create method.
    static ItemBase* create(const char* apName);
    static ItemBase* createWithFrameName(const char* apName);
    ItemBase();
    virtual ~ItemBase();
    /*
     ���������������������.
     ���������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
     ������������������contentsize������������������������
     **/
    virtual Polygon getPolygon();
    virtual void onEnter();
    virtual void onExit();
    
    //touch event.
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    //���������������������ItemBase���������������������������������������������������������������������������������������delegate���������
    void addItemTouchDelegate(ItemTouchDelegate* apDelegate);
    
    //������item������������������������������������delegate���������������������
    void setTouchable(bool abValue);
    bool getTouchable();
    
    void setTouchPriority(const int aValue);
    void setStartPos(CCPoint pos);
    CCPoint getStartPos();
protected:
    vector<ItemTouchDelegate*> m_vItemTouchDelegates;
    //���������������
    int m_iTouchPriority;
    bool m_bTouchable;
    CCPoint theStartPos;
};

/*
 ������������ItemBase������������������������������������������
 **/
static bool isTwoItemCollided( ItemBase* apItemOne, ItemBase* apItemTwo )
{
    return polygonCollision(apItemOne->getPolygon(), apItemTwo->getPolygon());
}

/*
 ���������������contentsize������������������������������������������world���������local
 **/
static Polygon getNodeContentPolygon(CCNode* apNode)
{
    CCPoint pts[4] = {
        CCPointZero, ccp(apNode->getContentSize().width, 0), ccp(apNode->getContentSize().width, apNode->getContentSize().height), ccp(0, apNode->getContentSize().height)
    };
    Polygon polygon;
    for (int inx = 0; inx <4; ++inx) {
        //���������world,������������������������������������������������������������������
        CCPoint pt = apNode->convertToWorldSpace(pts[inx]);
        polygon.addVec(pt);
    }
    return polygon;
}

#endif /* defined(__Doctor__ItemBase__) */
