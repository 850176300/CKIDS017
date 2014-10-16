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
#include "SuperGlobal.h"
#include "WashCarLayer.h"

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
    if (CCLayerColor::init()) {
        currentZorder = 0;
        ignoreAnchorPointForPosition(false);
        currenCar = DataContainer::getInstance()->getallCars()[GameController::getInstance()->getSelectCarIndex()];
        mainCar = CCSprite::create(("washing_cars/garage/fine_"+currenCar.itemName+".png").c_str());
        setContentSize(mainCar->getContentSize());
        mainCar->setPosition(ccp(mainCar->getContentSize().width / 2.0, mainCar->getContentSize().height/2.0));
        addChild(mainCar, currentZorder++);
        
        addTires1();
        addTires2();
        addDirtyLayer();
        mainCar->setPosition(mainCar->getPosition() + ccp(0, -10));
        dirtyLayer->setPosition(dirtyLayer->getPosition() + ccp(0, -10));
        setAnchorPoint(ccp(0.5f, 0.5f));
        setPosition(STVisibleRect::getPosition(currenCar.carPos.x, currenCar.carPos.y));
        return true;
    }
    return false;
}

void CarItem::addDirtyLayer(){
    _scribble = new Scribble(CCSprite::create("burshes/solid_brush.png"));
    _scribble->setBrushShader();
    _scribble->setTargetSolid(true);
    _scribble->setTargetAlphaTestValue(0.0f);
    _scribble->setBrushType(eScribbleBrushTypeEaser);
    
    dirtyLayer = DaubSprite::create(_scribble, CCSprite::create(("washing_cars/garage/dirty_"+currenCar.itemName+".png").c_str()));
    dirtyLayer->setPosition(mainCar->getPosition());
    dirtyLayer->show();
    addChild(dirtyLayer, currentZorder++);
}


void CarItem::addTires1() {
    tires1 = CCSprite::create(("washing_cars/garage/wheel/"+currenCar.itemName+"_0.png").c_str());
//        tires1 = CCSprite::create("washing_cars/garage/wheel/jeep_0.png");
    tires1->setPosition(currenCar.wheel1Pos);
    tires1->setScale(0.8f);
    tires1->setTag(kTire1TAG);
    addChild(tires1, currentZorder++);
}

void CarItem::addTires2() {
    tires2 = CCSprite::create(("washing_cars/garage/wheel/"+currenCar.itemName+"_0.png").c_str());
//        tires2 = CCSprite::create("washing_cars/garage/wheel/jeep_0.png");
    tires2->setPosition(currenCar.wheel2Pos);
    tires2->setScale(0.8f);
    tires2->setTag(kTire2TAG);
    addChild(tires2, currentZorder++);
}

void CarItem::changeTiresState1(){
    
}

void CarItem::changeTiresState2(){
    
}

void CarItem::moveByDistance(float dt, cocos2d::CCPoint distance) {
    CCRotateBy* rotate = CCRotateBy::create(dt/2.0, 360);
    CCRotateBy* rotate1 = CCRotateBy::create(dt/2.0, 360);
    runAction(CCMoveBy::create(dt, distance));
    tires1->runAction(CCRepeat::create(rotate, 2));
    tires2->runAction(CCRepeat::create(rotate1, 2));
}

#pragma mark 洗车和修车步骤代码
#pragma mark 步骤一:加汽油
void CarItem::addGas(){
    gasCount = 0;
    gasIndex = 0;
    gasisFull = false;
    gasSprite = CCSprite::create("washing_cars/garage/oiling0.png");
    gasSprite->setAnchorPoint(ccp(0, 0));
    gasSprite->setPosition(tires1->getPosition()+ccp(50, 50));
    gasSprite->setScale(0);
    addChild(gasSprite, currentZorder++);
}

void CarItem::showGas(){
    gasSprite->runAction(CCScaleTo::create(0.2f, 1.0f));
}
void CarItem::hideGas(){
    gasSprite->runAction(CCScaleTo::create(0.1f, 0));
}
void CarItem::removeGas(){
    gasSprite->runAction(CCSequence::create(CCScaleTo::create(0.1f, 0), CCCallFunc::create(gasSprite, callfunc_selector(CCSprite::removeFromParent)), NULL));
}
bool CarItem::getisFull(){
    return gasisFull;
}
void CarItem::judgeByPoint(cocos2d::CCPoint pos) {
    if (gasSprite->boundingBox().containsPoint(pos)) {
        gasCount ++;
        if (gasCount>100) {
            gasIndex ++;
            gasCount = 0;
            char filename[128] ;
            sprintf(filename, "washing_cars/garage/oiling%d.png", gasIndex);
            gasSprite->setTexture(CCSprite::create(filename)->getTexture());
            if (gasIndex >= 4) {
                gasisFull = true;
            }
        }
    }
}

#pragma mark 步骤二：给车胎充气
void CarItem::addTireTip(){
    tireIndex = 0;
    tire1Finished=false;
    tire2Finished=false;
    tireTip = CCSprite::create("washing_cars/garage/dialog.png");
    tireOnTip = CCSprite::create(("washing_cars/garage/wheel/"+currenCar.itemName+"_0.png").c_str());
    tireOnTip->setPosition(ccp(162, 153));
    tireTip->addChild(tireOnTip);
    tireTip->setScale(0);
    tireTip->setAnchorPoint(ccp(0, 0));
    addChild(tireTip, currentZorder++);
}

void CarItem::checkTireToolin(cocos2d::CCPoint pos) {

    
    if (tires1->boundingBox().containsPoint(pos) && tireTip->getScale() <= 0 && tireTip->numberOfRunningActions() == 0) {
        if (tire1Finished == false) {
            currentSelectTire = tires1;
        }else {
            currentSelectTire = NULL;
        }
        tireOnTip->setTexture(tires1->getTexture());
        tireTip->setPosition(tires1->getPosition()+ccp(10, 10));
        tireTip->runAction(CCScaleTo::create(0.2f, 1.0f));

    }
    if (tires2->boundingBox().containsPoint(pos) && tireTip->getScale() <= 0&& tireTip->numberOfRunningActions() == 0) {
        if (tire2Finished == false) {
            currentSelectTire = tires2;
        }else {
            currentSelectTire = NULL;
        }
        tireOnTip->setTexture(tires2->getTexture());
        tireTip->setPosition(tires2->getPosition()+ccp(10, 10));
        tireTip->runAction(CCScaleTo::create(0.2f, 1.0f));

    }
    if (!tires2->boundingBox().containsPoint(pos) && !tires1->boundingBox().containsPoint(pos)) {
        currentSelectTire = NULL;
        if (tireTip->getScale() > 0) {
            tireTip->runAction(CCScaleTo::create(0.1f, 0));
        }
    }
}

bool CarItem::checkisSelected(){
    if (currentSelectTire != NULL) {
        schedule(schedule_selector(CarItem::tireUpdate));
        return true;
    }
    return false;
}

void CarItem::tireUpdate(){
    tireCount++;
    if (tireCount > 200) {
        tireCount=0;
        tireIndex = tireIndex + 1;
        mainCar->setPositionY(mainCar->getPositionY()+1.25);
        char file[128];
        sprintf(file, "washing_cars/garage/wheel/%s_%d.png", currenCar.itemName.c_str(), tireIndex);
        currentSelectTire->setTexture(CCSprite::create(file)->getTexture());
        tireOnTip->setTexture(CCSprite::create(file)->getTexture());
        if (tireIndex >= 4) {
            tireIndex = 0;
            if (currentSelectTire->getTag() == kTire1TAG) {
                tire1Finished = true;
            }else if (currentSelectTire->getTag() == kTire2TAG) {
                tire2Finished = true;
            }
            unschedule(schedule_selector(CarItem::tireUpdate));
            if (getParent()) {
                WashCar* parent = (WashCar*)getParent();
                if (tire1Finished == true && tire2Finished == true) {
                    tireTip->runAction(CCSequence::create(CCScaleTo::create(0.2f, 0), CCCallFunc::create(tireTip, callfunc_selector(CCSprite::removeFromParent)), NULL));
                    parent->finishblowstep();
                }else {
                    parent->blowHandTip();
                }
            }
        }
    }
}

#pragma mark 水枪冲洗
void CarItem::addhoseBubble(){
    hoseStepFinished = false;
    waterBubble = CCSprite::create("washing_cars/garage/foam_water.png");
    waterBubble->setPosition(mainCar->getPosition());
    waterBubble->setOpacity(0);
    addChild(waterBubble, currentZorder++);
}

void CarItem::changeBubbleState(){
    int opacity = waterBubble->getOpacity();
    opacity += 1;
    if (opacity > 255) {
        hoseStepFinished = true;
        opacity = 255;
    }
    waterBubble->setOpacity(opacity);
}

bool CarItem::isHoseStepFinished(){
    return hoseStepFinished;
}

#pragma mark 涂抹过程
void CarItem::addspongePainter(){
    _paintScribble = new Scribble(CCSprite::create("burshes/solid_brush.png"));
    _paintScribble->setBrushShader();
    _paintScribble->setTargetSolid(true);
    _paintScribble->setTargetAlphaTestValue(0.0f);
    _paintScribble->setBrushType(eScribbleBrushTypeBrush);
    
    sponePaniter = DaubSprite::create(CCSizeMake(716, 288) , _paintScribble, CCSprite::create("washing_cars/garage/foam_3.png"));
    sponePaniter->setPosition(mainCar->getPosition());
    sponePaniter->show();
    addChild(sponePaniter, currentZorder++);
}

void CarItem::spongePanit(cocos2d::CCPoint prelocation, cocos2d::CCPoint location) {
    sponePaniter->paint(location, prelocation);
}

