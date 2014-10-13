//
//  SortRoomLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-12.
//
//

#include "SortRoomLayer.h"

CCScene* SortRoomLayer::scene(){
    CCScene* scene = CCScene::create();
    
    SortRoomLayer* layer = SortRoomLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}


bool SortRoomLayer::init(){
    if (GameLayerBase::initWithBgFileName(SortRoomLayerPath)) {
        showShader = false;
        theOrder = kRandom;
        CCSprite* carpet = CCSprite::create("sorting/room/carpet.png");
        carpet->setPosition(m_pBg->convertToWorldSpace(ccp(433, 193.5)));
        carpet->setScale(STVisibleRect::getRealDesignScale());
        addChild(carpet);
        
        shaderSprite = CCSprite::create("sorting/room/light_open.png");
        shaderSprite->setScale(STVisibleRect::getRealDesignScale());
        shaderSprite->setPosition(STVisibleRect::getCenterOfScene());
        addChild(shaderSprite, 50);
        shaderSprite->setOpacity(0);
        addAllSortItems();
        return true;
    }
    return false;
}

void SortRoomLayer::onEnter(){
    GameLayerBase::onEnter();
    if (theOrder == kSort) {
        if (getChildByTag(ktheMenuTags)->getChildByTag(kForcerTags)) {
            MyItemSprite* item = (MyItemSprite*)(getChildByTag(ktheMenuTags)->getChildByTag(kForcerTags));
            item->setNormalImage(CCSprite::create("sorting/room/cabinet_2.png"));
            item->setEnabled(false);
            theOrder = kSorted;
        }
    }
}


void SortRoomLayer::addAllSortItems(){
    /*添加床的点击按钮**/
    MyItemSprite* bed = MyItemSprite::menuItems("sorting/room/bed_1.png", false);
    bed->setAnchorPoint(ccp(1.0, 0.5f));
    bed->setPosition(ccp(STVisibleRect::getPointOfSceneRightBottom().x+250, STVisibleRect::getPosition(871, 304).y));
    bed->setTag(kBedTags);
    bed->setTarget(this, menu_selector(SortRoomLayer::onSortItemsClicked));
    
    /*添加柜子**/
    MyItemSprite* forcer = MyItemSprite::menuItems("sorting/room/cabinet_1.png", false);
    forcer->setAnchorPoint(ccp(0, 0.5f));
    forcer->setPosition(ccp(STVisibleRect::getOriginalPoint().x, STVisibleRect::getPosition(206, 626).y));
    forcer->setTag(kForcerTags);
    forcer->setTarget(this, menu_selector(SortRoomLayer::onSortItemsClicked));
    
    //添加书柜的下面部分
    CCSprite* forcer1 = CCSprite::create("sorting/room/cabinet_0.png");
    forcer1->setAnchorPoint(ccp(0, 1.0f));
    forcer1->setPosition(ccp(forcer->getPosition().x-8, forcer->getPosition().y-forcer->getContentSize().height/2.0+20));
    addChild(forcer1, 1);
    
    /*添加灯光按钮**/
    MyItemSprite* light = MyItemSprite::menuItems("sorting/room/button.png", false);
    light->setPosition(m_pBg->convertToWorldSpace(ccp(547, 577)));
    light->setScale(STVisibleRect::getRealDesignScale());
    light->setTag(kLightTags);
    light->setTarget(this, menu_selector(SortRoomLayer::onSortItemsClicked));
    
    
    /*添加跳跳熊**/
    MyItemSprite* jumpPanda = MyItemSprite::menuItems("sorting/room/jump.png", false);
    jumpPanda->setPosition(STVisibleRect::getPosition(279, 255));
    jumpPanda->setTag(kPandaTags);
    jumpPanda->setTarget(this, menu_selector(SortRoomLayer::onSortItemsClicked));
    
    
    /*添加灯**/
    MyItemSprite* light1 = MyItemSprite::menuItems("sorting/room/light_off.png");
    light1->setPosition(m_pBg->convertToWorldSpace(ccp(492, 664)));
    light1->setScale(STVisibleRect::getRealDesignScale());
    light1->setTag(kLight1Tags);
    light1->setTarget(this, menu_selector(SortRoomLayer::onLightClicked));
    
    
    SMMenu* theMenu = SMMenu::create(bed, forcer,light , jumpPanda,NULL);
    theMenu->setTag(ktheMenuTags);
    theMenu->setAnchorPoint(ccp(0, 0));
    theMenu->setPosition(ccp(0, 0));
    addChild(theMenu, 2);
    
    SMMenu* theMenu2 = SMMenu::create(light1, NULL);
    theMenu2->setAnchorPoint(ccp(0, 0));
    theMenu2->setPosition(ccp(0, 0));
    addChild(theMenu2, 2);
}


void SortRoomLayer::onSortItemsClicked(cocos2d::CCObject *pObj) {
    MyItemSprite* pNode = dynamic_cast<MyItemSprite*>(pObj);
    switch (pNode->getTag()) {
        case kBedTags:
        {
            pNode->setEnabled(false);
            pNode->setNormalImage(CCSprite::create("sorting/room/bed_2.png"));
        }
            break;
        case kForcerTags:
        {
            GameController::getInstance()->gotoSortToys(this);
        }
            break;
        case kLightTags:
        {
            if (shaderSprite->numberOfRunningActions() != 0) {
                shaderSprite->stopAllActions();
            }
            showShader = !showShader;
            if (showShader) {
                if (getChildByTag(ktheMenuTags)) {
                    SMMenu* menu = (SMMenu*)getChildByTag(ktheMenuTags);
                    menu->setEnabled(false);
                }
                shaderSprite->runAction(CCFadeIn::create(0.3f));
            }else {
                if (getChildByTag(ktheMenuTags)) {
                    SMMenu* menu = (SMMenu*)getChildByTag(ktheMenuTags);
                    menu->setEnabled(true);
                }
                shaderSprite->runAction(CCFadeOut::create(0.2f));
            }
        }
            break;
        case kPandaTags:
        {
            GameController::getInstance()->gotoJumpLayer();
        }
            break;
        default:
            break;
    }
}

void SortRoomLayer::onLightClicked(){
    if (shaderSprite->numberOfRunningActions() != 0) {
        shaderSprite->stopAllActions();
    }
    showShader = !showShader;
    if (showShader) {
        if (getChildByTag(ktheMenuTags)) {
            SMMenu* menu = (SMMenu*)getChildByTag(ktheMenuTags);
            menu->setEnabled(false);
        }
        shaderSprite->runAction(CCFadeIn::create(0.3f));
    }else {
        if (getChildByTag(ktheMenuTags)) {
            SMMenu* menu = (SMMenu*)getChildByTag(ktheMenuTags);
            menu->setEnabled(true);
        }
        shaderSprite->runAction(CCFadeOut::create(0.2f));
    }
}


