//
//  MovableItem.cpp
//  LibDoctor
//
//  Created by tanshoumei on 13-10-14.
//
//

#include "MovableItem.h"
#include "MathUtil.h"
#include "STVisibleRect.h"
#include "CocosHelper.h"
#include "CCEGLView.h"
//#include "NotificationDef.h"
#include "SimpleAudioEngine.h"
#define NotifyGLViewWillLoseFocus "NotifyGLViewWillLoseFocus"
using namespace CocosDenshion;
USING_NS_ST;

MovableItem* MovableItem::create(const char* apName)
{
    MovableItem* pItem = new MovableItem;
    pItem->initWithFile(apName);
    pItem->autorelease();
    return pItem;
}

MovableItem* MovableItem::createWithTexture(cocos2d::CCTexture2D *texture) {
    MovableItem* pItem = new MovableItem();
    pItem->initWithTexture(texture);
    pItem->autorelease();
    return pItem;
}


MovableItem::MovableItem():
m_iTouchEndType(kMovableItemTouchEndStop),
m_pMove(0),
m_uiMovingEffectId(0),
m_uiSelectEffectId(0),
m_bMovingLoop(true),
m_pMovableItemDelegate(0)
{
}

MovableItem::~MovableItem(){
    if (getTouchable() == true) {
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    }
}

bool MovableItem::initWithFile(const char *pszFilename)
{
    if(ItemBase::initWithFile(pszFilename))
    {
        m_sInitName.append(pszFilename);
        m_sMovingName.append(pszFilename);
        m_enState = kMovableItemStateStill;
        float scaleX = CCEGLView::sharedOpenGLView()->getScaleX();
        float scaleY = CCEGLView::sharedOpenGLView()->getScaleY();
        m_tMoveRect.origin = CCEGLView::sharedOpenGLView()->getVisibleOrigin();
        m_tMoveRect.size = CCSizeMake(STVisibleRect::getFrameSize().width / scaleX, STVisibleRect::getFrameSize().height / scaleY);
        CCLOG("%f,%f,%f,%f,", m_tMoveRect.origin.x, m_tMoveRect.origin.y, m_tMoveRect.size.width, m_tMoveRect.size.height);
        m_tMoveRect = STVisibleRect::getMovableRect();
        return true;
    }
    return false;
}

bool MovableItem::initWithTexture(cocos2d::CCTexture2D *pTexture) {
    if (ItemBase::initWithTexture(pTexture)) {
        m_sInitName.append("movable");
        m_sMovingName.append("movable");
        m_enState = kMovableItemStateStill;
        float scaleX = CCEGLView::sharedOpenGLView()->getScaleX();
        float scaleY = CCEGLView::sharedOpenGLView()->getScaleY();
        m_tMoveRect.origin = CCEGLView::sharedOpenGLView()->getVisibleOrigin();
        m_tMoveRect.size = CCSizeMake(STVisibleRect::getFrameSize().width / scaleX, STVisibleRect::getFrameSize().height / scaleY);
        CCLOG("%f,%f,%f,%f,", m_tMoveRect.origin.x, m_tMoveRect.origin.y, m_tMoveRect.size.width, m_tMoveRect.size.height);
        m_tMoveRect = STVisibleRect::getMovableRect();
        return true;
    }
    return false;
}

void MovableItem::onEnter()
{
//    ItemBase::onEnter();
    CCSprite::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MovableItem::_onApplicationWillEnterForeground), NotifyGLViewWillLoseFocus, NULL);
}

void MovableItem::onExit()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NotifyGLViewWillLoseFocus);
//    ItemBase::onExit();

    CCSprite::onExit();
}

bool MovableItem::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(m_pMove){
        stopAction(m_pMove);
        m_pMove = NULL;
    }
    bool ret = ItemBase::ccTouchBegan(pTouch, pEvent);
    if(ret)
    {
        CCLOG("MovableItem::ccTouchBegan:%s", m_sSelectSoundEffect.c_str());
        m_uiSelectEffectId = SimpleAudioEngine::sharedEngine()->playEffect(m_sSelectSoundEffect.c_str());
        changeToMoving();
    }
    return ret;
}

void MovableItem::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_bTouchable)
    {
        _touchEndDoing();
        return;
    }
    if(m_uiSelectEffectId > 0)
    {
//        SimpleAudioEngine::sharedEngine()->stopEffect(m_uiSelectEffectId);
//        m_uiSelectEffectId = 0;
    }
    if(0 == m_uiMovingEffectId)
    {
        m_uiMovingEffectId = SimpleAudioEngine::sharedEngine()->playEffect(m_sMovingSoundEffect.c_str(), m_bMovingLoop);
    }
    ItemBase::ccTouchMoved(pTouch, pEvent);
    //限制在屏幕范围内.先将坐标转换为世界坐标，看其是否还在限制范围内，如是，则设置新的坐标，否则，不做处理
    CCPoint newPtWorld = ccpAdd(convertToWorldSpace(ccp(getContentSize().width * .5f, getContentSize().height * .5f)), pTouch->getDelta());
//    CCLOG("moveRect:(%f,%f,%f,%f)",m_tMoveRect.origin.x, m_tMoveRect.origin.y, m_tMoveRect.size.width,m_tMoveRect.size.height);
//    CCLOG("touchPoint:(%f,%f), newPtWorld:(%f,%f)",pTouch->getLocation().x, pTouch->getLocation().y,newPtWorld.x,newPtWorld.y);
    if (m_pMovableItemDelegate) {
        m_pMovableItemDelegate->itemDidMoved(this, pTouch->getDelta());
    }else {
        if(m_tMoveRect.containsPoint(newPtWorld))
            setPosition(ccpAdd(getPosition(), pTouch->getDelta()));
        else
            CCLOG("out of movable range");
    }
}

CCRect MovableItem::getmovableRect(){
    return m_tMoveRect;
}

void MovableItem::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if(!m_bTouchable)
    {
        _touchEndDoing();
        return;
    }
    ItemBase::ccTouchEnded(pTouch, pEvent);
    _touchEndDoing();
}

void MovableItem::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    ItemBase::ccTouchCancelled(pTouch, pEvent);
    _touchEndDoing();
}

void MovableItem::setMovableItemDelegate(MovableItemDelegate *apDelegate)
{
    ItemBase::addItemTouchDelegate(apDelegate);
    m_pMovableItemDelegate = apDelegate;
}

void MovableItem::setMovingName(std::string asName)
{
    if(asName.compare(m_sMovingName) != 0)
    {
        m_sMovingName = asName;
        if(kMovableItemStateHandMoving == m_enState)
        {
            setDisplayFrame(CCSprite::create(m_sMovingName.c_str())->displayFrame());
        }
    }
}

void MovableItem::setStillName(std::string asName)
{
    if(asName.compare(m_sInitName) != 0)
    {
        m_sInitName = asName;
        if(kMovableItemStateHandMoving != m_enState)
        {
            setDisplayFrame(CCSprite::create(m_sInitName.c_str())->displayFrame());
        }
    }
}

void MovableItem::setSelectSoundEffect(std::string asName)
{
    m_sSelectSoundEffect = asName;
}

void MovableItem::setMovingSoundEffect(std::string asName)
{
    m_sMovingSoundEffect = asName;
}

void MovableItem::setStartLocation(const cocos2d::CCPoint aPt)
{
    m_tStartLocation = aPt;
}

CCPoint MovableItem::getStartLocation()
{
    return m_tStartLocation;
}

void MovableItem::setMoveRect(const cocos2d::CCRect aRect)
{
    m_tMoveRect = aRect;
}

void MovableItem::setTouchEndHandleType(const int aType)
{
    m_iTouchEndType = aType;
}

void MovableItem::setTouchable(bool abValue) {
    m_bTouchable = abValue;
    if (abValue) {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, m_iTouchPriority, true);
    }else {
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    }
}



void MovableItem::backToStartLocation()
{
    CCLOG("MovableItem::backToStartLocation in. state:%d", m_enState);
    if(m_enState != kMovableItemStateBackMoving)
    {
        _changeToBacking();
        CCLOG("MovableItem::backToStartLocation start");
        m_pMove = CCMoveTo::create(.2, m_tStartLocation);
        CCCallFunc *pCall = CCCallFunc::create(this, callfunc_selector(MovableItem::_itemBackEnd));
        CCAction* pAction = NULL;
        if (m_tStartLocation.x < 0) {
            pAction = CCSequence::create(pCall, NULL);
        }else {
            pAction = CCSequence::create(m_pMove, pCall, NULL);
        }
        runAction(pAction);        
    }
}

void MovableItem::_itemBackEnd()
{
    _changeToInit();
    if(m_pMovableItemDelegate)
        m_pMovableItemDelegate->ItemDidBackToStartLocation(this);
}

void MovableItem::_inertiaFront()
{
}

void MovableItem::changeToMoving()
{
    if(m_enState != kMovableItemStateHandMoving)
    {
        m_enState = kMovableItemStateHandMoving;
        if(m_sMovingName.compare(m_sInitName) != 0)
        {
            CCSprite* spr = CCSprite::create(m_sMovingName.c_str());
            if(spr)
                setDisplayFrame(spr->displayFrame());
        }
    }
}

//这里假设外貌和初始是一样的
void MovableItem::_changeToBacking()
{
    m_enState = kMovableItemStateBackMoving;
}

void MovableItem::_changeToInit()
{
    if(m_enState == kMovableItemStateStill)
        return;
    m_enState = kMovableItemStateStill;
    CCSprite* spr = CCSprite::create(m_sInitName.c_str());
    if(spr)
        setDisplayFrame(spr->displayFrame());
}

void MovableItem::setMovingSoundEffectLoop(bool aLoop)
{
    m_bMovingLoop = aLoop;
}

void MovableItem::_onApplicationWillEnterForeground(cocos2d::CCObject *apObj)
{
    if(kMovableItemTouchEndBackStart == m_iTouchEndType)
    {
        backToStartLocation();
    }
    if(m_pMovableItemDelegate)
        m_pMovableItemDelegate->itemDidBecomActive(this);
    _stopSoundEffect();
}

void MovableItem::_touchEndDoing()
{
    switch (m_iTouchEndType) {
        case kMovableItemTouchEndStop:
            //do nothing
            if (m_pMovableItemDelegate) {
                m_pMovableItemDelegate->ItemDidBackToStartLocation(this);
            }
            break;
        case kMovableItemTouchEndBackStart:
            backToStartLocation();
            break;
        case kMovableItemTouchEndInertia:
            _inertiaFront();
            break;
        default:
            break;
    }
    //停止音效
    _stopSoundEffect();
}

void MovableItem::_stopSoundEffect()
{
    CCLOG("MovableItem::_stopSoundEffect");
    if(m_uiMovingEffectId > 0)
    {
        SimpleAudioEngine::sharedEngine()->stopEffect(m_uiMovingEffectId);
        m_uiMovingEffectId = 0;
    }
    if(m_uiSelectEffectId > 0)
    {
        SimpleAudioEngine::sharedEngine()->stopEffect(m_uiSelectEffectId);
        m_uiSelectEffectId = 0;
    }
}