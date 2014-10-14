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
        currentZorder = 0;
        ignoreAnchorPointForPosition(false);
        currenCar = DataContainer::getInstance()->getallCars()[GameController::getInstance()->getChooseIndex()];
        mainCar = CCSprite::create(("washing_cars/garage/fine_"+currenCar.itemName+".png").c_str());
        setContentSize(mainCar->getContentSize());
        mainCar->setPosition(ccp(mainCar->getContentSize().width / 2.0, mainCar->getContentSize().height/2.0));
        addChild(mainCar, currentZorder++);
        
        addTires1();
        addTires2();
        
        setAnchorPoint(ccp(0.5f, 0.5f));
        setPosition(STVisibleRect::getPosition(currenCar.carPos.x, currenCar.carPos.y));
        return true;
    }
    return false;
}

void CarItem::addTires1() {
//    tires1 = CCSprite::create(("washing_cars/garage/wheel/"+currenCar.itemName+"_0.png").c_str());
        tires1 = CCSprite::create("washing_cars/garage/wheel/jeep_0.png");
    tires1->setPosition(mainCar->getPosition() - currenCar.wheel1Pos);
    tires1->setScale(0.8f);
    addChild(tires1, currentZorder++);
}

void CarItem::addTires2() {
//    tires2 = CCSprite::create(("washing_cars/garage/wheel/"+currenCar.itemName+"_0.png").c_str());
        tires2 = CCSprite::create("washing_cars/garage/wheel/jeep_0.png");
    tires2->setPosition(mainCar->getPosition() - currenCar.wheel2Pos);
    tires2->setScale(0.8f);
    addChild(tires2, currentZorder++);
}

void CarItem::changeTiresState1(){
    
}

void CarItem::changeTiresState2(){
    
}

void CarItem::moveByDistance(float dt, cocos2d::CCPoint distance) {
    
}





