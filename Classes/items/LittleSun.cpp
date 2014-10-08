//
//  LittleSun.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-20.
//
//

#include "LittleSun.h"
#include "PlantingLayer.h"
LittleSun* LittleSun::createWithFile(const char *file) {
    LittleSun* pRet = new LittleSun();
    if (pRet && pRet->initWithFile(file)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool LittleSun::initWithFile(const char *file) {
    if (CCSprite::initWithFile(file)) {
        setScale(0);
        return true;
    }
    return false;
}

void LittleSun::onEnter() {
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void LittleSun::onExit(){
    CCSprite::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool LittleSun::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (getParent()) {
        if (!boundingBox().containsPoint(getParent()->convertToNodeSpace(pTouch->getLocation()))) {
            return false;
        }
    }
    if (getScale() < 1.0) {
        return true;
    }
    if (getTag() == 22220 && getPositionY() > STVisibleRect::getCenterOfScene().y) {
        return true;
    }
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    removeAllComponents();
    PlantingLayer* parent = (PlantingLayer*)getParent();
    if (getTag() == 22220) {
        parent->onSunClicked();
        runAction(CCSequence::create(CCScaleTo::create(0.3f, 0),CCCallFunc::create(this, callfunc_selector(LittleSun::addSunParticles)), CCCallFunc::create(this, callfunc_selector(CCSprite::removeFromParent)), NULL));
    }else {
        parent->onCloudeClicked();
        runAction(CCSequence::create(CCScaleTo::create(0.3f, 0), CCCallFunc::create(this, callfunc_selector(LittleSun::addParticle)),CCCallFunc::create(this, callfunc_selector(CCSprite::removeFromParent)), NULL));
    }
    
    return true;
}

void LittleSun::addParticle(){
    PlantingLayer* parent = (PlantingLayer*)getParent();
    CCParticleSystemQuad* particle = CCParticleSystemQuad::create("particles/boning.plist");
    particle->setPosition(parent->convertToNodeSpace(getPosition()));
    parent->addChild(particle, 8);
}

void LittleSun::addSunParticles(){
    PlantingLayer* parent = (PlantingLayer*)getParent();
    CCParticleSystemQuad* particle = CCParticleSystemQuad::create("particles/sunparticles.plist");
    particle->setPosition(parent->convertToNodeSpace(getPosition()));
    parent->addChild(particle, 8);
}

