//
//  ShopLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#include "ShopLayer.h"
#include "cocos-ext.h"
#include "SuperGlobal.h"
#include "DataContainer.h"
USING_NS_CC_EXT;

#define FrameDeltaX 10.0
#define FrameDeltaY 60.0
#define ItemDeltaY -5.0

bool ShopLayer::init(){
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 0))) {
        setTouchMode(kCCTouchesOneByOne);
        setTouchPriority(kCCMenuHandlerPriority - 5);
        startY = 0;
        
        boxLayer = CCLayer::create();
        addChild(boxLayer, 1);
        
        CCSprite* frame = CCSprite::create(ShopFrameBGPath);
        frame->setPosition(ccp(getContentSize().width/2.0, getContentSize().height/2.0));
        boxLayer->addChild(frame, 1);
        
        iapScrollMenu = ScrollMenu::create();
        iapScrollMenu->ignoreAnchorPointForPosition(false);
        iapScrollMenu->setTouchPriority(kCCMenuHandlerPriority - 6);
        iapScrollMenu->setViewSize(CCSizeMake(frame->getContentSize().width-FrameDeltaX*2, frame->getContentSize().height-FrameDeltaY*2-20));
        iapScrollMenu->setMenu(createiapMenu(frame->getContentSize().width*0.5 - FrameDeltaX));
        iapScrollMenu->setContentSize(CCSizeMake(frame->getContentSize().width - FrameDeltaX*2, startY));
        iapScrollMenu->setContentOffset(ccp(0, frame->getContentSize().height-FrameDeltaY*2-20-startY));
        iapScrollMenu->setPosition(frame->getPosition()+CCPoint(0, -35));
        boxLayer->addChild(iapScrollMenu, 2);
        iapScrollMenu->setDirection(kCCScrollViewDirectionVertical);
        
        restoreBtn = MyItemSprite::menuItems(RestorePng);
        restoreBtn->setAnchorPoint(ccp(0.5f, 1.0f));
        restoreBtn->setTarget(this, menu_selector(ShopLayer::onResetoreClicked));
        restoreBtn->setPosition(ccp(frame->getPositionX(), frame->getPositionY()-frame->getContentSize().height/2.0-30));
        
        closeBtn = MyItemSprite::menuItems(ClosePng);
        closeBtn->setTarget(this, menu_selector(ShopLayer::removeFromNode));
        closeBtn->setPosition(frame->getPosition() + ccp(frame->getContentSize().width/2.0, frame->getContentSize().height/2.0-60));
        
        
        CCMenu* theMenu = CCMenu::create(restoreBtn, closeBtn, NULL);
        theMenu->setAnchorPoint(ccp(0, 0));
        theMenu->setPosition(ccp(0, 0));
        boxLayer->addChild(theMenu, 2);
        
        boxLayer->setPositionY(STVisibleRect::getGlvisibleSize().height);
        return true;
    }
    return false;
}

CCMenu* ShopLayer::createiapMenu(float posX){
    vector<IapItem> iaps = DataContainer::getInstance()->getallIapItems();
    
    CCArray* menuitems = CCArray::createWithCapacity(iaps.size());
    for (vector<IapItem>::size_type i = iaps.size() - 1; (int)i >= 0; --i) {
        MyItemSprite* item = MyItemSprite::menuItems(("ui/shop/"+iaps[i].itemPng).c_str());
        item->setAnchorPoint(ccp(0.5f, 0.0f));
        item->setPosition(ccp(posX, startY));
        startY += item->getContentSize().height + ItemDeltaY;
        item->setTag(i);
        item->setTarget(this, menu_selector(ShopLayer::onBuyItem));
        menuitems->addObject(item);
    }
    CCMenu* iapMenu = CCMenu::createWithArray(menuitems);
    iapMenu->setTouchPriority(kCCMenuHandlerPriority - 5);
    return iapMenu;
}

void ShopLayer::onBuyItem(cocos2d::CCObject *pObj) {
    if (boxLayer->numberOfRunningActions() != 0) {
        return;
    }
}

void ShopLayer::onResetoreClicked(){
    if (boxLayer->numberOfRunningActions() != 0) {
        return;
    }
}

void ShopLayer::showinNode(cocos2d::CCNode *pNode) {
    pNode->addChild(this, 210);
    setTouchEnabled(true);
    runAction(CCFadeTo::create(0.2f, 150));
    boxLayer->runAction(CCSequence::create(
                                           CCDelayTime::create(0.2f),
                                           CCMoveBy::create(0.5f, ccp(0, -STVisibleRect::getGlvisibleSize().height)),
                                           CCMoveBy::create(0.2f, ccp(0, 50)),
                                           CCMoveBy::create(0.1f, ccp(0, -50)),
                                           NULL));
}

void ShopLayer::removeFromNode(){
    boxLayer->runAction(CCSequence::create(
                                           CCMoveBy::create(0.1f, ccp(0, -50)),
                                           CCMoveBy::create(0.4f, ccp(0, STVisibleRect::getGlvisibleSize().height+50))
                                           ,NULL));
    runAction(CCSequence::create(
                                 CCDelayTime::create(0.5f),
                                 CCFadeTo::create(0.2f, 0),
                                 CCCallFunc::create(this, callfunc_selector(ShopLayer::setTouchdisEnable))
                                 ,NULL));
}

void ShopLayer::setTouchdisEnable(){
    setTouchEnabled(false);
    removeFromParentAndCleanup(false);
}

bool ShopLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    CCPoint location = pTouch->getLocation();
    location = boxLayer->convertToNodeSpace(location);
    if (iapScrollMenu->boundingBox().containsPoint(location) || (restoreBtn->boundingBox().containsPoint(location) && restoreBtn->isEnabled()) || (closeBtn->boundingBox().containsPoint(location) && closeBtn->isEnabled())) {
        return false;
    }
    return true;
}

