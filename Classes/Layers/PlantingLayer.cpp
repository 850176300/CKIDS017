//
//  PlantingLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-15.
//
//

#include "PlantingLayer.h"
#include "Baby.h"
#include "DataContainer.h"
#include "TipLayer.h"
#include "SunSprite.h"
#include "LittleSunComp.h"
#include "LittleSun.h"
#include "CloudComp.h"


CCScene* PlantingLayer::scene(){
    CCScene* scene = CCScene::create();
    
    PlantingLayer* layer = PlantingLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool PlantingLayer::init(){
    if (GameLayerBase::initWithBgFileName(PlantingBGPath)) {
        parter = CCSprite::create("planting/parterre.png");
        parter->setAnchorPoint(ccp(0.5f, 0));
        parter->setPosition(ccp(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y));
        addChild(parter, 5);
        //添加枯叶层
        addFields();
        addBaby();
        currentState = kMubing;
        this->runAction(CCSequence::create(CCDelayTime::create(1.0f), CCCallFunc::create(this, callfunc_selector(PlantingLayer::performStateChanged)), NULL));
        return true;
    }
    return false;
}

void PlantingLayer::addFields(){
    leftField = Field::create(1);
    middleField = Field::create(2);
    rightField = Field::create(3);
    
    leftField->ignoreAnchorPointForPosition(false);
    middleField->ignoreAnchorPointForPosition(false);
    rightField->ignoreAnchorPointForPosition(false);
    
    leftField->setAnchorPoint(ccp(0.5, 0.5f));
    middleField->setAnchorPoint(ccp(0.5f, 0.5f));
    rightField->setAnchorPoint(ccp(0.5f, 0.5f));
    
    float delta = parter->getContentSize().width*(STVisibleRect::getRealDesignScale() - 1.0) /4.0;
    leftField->setPosition(parter->convertToWorldSpace(ccp(85.5-delta, 237)));
    middleField->setPosition(parter->convertToWorldSpace(ccp(493, 237)));
    rightField->setPosition(parter->convertToWorldSpace(ccp(938+delta, 237)));
    
    leftField->setmubeaserPercent(0.84f);
    middleField->setmubeaserPercent(0.99f);
    rightField->setmubeaserPercent(0.82f);
    
    leftField->setTag(kLeftFieldTag);
    middleField->setTag(kMiddleFieldTag);
    rightField->setTag(kRightFieldTag);
    
    addChild(leftField, 6);
    addChild(middleField, 6);
    addChild(rightField, 6);
    
    leftField->setDelegate(this);
    middleField->setDelegate(this);
    rightField->setDelegate(this);
    
    parter->setScaleX(STVisibleRect::getRealDesignScale());
}

void PlantingLayer::addBaby(){
    Baby* baby = Baby::createWithParams(GameController::getInstance()->getChooseIndex(), "planting/model/");
    baby->setAnchorPoint(ccp(1.0, 0));
    baby->setPosition(ccpAdd(ccp(STVisibleRect::getPointOfSceneRightBottom().x - 120, STVisibleRect::getOriginalPoint().y+150), ccp(STVisibleRect::getGlvisibleSize().width, 0)));
    addChild(baby, 3);
    baby->setTag(kBabyTags);
    baby->runAction(CCSequence::create(CCDelayTime::create(0.5f), CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)), CCCallFunc::create(baby, callfunc_selector(Baby::runAnimation)),NULL));
}

void PlantingLayer::onEnter(){
    GameLayerBase::onEnter();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void PlantingLayer::onEnterTransitionDidFinish(){
    GameLayerBase::onEnterTransitionDidFinish();
    
    
}

void PlantingLayer::onExit(){
    GameLayerBase::onExit();
}

void PlantingLayer::performStateChanged(){
    switch (currentState) {
        case kMubing:
            currentField = leftField;
            playMubTip();
            break;
        case kDuging:
            currentField = leftField;
            currentField->addhole();
            playShovel();
            break;
        case kPlantSeed:
            currentField = leftField;
            showShovel();
            playMovingAction();
            break;
        case kSelectSeed:
            currentField = leftField;
            showhandTip();
            break;
        case kFirstGrow:
            leftField->addTree();
            middleField->addTree();
            rightField->addTree();
            currentField = leftField;
            showKettle();
            break;
        case kInsectShow:
            currentField = leftField;
            showInsects();
            break;
        case kSecondGrow:
            currentField = leftField;
            showSunAndProgress();
            break;
        case kThirdGrow:
            currentField = leftField;
            showFirstSnail();
            break;
        case kWatering:
            currentField = leftField;
            addKettleLast();
            break;
        case kWellDone:
            showWellDone();
            break;
        default:
            break;
    }
}

#pragma 耕地
void PlantingLayer::playMubTip(){
    rake = MovableItem::create("planting/rake.png");
    rake->setAnchorPoint(ccp(36.8/169.0, 1.0-120.2/152.0));
    rake->setPosition(STVisibleRect::conformByAnchorPoint(rake, STVisibleRect::getCenterOfScene(), rake->getAnchorPoint()));
    rake->setStartLocation(rake->getPosition());
    rake->setPosition(ccpAdd(rake->getPosition(), ccp(-STVisibleRect::getGlvisibleSize().width, 0)));
    rake->setTouchable(false);
    rake->setTouchEndHandleType(kMovableItemTouchEndBackStart);
    
    rake->setMovableItemDelegate(this);
    rake->setTag(kMubfieldTag);
    addChild(rake, 7);
    
    playmubHandAnimation(0.5f);

    
    
}

void PlantingLayer::playmubHandAnimation(float dt){
    //add tip 添加手指，添加提示动画
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0.2, 0.5));
    hand->setPosition(rake->getStartLocation());
    hand->setScale(0);
    addChild(hand, 8);
    hand->runAction(CCSequence::create(
                                       CCDelayTime::create(dt+0.5f),
                                       CCScaleTo::create(0.2f, 1.1f),
                                       CCScaleTo::create(0.1f, 1.0f),
                                       CCDelayTime::create(0.1f),
                                       CCMoveTo::create(0.3f, currentField->getPosition()),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.2f, ccp(50, 0)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.3f, ccp(-100, 0)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.1f, ccp(50, 0)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveTo::create(0.3f, rake->getStartLocation()),
                                       CCDelayTime::create(0.1f),
                                       CCScaleTo::create(0.2f, 0),
                                       CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                       NULL));
    rake->runAction(CCSequence::create(
                                       CCDelayTime::create(dt),
                                       CCMoveTo::create(0.5f, rake->getStartLocation()),
                                       CCDelayTime::create(0.4f),
                                       CCMoveTo::create(0.3f, currentField->getPosition()),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.2f, ccp(50, 0)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.3f, ccp(-100, 0)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveBy::create(0.1f, ccp(50, 0)),
                                       CCDelayTime::create(0.1f),
                                       CCMoveTo::create(0.3f, rake->getStartLocation()),
                                       CCDelayTime::create(0.3f),
                                       CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), rake),
                                       NULL));
}

#pragma 挖洞
void PlantingLayer::playShovel(){
    shovel = MovableItem::create("planting/shovel.png");
    shovel->setAnchorPoint(ccp(42/175.0, 1.0-115/147.0));
    shovel->setPosition(STVisibleRect::conformByAnchorPoint(shovel, STVisibleRect::getCenterOfScene(), shovel->getAnchorPoint()));
    shovel->setStartLocation(shovel->getPosition());
    shovel->setPosition(ccpAdd(shovel->getPosition(), ccp(STVisibleRect::getGlvisibleSize().width, 0)));
    shovel->setTouchEndHandleType(kMovableItemTouchEndBackStart);
    shovel->setMovableItemDelegate(this);
    shovel->setTag(kDugfieldTag);
    addChild(shovel, 7);
    
    playpitHandAnimation(0.1f);
}

void PlantingLayer::playpitHandAnimation(float dt) {
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0.2, 0.5));
    hand->setPosition(shovel->getStartLocation());
    hand->setScale(0);
    addChild(hand, 8);
    hand->runAction(CCSequence::create(
                                       CCDelayTime::create(dt+0.5f),
                                       CCScaleTo::create(0.2f, 1.1f),
                                       CCScaleTo::create(0.1f, 1.0f),
                                       CCDelayTime::create(0.1f),
                                       CCMoveTo::create(0.3f, currentField->getPosition()),
                                       CCDelayTime::create(0.1f),
                                       CCMoveTo::create(0.3f, shovel->getStartLocation()),
                                       CCDelayTime::create(0.1f),
                                       CCScaleTo::create(0.2f, 0),
                                       CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                       NULL));
    shovel->runAction(CCSequence::create(
                                       CCDelayTime::create(dt),
                                       CCMoveTo::create(0.5f, shovel->getStartLocation()),
                                       CCDelayTime::create(0.4f),
                                       CCMoveTo::create(0.3f, currentField->getPosition()),
                                       CCDelayTime::create(0.1f),
                                       CCMoveTo::create(0.3f, shovel->getStartLocation()),
                                       CCDelayTime::create(0.3f),
                                       CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), shovel),
                                       NULL));
}

#pragma 选择种子
void PlantingLayer::showAllSeed() {
    vector<LockItem> seeds = DataContainer::getInstance()->getAllSeed();
    CCArray* itemsforMenu = CCArray::createWithCapacity(3);
    for (vector<LockItem>::size_type i = 0; i < seeds.size(); ++i) {
        MyItemSprite* menuItem = MyItemSprite::menuItems(("planting/seed_bag_"+seeds[i].itemName + ".png").c_str());
        if (seeds[i].isFree == false) {
            CCSprite* lock = CCSprite::create("ui/suo.png");
            lock->setAnchorPoint(ccp(1.0, 0));
            lock->setPosition(ccp(menuItem->getContentSize().width - 10, 10));
            lock->setTag(theLockTagforAll);
            menuItem->addChild(lock);
        }
        menuItem->setAnchorPoint(ccp(0, 0));
        menuItem->setTag(i);
        menuItem->setTarget(this, menu_selector(PlantingLayer::selectTheSeed));
        menuItem->setPosition(ccp(STVisibleRect::getOriginalPoint().x + menuItem->getContentSize().width * i + 50 + 50 * i, STVisibleRect::getOriginalPoint().y+200));
        itemsforMenu->addObject(menuItem);
    }
    theMenu = SMMenu::createWithArray(itemsforMenu);
    theMenu->setAnchorPoint(ccp(0, 0));
    theMenu->setPosition(ccp(-STVisibleRect::getGlvisibleSize().width, 0));
    addChild(theMenu, 7);
    
    theMenu->setEnabled(false);
    theMenu->runAction(CCSequence::create(
                                          CCMoveBy::create(0.5f, ccp(STVisibleRect::getGlvisibleSize().width, 0)),
                                          CCDelayTime::create(0.2f),
                                          CCCallFunc::create(this, callfunc_selector(PlantingLayer::settheMenuenble)),
                                          NULL));
}

void PlantingLayer::showhandTip(){
    CCLayer* tipLayer = CCLayer::create();
    CCSprite* tip = CCSprite::create("ui/prompt/clean_your_seed.png");
    tip->setAnchorPoint(ccp(0.5, 0));
    tip->setPosition(ccpAdd(STVisibleRect::getCenterOfScene(), ccp(0, 20)));
    tipLayer->addChild(tip);
    
    CCSprite* seed1 = CCSprite::create("ui/prompt/clean_your_seed_1.png");
    CCSprite* seed2 = CCSprite::create("ui/prompt/clean_your_seed_2.png");
    CCSprite* seed3 = CCSprite::create("ui/prompt/clean_your_seed_3.png");
    seed1->setAnchorPoint(ccp(0.5f, 1.0));
    seed2->setAnchorPoint(ccp(0.5f, 1.0));
    seed3->setAnchorPoint(ccp(0.5f, 1.0));
    
    seed2->setPosition(ccpAdd(STVisibleRect::getCenterOfScene(), ccp(0, -20)));
    seed1->setPosition(ccpAdd(seed2->getPosition(), ccp(-seed1->getContentSize().width - 20, 0)));
    seed3->setPosition(ccpAdd(seed2->getPosition(), ccp(seed3->getContentSize().width+20, 0)));
    tipLayer->addChild(seed1);
    tipLayer->addChild(seed2);
    tipLayer->addChild(seed3);
    
    TipLayer* layer = TipLayer::createWithNode(tipLayer);
    layer->addToNode(this);
    runAction(CCSequence::create(CCDelayTime::create(3.0f), CCCallFunc::create(this, callfunc_selector(PlantingLayer::showAllSeed)), NULL));
}

void PlantingLayer::settheMenuenble(){
    theMenu->setEnabled(true);
}

void PlantingLayer::selectTheSeed(cocos2d::CCObject *pObj) {
    MyItemSprite* menuSprite = dynamic_cast<MyItemSprite*>(pObj);
    leftField->setSelectSeed(menuSprite->getTag());
    middleField->setSelectSeed(menuSprite->getTag());
    rightField->setSelectSeed(menuSprite->getTag());
    seedItem = MovableItem::createWithTexture(((CCSprite*)menuSprite->getNormalImage())->getTexture());
    seedItem->setPosition(STVisibleRect::conformByAnchorPoint(menuSprite, menuSprite->getPosition(), ccp(1.0, 1.0)));
    seedItem->setStartLocation(STVisibleRect::getCenterOfScene());
    seedItem->setTag(kSeedfieldTag);
    seedItem->setTouchEndHandleType(kMovableItemTouchEndBackStart);
    seedItem->setMovableItemDelegate(this);
    addChild(seedItem, 7);
    menuSprite->setScale(0);
    theMenu->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)), CCDelayTime::create(0.5f), CCCallFunc::create(theMenu, callfunc_selector(SMMenu::removeFromParent)),NULL));
    seedItem->runAction(CCSequence::create(CCMoveTo::create(0.3f, STVisibleRect::getCenterOfScene()), CCCallFunc::create(this, callfunc_selector(PlantingLayer::showhandMoving)),NULL));
}

void PlantingLayer::showhandMoving(){
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0.2, 0.8));
    hand->setPosition(STVisibleRect::getCenterOfScene());
    hand->setScale(0);
    addChild(hand, 7);
    CCAction* moveAction = CCSequence::create(
                                              CCMoveTo::create(0.3f, leftField->getPosition()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.2f, STVisibleRect::getCenterOfScene()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.2f, middleField->getPosition()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.1f, STVisibleRect::getCenterOfScene()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.3f, rightField->getPosition()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.2f, STVisibleRect::getCenterOfScene()),
                                              NULL);
    CCAction* handAction = CCSequence::create(
                                              CCScaleTo::create(0.2f, 1.1f),
                                              CCScaleTo::create(0.1, 1.0f),
                                              CCDelayTime::create(0.1f),
                                              moveAction,
                                              CCScaleTo::create(0.2f, 0),
                                              CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                              NULL);
    CCAction* seedAction = CCSequence::create(CCDelayTime::create(0.4f), moveAction->copy(), CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), seedItem), NULL);
    hand->runAction(handAction);
    seedItem->runAction(seedAction);
}

#pragma 盖土
void PlantingLayer::showShovel() {
    theShovel = MovableItem::create("planting/shovel.png");
    theShovel->setAnchorPoint(ccp(42/175.0, 1.0-115/147.0));
    theShovel->setPosition(STVisibleRect::conformByAnchorPoint(theShovel, STVisibleRect::getCenterOfScene(), theShovel->getAnchorPoint()));
    theShovel->setStartLocation(theShovel->getPosition());
    theShovel->setPosition(ccpAdd(theShovel->getPosition(), ccp(STVisibleRect::getGlvisibleSize().width, 0)));
    theShovel->setTouchEndHandleType(kMovableItemTouchEndBackStart);
    theShovel->setMovableItemDelegate(this);
    theShovel->setTag(kPlantSeedShovelTag);
    addChild(theShovel, 7);
}

void PlantingLayer::playMovingAction() {
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0.2, 0.6));
    hand->setPosition(theShovel->getStartLocation());
    hand->setScale(0);
    addChild(hand, 7);
    CCAction* moveAction = CCSequence::create(
                                              CCMoveTo::create(0.3f, leftField->getPosition()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.2f, theShovel->getStartLocation()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.2f, middleField->getPosition()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.1f, theShovel->getStartLocation()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.3f, rightField->getPosition()),
                                              CCDelayTime::create(0.1f),
                                              CCMoveTo::create(0.2f, theShovel->getStartLocation()),
                                              NULL);
    CCAction* handAction = CCSequence::create(
                                              CCDelayTime::create(0.5f),
                                              CCScaleTo::create(0.2f, 1.1f),
                                              CCScaleTo::create(0.1, 1.0f),
                                              CCDelayTime::create(0.1f),
                                              moveAction,
                                              CCScaleTo::create(0.2f, 0),
                                              CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                              NULL);
    CCAction* shovelAction = CCSequence::create(CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)), CCDelayTime::create(0.4f),moveAction->copy(), CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), theShovel), NULL);
    hand->runAction(handAction);
    theShovel->runAction(shovelAction);
}

#pragma 洒水
void PlantingLayer::showKettle() {
    kettle = MovableItem::create("planting/kettle.png");
    kettle->setTag(kKettlefieldTag);
    kettle->setPosition(STVisibleRect::getCenterOfScene()+ccp(0, 100)+(ccp(STVisibleRect::getGlvisibleSize().width, 0)));
    kettle->setStartLocation(STVisibleRect::getCenterOfScene()+ccp(0, 100));
    kettle->setMovableItemDelegate(this);
    kettle->setTouchEndHandleType(kMovableItemTouchEndStop);
    addChild(kettle, 7);
    showkettleTip(0.5f);
}

void PlantingLayer::showkettleTip(float dt){
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0.2, 0.8));
    hand->setPosition(kettle->getStartLocation());
    hand->setScale(0);
    addChild(hand, 7);
    
    kettle->runAction(CCSequence::create(
                                         CCMoveTo::create(dt, kettle->getStartLocation()),
                                         CCDelayTime::create(0.3f),
                                         CCRotateBy::create(0.2f, -20),
                                         CCDelayTime::create(0.1f),
                                         CCMoveTo::create(0.3f, currentField->getPosition()),
                                         CCDelayTime::create(0.3f),
                                         CCMoveTo::create(0.2f, kettle->getStartLocation()),
                                         CCRotateBy::create(0.2f, 20),
                                         CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), kettle),
                                         NULL));
    hand->runAction(CCSequence::create(
                                       CCDelayTime::create(dt),
                                       CCScaleTo::create(0.2f, 1.1f),
                                       CCScaleTo::create(0.1f, 1.0f),
                                       CCDelayTime::create(0.3f),
                                       CCMoveTo::create(0.3f, currentField->getPosition()),
                                       CCDelayTime::create(0.3f),
                                       CCMoveTo::create(0.2f, kettle->getStartLocation()),
                                       CCScaleTo::create(0.2f, 0),
                                       CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                       NULL));
    
}

#pragma 虫子出现
void PlantingLayer::showInsects(){
    insectsCount = InsectNUM;
    leftField->addInsects(0.1f);
    middleField->addInsects(0);
    rightField->addInsects(0.2f);
    
    CCSequence* handAction = CCSequence::create(
                                             CCScaleTo::create(0.2f, 1.1f),
                                             CCScaleTo::create(0.1f, 1.0f),
                                             CCMoveBy::create(0.3f, ccp(-100, -80)),
                                             CCDelayTime::create(0.2f),
                                             CCMoveBy::create(0.3f, ccp(100, 80)),
                                             CCDelayTime::create(0.2f),
                                             CCMoveBy::create(0.3f, ccp(-100, -80)),
                                             CCDelayTime::create(0.2f),
                                             CCScaleTo::create(0.2f, 0),
                                             NULL);
    //添加手指动画
    CCSprite* hand1 = CCSprite::create("ui/prompt/hand.png");
    hand1->setAnchorPoint(ccp(0, 1.0));
    hand1->setPosition(leftField->getPosition() + ccp(50+100, 90+80));
    hand1->setScale(0);
    addChild(hand1, 7);
    
    CCSprite* hand2 = CCSprite::create("ui/prompt/hand.png");
    hand2->setAnchorPoint(ccp(0, 1.0));
    hand2->setPosition(middleField->getPosition() + ccp(50+100, 90+80));
    hand2->setScale(0);
    addChild(hand2, 7);
    
    CCSprite* hand3 = CCSprite::create("ui/prompt/hand.png");
    hand3->setAnchorPoint(ccp(0, 1.0));
    hand3->setPosition(rightField->getPosition() + ccp(50+100, 90+80));
    hand3->setScale(0);
    addChild(hand3, 7);
    
    hand1->runAction(CCSequence::create(CCDelayTime::create(0.1f),handAction, CCCallFunc::create(hand1, callfunc_selector(CCSprite::removeFromParent)), NULL));
    hand2->runAction(CCSequence::create(CCDelayTime::create(0.1f),handAction->copy(), CCCallFunc::create(hand2, callfunc_selector(CCSprite::removeFromParent)), NULL));
    hand3->runAction(CCSequence::create(CCDelayTime::create(0.1f),handAction->copy(), CCCallFunc::create(hand3, callfunc_selector(CCSprite::removeFromParent)), NULL));
    runAction(CCSequence::create(CCDelayTime::create(2.0f), CCCallFunc::create(this, callfunc_selector(PlantingLayer::addTouchDelegate)), NULL));
}

bool PlantingLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    removeTouchDelegate();
    CCPoint location = pTouch->getLocation();
    bool flag = false;
    flag = leftField->checkHaspad(leftField->convertTouchToNodeSpace(pTouch));
    if (flag == true) {
        currentField = leftField;
        addbatAtPoint(location, flag);
        return true;
    }
    flag = middleField->checkHaspad(middleField->convertTouchToNodeSpace(pTouch));
    if (flag == true) {
        currentField = middleField;
        addbatAtPoint(location, flag);
        return true;
    }
    flag = rightField->checkHaspad(rightField->convertTouchToNodeSpace(pTouch));
    if (flag == true) {
        currentField = rightField;
        addbatAtPoint(location, flag);
        return true;
    }
    
    if (getChildByTag(kBabyTags)->boundingBox().containsPoint(pTouch->getLocation())) {
        addTouchDelegate();
        return false;
    }
    addbatAtPoint(location, flag);
    return true;
}

void PlantingLayer::addbatAtPoint(cocos2d::CCPoint location, bool isHit) {
    CCSprite* pad = CCSprite::create("planting/bat.png");
    pad->setAnchorPoint(ccp(1.0, 0));
    pad->setPosition(STVisibleRect::conformByAnchorPoint(pad, location, ccp(1.0, 0), ccp(45.0/pad->getContentSize().width, 1-38.0/pad->getContentSize().height)));
    addChild(pad, 8);
    
    pad->runAction(CCSequence::create(CCRotateBy::create(0.1f, 10), CCDelayTime::create(0.1f), CCRotateBy::create(0.2f, -20), CCDelayTime::create(0.1f), CCRotateBy::create(0.1f, 10), CCCallFunc::create(pad, callfunc_selector(CCSprite::removeFromParent)),NULL));
    if (isHit) {
        currentField->insectDisAppear();
        --insectsCount;
    }
    if (insectsCount > 0) {
        this->scheduleOnce(schedule_selector(PlantingLayer::addTouchDelegate), 0.5f);
    }else {
        currentState = kSecondGrow;
        this->scheduleOnce(schedule_selector(PlantingLayer::performStateChanged), 0.5f);
    }
}

void PlantingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {
    
    
}

void PlantingLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){

}

void PlantingLayer::addTouchDelegate(){
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void PlantingLayer::removeTouchDelegate(){
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

#pragma 第二生长过程
void PlantingLayer::showSunAndProgress(){
    startCloud = false;
    CCSprite* timer1 = CCSprite::create("planting/timer_1.png");
    timer1->setPosition(ccp(STVisibleRect::getPointOfSceneRightBottom().x - 50, STVisibleRect::getCenterOfScene().y+100));
    timer1->setTag(kSunTimerProgress1);
    timer1->setPosition(timer1->getPosition() + ccp(500, 0));
    addChild(timer1, 7);
    
    
    CCProgressTimer* progress = CCProgressTimer::create(CCSprite::create("planting/timer_2.png"));
    progress->setType(kCCProgressTimerTypeBar);
    progress->setMidpoint(ccp(0.5, 0));
    progress->setBarChangeRate(ccp(0, 1));
    progress->setPosition(timer1->getPosition());
    progress->setTag(kSunTimerProgress2);
    addChild(progress, 8);
    
    SunSprite* sunSprite = SunSprite::createOne();
    sunSprite->setPosition(STVisibleRect::getPointOfSceneLeftUp() + ccp(20+sunSprite->getContentSize().width/2.0, -30-sunSprite->getContentSize().height/2.0));
    sunSprite->setTag(kSunSpriteTag);
    sunSprite->setPosition(sunSprite->getPosition()+ccp(-500, 0));
    addChild(sunSprite, 7);
    
    
    sunSprite->runAction(CCSequence::create(CCDelayTime::create(3.0f) ,CCMoveBy::create(0.5f, ccp(500, 0)), CCCallFunc::create(sunSprite, callfunc_selector(SunSprite::runAnimation)), NULL));
    timer1->runAction(CCSequence::create(CCDelayTime::create(3.0), CCMoveBy::create(.5f, ccp(-500, 0)), NULL));
    progress->runAction(CCSequence::create(CCDelayTime::create(3.0), CCMoveBy::create(.5f, ccp(-500, 0)), NULL));
    
    CCSprite* tip = CCSprite::create("ui/prompt/weather.png");
    TipLayer* layer = TipLayer::createWithNode(tip);
    layer->addToNode(this);
}

void PlantingLayer::addlittleSun()
{
    if (startCloud == true) {
        
        LittleSun* cloud = LittleSun::createWithFile("planting/cloud.png");
        cloud->setPosition(getChildByTag(kSunSpriteTag)->getPosition() + ccp(80, 80));
        cloud->addComponent(new CloudComp());
        addChild(cloud, 6, 22221);
        LittleSun* sun = LittleSun::createWithFile("planting/little_sun.png");
        sun->setPosition(getChildByTag(kSunSpriteTag)->getPosition());
        sun->addComponent(new LittleSunComp());
        addChild(sun, 9, 22220);
        this->scheduleOnce(schedule_selector(PlantingLayer::addlittleSun1), 1.0f);
    }else {
        LittleSun* sun = LittleSun::createWithFile("planting/little_sun.png");
        sun->setPosition(getChildByTag(kSunSpriteTag)->getPosition());
        sun->addComponent(new LittleSunComp());
        addChild(sun, 9, 22220);
    }
}

void PlantingLayer::addlittleSun1(){
    if (getChildByTag(kSunSpriteTag)) {
        CCPoint pp =getChildByTag(kSunSpriteTag)->getPosition();
        LittleSun* sun = LittleSun::createWithFile("planting/little_sun.png");
        sun->setPosition(pp);
        sun->addComponent(new LittleSunComp());
        addChild(sun, 9, 22220);
    }
}


void PlantingLayer::onSunClicked(){
    CCProgressTimer* timer = (CCProgressTimer*)getChildByTag(kSunTimerProgress2);
    CCProgressTimer* timer1 = (CCProgressTimer*)getChildByTag(kSunTimerProgress1);
    float current = timer->getPercentage();
    if (current + 1/SunTotal*100.0 > 100*9/SunTotal + 1) {//表示已经收集了10个太阳
        startCloud = true;
    }
    if (current + 1/SunTotal*100.0 > 101.0) {
        timer->runAction(CCSequence::create(
                                            CCRotateBy::create(0.05f, -10),
                                            CCRotateBy::create(0.1f, 20),
                                            CCRotateBy::create(0.1f, -20),
                                            CCRotateBy::create(0.1f, 20),
                                            CCRotateBy::create(0.05f, -10),
                                            NULL));
        timer1->runAction(CCSequence::create(
                                             CCRotateBy::create(0.05f, -10),
                                             CCRotateBy::create(0.1f, 20),
                                             CCRotateBy::create(0.1f, -20),
                                             CCRotateBy::create(0.1f, 20),
                                             CCRotateBy::create(0.05f, -10),
                                             NULL));
        return;
    }
    timer1->runAction(CCSequence::create(/*CCScaleTo::create(0.1f, 1.1f, 1.0f), CCScaleTo::create(0.1f, 1.0f,1.0f),*/CCDelayTime::create(0.3f),CCCallFuncND::create(this, callfuncND_selector(PlantingLayer::progressAction), (void*)true), NULL));
}
void PlantingLayer::onCloudeClicked(){
    CCProgressTimer* timer = (CCProgressTimer*)getChildByTag(kSunTimerProgress2);
    CCProgressTimer* timer1 = (CCProgressTimer*)getChildByTag(kSunTimerProgress1);
    float current = timer->getPercentage();

    if (current + 1/SunTotal * 100.0 >= 101.0) {
        timer->runAction(CCSequence::create(
                                            CCRotateBy::create(0.05f, -10),
                                            CCRotateBy::create(0.1f, 20),
                                            CCRotateBy::create(0.1f, -20),
                                            CCRotateBy::create(0.1f, 20),
                                            CCRotateBy::create(0.05f, -10),
                                            NULL));
        timer1->runAction(CCSequence::create(
                                             CCRotateBy::create(0.05f, -10),
                                             CCRotateBy::create(0.1f, 20),
                                             CCRotateBy::create(0.1f, -20),
                                             CCRotateBy::create(0.1f, 20),
                                             CCRotateBy::create(0.05f, -10),
                                             NULL));
        return;
    }
    if (current <= 0) {
        return;
    }
    timer1->runAction(CCSequence::create(/*CCScaleTo::create(0.1f, 1.1f, 1.0f), CCScaleTo::create(0.1f, 1.0f,1.0f),*/CCDelayTime::create(0.3f),CCCallFuncND::create(this, callfuncND_selector(PlantingLayer::progressAction), (void*)false), NULL));
    
}
void PlantingLayer::progressAction(cocos2d::CCNode *pNode, void *upOrdown){
    bool upDown = static_cast<bool>(upOrdown);
    CCProgressTimer* timer = (CCProgressTimer*)getChildByTag(kSunTimerProgress2);
    float current = timer->getPercentage();
    if (upDown ==  true) {
        current += 1/SunTotal*100.0;
    }else {
         current -= 2/SunTotal*100.0;
    }
    timer->setPercentage(current);
    if (current >= 100.0) {
        SunSprite* sun = (SunSprite*)getChildByTag(kSunSpriteTag);
        sun->stopProduct = true;
        sun->runAction(CCSequence::create(CCMoveBy::create(0.3f, ccp(-300, 0)), CCCallFunc::create(sun, callfunc_selector(SunSprite::removeFromParent)),NULL));
        schedule(schedule_selector(PlantingLayer::updateForCheck), 0.1f);
    }
}

void PlantingLayer::updateForCheck(){
    if (getChildByTag(22220) || getChildByTag(22221)) {
        return;
    }else {
        unschedule(schedule_selector(PlantingLayer::updateForCheck));
        this->schedule(schedule_selector(PlantingLayer::playSunAnimation), 0.5f, ((int)SunTotal - 1) / 3, 0);
    }
}

void PlantingLayer::playSunAnimation(){
    CCProgressTimer* timer = (CCProgressTimer*)getChildByTag(kSunTimerProgress2);
    float current = timer->getPercentage() - 3.0 / SunTotal * 100.0;
    
    timer->setPercentage(current);
    
    createSunsby(1);
    createSunsby(2);
    createSunsby(3);
    
    if (current <= 0){
        CCProgressTimer* timer1 = (CCProgressTimer*)getChildByTag(kSunTimerProgress1);
        timer->runAction(CCSequence::create(CCDelayTime::create(0.2f), CCMoveBy::create(0.3f, ccp(500, 0)), CCDelayTime::create(2.0f),CCCallFunc::create(this, callfunc_selector(PlantingLayer::secondGrowNow)), CCCallFunc::create(timer, callfunc_selector(CCProgressTimer::removeFromParent)),NULL));
        timer1->runAction(CCSequence::create(CCDelayTime::create(0.2f), CCMoveBy::create(0.3f, ccp(500, 0)), CCCallFunc::create(timer1, callfunc_selector(CCSprite::removeFromParent)),NULL));
    }
}

void PlantingLayer::secondGrowNow(){
    leftField->secondGrow();
    middleField->secondGrow();
    rightField->secondGrow();
    currentState = kThirdGrow;
    scheduleOnce(schedule_selector(PlantingLayer::performStateChanged), 0.2f);
}

void PlantingLayer::createSunsby(int atPos) {
    CCPoint p1, p2, endP;//对应贝塞尔曲线的三个点
    CCProgressTimer* timer = (CCProgressTimer*)getChildByTag(kSunTimerProgress2);
    float percent = timer->getPercentage() + 3.0/SunTotal*100.0;
    if (atPos == 1) {
        endP = leftField->getPosition();
    }else if (atPos == 2) {
        endP = middleField->getPosition();
    }else {
        endP = rightField->getPosition();
    }
    p1 = ccp(endP.x, endP.y + 150);
    p2 = ccp(-30, timer->getSprite()->getContentSize().height * (-0.5f + percent / 100.0)) + timer->getPosition();
    ccBezierConfig config = {endP, p2, p1};
    
    CCSprite* sun = CCSprite::create("planting/little_sun.png");
    sun->setPosition(ccp(0, timer->getSprite()->getContentSize().height * (-0.5f + percent / 100.0)) + timer->getPosition());
    sun->setScale(0);
    addChild(sun, 10);
    CCLog("the timer percent is %.2f", percent / 100.0);
    CCLog("the deltaPoint is %s", GetSizeString(timer->getSprite()->getContentSize()));
    CCLog("the timer Position is %s", GetPointString(timer->getPosition()));
    sun->runAction(CCSequence::create(CCSpawn::create(CCScaleTo::create(0.2f, 1.0f), CCBezierTo::create(2.0, config), NULL), CCScaleTo::create(0.2f, 0), CCCallFunc::create(sun, callfunc_selector(CCSprite::removeFromParent)), NULL));
}

//第三阶段生长
void PlantingLayer::showFirstSnail() {
//    //显示树苗
//    leftField->secondGrow();
//    middleField->secondGrow();
//    rightField->secondGrow();
//    //
    snailLayer = SnailLayer::create();
    snailLayer->setPosition(STVisibleRect::getOriginalPoint()+ccp(-STVisibleRect::getGlvisibleSize().width, 0));
    addChild(snailLayer, 8);
    
    CCSprite* snail = CCSprite::create("planting/snail.png");
    snail->setPosition(middleField->getPosition() + ccp(-50, 40));
    addChild(snail, 11);
    snail->setOpacity(0);
    
    CCSprite* bottleTop = CCSprite::create("planting/bottle_2.png");
    bottleTop->setAnchorPoint(ccp(0, 0));
    bottleTop->setPosition(STVisibleRect::getOriginalPoint() + BottlePointDelta +ccp(-STVisibleRect::getGlvisibleSize().width, 0));
    bottleTop->setTag(kBottleTopTags);
    addChild(bottleTop, 10);
    
    snailLayer->runAction(CCMoveBy::create(0.6f, ccp(STVisibleRect::getGlvisibleSize().width, 0)));
    bottleTop->runAction(CCMoveBy::create(0.6f, ccp(STVisibleRect::getGlvisibleSize().width, 0)));
    snail->runAction(CCSequence::create(
                                        CCDelayTime::create(0.6f),
                                        CCFadeIn::create(0.1f),
                                        CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::showTipForSnail), snail),
                                        NULL));
}

void PlantingLayer::showTipForSnail(cocos2d::CCSprite *snail){
    CCPoint startPoint = snail->getPosition();
    
    CCSprite* hand = CCSprite::create("ui/prompt/hand.png");
    hand->setAnchorPoint(ccp(0, 1.0));
    hand->setPosition(STVisibleRect::getCenterOfScene());
    hand->setScale(0);
    addChild(hand, 11);
    
    
    hand->runAction(CCSequence::create(
                                       CCScaleTo::create(0.2f, 1.1f),
                                       CCScaleTo::create(0.1f, 1.0f),
                                       CCDelayTime::create(0.05f),
                                       CCMoveTo::create(0.2f, startPoint),
                                       CCDelayTime::create(0.1f),
                                       CCMoveTo::create(0.2f, STVisibleRect::getCenterOfScene()),
                                       CCDelayTime::create(0.05f),
                                       CCMoveTo::create(0.2f, startPoint),
                                       CCDelayTime::create(0.1f),
                                       CCMoveTo::create(0.2f, STVisibleRect::getCenterOfScene()),
                                       CCDelayTime::create(0.05f),
                                       CCMoveTo::create(0.2f, startPoint),
                                       CCDelayTime::create(0.05f),
                                       CCMoveTo::create(0.3f, snailLayer->getConfilctRect().origin + CCPoint(90, 10)),
                                       CCDelayTime::create(0.1f),
                                       CCScaleTo::create(0.2f, 0),
                                       CCCallFunc::create(hand, callfunc_selector(CCSprite::removeFromParent)),
                                       NULL));
    snail->runAction(CCSequence::create(
                                        CCDelayTime::create(1.7f),
                                        CCMoveTo::create(0.3f, snailLayer->getConfilctRect().origin + CCPoint(90, 10)),
                                        CCDelayTime::create(0.2f),
                                        CCFadeOut::create(0.1f),
                                        CCCallFunc::create(this, callfunc_selector(PlantingLayer::updateForShowSnail)),
                                        CCCallFunc::create(snail, callfunc_selector(CCSprite::removeFromParent)),
                                        NULL));
}

void PlantingLayer::updateForShowSnail(){
    addSnailCount = SnailCounts;
    this->schedule(schedule_selector(PlantingLayer::addallSnails), 1.0f, SnailCounts-1, 0);
}

void PlantingLayer::addallSnails(){
    srand((unsigned)time(0));
    int r = rand();
    CCPoint atPos = CCPointZero;
    if (r%3==0) {
        atPos = leftField->getPosition() + ccp(10*(r%7), r%7*5);
    }else if (r%3==1){
        atPos = middleField->getPosition() + ccp(10*(r%11) - 50, r%7*5);
    }else {
        atPos = rightField->getPosition() + ccp(10*(r%11) - 50, r%7*5);
    }
    
    MovableItem* moveSnail = MovableItem::create("planting/snail.png");
    moveSnail->setTag(kSnailTags);
    moveSnail->setPosition(atPos);
    moveSnail->setTouchEndHandleType(kMovableItemTouchEndStop);
    moveSnail->setMovableItemDelegate(this);
    moveSnail->setStartLocation(moveSnail->getPosition());
    moveSnail->setScale(0);
    
    addChild(moveSnail, 11);
    
    moveSnail->setFlipX(r%2 == 1 ? true:false);
    moveSnail->isFlipX = r%2 == 1 ? true:false;
    moveSnail->runAction(CCSequence::create(CCScaleTo::create(0.2f, 1.1f), CCScaleTo::create(0.1f, 1.0f), CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), moveSnail), NULL));
//    addSnailCount++;
//    CCLog("had add Snail total count is %d", addSnailCount);
}

//第三阶段过后的洒水阶段
void PlantingLayer::addKettleLast(){
    showKettle();
}
//完成效果添加
void PlantingLayer::showWellDone(){
    WellDoneLayer* layer = WellDoneLayer::createWithBoolen(true);
    layer->showINtheNode(this);
}


void PlantingLayer::setItemCanMove(MovableItem *pItem) {
    pItem->setTouchable(true);
}

void PlantingLayer::itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch) {
    if (pItem->getTag() == kKettlefieldTag) {
        pItem->setRotation(-20);
        CCParticleSystemQuad* particles = CCParticleSystemQuad::create("particles/waterEffect.plist");
        particles->ignoreAnchorPointForPosition(false);
        particles->setAnchorPoint(ccp(1.0, 1.0));
        particles->setPosition(pItem->convertToWorldSpace(ccp(20, 70)));
        particles->setTag(kWaterParticleTag);
        CCLog("the point is %s", GetRectString(pItem->boundingBox()));
        addChild(particles, 8);
        schedule(schedule_selector(PlantingLayer::updateField), 1/20.0);
    }else if (pItem->getTag() == kLittleSunTag) {
        if (pItem->getScale() >= 1.0f) {
            pItem->removeAllComponents();
            pItem->setTouchable(false);
            pItem->removeFromParent();
//            pItem->runAction(CCSequence::)
        }
    }
}

void PlantingLayer::updateField(){
   if (currentField->getWaterRect().containsPoint(kettle->convertToWorldSpace(ccp(-80, -20)))) {
       if (currentState == kFirstGrow && currentField->firstGrowUpFinished == false) {
           currentField->firstGrowUp();
       }
       if (currentState == kWatering && currentField->lastGrowUpFinished == false) {
           currentField->lastGrowUp();
       }
    }
}

void PlantingLayer::ItemDidBackToStartLocation(MovableItem *pItem) {
    if (pItem->getTag() == kKettlefieldTag) {
        pItem->setTouchable(false);
        removeChildByTag(kWaterParticleTag);
        if (currentField->firstGrowUpFinished == true || currentField->lastGrowUpFinished == true) {
            pItem->setRotation(0);
            if (currentField->getTag() == kLeftFieldTag) {
                currentField = middleField;
                showkettleTip(0.3f);
            }else if (currentField->getTag() == kMiddleFieldTag) {
                currentField = rightField;
                showkettleTip(0.3f);
            }else {
                if (currentState == kFirstGrow) {
                    currentState = kInsectShow;
                }else {
                    currentState = kWellDone;
                }
                kettle->runAction(CCSequence::create(
                                                     CCMoveTo::create(0.3f, kettle->getStartLocation()),
                                                     CCDelayTime::create(0.1f),
                                                     CCMoveBy::create(0.3f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),
                                                     CCCallFunc::create(this, callfunc_selector(PlantingLayer::performStateChanged)),
                                                     NULL));
            }
        }else {
            pItem->runAction(CCSequence::create(CCRotateBy::create(0.2f, 20), CCMoveTo::create(0.3f, pItem->getStartLocation()), CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), pItem),NULL));
        }
       
    }else if (pItem->getTag() == kSnailTags) {

        
        if (snailLayer->getConfilctRect().containsPoint(pItem->getPosition())) {
            snailLayer->addSnail(snailLayer->convertToNodeSpace(pItem->getPosition()), pItem->isFlipX);
            pItem->removeFromParent();
            addSnailCount--;
            CCLog("had add Snail total count is %d", addSnailCount);
            if (addSnailCount <= 0) {
                snailLayer->runAction(CCSequence::create(CCDelayTime::create(2.0f),CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)), CCCallFunc::create(snailLayer, callfunc_selector(SnailLayer::removeFromParent)),NULL));
                currentState = kWatering;
                getChildByTag(kBottleTopTags)->runAction(CCSequence::create(CCDelayTime::create(2.0f),CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)), CCCallFunc::create(this, callfunc_selector(PlantingLayer::performStateChanged)),CCCallFunc::create(getChildByTag(kBottleTopTags), callfunc_selector(CCSprite::removeFromParent)), NULL));
            }
        }else{
            pItem->setTouchable(false);
            pItem->stopAllActions();
            pItem->runAction(CCSequence::create(CCMoveTo::create(0.3f, pItem->getStartLocation()), CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), pItem), NULL));
        }
    }
}

void PlantingLayer::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    if (pItem->getTag() == kMubfieldTag) {
        CCPoint afterPP = ccpAdd(pItem->getPosition(), detla);
        if (STVisibleRect::getMovableRect().containsPoint(afterPP) && pItem->getTouchable()) {
            if (currentField != NULL) {
                currentField->mudPaint(pItem->getPosition(), afterPP);
            }
            pItem->setPosition(afterPP);
        }
    }else if (pItem->getTag() == kDugfieldTag) {
        CCPoint afterPP = ccpAdd(pItem->getPosition(), detla);
        if (STVisibleRect::getMovableRect().containsPoint(afterPP) && pItem->getTouchable()) {
            pItem->setPosition(afterPP);
            CCRect moveRect = CCRectMake(currentField->getPositionX() - 40, currentField->getPositionY() - 40, 80, 80);
            if (moveRect.containsPoint(afterPP)) {
                if (currentField->changeHole()) {
                    shovel->setTouchable(false);
                    shovel->runAction(CCSequence::create(CCMoveTo::create(0.3f, shovel->getStartLocation()), CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), shovel), NULL));
                }else {
                    theHoleDugFinished();
                }
                
            }
        }
    }else if (pItem->getTag() == kSeedfieldTag) {
        CCPoint afterPP = ccpAdd(pItem->getPosition(), detla);
         if (STVisibleRect::getMovableRect().containsPoint(afterPP) && pItem->getTouchable()) {
            pItem->setPosition(afterPP);
            theSeedputonField(afterPP);
         }
    }else if (pItem->getTag() == kPlantSeedShovelTag) {
        CCPoint afterPP = ccpAdd(pItem->getPosition(), detla);
        if (STVisibleRect::getMovableRect().containsPoint(afterPP) && pItem->getTouchable()) {
            pItem->setPosition(afterPP);
            thePlantSeedField(afterPP);
        }
    }else if (pItem->getTag() == kKettlefieldTag) {
        CCPoint afterPP = ccpAdd(pItem->getPosition(), detla);
        if (STVisibleRect::JudgeContain(STVisibleRect::getMovableRect(), CCRectMake(afterPP.x - pItem->getContentSize().width/2.0+80, afterPP.y-pItem->getContentSize().height/2.0, pItem->getContentSize().width-160, pItem->getContentSize().height)) && pItem->getTouchable()) {
            pItem->setPosition(afterPP);
            getChildByTag(kWaterParticleTag)->setPosition(ccpAdd(getChildByTag(kWaterParticleTag)->getPosition(), detla));
        }
    }else if (pItem->getTag() == kSnailTags) {
        CCPoint afterPP = ccpAdd(pItem->getPosition(), detla);
        if (STVisibleRect::JudgeContain(STVisibleRect::getMovableRect(), CCRectMake(afterPP.x - pItem->getContentSize().width/2.0, afterPP.y-pItem->getContentSize().height/2.0, pItem->getContentSize().width, pItem->getContentSize().height)) && pItem->getTouchable()) {
            pItem->setPosition(afterPP);
        }
    }
}

void PlantingLayer::theFieldmudFinished(){
    if (currentField->getTag() == kLeftFieldTag) {
        rake->setTouchable(false);
        currentField = middleField;
        playmubHandAnimation(0.3f);
    }else if (currentField->getTag() == kMiddleFieldTag) {
        rake->setTouchable(false);
        currentField = rightField;
        playmubHandAnimation(0.3f);
    }else {
        rake->setTouchable(false);
        currentState = kDuging;
    
        rake->runAction(CCSequence::create(
                                           CCDelayTime::create(0.3f),
                                           CCMoveTo::create(0.3f, rake->getStartLocation()),
                                           CCDelayTime::create(0.2f),
                                           CCMoveBy::create(0.3f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),
                                           CCCallFunc::create(this, callfunc_selector(PlantingLayer::performStateChanged)),
                                           CCCallFunc::create(rake, callfunc_selector(MovableItem::removeFromParent)),
                                           NULL));
    }
}

void PlantingLayer::theHoleDugFinished(){
    if (currentField->getTag() == kLeftFieldTag) {
        shovel->setTouchable(false);
        currentField = middleField;
        currentField->addhole();
        playpitHandAnimation(0.3f);
    }else if (currentField->getTag() == kMiddleFieldTag) {
        shovel->setTouchable(false);
        currentField = rightField;
        currentField->addhole();
        playpitHandAnimation(0.3f);
    }else {
        shovel->setTouchable(false);
        currentState = kSelectSeed;
        shovel->runAction(CCSequence::create(
                                           CCDelayTime::create(0.3f),
                                           CCMoveTo::create(0.3f, shovel->getStartLocation()),
                                           CCDelayTime::create(0.2f),
                                           CCMoveBy::create(0.3f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),
                                           CCCallFunc::create(shovel, callfunc_selector(MovableItem::removeFromParent)),
                                           CCCallFunc::create(this, callfunc_selector(PlantingLayer::performStateChanged)),
                                           NULL));
    }
}

void PlantingLayer::theSeedputonField(cocos2d::CCPoint afterPP){
    
    CCRect moveRect1 = CCRectMake(leftField->getPositionX() - 40, leftField->getPositionY() - 40, 80, 80);
    CCRect moveRect2 = CCRectMake(middleField->getPositionX() - 40, middleField->getPositionY() - 40, 80, 80);
    CCRect moveRect3 = CCRectMake(rightField->getPositionX() - 40, rightField->getPositionY() - 40, 80, 80);
    bool flag = false;
    if (moveRect1.containsPoint(afterPP) && leftField->getisAddSeed() == false) {
        flag = true;
        seedItem->setTouchable(false);
        leftField->addSeed();
    }else if (moveRect2.containsPoint(afterPP) && middleField->getisAddSeed() == false) {
        flag = true;
        seedItem->setTouchable(false);
        middleField->addSeed();
    }else if (moveRect3.containsPoint(afterPP) && rightField->getisAddSeed() == false) {
        flag = true;
        seedItem->setTouchable(false);
        rightField->addSeed();
    }
    
    
    if (leftField->getisAddSeed() && middleField->getisAddSeed() && rightField->getisAddSeed()) {
        currentState = kPlantSeed;
        seedItem->runAction(CCSequence::create(
                                               CCMoveTo::create(0.3f, seedItem->getStartLocation()),
                                               CCDelayTime::create(0.1f),
                                               CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),
                                               CCCallFunc::create(this, callfunc_selector(PlantingLayer::performStateChanged)),
                                               NULL));
    }else {
        if (flag == true) {
            seedItem->runAction(CCSequence::create(CCMoveTo::create(0.3f, seedItem->getStartLocation()), CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), seedItem), NULL));
        }
    }
}

void PlantingLayer::thePlantSeedField(cocos2d::CCPoint afterPP) {
    CCRect moveRect1 = CCRectMake(leftField->getPositionX() - 40, leftField->getPositionY() - 40, 80, 80);
    CCRect moveRect2 = CCRectMake(middleField->getPositionX() - 40, middleField->getPositionY() - 40, 80, 80);
    CCRect moveRect3 = CCRectMake(rightField->getPositionX() - 40, rightField->getPositionY() - 40, 80, 80);
    bool flag = false;
    if (moveRect1.containsPoint(afterPP) && leftField->hadPlantSeed == false) {
        leftField->hadPlantSeed = true;
        theShovel->setTouchable(false);
        flag = true;
        leftField->runAction(CCRepeat::create(CCSequence::create(CCCallFunc::create(leftField, callfunc_selector(Field::plantSeed)), CCDelayTime::create(0.2f), NULL), 4));
    }else if (moveRect2.containsPoint(afterPP) && middleField->hadPlantSeed == false) {
        middleField->hadPlantSeed = true;
        theShovel->setTouchable(false);
        flag = true;
        middleField->runAction(CCRepeat::create(CCSequence::create(CCCallFunc::create(middleField, callfunc_selector(Field::plantSeed)), CCDelayTime::create(0.2f), NULL), 4));
    }else if (moveRect3.containsPoint(afterPP) && rightField->hadPlantSeed == false) {
        rightField->hadPlantSeed = true;
        theShovel->setTouchable(false);
        flag = true;
        rightField->runAction(CCRepeat::create(CCSequence::create(CCCallFunc::create(rightField, callfunc_selector(Field::plantSeed)), CCDelayTime::create(0.2f), NULL), 4));
    }
    
    
    if (leftField->hadPlantSeed == true && middleField->hadPlantSeed == true && rightField->hadPlantSeed == true) {
        currentState = kFirstGrow;
        theShovel->runAction(CCSequence::create(
                                               CCMoveTo::create(0.3f, theShovel->getStartLocation()),
                                               CCDelayTime::create(0.1f),
                                               CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)),
                                               CCCallFunc::create(this, callfunc_selector(PlantingLayer::performStateChanged)),
                                               NULL));
    }else {
        if (flag == true) {
            theShovel->runAction(CCSequence::create(CCMoveTo::create(0.3f, theShovel->getStartLocation()), CCDelayTime::create(0.5f), CCCallFuncO::create(this, callfuncO_selector(PlantingLayer::setItemCanMove), theShovel), NULL));
        }
    }
}

#pragma welldone layer delegate
void PlantingLayer::onLeftButtonClicked(TapType type) {
    if (type == kHomeType) {
        
    }else {
        
    }
}

void PlantingLayer::onResetButtonClicked(){
    GameController::getInstance()->gotoPlanting(true);
}