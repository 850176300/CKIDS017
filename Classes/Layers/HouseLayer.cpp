//
//  HouseLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-15.
//
//

#include "HouseLayer.h"
#include "DataContainer.h"

string gameTypes[6] = {"planting", "washing_clothes", "drying", "cleaning", "sorting", "washing_cars"};
CCScene* HouseLayer::scene(bool LorR) {
    CCScene* scene = CCScene::create();
    
    HouseLayer* layer = HouseLayer::create(LorR);
    
    scene->addChild(layer);
    
    return scene;
}

HouseLayer* HouseLayer::create(bool LorR) {
    HouseLayer* pRet = new HouseLayer();
    if (pRet && pRet->init(LorR)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool HouseLayer::init(bool LorR) {
    if (GameLayerBase::initWithBgFileName(HouseLayerBGPath)) {
        this->LorR = LorR;
        //add house item and add four subitem in it
        addHouse();
        return true;
    }
    return false;
}

void HouseLayer::addHouse(){
    houseSprite = CCSprite::create("bg/bg_select_game.png");
    STVisibleRect::setPosition(houseSprite, 383.50-STVisibleRect::getGlvisibleSize().width, 400.50);
    
    CCArray* menuItemArray = CCArray::createWithCapacity(6);
    int index = GameController::getInstance()->getChooseIndex();
    for (int i = 0; i < 6; ++i) {
        MyItemSprite* menuItem = MyItemSprite::menuItems(("select_game/"+gameTypes[i]+"_"+DataContainer::getInstance()->getBabyByIndex(index)+".png").c_str());
        menuItem->setPosition(ccpAdd(FirstHousePP, ccp(HouseSeperateX*(i%3), i/3*HouseSeperateY)));
        menuItem->setTarget(this, menu_selector(HouseLayer::onTypdeItemClicked));
        menuItem->setTag(i);
        menuItemArray->addObject(menuItem);
    }
    SMMenu* typeMenu = SMMenu::createWithArray(menuItemArray);
    typeMenu->setAnchorPoint(ccp(0, 0));
    typeMenu->setPosition(ccp(0, 0));
    houseSprite->addChild(typeMenu);
//
    addChild(houseSprite);
    houseSprite->setVisible(false);
}

void HouseLayer::onEnter(){
    GameLayerBase::onEnter();
//    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void HouseLayer::onExit(){
    GameLayerBase::onExit();
}

void HouseLayer::onEnterTransitionDidFinish(){
    GameLayerBase::onEnter();
    if (LorR == true) {
        // show shop layer
        
    }
    LorR = false;
    if (houseSprite->getPositionX() < 0) {
        houseSprite->setVisible(true);
        houseSprite->runAction(CCSequence::create(CCDelayTime::create(0.1f), CCMoveBy::create(0.5f, ccp(STVisibleRect::getGlvisibleSize().width + 50, 0)), CCMoveBy::create(0.2f, ccp(-50, 0)), NULL));
    }
}

void HouseLayer::onTypdeItemClicked(cocos2d::CCObject *pObj) {
    CCNode* pNode = dynamic_cast<CCNode*>(pObj);
    switch (pNode->getTag()) {
        case 0:
            //planting layer
        {
            GameController::getInstance()->gotoPlanting();
        }
            break;
        case 1:
            //washing clothes
        {
            
        }
            break;
        case 2:
            //drying clothes
        {
            
        }
            break;
            
        default:
            break;
    }
}

