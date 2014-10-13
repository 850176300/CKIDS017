//
//  WashClothes.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-24.
//
//

#include "WashClothes.h"
#include "Baby.h"
#include "TipLayer.h"

CCScene* WashClothes::scene(){
    CCScene* scene = CCScene::create();
    
    WashClothes* layer = WashClothes::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool WashClothes::init(){
    if (GameLayerBase::initWithBgFileName(WashBGPath)) {
        loadAllPoint();
        addplant();
        addTwoBasket();
        currentStep = kSortClothes;
        perFormByStep();
        movedCount=0;
        colorClotesWashDone = false;
        whiteClothesWashDone = false;
        return true;
    }
    return false;
}

void WashClothes::onEnter(){
//    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    GameLayerBase::onEnter();
}

void WashClothes::onEnterTransitionDidFinish(){
    GameLayerBase::onEnterTransitionDidFinish();
}

void WashClothes::onExit(){
    GameLayerBase::onExit();
}

void WashClothes::perFormByStep(){
    switch (currentStep) {
        case kSortClothes:
            addBaby();
            break;
        case kWashClothe1:
            powderCount = 0;
            handTip(CCDelayTime::create(0), powderContainer, CCCallFuncO::create(this, callfuncO_selector(WashClothes::setMenuItemCanTouch), powderContainer));
            break;
        case kWashClothe2:
            powderCount = 0;
            handTip(CCDelayTime::create(0), powderContainer, CCCallFuncO::create(this, callfuncO_selector(WashClothes::setMenuItemCanTouch), powderContainer));
            break;
        case kWashWellDone:
            playWellDone();
            break;
        default:
            break;
    }
}

void WashClothes::loadAllPoint(){
    clothePP1.push_back(ccp(213.5, 307.5));
    clothePP1.push_back(ccp(427.0, 158.0));
    clothePP1.push_back(ccp(399.5, 292.5));
    clothePP1.push_back(ccp(277.5, 191.5));
    clothePP1.push_back(ccp(471.5, 260.0));
    clothePP1.push_back(ccp(154.0, 267.0));
    
    clothePP2.push_back(ccp(476.5, 255));
    clothePP2.push_back(ccp(457.0, 141));
    clothePP2.push_back(ccp(144, 192.5));
    clothePP2.push_back(ccp(244, 139));
    clothePP2.push_back(ccp(368.5, 356.5));
    clothePP2.push_back(ccp(311, 233.5));
}

void WashClothes::addplant(){
    CCSprite* plant = CCSprite::create("washing_clothes/bg_washing_clothes_plank.png");
    STVisibleRect::setPosition(plant, 795.5, 561.5);
    addChild(plant, 1);
    
    laundry1 = MovableItem::create("washing_clothes/laundry_detergent_1_1.png");
    laundry2 = MovableItem::create("washing_clothes/laundry_detergent_2_1.png");
    
    laundry1->setTag(kLaundryTag1);
    laundry2->setTag(kLaundryTag2);
    laundry1->setTouchEndHandleType(kMovableItemTouchEndBackStart);
    laundry2->setTouchEndHandleType(kMovableItemTouchEndBackStart);
    laundry1->setMovableItemDelegate(this);
    laundry2->setMovableItemDelegate(this);
    STVisibleRect::setPosition(laundry1, 720.5, 651.0);
    STVisibleRect::setPosition(laundry2, 880.5, 651.0);
    laundry1->setStartLocation(laundry1->getPosition());
    laundry2->setStartLocation(laundry2->getPosition());
    addChild(laundry1,2);
    addChild(laundry2, 2);
    laundry1->startZorder = 2;
    laundry2->startZorder = 2;
}

void WashClothes::addTwoBasket(){
    //添加彩色篮子21,56
    {
        CCSprite* basket1 = CCSprite::create("washing_clothes/box_colored_clothes_2.png");
        CCSprite* basket2 = CCSprite::create("washing_clothes/box_colored_clothes_1.png");
        basket1->setAnchorPoint(ccp(1.0f, 0.5f));
        basket2->setAnchorPoint(ccp(1.0f, 0.5f));
        basket1->setPosition(ccp(STVisibleRect::getPointOfSceneRightUp().x-60, STVisibleRect::getPosition(811.5, 306.5).y));
        basket2->setPosition(ccp(STVisibleRect::getPointOfSceneRightUp().x-60, STVisibleRect::getPosition(811.5, 306.5).y));
        addChild(basket1, 6);
        addChild(basket2, 8);
        CCPoint origin = basket1->convertToWorldSpace(ccp(21, 38));
        colorRect = CCRectMake(origin.x, origin.y, NodeSize.width, NodeSize.height);
        colorNode = CCLayer::create();
        colorNode->setContentSize(NodeSize);
        colorNode->setPosition(origin);
        addChild(colorNode,7);
    }
    {
        CCSprite* basket1 = CCSprite::create("washing_clothes/box_white_clothes_2.png");
        CCSprite* basket2 = CCSprite::create("washing_clothes/box_white_clothes_1.png");
        basket1->setAnchorPoint(ccp(1.0f, 0.5f));
        basket2->setAnchorPoint(ccp(1.0f, 0.5f));
        basket1->setPosition(ccp(STVisibleRect::getPointOfSceneRightUp().x-60, STVisibleRect::getPosition(811.5, 149.5).y));
        basket2->setPosition(ccp(STVisibleRect::getPointOfSceneRightUp().x-60, STVisibleRect::getPosition(811.5, 155.5).y));
        addChild(basket1, 9);
        addChild(basket2, 11);
        CCPoint origin = basket2->convertToWorldSpace(ccp(21, 38));
        whiteRect = CCRectMake(origin.x, origin.y, NodeSize.width, NodeSize.height);
        whiteNode = CCLayer::create();
        whiteNode->setContentSize(NodeSize);
        whiteNode->setPosition(origin);
        addChild(whiteNode, 10);
    }
}

void WashClothes::addBaby(){
    Baby* baby = Baby::createWithParams(GameController::getInstance()->getChooseIndex(), "planting/model/");
    baby->setPosition(ccp(STVisibleRect::getOriginalPoint().x+370-STVisibleRect::getGlvisibleSize().width, STVisibleRect::getPosition(374.0, 392.0).y));
    baby->setOpacity(0);
    addChild(baby, 20);
    baby->runAction(CCSequence::create(CCDelayTime::create(0.5f),
                                       CCFadeIn::create(0),
                                       CCMoveBy::create(0.6f, ccp(STVisibleRect::getGlvisibleSize().width, 0)),
                                       CCCallFunc::create(baby, callfunc_selector(Baby::runAnimation)),
                                       CCDelayTime::create(0.5f),
                                       CCCallFunc::create(this, callfunc_selector(WashClothes::showTip)),
                                       CCDelayTime::create(3.0f),
                                       CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),
                                       CCCallFunc::create(this, callfunc_selector(WashClothes::addAllClothes)),
                                       CCCallFunc::create(baby, callfunc_selector(Baby::removeFromParent)),
                                       NULL));
}

void WashClothes::showTip(){
    CCSprite* tip = CCSprite::create("ui/prompt/washing_clothes.png");
    TipLayer* layer = TipLayer::createWithNode(tip);
    layer->addToNode(this);
}

void WashClothes::addAllClothes(){
    vector<int> allZorder;
    for (int m = 0; m < ClothesCount; ++m) {
        allZorder.push_back(m+1);
    }
    vector<string> colourClothes;
    colourClothes.push_back("washing_clothes/dirty_clothes/colours_1.png");
    colourClothes.push_back("washing_clothes/dirty_clothes/colours_2.png");
    colourClothes.push_back("washing_clothes/dirty_clothes/colours_3.png");
    colourClothes.push_back("washing_clothes/dirty_clothes/colours_4.png");
    colourClothes.push_back("washing_clothes/dirty_clothes/colours_5.png");
    colourClothes.push_back("washing_clothes/dirty_clothes/colours_6.png");
    srand(unsigned(time(0)));
    for (vector<CCPoint>::size_type i = 0; i < clothePP1.size(); ++i) {
        int r = rand() % colourClothes.size();

        MovableItem* clothe = MovableItem::create(colourClothes[r].c_str());
        clothe->setTag(kcolourClothesTag+i);
        clothe->setTouchable(true);
        clothe->setMovableItemDelegate(this);
        clothe->setTouchEndHandleType(kMovableItemTouchEndStop);
        STVisibleRect::setPosition(clothe, clothePP1[i].x, clothePP1[i].y);
        clothe->setStartLocation(clothe->getPosition());
        clothe->startZorder = r % allZorder.size();
        addChild(clothe, clothe->startZorder);
        allZorder.erase(allZorder.begin()+clothe->startZorder-1);
        colourClothes.erase(colourClothes.begin()+r);
    }
    colourClothes.clear();
    
    //white clothes
    vector<string> whiteClothes;
    whiteClothes.push_back("washing_clothes/dirty_clothes/white_1.png");
    whiteClothes.push_back("washing_clothes/dirty_clothes/white_2.png");
    whiteClothes.push_back("washing_clothes/dirty_clothes/white_3.png");
    whiteClothes.push_back("washing_clothes/dirty_clothes/white_4.png");
    whiteClothes.push_back("washing_clothes/dirty_clothes/white_5.png");
    whiteClothes.push_back("washing_clothes/dirty_clothes/white_6.png");
    
    for (vector<CCPoint>::size_type i = 0; i < clothePP2.size(); ++i) {
        int r = rand() % whiteClothes.size();
        
        MovableItem* clothe = MovableItem::create(whiteClothes[r].c_str());
        clothe->setTag(kwhiteClothesTag+i);
        clothe->setTouchable(true);
        clothe->setMovableItemDelegate(this);
        clothe->setTouchEndHandleType(kMovableItemTouchEndStop);
        STVisibleRect::setPosition(clothe, clothePP2[i].x, clothePP2[i].y);
        clothe->setStartLocation(clothe->getPosition());
        clothe->startZorder = r % allZorder.size();
        addChild(clothe, clothe->startZorder);
        allZorder.erase(allZorder.begin()+clothe->startZorder-1);
        whiteClothes.erase(whiteClothes.begin()+r);
    }
    whiteClothes.clear();
    allZorder.clear();
}

void WashClothes::setItemcanMove(MovableItem *pItem) {
    pItem->setTouchable(true);
}

void WashClothes::setMenuItemCanTouch(cocos2d::CCMenuItem *pItem) {
    pItem->setEnabled(true);
}

void WashClothes::backtoStartZorder(MovableItem *pItem) {
    pItem->setZOrder(pItem->startZorder);
}


void WashClothes::handTip(CCDelayTime* delay,cocos2d::CCNode *pNode, CCAction* pAction) {
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0.2, 0.8));
    hand->setPosition(pNode->getParent()->convertToWorldSpace(pNode->getPosition()) + ccp(50, 100));
    addChild(hand, 15);
    hand->setOpacity(0);
    
    hand->runAction(CCSequence::create(
                                       delay,
                                       CCFadeIn::create(0.1f),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.3f,ccp(-50, -100)),
                                       CCDelayTime::create(0.2f) ,
                                       CCMoveBy::create(0.3f, ccp(50, 100)),
                                       CCDelayTime::create(.01f),
                                       CCMoveBy::create(0.3f, ccp(-50, -100)),
                                       CCDelayTime::create(0.2f),
                                       CCMoveBy::create(0.3f, ccp(50, 100)),
                                       CCFadeOut::create(0.3f),pAction,
                                       CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                       NULL));
}

#pragma 衣服整理完毕过后的动作（洗衣机出现，然后提示玩家选择要洗得衣服）
void WashClothes::sortedSucceed(){
    //将篮子里面的衣服生成一个movableitem
    MovableItem* coloredClothes=NULL;
    MovableItem* whiteClothes = NULL;
    {
        CCPoint pp = colorNode->getPosition();
        CCPoint pp1 = whiteNode->getPosition();
        CCRenderTexture* render = CCRenderTexture::create(NodeSize.width, NodeSize.height, kTexture2DPixelFormat_RGBA8888);
        render->begin();
        colorNode->setPosition(ccp(0, 0));
        colorNode->visit();
        colorNode->setPosition(pp);
        render->end();
        
        CCTexture2D* texture = new CCTexture2D();
        texture->initWithImage(render->newCCImage());
        coloredClothes = MovableItem::createWithTexture(texture);
//        coloredClothes->setTouchable(true);
        coloredClothes->setTouchEndHandleType(kMovableItemTouchEndStop);
        coloredClothes->setMovableItemDelegate(this);
        coloredClothes->setPosition(colorNode->getPosition() + ccp(NodeSize.width/2.0, NodeSize.height/2.0));
        coloredClothes->setStartLocation(colorNode->getPosition() + ccp(NodeSize.width/2.0, NodeSize.height/2.0));
        coloredClothes->setTag(kSortedColorClothes);
        addChild(coloredClothes, 7);
        coloredClothes->startZorder = 7;
        colorNode->removeFromParent();
        texture->release();
        
        render->clear(0, 0, 0, 0);
        render->begin();
        whiteNode->setPosition(ccp(0, 0));
        whiteNode->visit();
        whiteNode->setPosition(pp1);
        render->end();
        
        CCTexture2D* texture1 = new CCTexture2D();
        texture1->initWithImage(render->newCCImage());
        whiteClothes = MovableItem::createWithTexture(texture1);
//        whiteClothes->setTouchable(true);
        whiteClothes->setTouchEndHandleType(kMovableItemTouchEndStop);
        whiteClothes->setMovableItemDelegate(this);
        whiteClothes->setPosition(whiteNode->getPosition() + ccp(NodeSize.width/2.0, NodeSize.height/2.0));
        whiteClothes->setStartLocation(whiteNode->getPosition() + ccp(NodeSize.width/2.0, NodeSize.height/2.0));
        whiteClothes->setTag(kSortedWhiteClohtes);
        addChild(whiteClothes, 10);
        whiteClothes->startZorder = 10;
        whiteNode->removeFromParent();
        texture1->release();
    }
    {//洗衣机进入
        washer = CCSprite::create("washing_clothes/washer.png");
        washer->setAnchorPoint(ccp(0, 0.5f));
        washer->setPosition(ccp(STVisibleRect::getOriginalPoint().x-10-STVisibleRect::getGlvisibleSize().width, STVisibleRect::getPosition(280, 354).y));
        addChild(washer, 5);
        
        washerDoor = CCSprite::create("washing_clothes/door_close0.png");
        washerDoor->setPosition(washer->convertToWorldSpace(ccp(262, washer->getContentSize().height-341)));
        addChild(washerDoor, 11);
        
        CCSprite* washerinner = CCSprite::create("washing_clothes/door_inside.png");
        washerinner->setPosition(ccp(262, washer->getContentSize().height-341));
        washer->addChild(washerinner);
        
        powderContainer = MyItemSprite::menuItems("washing_clothes/drawer_close.png", false);
        powderContainer->setPosition(ccp(171, washer->getContentSize().height - 203));
        powderContainer->setEnabled(false);
        powderContainer->setTarget(this, menu_selector(WashClothes::powderClicked));
        
        powerButton = MyItemSprite::menuItems("washing_clothes/washer_btn_off.png");
        powerButton->setEnabled(false);
        powerButton->setPosition(ccp(496, washer->getContentSize().height-63));
        powerButton->setTarget(this, menu_selector(WashClothes::powerBtnClicked));
        
        SMMenu* theMenu = SMMenu::create(powderContainer, powerButton, NULL);
        theMenu->setAnchorPoint(ccp(0, 0));
        theMenu->setPosition(ccp(0, 0));
        washer->addChild(theMenu);
        
        washer->runAction(CCSequence::create(CCDelayTime::create(0.2f), CCMoveBy::create(0.5f, ccp(STVisibleRect::getGlvisibleSize().width, 0)), NULL));
        washerDoor->runAction(CCSequence::create(CCDelayTime::create(0.2f), CCMoveBy::create(0.5f, ccp(STVisibleRect::getGlvisibleSize().width, 0)), CCCallFunc::create(this, callfunc_selector(WashClothes::runOpenAnimation)),NULL));
    }
    {
        handTip(CCDelayTime::create(1.2f),coloredClothes, CCCallFuncO::create(this, callfuncO_selector(WashClothes::setItemcanMove), coloredClothes));
        handTip(CCDelayTime::create(1.2f),whiteClothes, CCCallFuncO::create(this, callfuncO_selector(WashClothes::setItemcanMove), whiteClothes));
    }
}


void WashClothes::powderClicked(){
    CCPoint origin = washer->convertToWorldSpace(ccp(288, 454));
    drawerRect = CCRectMake(origin.x - 30, origin.y - 30, 60, 60);
    powderContainer->setEnabled(false);
    powderContainer->setNormalImage(CCSprite::create("washing_clothes/drawer_empty.png"));
    CCSprite* sp =CCSprite::create("washing_clothes/drawer_empty.png");
    sp->setColor(ccGRAY);
    powderContainer->setSelectedImage(sp);
    
    if (currentStep == kWashClothe1) {
        laundry1->setTouchable(true);
        loopJumpAction(laundry1, 1);
    }else {
        laundry2->setTouchable(true);
        loopJumpAction(laundry2, 2);
    }
}

void WashClothes::powerBtnClicked(){
    if (flag == false) {
        powerButton->setNormalImage(CCSprite::create("washing_clothes/washer_btn_on.png"));
        CCSprite* sprite = CCSprite::create("washing_clothes/washer_btn_on.png");
        sprite->setColor(ccGRAY);
        powerButton->setSelectedImage(sprite);
        flag = true;
    }else {
        powerButton->setNormalImage(CCSprite::create("washing_clothes/washer_btn_off.png"));
        CCSprite* sprite = CCSprite::create("washing_clothes/washer_btn_off.png");
        sprite->setColor(ccGRAY);
        powerButton->setSelectedImage(sprite);
        flag = false;
    }
}

void WashClothes::runCloseAnimation(){
    CCAnimation* animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("washing_clothes/door_close2.png");
    animation->addSpriteFrameWithFileName("washing_clothes/door_close1.png");
    animation->addSpriteFrameWithFileName("washing_clothes/door_close0.png");
    animation->setLoops(1);
    animation->setDelayPerUnit(0.2f);
    animation->setRestoreOriginalFrame(false);
    CCAnimate* animate = CCAnimate::create(animation);
    washerDoor->runAction(animate);
}

void WashClothes::runOpenAnimation(){
    CCAnimation* animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName("washing_clothes/door_close0.png");
    animation->addSpriteFrameWithFileName("washing_clothes/door_close1.png");
    animation->addSpriteFrameWithFileName("washing_clothes/door_close2.png");
    animation->setLoops(1);
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(false);
    CCAnimate* animate = CCAnimate::create(animation);
    washerDoor->runAction(animate);
}
#pragma wash step
void  WashClothes::loopJumpAction(cocos2d::CCSprite *goalNode, int index) {
    stringstream s;
    s<<"washing_clothes/laundry_detergent_"<<index;
    string str1 = s.str() + "_1.png";
    string str2 = s.str() + "_2.png";

    CCSequence* sequence = CCSequence::create(
                                              CCMoveBy::create(0.3f, ccp(0, 50)),
                                              CCDelayTime::create(0.05),
                                              CCMoveBy::create(0.2f, ccp(0, -50)),
                                              CCDelayTime::create(0.05f),
                                              CCMoveBy::create(0.2f, ccp(0, 20)),
                                              CCDelayTime::create(0.05f),
                                              CCMoveBy::create(0.1f, ccp(0, -20)),
                                              NULL);
    CCRepeatForever* foreverAct = CCRepeatForever::create(CCSequence::create(CCCallFuncO::create(goalNode, callfuncO_selector(CCSprite::setTexture), CCSprite::create(str2.c_str())->getTexture()),sequence, CCDelayTime::create(3.0f),CCCallFuncO::create(goalNode, callfuncO_selector(CCSprite::setTexture), CCSprite::create(str1.c_str())->getTexture()), NULL));
    goalNode->runAction(foreverAct);
    schedule(schedule_selector(WashClothes::updatepowder));
}

#pragma washing clothes
void WashClothes::updatepowder(){
//    CCLog("the draw rect is %s, and the point is %s", GetRectString(drawerRect), GetPointString(laundry2->getPosition()));
    if (currentStep == kWashClothe1) {
        if (drawerRect.containsPoint(laundry1->getPosition())) {
            powderCount++;
            if (powderCount / 50 > 0) {
                unschedule(schedule_selector(WashClothes::updatepowder));
                powderContainer->setNormalImage(CCSprite::create("washing_clothes/drawer_open_c.png"));
                laundry1->setTouchable(false);
                if (getChildByTag(kPowderParticleTag)) {
                    getChildByTag(kPowderParticleTag)->removeFromParent();
                }
                laundry1->runAction(CCSequence::create(
                                                       CCRotateTo::create(0.2f, 0),
                                                       CCDelayTime::create(0.1f),
                                                       CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),
                                                       CCCallFunc::create(this, callfunc_selector(WashClothes::restorePowderContainer)),
                                                       CCCallFunc::create(laundry1, callfunc_selector(MovableItem::removeFromParent)),
                                                       NULL));
            }
        }
    }else {
        if (drawerRect.containsPoint(laundry2->getPosition())) {
            powderCount++;
            if (powderCount / 50 > 0) {
                unschedule(schedule_selector(WashClothes::updatepowder));
                powderContainer->setNormalImage(CCSprite::create("washing_clothes/drawer_open.png"));
                laundry2->setTouchable(false);
                if (getChildByTag(kPowderParticleTag)) {
                    getChildByTag(kPowderParticleTag)->removeFromParent();
                }
                laundry2->runAction(CCSequence::create(
                                                       CCRotateTo::create(0.2f, 0),
                                                       CCDelayTime::create(0.1f),
                                                       CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),
                                                       CCCallFunc::create(this, callfunc_selector(WashClothes::restorePowderContainer)),
                                                       CCCallFunc::create(laundry2, callfunc_selector(MovableItem::removeFromParent)),
                                                       NULL));
            }
        }
    }
}

void WashClothes::restorePowderContainer(){
    CCSprite* sprite = CCSprite::create("washing_clothes/drawer_close.png");
    sprite->setColor(ccGRAY);
    powderContainer->setNormalImage(CCSprite::create("washing_clothes/drawer_close.png"));
    powderContainer->setSelectedImage(sprite);
    handTip(CCDelayTime::create(0.1f), powerButton, CCCallFuncO::create(this, callfuncO_selector(WashClothes::setMenuItemCanTouch), powerButton));
    
    MovableItem* washitem = NULL;
    if (currentStep == kWashClothe1) {
        washitem = (MovableItem*)getChildByTag(kSortedColorClothes);
    }else {
        washitem = (MovableItem*)getChildByTag(kSortedWhiteClohtes);
    }
    
    washSpeed = CCSpeed::create(CCRepeatForever::create(CCRotateBy::create(1.0f, 360)), 0.01f);
//    washSpeed->setSpeed(0);
    washitem->runAction(washSpeed);
    washSpeed->retain();
    
    washingStepNow = kwashing1;
    washCount = 0;
    flag = false;
    schedule(schedule_selector(WashClothes::updateWashing), 1/20.0);
    
}

void WashClothes::updateWashing(float dt){
    if (flag == true) {
        float speed = washSpeed->getSpeed();
        speed += speed * dt;
        if (speed > 5.0f) {
            speed = 5.0f;
        }
        washSpeed->setSpeed(speed);
        if (speed > 2.0f) {
            washCount ++;
            
            if (washCount / 100 == 1 && washingStepNow == kwashing1) {
                MovableItem* washitem = NULL;
                if (currentStep == kWashClothe1) {
                    washitem = (MovableItem*)getChildByTag(kSortedColorClothes);
                    washitem->setTexture(CCSprite::create("washing_clothes/door_clothes.png")->getTexture());
                }else {
                    washitem = (MovableItem*)getChildByTag(kSortedWhiteClohtes);
                    washitem->setTexture(CCSprite::create("washing_clothes/door_clothes_w.png")->getTexture());
                }
                washingStepNow = kwashing2;
            }else if (washCount / 100 == 2 && washingStepNow == kwashing2) {
                
                MovableItem* washitem = NULL;
                if (currentStep == kWashClothe1) {
                    washitem = (MovableItem*)getChildByTag(kSortedColorClothes);
                    washitem->setTexture(CCSprite::create("washing_clothes/door_clothes_clean.png")->getTexture());
                }else {
                    washitem = (MovableItem*)getChildByTag(kSortedWhiteClohtes);
                    washitem->setTexture(CCSprite::create("washing_clothes/door_clothes_w_clean.png")->getTexture());
                }
                powerButton->setNormalImage(CCSprite::create("washing_clothes/washer_btn_off.png"));
                CCSprite* sprite = CCSprite::create("washing_clothes/washer_btn_off.png");
                sprite->setColor(ccGRAY);
                powerButton->setSelectedImage(sprite);
                flag = false;
                powerButton->setEnabled(false);
                washingStepNow = kwashdone;
            }
         }
    }else {
        float speed = washSpeed->getSpeed();
        speed -= 2*speed * dt;
        if (speed < 0.01) {
            speed = 0.01;
        }
        washSpeed->setSpeed(speed);
        if (speed <= 0.01 && washingStepNow == kwashdone) {
            unschedule(schedule_selector(WashClothes::updateWashing));
            washCount = 0;
            MovableItem* washitem = NULL;
            if (currentStep == kWashClothe1) {
                washitem = (MovableItem*)getChildByTag(kSortedColorClothes);
                washitem->setTag(kWashDoneColorClothes);
            }else {
                washitem = (MovableItem*)getChildByTag(kSortedWhiteClohtes);
                washitem->setTag(kWashDoneWhiteClothes);
            }
            washitem->stopAllActions();
            washSpeed->release();
            runOpenAnimation();
            handTip(CCDelayTime::create(0.5f), washitem, CCCallFuncO::create(this, callfuncO_selector(WashClothes::setItemcanMove), washitem));
        }
    }
}
#pragma 衣服洗完过后的动画
void WashClothes::playWellDone(){
    washer->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),CCCallFunc::create(washer, callfunc_selector(CCSprite::removeFromParent)), NULL));
    washerDoor->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),CCCallFunc::create(washer, callfunc_selector(CCSprite::removeFromParent)), NULL));
    Baby* baby = Baby::createWithParams(GameController::getInstance()->getChooseIndex(), "planting/model/");
    baby->setPosition(ccp(STVisibleRect::getOriginalPoint().x+370-STVisibleRect::getGlvisibleSize().width, STVisibleRect::getPosition(374.0, 392.0).y));
    addChild(baby, 20);
    
    baby->runAction(CCSequence::create(CCDelayTime::create(0.5f), CCMoveBy::create(0.5f, ccp(STVisibleRect::getGlvisibleSize().width, 0)), CCCallFunc::create(baby, callfunc_selector(Baby::runAnimation)), CCCallFunc::create(this, callfunc_selector(WashClothes::showWellDoneLayer)),NULL));
   
}

void WashClothes::showWellDoneLayer(){
    WellDoneLayer* doneLayer = WellDoneLayer::createWithBoolen(true);
    doneLayer->setDelegate(this);
    doneLayer->showINtheNode(this);
}


#pragma movableitem touch events
void WashClothes::itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch) {
    pItem->setZOrder(20);
    if (pItem->getTag() == kLaundryTag1 || pItem->getTag() == kLaundryTag2) {
        pItem->stopAllActions();
        pItem->setRotation(-40);
        if (pItem->getTag() == kLaundryTag1) {
            pItem->setTexture(CCSprite::create("washing_clothes/use_laundry_detergent_1.png")->getTexture());
            CCParticleSystemQuad* particles = CCParticleSystemQuad::create("particles/colorpowder.plist");
            particles->setPosition(pItem->convertToWorldSpace(ccp(30, 155)));
            particles->setTag(kPowderParticleTag);
            addChild(particles, 19);
        }else {
            pItem->setTexture(CCSprite::create("washing_clothes/use_laundry_detergent_2.png")->getTexture());
            CCParticleSystemQuad* particles = CCParticleSystemQuad::create("particles/whitpowder.plist");
            particles->setPosition(pItem->convertToWorldSpace(ccp(30, 155)));
            particles->setTag(kPowderParticleTag);
            addChild(particles, 19);
        }
    }
}

void WashClothes::ItemDidBackToStartLocation(MovableItem *pItem) {
    if (abs(pItem->getTag() - kcolourClothesTag) < 6) {//彩色衣服 ZOrder = 10
        if (STVisibleRect::JudgeContain(colorRect, pItem->boundingBox())) {
            pItem->setTouchable(false);
            CCSprite* cloth = CCSprite::createWithTexture(pItem->getTexture());
            cloth->setPosition(colorNode->convertToNodeSpace(pItem->getPosition()));
            colorNode->addChild(cloth);
            pItem->removeFromParent();
            movedCount++;
            if (movedCount >= ClothesCount) {
                sortedSucceed();
            }
        }else {
            pItem->setTouchable(false);
            pItem->runAction(CCSequence::create(
                                                CCMoveTo::create(0.3f, pItem->getStartLocation()),
                                                CCCallFuncO::create(this, callfuncO_selector(WashClothes::backtoStartZorder), pItem),
                                                CCCallFuncO::create(this, callfuncO_selector(WashClothes::setItemcanMove), pItem),
                                                NULL));
        }
    }else if (abs(pItem->getTag() - kwhiteClothesTag) < 6) {//白色衣服 Zorder = 5
        if (STVisibleRect::JudgeContain(whiteRect, pItem->boundingBox())) {
            pItem->setTouchable(false);
            CCSprite* cloth = CCSprite::createWithTexture(pItem->getTexture());
            cloth->setPosition(whiteNode->convertToNodeSpace(pItem->getPosition()));
            whiteNode->addChild(cloth);
            pItem->removeFromParent();
            movedCount++;
            if (movedCount >= ClothesCount) {
                sortedSucceed();
            }
        }else {
            pItem->setTouchable(false);
            pItem->runAction(CCSequence::create(
                                                CCMoveTo::create(0.3f, pItem->getStartLocation()),
                                                 CCCallFuncO::create(this, callfuncO_selector(WashClothes::backtoStartZorder), pItem),
                                                CCCallFuncO::create(this, callfuncO_selector(WashClothes::setItemcanMove), pItem),
                                                NULL));
        }
    }else if (pItem->getTag() == kLaundryTag1 || pItem->getTag() == kLaundryTag2) {
        //放洗衣粉
        if (getChildByTag(kPowderParticleTag)) {
            getChildByTag(kPowderParticleTag)->removeFromParent();
        }
        pItem->setRotation(0);
        if (pItem->getTag() == kLaundryTag1) {
            pItem->setTexture(CCSprite::create("washing_clothes/laundry_detergent_1_1.png")->getTexture());
            
        }else {
            pItem->setTexture(CCSprite::create("washing_clothes/laundry_detergent_2_1.png")->getTexture());
        }
    }else if (pItem->getTag() == kSortedColorClothes || pItem->getTag() == kSortedWhiteClohtes) {
        CCPoint origin = washer->convertToWorldSpace(ccp(199,washer->getContentSize().height - 476));
        CCRect moveRect = CCRectMake(origin.x, origin.y, 300, 300);
        if (moveRect.containsPoint(pItem->getPosition())) {
            pItem->setTouchable(false);
            pItem->setZOrder(10);
            pItem->startZorder = 10;
            if (pItem->getTag() == kSortedColorClothes) {
                currentStep = kWashClothe1;
                if (getChildByTag(kSortedWhiteClohtes)) {
                    ((MovableItem*)getChildByTag(kSortedWhiteClohtes))->setTouchable(false);
                }
                
            }else {
                currentStep = kWashClothe2;
                if (getChildByTag(kSortedColorClothes)) {
                    ((MovableItem*)getChildByTag(kSortedColorClothes))->setTouchable(false);
                }
                
            }
            pItem->setStartLocation(ccp(moveRect.origin.x + moveRect.size.width/2.0, moveRect.origin.y+moveRect.size.height/2.0));
            pItem->runAction(CCSequence::create(CCMoveTo::create(0.2f, ccp(moveRect.origin.x + moveRect.size.width/2.0, moveRect.origin.y+moveRect.size.height/2.0)), CCCallFunc::create(this, callfunc_selector(WashClothes::runCloseAnimation)),CCDelayTime::create(0.3f), CCScaleTo::create(0.1f, 1.0/1.35),CCCallFunc::create(this, callfunc_selector(WashClothes::perFormByStep)), NULL));
        }else {
            pItem->setTouchable(false);
            pItem->runAction(CCSequence::create(
                                                CCMoveTo::create(0.3f, pItem->getStartLocation()),
                                                CCCallFuncO::create(this, callfuncO_selector(WashClothes::backtoStartZorder), pItem),
                                                CCCallFuncO::create(this, callfuncO_selector(WashClothes::setItemcanMove), pItem),
                                                NULL));
        }
    }else if (pItem->getTag() == kWashDoneColorClothes || pItem->getTag() == kWashDoneWhiteClothes) {
        if ((colorRect.containsPoint(pItem->getPosition()) && pItem->getTag() == kWashDoneColorClothes) || (whiteRect.containsPoint(pItem->getPosition()) && pItem->getTag() == kWashDoneWhiteClothes)) {
            if (pItem->getTag() == kWashDoneColorClothes) {
                pItem->setTouchable(false);
                pItem->setZOrder(7);
                pItem->runAction(CCMoveTo::create(0.2f, ccp(colorRect.origin.x + colorRect.size.width/2.0, colorRect.origin.y+colorRect.size.height/2.0)));
                colorClotesWashDone = true;
            }else {
                pItem->setZOrder(10);
                pItem->setTouchable(false);
                pItem->runAction(CCMoveTo::create(0.2f, ccp(whiteRect.origin.x + whiteRect.size.width/2.0, whiteRect.origin.y+whiteRect.size.height/2.0)));
                whiteClothesWashDone = true;
            }
            if (whiteClothesWashDone == true && colorClotesWashDone == true) {
                currentStep = kWashWellDone;
                scheduleOnce(schedule_selector(WashClothes::perFormByStep), 0.3f);
            }else {
                if (whiteClothesWashDone == true) {
                    handTip(CCDelayTime::create(0), getChildByTag(kSortedColorClothes), CCCallFuncO::create(this, callfuncO_selector(WashClothes::setItemcanMove), getChildByTag(kSortedColorClothes)));
                }else if (colorClotesWashDone == true) {
                    handTip(CCDelayTime::create(0), getChildByTag(kSortedWhiteClohtes), CCCallFuncO::create(this, callfuncO_selector(WashClothes::setItemcanMove), getChildByTag(kSortedWhiteClohtes)));
                }
            }
        }else {
            pItem->setTouchable(false);
            pItem->runAction(CCSequence::create(
                                                CCMoveTo::create(0.3f, pItem->getStartLocation()),
                                                CCCallFuncO::create(this, callfuncO_selector(WashClothes::backtoStartZorder), pItem),
                                                CCCallFuncO::create(this, callfuncO_selector(WashClothes::setItemcanMove), pItem),
                                                NULL));
        }
    }
}

void WashClothes::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    CCPoint afterPP =pItem->boundingBox().origin + detla;
    CCRect moverect = CCRectMake(afterPP.x, afterPP.y+20, pItem->boundingBox().size.width, pItem->boundingBox().size.height-20);
    if (STVisibleRect::JudgeContain(STVisibleRect::getMovableRect(), moverect)) {
        pItem->setPosition(pItem->getPosition() + detla);
        if (pItem->getTag() == kLaundryTag1 || pItem->getTag() == kLaundryTag2) {
            getChildByTag(kPowderParticleTag)->setPosition(getChildByTag(kPowderParticleTag)->getPosition() + detla);
        }
    }
}




