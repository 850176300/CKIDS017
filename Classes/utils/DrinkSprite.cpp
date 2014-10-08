//
//  DrinkSprite.cpp
//  BBQParty
//
//  Created by liuwei on 14-8-25.
//
//

#include "DrinkSprite.h"
#include "SoundPlayer.h"


DrinkSprite* DrinkSprite::create(const char *pszFile, const char *maskFile) {
    DrinkSprite* sprite = new DrinkSprite();
    if (sprite && sprite->initWithFileAndmask(pszFile, maskFile)) {
        sprite->autorelease();
        return sprite;
    }else {
        delete sprite;
        sprite = NULL;
        return  NULL;
    }
}

DrinkSprite*  DrinkSprite::create(cocos2d::CCTexture2D *texture, const char *maskFile) {
    DrinkSprite* sprite = new DrinkSprite();
    if (sprite && sprite->initWithTextureAndmask(texture, maskFile)) {
        sprite->autorelease();
        return sprite;
    }else {
        delete sprite;
        sprite = NULL;
        return  NULL;
    }
}

DrinkSprite::DrinkSprite(){}
DrinkSprite::~DrinkSprite(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    if (brush_) {
        brush_->release();
        brush_ = NULL;
    }
}


bool DrinkSprite::initWithFileAndmask(const char *pszFilename, const char *maskFile) {
    CCSprite* bg = CCSprite::create(pszFilename);
    if (CCSprite::initWithFile("transparent.png", bg->getTextureRect())) {
        beenFinished = false;
        height = bg->getContentSize().height;
        this->addChild(bg);
        bg->setPosition(ccp(bg->getContentSize().width/2.0, bg->getContentSize().height/2.0));
        
        render_ = CCRenderTexture::create(bg->getContentSize().width, bg->getContentSize().height);
        render_->setPosition(bg->getPosition());
        this->addChild(render_,1);
        
        render_->begin();
        bg->visit();
        render_->end();
        
        bg->removeFromParent();
        
        brush_ = CCSprite::create(maskFile);
        brush_->retain();
        ccBlendFunc ccbFunc = {GL_ZERO,GL_ONE_MINUS_SRC_ALPHA};
        brush_->setBlendFunc(ccbFunc);
        brush_->setFlipY(true);
        
        brush_->setAnchorPoint(ccp(0.5, 0));
        startDrink();
        return true;
    }
    return false;
}

bool DrinkSprite::initWithTextureAndmask(cocos2d::CCTexture2D *pTexture, const char *maskFile) {
    CCSprite* bg = CCSprite::createWithTexture(pTexture);
    if (CCSprite::initWithFile("transparent.png", bg->getTextureRect())) {
        beenFinished = false;
        height = bg->getContentSize().height;
        this->addChild(bg);
        bg->setPosition(ccp(bg->getContentSize().width/2.0, bg->getContentSize().height/2.0));
        
        render_ = CCRenderTexture::create(bg->getContentSize().width, bg->getContentSize().height);
        render_->setPosition(bg->getPosition());
        this->addChild(render_,1);
        
        render_->begin();
        bg->visit();
        render_->end();
        
        bg->removeFromParent();
        
        brush_ = CCSprite::create(maskFile);
        brush_->retain();
        ccBlendFunc ccbFunc = {GL_ZERO,GL_ONE_MINUS_SRC_ALPHA};
        brush_->setBlendFunc(ccbFunc);
        brush_->setFlipY(true);
        
        brush_->setAnchorPoint(ccp(0.5, 0));
        startDrink();
        return true;
    }
    return false;
}


void DrinkSprite::startDrink(){
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(render_, EVENT_COME_TO_BACKGROUND);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(render_, EVENT_COME_TO_FOREGROUND);
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, false);
}
void DrinkSprite::onEnter(){
    CCNode::onEnter();
    
}

void DrinkSprite::onExit(){
    
    CCNode::onExit();
    SoundPlayer::getInstance()->stopDrinkMusic();
}

void DrinkSprite::update(float dt) {
    if (height <= 0 && beenFinished == true) {
        return;
    }
    brush_->setPosition(ccp(this->getContentSize().width/2.0, height));
    render_->begin();
    brush_->visit();
    render_->end();
    height -= 2;
    if (height <= 0) {
        beenFinished = true;
        height = 0;
        SoundPlayer::getInstance()->stopDrinkMusic();
        unscheduleUpdate();
    }
    
}

bool DrinkSprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    if (boundingBox().containsPoint(pTouch->getLocation())) {
        if (beenFinished == false) {
            scheduleUpdate();
            playEffect();
            schedule(schedule_selector(DrinkSprite::playEffect), 1.0f);
        }else {
            
        }
        return true;
    }else {
        return false;
    }
}

void DrinkSprite::playEffect(){
    SoundPlayer::getInstance()->stopDrinkMusic();
    SoundPlayer::getInstance()->addWaterGroundMusic();
}

void DrinkSprite::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    
}

void DrinkSprite::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    unscheduleUpdate();
    unschedule(schedule_selector(DrinkSprite::playEffect));
    SoundPlayer::getInstance()->stopDrinkMusic();
}

void DrinkSprite::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    unscheduleUpdate();
    unschedule(schedule_selector(DrinkSprite::playEffect));
    SoundPlayer::getInstance()->stopDrinkMusic();
}
