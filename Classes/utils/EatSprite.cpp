//
//  EatSprite.cpp
//  MAKE-Dumpling
//
//  Created by zhuliang on 21/11/13.
//
//

#include "EatSprite.h"
#include "SimpleAudioEngine.h"
#include "SoundPlayer.h"

EatSprite* EatSprite::create(cocos2d::CCTexture2D *texture)
{
    EatSprite *eatSprite = new EatSprite();

    CCSprite *bg = CCSprite::createWithTexture(texture);
    bg->setFlipY(true);
    
    if (eatSprite && eatSprite->initWithFile("transparent.png", bg->getTextureRect()))
    {
        eatSprite->addChild(bg);
        bg->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2));
        //bg->setFlipY(true);
        
        eatSprite->render_= CCRenderTexture::create(CCDirector::sharedDirector()->getWinSize().width,CCDirector::sharedDirector()->getWinSize().height);
        eatSprite->render_->setPosition(CCDirector::sharedDirector()->getWinSize().width/2,CCDirector::sharedDirector()->getWinSize().height/2);
        eatSprite->addChild(eatSprite->render_,1);
        eatSprite->render_->begin();
        bg->visit();
        eatSprite->render_->end();
        
        bg->removeFromParent();
        
        eatSprite->brush_ = CCSprite::create("brush.png");
        eatSprite->brush_->retain();
        ccBlendFunc ccbFunc = {GL_ZERO,GL_ONE_MINUS_SRC_ALPHA};
        eatSprite->brush_->setBlendFunc(ccbFunc);
        
        eatSprite->touches_ = CCArray::createWithCapacity(0);
        eatSprite->touches_->retain();
        
       
        
        eatSprite->isEnable = true;
        
        eatSprite->startDraw();
        
        eatSprite->autorelease();
        
        
        return eatSprite;
        
        
    }
    CC_SAFE_DELETE(eatSprite);
    
    return eatSprite;

}

void EatSprite::onEnter(){
    CCNode::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void EatSprite::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);

    CCNode::onExit();
}

void EatSprite::removeEatAction()
{
     //    this->unscheduleUpdate();
}


EatSprite::~EatSprite()
{
    CCLog("eatsprite del");
//    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCTextureCache::sharedTextureCache()->removeTextureForKey("transparent.png");
    CCTextureCache::sharedTextureCache()->removeTextureForKey("brush.png");
    
    brush_->release();
    
    touches_->release();
    
    
    
}

void EatSprite::startDraw()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(render_, EVENT_COME_TO_BACKGROUND);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(render_, EVENT_COME_TO_FOREGROUND);
//    this->unscheduleUpdate();
//    this->scheduleUpdate();

}

void EatSprite::update(float dt)
{
    CCLog("eatSprite on update the view =======");
    render_->begin();
    
    CCObject *obj = NULL;
    CCARRAY_FOREACH(touches_, obj)
    {
        
    }
    
    touches_->removeAllObjects();
    
    render_->end();
    
}


#pragma mark -touchDelegate
bool EatSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!isEnable) {
        return false;
    }
    
    SoundPlayer::getInstance()->eatthingsGroundMusic();
//    if(!CCUserDefault::sharedUserDefault()->getBoolForKey(EFFECT_STATUS))
//        CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("eat.mp3");
    
//    touches_->addObject(pTouch);
    
    
    CCPoint touchLocation = CCDirector::sharedDirector()->convertToGL(pTouch->getLocation());
    
    render_->begin();
    touchLocation = render_->getSprite()->convertToNodeSpace(touchLocation);
    brush_->setPosition(touchLocation);
    brush_->visit();
    render_->end();
    
//    touchCount++;
//    if (touchCount == 3) {
//        CCNotificationCenter::sharedNotificationCenter()->postNotification("showSurprise");
//    }
    
    return true;
    
}


void EatSprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
        

    
    
}


void EatSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    touches_->removeAllObjects();

}


void EatSprite::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    touches_->removeAllObjects();
    
}




