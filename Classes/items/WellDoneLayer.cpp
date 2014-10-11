//
//  WellDoneLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-24.
//
//

#include "WellDoneLayer.h"
#include "MyItemSprite.h"
#include "SMMenu.h"
#include "STVisibleRect.h"

USING_NS_ST;
#define ItemsSize CCSizeMake(102,109)
WellDoneLayer* WellDoneLayer::createWithBoolen(bool isSucceed) {
    WellDoneLayer* pRet = new WellDoneLayer();
    if (pRet && pRet->initWithBoolen(isSucceed)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool WellDoneLayer::initWithBoolen(bool isSucceed){
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 150))) {
        boolenParm = isSucceed;
        CCSprite* title = NULL;
        if (isSucceed) {
            title = CCSprite::create("ui/prompt/well_done.png");
        }else {
            title = CCSprite::create("ui/prompt/failed.png");
        }
        MyItemSprite* left = NULL;
        if (isSucceed) {
            left = MyItemSprite::menuItems("ui/btn_home.png");
        }else {
            left = MyItemSprite::menuItems("ui/home_btn_play.png");
            left->setScale(102.0/178.0);
        }
        MyItemSprite* reset = MyItemSprite::menuItems("ui/btn_reset.png");
        
        
        itemsNode = CCNode::create();
        itemsNode->setAnchorPoint(ccp(0.5f, 0.5f));
        itemsNode->setContentSize(CCSizeMake(title->getContentSize().width, title->getContentSize().height+30+ItemsSize.height));
        
        left->setAnchorPoint(ccp(1.0, 0));
        reset->setAnchorPoint(ccp(0, 0));
        left->setPosition(ccp(itemsNode->getContentSize().width/2.0-20, 0));
        reset->setPosition(ccp(itemsNode->getContentSize().width/2.0+20, 0));
        left->setTarget(this, menu_selector(WellDoneLayer::onLeftBtnClicked));
        reset->setTarget(this, menu_selector(WellDoneLayer::onResetBtnClicked));
        
        SMMenu* menu = SMMenu::create(left, reset, NULL);
        menu->setAnchorPoint(ccp(0, 0));
        menu->setPosition(ccp(0, 0));
        itemsNode->addChild(menu);
        
        title->setAnchorPoint(ccp(0.5, 0));
        title->setPosition(ccp(itemsNode->getContentSize().width/2.0, ItemsSize.height + 30));
        itemsNode->addChild(title);
        
        itemsNode->ignoreAnchorPointForPosition(false);
        itemsNode->setPosition(ccp(this->getContentSize().width/2.0, -20+this->getContentSize().height*1.5));
        addChild(itemsNode, 3);
        
        if (isSucceed) {
            logoSprite = CCSprite::create("ui/home_logo_2.png");
            logoSprite->setPosition(ccp(this->getContentSize().width/2.0, this->getContentSize().height*.5f));
            addChild(logoSprite, 2);
            logoSprite->setScale(0);
        }
        
        return true;
    }
    return false;
}

void WellDoneLayer::onEnter(){
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority+10, true);
}

void WellDoneLayer::onExit(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCLayer::onExit();
   
}

void WellDoneLayer::setDelegate(WellDoneLayerDelegate *pDelegate) {
    theDelegate = pDelegate;
}

void WellDoneLayer::onLeftBtnClicked(){
    if (theDelegate) {
        if (boolenParm == true) {
            theDelegate->onLeftButtonClicked(kHomeType);
        }else {
            theDelegate->onLeftButtonClicked(kRestartType);
        }
    }
}

void WellDoneLayer::onResetBtnClicked(){
    if (theDelegate) {
        theDelegate->onResetButtonClicked();
    }
}

void WellDoneLayer::showINtheNode(cocos2d::CCNode *parent) {
    this->setPosition(STVisibleRect::getOriginalPoint());
    parent->addChild(this, 100);
    if (boolenParm == true) {
        itemsNode->runAction(CCSequence::create(
                                                CCMoveBy::create(.5f, ccp(0, -this->getContentSize().height)),
                                                CCMoveBy::create(0.2f, ccp(0, 50)),
                                                CCMoveBy::create(0.1f, ccp(0, -50)),
                                                
                                                NULL));
        logoSprite->runAction(CCSequence::create(
                                                 CCDelayTime::create(0.8f),
                                                 CCScaleTo::create(0.2f, 1.1f),
                                                 CCScaleTo::create(0.1f, 1.0f),
                                                 CCCallFunc::create(this, callfunc_selector(WellDoneLayer::addParticle)),
                                                 NULL));
    }else {
        itemsNode->runAction(CCMoveBy::create(0.5f, ccp(0, -this->getContentSize().height)));
    }
}


void WellDoneLayer::addParticle(){
    CCParticleSystemQuad* welldoneParticle = CCParticleSystemQuad::create("particles/welldone.plist");
    addChild(welldoneParticle, 1);
    if (boolenParm == true) {
        logoSprite->runAction(CCRepeatForever::create(CCRotateBy::create(3.0f, 360)));
    }
}