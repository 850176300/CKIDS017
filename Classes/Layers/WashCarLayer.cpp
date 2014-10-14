//
//  WashCarLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#include "WashCarLayer.h"

CCScene* WashCar::scene(){
    CCScene* scene = CCScene::create();
    
    WashCar* layout = WashCar::create();
    
    scene->addChild(layout);
    
    return scene;
}

bool WashCar::init(){
    if (GameLayerBase::initWithBgFileName(WashCarBGPath)) {
        hasShowHandTip = false;
        garageDoor = CCSprite::create("washing_cars/garage/door.png");
        garageDoor->setPosition(m_pBg->convertToWorldSpace(ccp(80, 429)));
        garageDoor->setScale(STVisibleRect::getRealDesignScale());
        addChild(garageDoor, 1);
        
        MovableItem* tripItem = MovableItem::create("washing_cars/garage/door_trip.png");
        tripItem->setTag(kTripTag);
        tripItem->setTouchable(false);
        tripItem->setTouchEndHandleType(kMovableItemTouchEndStop);
        tripItem->setPosition(m_pBg->convertToWorldSpace(ccp(238.5, 732)));
        tripItem->setStartLocation(tripItem->getPosition());
        tripItem->setMovableItemDelegate(this);
        tripItem->setScale(STVisibleRect::getRealDesignScale());
        addChild(tripItem, 2);
        
        maxDeltaY = tripItem->getContentSize().height * 0.5f - (STVisibleRect::getPointOfSceneLeftUp().y - tripItem->getPositionY());
        return true;
    }
    return false;
}

void WashCar::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    if (hasShowHandTip == false) {
        hasShowHandTip = true;
        playHandTip();
    }
}

void WashCar::playHandTip(){
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0.2f, 0.8f));
    hand->setPosition(ccp(m_pBg->convertToWorldSpace(ccp(238.5, 732)).x, STVisibleRect::getPointOfSceneLeftUp().y-50));
    addChild(hand, 5);
    
    MovableItem* pItem = (MovableItem*)getChildByTag(kTripTag);

    hand->runAction(CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.2f, ccp(0, -50)),
                                       CCDelayTime::create(0.2f),
                                       CCMoveBy::create(0.1f, ccp(0, 50)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.2f, ccp(0, -50)),
                                       CCDelayTime::create(0.2f),
                                       CCScaleTo::create(0.1f, 0),
                                       CCCallFuncO::create(this, callfuncO_selector(WashCar::setTouchItemCanTouch), (MovableItem*)getChildByTag(kTripTag)),
                                       CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                       NULL));
    pItem->runAction(CCSequence::create(
                                        CCDelayTime::create(0.1f),
                                        CCMoveBy::create(0.2f, ccp(0, -50)),
                                        CCDelayTime::create(0.2f),
                                        CCMoveBy::create(0.1f, ccp(0, 50)),
                                        CCDelayTime::create(0.1f),
                                        CCMoveBy::create(0.2f, ccp(0, -50)),
                                        CCDelayTime::create(0.1f),
                                        CCMoveBy::create(0.1f, ccp(0, 50)),
                                        NULL));
}

void WashCar::setTouchItemCanTouch(MovableItem *pItem) {
    pItem->setTouchable(true);
}

void WashCar::ItemDidBackToStartLocation(MovableItem *pItem) {
    if (pItem->getTag() == kTripTag) {
        pItem->runAction(CCMoveTo::create(0.2f, pItem->getStartLocation()));
        if (pItem->getStartLocation().y - pItem->getPositionY() > 100) {
            pItem->setTouchable(false);
            garageDoor->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, STVisibleRect::getGlvisibleSize().height)), CCCallFunc::create(garageDoor, callfunc_selector(CCSprite::removeFromParent)),NULL));
        }
    }
}

void WashCar::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    if (pItem->getTag() == kTripTag) {
        if (pItem->getPositionY()+detla.y < pItem->getStartLocation().y && pItem->getPositionY() + detla.y > pItem->getStartLocation().y - maxDeltaY) {
            pItem->setPositionY(pItem->getPositionY() + detla.y);
        }
    }
}
