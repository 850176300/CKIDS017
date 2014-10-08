//
//  Baby.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-12.
//
//

#include "Baby.h"
#include "DataContainer.h"
Baby* Baby::createWithParams(int index, string prefix/* = "select_figure/"*/) {
    Baby* pRet = new Baby();
    if (pRet && pRet->initWithParams(index, prefix)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool Baby::initWithParams(int index, string prefix) {
    indexTag = index;
    normal = prefix + DataContainer::getInstance()->getBabyByIndex(index)+"_normal.png";
    close = prefix + DataContainer::getInstance()->getBabyByIndex(index)+"_close_eye.png";
    smile = prefix + DataContainer::getInstance()->getBabyByIndex(index)+"_smile.png";
    if (CCSprite::initWithFile(normal.c_str())) {
        isSmiling = false;
//        runAnimation();
        if (!DataContainer::getInstance()->getBabyisFree(index)) {
            CCSprite* lock = CCSprite::create("ui/suo.png");
            lock->setAnchorPoint(ccp(1.0, 0));
            lock->setPosition(ccp(getContentSize().width - 10, 10));
            lock->setTag(theLockTagforAll);
            addChild(lock);
        }
        return true;
    }
    return false;
}

void Baby::onEnter(){
    CCSprite::onEnter();
    if (DataContainer::getInstance()->getBabyisFree(indexTag)) {
        removeChildByTag(kLockTag);
    }
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void Baby::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}

void Baby::setTouchPriority(int priority) {
    CCDirector::sharedDirector()->getTouchDispatcher()->setPriority(priority, this);
}

void Baby::setTouchDelegate(BabyDelegate *delegate) {
    if (pDelegate != NULL) {
        pDelegate = NULL;
    }
    pDelegate = delegate;
}

void Baby::runAnimation(){
    CCAnimation* animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName(normal.c_str());
    animation->addSpriteFrameWithFileName(close.c_str());
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.5f);
    
    CCAnimate* pAction = CCAnimate::create(animation);
    runAction(pAction);
    numofRunningActions = numberOfRunningActions();
}


bool Baby::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (getParent()) {
        if (!boundingBox().containsPoint(getParent()->convertToNodeSpace(pTouch->getLocation()))) {
            return false;
        }
    }
    if (numberOfRunningActions() <= numofRunningActions && isSmiling == false) {
        stopAllActions();
        setTexture(CCSprite::create(smile.c_str())->getTexture());
        isSmiling = true;
        if (pDelegate != NULL) {
            pDelegate->onBabyClicked(indexTag);
        }else {
            scheduleOnce(schedule_selector(Baby::stopSmile), 1.0f);
        }
        return true;
    }
    return false;
}

void Baby::stopSmile(){
    isSmiling = false;
    runAnimation();
}

