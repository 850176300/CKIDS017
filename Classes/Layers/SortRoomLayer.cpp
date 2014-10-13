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

        CCSprite* carpet = CCSprite::create("sorting/room/carpet.png");
        carpet->setPosition(m_pBg->convertToWorldSpace(ccp(433, 193.5)));
        carpet->setScale(STVisibleRect::getRealDesignScale());
        addChild(carpet);
        
        addAllSortItems();
        return true;
    }
    return false;
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
    MyItemSprite* light = MyItemSprite::menuItems("sorting/room/button.png");
    light->setPosition(m_pBg->convertToWorldSpace(ccp(547, 577)));
    light->setScale(STVisibleRect::getRealDesignScale());
    light->setTag(kLightTags);
    light->setTarget(this, menu_selector(SortRoomLayer::onSortItemsClicked));
    
    
    /*添加跳跳熊**/
    MyItemSprite* jumpPanda = MyItemSprite::menuItems("sorting/room/jump.png");
    jumpPanda->setPosition(STVisibleRect::getPosition(279, 255));
    jumpPanda->setTag(kPandaTags);
    jumpPanda->setTarget(this, menu_selector(SortRoomLayer::onSortItemsClicked));
    
    
    /*添加灯**/
    MyItemSprite* light1 = MyItemSprite::menuItems("sorting/room/light_off.png");
    light1->setPosition(m_pBg->convertToWorldSpace(ccp(492, 664)));
    light1->setScale(STVisibleRect::getRealDesignScale());
    light1->setTag(kLight1Tags);
    light1->setTarget(this, menu_selector(SortRoomLayer::onSortItemsClicked));
    
    
    SMMenu* theMenu = SMMenu::create(bed, forcer,light ,light1, jumpPanda,NULL);
    theMenu->setAnchorPoint(ccp(0, 0));
    theMenu->setPosition(ccp(0, 0));
    addChild(theMenu, 2);
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
            
        }
            break;
        case kLightTags:
        {
            
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




