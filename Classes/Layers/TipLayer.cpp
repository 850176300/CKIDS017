//
//  TipLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-17.
//
//

#include "TipLayer.h"
#include "STVisibleRect.h"

USING_NS_ST;
TipLayer* TipLayer::createWithNode(cocos2d::CCNode *pNode) {
    TipLayer* pRet = new TipLayer();
    if (pRet && pRet->initWithTipNode(pNode)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool TipLayer::initWithTipNode(cocos2d::CCNode *pNode) {
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 150))) {
        pNode->ignoreAnchorPointForPosition(false);
        pNode->setPosition(ccpAdd(STVisibleRect::getCenterOfScene(), ccp(0, STVisibleRect::getGlvisibleSize().height)));
        pNode->setTag(theNodeTag);
        addChild(pNode);
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
        return true;
    }
    return false;
}

void TipLayer::onEnter(){
    CCLayerColor::onEnter();
}

bool TipLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {
    return true;
}
void TipLayer::addToNode(cocos2d::CCNode *parent) {
    if (parent) {
        parent->addChild(this, 200);
        this->getChildByTag(theNodeTag)->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, -STVisibleRect::getGlvisibleSize().height)), CCDelayTime::create(2.0f),CCMoveBy::create(0.5f, ccp(0, -STVisibleRect::getGlvisibleSize().height)),CCCallFunc::create(this, callfunc_selector(TipLayer::removeFromNode)),NULL));
    }
}

void TipLayer::removeFromNode(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    this->removeFromParent();
}