//
//  ItemBase.cpp
//  Doctor
//
//  Created by tanshoumei on 13-8-14.
//
//

#include "ItemBase.h"

ItemBase* ItemBase::create(const char *apName)
{
    ItemBase* pItem = new ItemBase;
    pItem->initWithFile(apName);
    pItem->autorelease();
    return pItem;
}

ItemBase* ItemBase::createWithFrameName(const char *apName)
{
    ItemBase* pItem = new ItemBase;
    pItem->initWithSpriteFrameName(apName);
    pItem->autorelease();
    return pItem;
}

ItemBase::ItemBase():
m_bTouchable(0),
m_iTouchPriority(0)
{
}

ItemBase::~ItemBase()
{
}

void ItemBase::onEnter()
{
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_iTouchPriority, true);
}

void ItemBase::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

void ItemBase::addItemTouchDelegate(ItemTouchDelegate *apDelegate)
{

    if(std::find(m_vItemTouchDelegates.begin(), m_vItemTouchDelegates.end(), apDelegate) == m_vItemTouchDelegates.end())
    {
        m_vItemTouchDelegates.push_back(apDelegate);
    }
}

void ItemBase::setTouchable(bool abValue)
{
    m_bTouchable = abValue;
}

bool ItemBase::getTouchable()
{
    return m_bTouchable;
}

/*
 ���������������contentsize������������������������������������������world���������local
 **/
Polygon ItemBase::getPolygon()
{
    CCPoint pts[4] = {
        CCPointZero, ccp(getContentSize().width, 0), ccp(getContentSize().width, getContentSize().height), ccp(0, getContentSize().height)
    };
    Polygon polygon;
    for (int inx = 0; inx <4; ++inx) {
        CCPoint pt = convertToWorldSpace(pts[inx]);
        polygon.addVec(pt);
    }
    return polygon;
}

bool ItemBase::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    //���m_bTouchable == true���������������item������������������������������������������touch event.
    if(!m_bTouchable || !ptInPolygon(pTouch->getLocation(), getPolygon()))
        return false;
    vector<ItemTouchDelegate*>::iterator itr;
    for (itr = m_vItemTouchDelegates.begin(); itr != m_vItemTouchDelegates.end(); ++itr) {
        (*itr)->itemTouchDidBegan(this, pTouch);
    }
    return true;
}

void ItemBase::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	vector<ItemTouchDelegate*>::iterator itr;
    for (itr = m_vItemTouchDelegates.begin(); itr != m_vItemTouchDelegates.end(); ++itr) {
        (*itr)->itemTouchDidMoved(this, pTouch);
    }
}

void ItemBase::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	vector<ItemTouchDelegate*>::iterator itr;
    for (itr = m_vItemTouchDelegates.begin(); itr != m_vItemTouchDelegates.end(); ++itr) {
        (*itr)->itemTouchDidEnded(this, pTouch);
    }
}

void ItemBase::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	vector<ItemTouchDelegate*>::iterator itr;
    for (itr = m_vItemTouchDelegates.begin(); itr != m_vItemTouchDelegates.end(); ++itr) {
        (*itr)->itemTouchDidCancel(this, pTouch);
    }
}

void ItemBase::setTouchPriority(const int aValue)
{
    m_iTouchPriority = aValue;
    CCTouchHandler* pHandler = CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this);
    if(pHandler)
        pHandler->setPriority(m_iTouchPriority);
}

void ItemBase::setStartPos(cocos2d::CCPoint pos) {
    theStartPos = pos;
}

CCPoint ItemBase::getStartPos(){
    return theStartPos;
}
