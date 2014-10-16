//
//  WashCarLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#include "WashCarLayer.h"

#define TOOLWIDTH 148
#define TOOLHEIGHT 127
#define TOOLDELTA 5

CCScene* WashCar::scene(){
    CCScene* scene = CCScene::create();
    
    WashCar* layout = WashCar::create();
    
    scene->addChild(layout);
    
    return scene;
}

bool WashCar::init(){
    if (GameLayerBase::initWithBgFileName(WashCarBGPath)) {
        hasShowHandTip = false;
        garageDoor = CCSprite::create("washing_cars/garage/door.png");
        garageDoor->setPosition(m_pBg->convertToWorldSpace(ccp(80, 429)));
        garageDoor->setScale(STVisibleRect::getRealDesignScale());
        addChild(garageDoor, 1);
        
        MovableItem* tripItem = MovableItem::create("washing_cars/garage/door_trip.png");
        tripItem->setTag(kTripTag);
        tripItem->setTouchable(false);
        tripItem->setTouchEndHandleType(kMovableItemTouchEndStop);
        tripItem->setPosition(m_pBg->convertToWorldSpace(ccp(238.5, 732)));
        tripItem->setStartLocation(tripItem->getPosition());
        tripItem->setMovableItemDelegate(this);
        tripItem->setScale(STVisibleRect::getRealDesignScale());
        addChild(tripItem, 2);
        
        maxDeltaY = tripItem->getContentSize().height * 0.5f - (STVisibleRect::getPointOfSceneLeftUp().y - tripItem->getPositionY());
        
        myCar = CarItem::create();
        addChild(myCar, 10);
        
        myCar->setVisible(false);
        myCar->setPosition(myCar->getPosition()+ccp(-STVisibleRect::getGlvisibleSize().width, 0));
        currenState = kSpongeToolStep;
        return true;
    }
    return false;
}

void WashCar::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    if (hasShowHandTip == false) {
        hasShowHandTip = true;
        playHandTip();
    }
}

void WashCar::playHandTip(){
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0.2f, 0.8f));
    hand->setPosition(ccp(m_pBg->convertToWorldSpace(ccp(238.5, 732)).x, STVisibleRect::getPointOfSceneLeftUp().y-50));
    addChild(hand, 5);
    
    MovableItem* pItem = (MovableItem*)getChildByTag(kTripTag);

    hand->runAction(CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.2f, ccp(0, -50)),
                                       CCDelayTime::create(0.2f),
                                       CCMoveBy::create(0.1f, ccp(0, 50)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.2f, ccp(0, -50)),
                                       CCDelayTime::create(0.2f),
                                       CCScaleTo::create(0.1f, 0),
                                       CCCallFuncO::create(this, callfuncO_selector(WashCar::setTouchItemCanTouch), (MovableItem*)getChildByTag(kTripTag)),
                                       CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                       NULL));
    pItem->runAction(CCSequence::create(
                                        CCDelayTime::create(0.1f),
                                        CCMoveBy::create(0.2f, ccp(0, -50)),
                                        CCDelayTime::create(0.2f),
                                        CCMoveBy::create(0.1f, ccp(0, 50)),
                                        CCDelayTime::create(0.1f),
                                        CCMoveBy::create(0.2f, ccp(0, -50)),
                                        CCDelayTime::create(0.1f),
                                        CCMoveBy::create(0.1f, ccp(0, 50)),
                                        NULL));
}

#pragma mark 添加工具滑动视图
void WashCar::addtooltips(){
    washMenu = ScrollMenu::create();
    washMenu->setViewSize(CCSizeMake(TOOLWIDTH*3+TOOLDELTA*2, TOOLHEIGHT));
    washMenu->ignoreAnchorPointForPosition(false);
    washMenu->setAnchorPoint(ccp(0.5f, 1.0f));
    washMenu->setPosition(ccp(STVisibleRect::getCenterOfScene().x, STVisibleRect::getPointOfSceneLeftUp().y + 515));
    
    float startx = 0, starty = 0;
    string tools[7] = {"gas", "blow", "hose", "sponge", "squeegee","hose", "wax"};
    CCArray* toolMenuArrs = CCArray::createWithCapacity(7);
    for (int i = 0; i<7; ++i) {
        CCMenuItemSprite* item  = CCMenuItemSprite::create(CCSprite::create(("ui/washing_cars/"+tools[i]+"_default.png").c_str()), CCSprite::create(("ui/washing_cars/"+tools[i]+"_active.png").c_str()));
        item->setAnchorPoint(ccp(0, 0));
        item->setPosition(ccp(startx, 0));
        if (item->getContentSize().height > starty) {
            starty = item->getContentSize().height;
        }
        startx += item->getContentSize().width + TOOLDELTA;
        item->setEnabled(false);
        toolMenuArrs->addObject(item);
        if (i == 0) {
            item->selected();
        }
    }
    
    toolMenu = CCMenu::createWithArray(toolMenuArrs);
    toolMenu->setEnabled(false);
    
    washMenu->setMenu(toolMenu);
    washMenu->setContentSize(CCSizeMake(startx-TOOLDELTA, starty));
    washMenu->setTouchEnabled(false);
    addChild(washMenu, 20);
    
    washMenu->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, -530)), CCCallFunc::create(this, callfunc_selector(WashCar::addgasTool)),NULL));
}

void WashCar::moveToolTip(){
    washMenu->setContentOffsetInDuration(washMenu->getContentOffset() + ccp(-TOOLWIDTH-TOOLDELTA, 0), 0.3f);
    CCMenuItemSprite* spriteItem = dynamic_cast<CCMenuItemSprite*>(toolMenu->getChildren()->objectAtIndex((int)(currenState - kGasToolStep)));
    spriteItem->runAction(CCSequence::create(CCDelayTime::create(0.3f), CCCallFunc::create(spriteItem, callfunc_selector(CCMenuItemSprite::selected)), NULL));
}

void WashCar::setTouchItemCanTouch(MovableItem *pItem) {
    pItem->setTouchable(true);
}

#pragma mark 对state进行反应
void WashCar::performState(){
    switch (currenState) {
        case kGasToolStep:
        {
            myCar->addGas();
            addtooltips();
        }
            break;
        case kBlowToolStep:
        {
            moveToolTip();
            addblowTool();
            myCar->addTireTip();
        }
            break;
        case kHoseToolStep:
        {
            moveToolTip();
            addhoseTools();
            myCar->addhoseBubble();
        }
            break;
        case kSpongeToolStep:
        {
//            moveToolTip();
            myCar->addspongePainter();
            addSpongeTool();
        }
            break;
        case kCleanToolStep:
        {
            
        }
            break;
        case kHose2ToolStep:
        {
            
        }
            break;
        case kWaxToolStep:
        {
        }
            break;
        default:
            
            break;
    }
}

#pragma mark 添加汽油
void WashCar::addgasTool(){
    gasBox = CCSprite::create("washing_cars/garage/tool_gas.png");
    gasBox->setPosition(STVisibleRect::getOriginalPoint() + ccp(388, 50-STVisibleRect::getGlvisibleSize().height));
    addChild(gasBox, 10);
    
    gasTool = MovableItem::create("washing_cars/garage/tool_gas2.png");
    gasTool->setPosition(STVisibleRect::getOriginalPoint() + ccp(388, 50));
    gasTool->setStartLocation(gasTool->getPosition());
    gasTool->setTouchable(false);
    gasTool->setTag(kGasTags);
    gasTool->setMovableItemDelegate(this);
    gasTool->setTouchEndHandleType(kMovableItemTouchEndStop);
    addChild(gasTool, 11);
    
    gasminy = gasTool->getPositionY() - (gasTool->getContentSize().height / 2.0 - GameController::getInstance()->getBannerHeight() - 50);
    gasmaxy = gasTool->getPositionY() + gasTool->getContentSize().height / 2.0 - 50;
    
    gasTool->setPosition(gasTool->getPosition() + ccp(0, -STVisibleRect::getGlvisibleSize().height));
    gasBox->runAction(CCMoveBy::create(0.5f, ccp(0, STVisibleRect::getGlvisibleSize().height)));
    gasTool->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, STVisibleRect::getGlvisibleSize().height)), CCCallFuncO::create(this, callfuncO_selector(WashCar::setTouchItemCanTouch), gasTool),NULL));
}

void WashCar::checkoilin(){
    if (myCar->getisFull()) {
        if (gasBox->numberOfRunningActions() == 0) {
            gasBox->runAction(CCRepeatForever::create(CCSequence::create(CCMoveBy::create(0.2f, ccp(0, 20)), CCMoveBy::create(0.1f, ccp(0, -20)),CCMoveBy::create(0.2f, ccp(0, 20)), CCMoveBy::create(0.1f, ccp(0, -20)), CCDelayTime::create(0.5f), NULL)));
        }else {
            return;
        }
    }else {
        myCar->judgeByPoint(myCar->convertToNodeSpace(gasTool->getPosition() + ccp(gasTool->getContentSize().width/2.0, gasTool->getContentSize().height/2.0)));
    }
}
#pragma mark 给车胎充气
void WashCar::addblowTool(){
    blowTool = MovableItem::create("washing_cars/garage/tool_blow1.png");
    blowTool->setTouchable(false);
    blowTool->setTouchEndHandleType(kMovableItemTouchEndStop);
    blowTool->setTag(kBlowTags);
    blowTool->setMovableItemDelegate(this);
    blowTool->setPosition(ccp(STVisibleRect::getPointOfSceneRightBottom().x-300, myCar->getPositionY()-100));
    blowTool->setStartLocation(blowTool->getPosition());
    addChild(blowTool, 10);
    blowminX = STVisibleRect::getOriginalPoint().x;
    blowmaxX = STVisibleRect::getPointOfSceneRightBottom().x;
    blowTool->setPosition(blowTool->getPosition() + ccp(STVisibleRect::getGlvisibleSize().width, 0));
    blowTool->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),CCCallFunc::create(this, callfunc_selector(WashCar::firstPlayhandTip)),NULL));
}

void WashCar::firstPlayhandTip(){
    blowHandTip(true);
}

void WashCar::blowHandTip(bool startLocation){
    blowTool->stopAllActions();
    blowTool->setTexture(CCSprite::create("washing_cars/garage/tool_blow1.png")->getTexture());
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0.2f, 0.8f));

    CCPoint toPos;
    if (startLocation == true) {
        toPos = blowTool->getStartLocation();
    }else {
        toPos = blowTool->getPosition();
    }
    hand->setPosition(toPos);
    addChild(hand, 12);
    
    hand->runAction(CCSequence::create(
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.2f, ccp(-100, 0)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.3f, ccp(200, 0)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.2f, ccp(100, 0)),
                                       CCFadeOut::create(0.1f),
                                       CCCallFuncO::create(this, callfuncO_selector(WashCar::setTouchItemCanTouch), blowTool),
                                       CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                       NULL
                                       ));
}

void WashCar::finishblowstep(){
    currenState = kHoseToolStep;
    blowTool->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width-1000, 0)),CCCallFunc::create(this, callfunc_selector(WashCar::performState)), CCCallFunc::create(blowTool, callfunc_selector(MovableItem::removeFromParent)), NULL));
}

void WashCar::playBlowAnimation(){
    CCAnimation* animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("washing_cars/garage/tool_blow1.png");
    animation->addSpriteFrameWithFileName("washing_cars/garage/tool_blow2.png");
    animation->addSpriteFrameWithFileName("washing_cars/garage/tool_blow3.png");
    animation->addSpriteFrameWithFileName("washing_cars/garage/tool_blow4.png");
    animation->addSpriteFrameWithFileName("washing_cars/garage/tool_blow5.png");
    animation->setDelayPerUnit(0.1f);
    animation->setLoops(-1);
    animation->setRestoreOriginalFrame(true);
    CCAnimate* animate = CCAnimate::create(animation);
    
    blowTool->runAction(animate);
}
#pragma mark 使用水枪
void WashCar::addhoseTools(){
    hoseTool = MovableItem::create("washing_cars/garage/tool_hose.png");
    hoseTool->setPosition(ccp(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y+100));
    hoseTool->setStartLocation(hoseTool->getPosition());
    hoseTool->setTag(kHoseTags);
    hoseTool->setMovableItemDelegate(this);
    hoseTool->setTouchable(false);
    hoseTool->setTouchEndHandleType(kMovableItemTouchEndStop);
    minhosey = STVisibleRect::getOriginalPoint().y-(hoseTool->getContentSize().height-GameController::getInstance()->getBannerHeight()-20);
    maxhosey = STVisibleRect::getOriginalPoint().y + hoseTool->getContentSize().height - 20;
    hoseTool->setPosition(hoseTool->getPosition() + ccp(0, -STVisibleRect::getGlvisibleSize().height));
    addChild(hoseTool, 11);
    
    hoseTool->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, STVisibleRect::getGlvisibleSize().height)), CCCallFuncO::create(this, callfuncO_selector(WashCar::setTouchItemCanTouch), hoseTool),NULL));
    
}

#pragma mark 使用涂抹工具
void WashCar::addSpongeTool(){
    spongeTool = MovableItem::create("washing_cars/garage/sponge.png");
    spongeTool->setPosition(STVisibleRect::getCenterOfScene());
    spongeTool->setStartLocation(spongeTool->getPosition());
    spongeTool->setTouchable(false);
    spongeTool->setTouchEndHandleType(kMovableItemTouchEndStop);
    spongeTool->setMovableItemDelegate(this);
    spongeTool->setTag(kSpongeTags);
    addChild(spongeTool, 11);
    
    spongeTool->setPosition(spongeTool->getPosition() + ccp(STVisibleRect::getGlvisibleSize().width, 0));
    spongeTool->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)), CCCallFuncO::create(this, callfuncO_selector(WashCar::setTouchItemCanTouch), spongeTool),NULL));
}

void WashCar::ItemDidBackToStartLocation(MovableItem *pItem) {
    if (pItem->getTag() == kTripTag) {
        pItem->runAction(CCMoveTo::create(0.2f, pItem->getStartLocation()));
        if (pItem->getStartLocation().y - pItem->getPositionY() > 100) {
            pItem->setTouchable(false);
            garageDoor->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, STVisibleRect::getGlvisibleSize().height)), CCCallFunc::create(garageDoor, callfunc_selector(CCSprite::removeFromParent)),NULL));
            myCar->setVisible(true);
            myCar->moveByDistance(0.8f, ccp(STVisibleRect::getGlvisibleSize().width, 0));
            scheduleOnce(schedule_selector(WashCar::performState), 0.8f);
        }
    }else if (pItem->getTag() == kGasTags) {
        
        oilP->removeFromParent();
        unschedule(schedule_selector(WashCar::checkoilin));
        if (myCar->getisFull()) {
            myCar->removeGas();
            gasBox->stopAllActions();
            gasTool->setTouchable(false);
            currenState = kBlowToolStep;
            gasBox->runAction(CCSequence::create(CCMoveBy::create(0.3f, ccp(0, -STVisibleRect::getGlvisibleSize().height)), CCCallFunc::create(gasBox, callfunc_selector(CCSprite::removeFromParent)),NULL));
            gasTool->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, -STVisibleRect::getGlvisibleSize().height)), CCCallFunc::create(this, callfunc_selector(WashCar::performState)),CCCallFunc::create(gasTool, callfunc_selector(MovableItem::removeFromParent)),NULL));
        }else {
            myCar->hideGas();
        }
    }else if (pItem->getTag() == kBlowTags){
        if (myCar->checkisSelected()) {
            pItem->setTouchable(false);
            playBlowAnimation();
        }
    }else if (pItem->getTag() == kHoseTags) {
        waterParticle->removeFromParent();
        if (myCar->isHoseStepFinished() == true) {
            hoseTool->setTouchable(false);
            currenState = kSpongeToolStep;
            hoseTool->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, -STVisibleRect::getGlvisibleSize().height)), CCCallFunc::create(this, callfunc_selector(WashCar::performState)), CCCallFunc::create(hoseTool, callfunc_selector(MovableItem::removeFromParent)),NULL));
        }
    }
}

void WashCar::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    if (pItem->getTag() == kTripTag) {
        if (pItem->getPositionY()+detla.y < pItem->getStartLocation().y && pItem->getPositionY() + detla.y > pItem->getStartLocation().y - maxDeltaY) {
            pItem->setPositionY(pItem->getPositionY() + detla.y);
        }
    }else if (pItem->getTag() == kGasTags) {
        if (pItem->getPositionY() + detla.y > gasminy && pItem->getPositionY() + detla.y < gasmaxy) {
            pItem->setPositionY(pItem->getPositionY() + detla.y);
            oilP->setPositionY(pItem->getPositionY()+pItem->getContentSize().height/2.0-6);
        }
    }else if (pItem->getTag() == kBlowTags) {
        if (pItem->getPositionX() + detla.x > blowminX && pItem->getPositionX() + detla.x < blowmaxX) {
            pItem->setPositionX(pItem->getPositionX() + detla.x);
            myCar->checkTireToolin(myCar->convertToNodeSpace(pItem->getPosition()+ccp(-pItem->getContentSize().width/2.0, 0)));
        }
    }else if (pItem->getTag() == kHoseTags){
        CCRect hoseRect = CCRectMake(STVisibleRect::getOriginalPoint().x, minhosey, STVisibleRect::getGlvisibleSize().width+200, maxhosey-minhosey);
        CCRect itemRect = hoseTool->boundingBox();
        itemRect.origin = itemRect.origin + detla;
        if (STVisibleRect::JudgeContain(hoseRect, itemRect)) {
            hoseTool->setPosition(hoseTool->getPosition() + detla);
            waterParticle->setPosition(pItem->convertToWorldSpace(ccp(0, pItem->getContentSize().height - 6)));
            if (myCar->boundingBox().containsPoint(waterParticle->getPosition()+ccp(-100, 50)) && myCar->isHoseStepFinished() == false) {
                myCar->changeBubbleState();
                CCParticleSystemQuad* particle = CCParticleSystemQuad::create("particles/dirtyexplor.plist");
                particle->setPosition(waterParticle->getPosition()+ccp(-100, 50));
                addChild(particle, 11);
            }

        }
    }else if (pItem->getTag() == kSpongeTags) {
        CCRect itemrect = pItem->boundingBox();
        itemrect.origin = itemrect.origin + detla;
        if (STVisibleRect::JudgeContain(STVisibleRect::getMovableRect(), itemrect)) {
            pItem->setPosition(pItem->getPosition() + detla);
            myCar->spongePanit(myCar->convertToNodeSpace(pItem->getPosition()), myCar->convertToNodeSpace(pItem->getPosition() - detla));
        }
        
    }
}

void WashCar::itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch) {
    if (pItem->getTag() == kGasTags) {
        myCar->showGas();
        oilP = CCParticleSystemQuad::create("particles/oilanimation.plist");
        oilP->setPosition(pItem->getPosition()+ccp(pItem->getContentSize().width/2.0, pItem->getContentSize().height/2.0-6));
        oilP->setTag(kgasPariticlesTags);
        addChild(oilP, 12);
        schedule(schedule_selector(WashCar::checkoilin));
    }else if (pItem->getTag() == kHoseTags) {
        waterParticle = CCParticleSystemQuad::create("particles/wateranimation.plist");
        waterParticle->setPosition(pItem->convertToWorldSpace(ccp(0, pItem->getContentSize().height - 6)));
        addChild(waterParticle, 12);
    }
}
