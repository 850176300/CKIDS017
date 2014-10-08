//
//  SunSprite.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-19.
//
//

#include "SunSprite.h"
#include "PlantingLayer.h"
#include "SuperGlobal.h"
SunSprite* SunSprite::createOne(){
    SunSprite* pRet = new SunSprite();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool SunSprite::init(){
    if (CCSprite::initWithFile("planting/weather_1.png")) {
        stopProduct = false;
        return true;
    }
    return false;
}

bool SunSprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
//    CCLog("the touch point is %s, and boundingBox is %s", GetPointString(convertTouchToNodeSpace(pTouch)), GetRectString(boundingBox()));
    if (getParent()) {
        if (!boundingBox().containsPoint(getParent()->convertToNodeSpace(pTouch->getLocation()))) {
            return false;
        }
    }
    unschedule(schedule_selector(SunSprite::updateSun));
    stopAllActions();
    setTexture(CCSprite::create("planting/weather_3.png")->getTexture());
    runAction(CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(SunSprite::runAnimation)), NULL));
    return true;
}

void SunSprite::onEnter(){
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

void SunSprite::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}
void SunSprite::runAnimation(){
    CCAnimation* animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("planting/weather_1.png");
    animation->addSpriteFrameWithFileName("planting/weather_4.png");
    animation->setDelayPerUnit(0.5f);
    animation->setLoops(-1);
    
    CCAnimate* animate = CCAnimate::create(animation);
    runAction(animate);
    
    schedule(schedule_selector(SunSprite::updateSun), 2.0f, -1, 2.0f);
}

void SunSprite::updateSun(float dt) {
    if (stopProduct == true) {
        return;
    }
    productSun();
}

void SunSprite::productSun(){
    if (getParent()) {
        PlantingLayer* layer = (PlantingLayer*)getParent();
        layer->addlittleSun();
    }
    unschedule(schedule_selector(SunSprite::updateSun));
    stopAllActions();
    setTexture(CCSprite::create("planting/weather_2.png")->getTexture());
    runAction(CCSequence::create(CCDelayTime::create(0.5f), CCCallFunc::create(this, callfunc_selector(SunSprite::runAnimation)), NULL));
}
