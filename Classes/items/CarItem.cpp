//
//  CarItem.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#include "CarItem.h"
#include "GameController.h"
#include "DataContainer.h"

CarItem* CarItem::create(){
    CarItem* pRet = new CarItem();

    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool CarItem::init(){
    if (CCNode::init()) {
        ignoreAnchorPointForPosition(false);
        currenCar = DataContainer::getInstance()->getallCars()[GameController::getInstance()->getChooseIndex()];
        CCSprite* car = CCSprite::create(("ui/shop/"+currenCar.itemName).c_str());
        setContentSize(car->getContentSize());
        
        addChild(car, 0);
        car->setAnchorPoint(ccp(0, 0));
        car->setPosition(ccp(0, 0));
        
        
        return true;
    }
    return false;
}

void CarItem::addTires1() {
    
}

void CarItem::addTires2() {
    
}

void CarItem::changeTiresState1(){
    
}

void CarItem::changeTiresState2(){
    
}

void CarItem::moveByDistance(float dt, cocos2d::CCPoint distance) {
    
}





