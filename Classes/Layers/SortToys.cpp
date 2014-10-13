//
//  SortToys.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-13.
//
//

#include "SortToys.h"
#include "DataContainer.h"
#include "TipLayer.h"
#include "SortRoomLayer.h"
#define RectYDelta 50
#define BoxYDelta 200
CCScene* SortToys::scene(CCObject* pObj){
    CCScene* scene = CCScene::create();
    
    SortToys* layer = SortToys::createWithObj(pObj);
    
    scene->addChild(layer);
    
    return scene;
}

SortToys* SortToys::createWithObj(cocos2d::CCObject *pObj) {
    SortToys* pRet = new SortToys();
    if (pRet && pRet->initWithObj(pObj)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool SortToys::initWithObj(cocos2d::CCObject *pObj){
    _parent = pObj;
    _parent->retain();
    if (GameLayerBase::initWithBgFileName(SortToyBGPath)) {
        allToyCount = 0;
        addblocks();
        addcars();
        adddolls();
        showNextBtn();
        return true;
    }
    return false;
}

void SortToys::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    CCSprite* tip = CCSprite::create("ui/prompt/sorting.png");
    TipLayer* tipLayer = TipLayer::createWithNode(tip);
    tipLayer->addToNode(this);
}


void SortToys::addblocks(){
    CCSprite* box1 = CCSprite::create("sorting/toys_into/box_blocks_0.png");
    CCSprite* box2 = CCSprite::create("sorting/toys_into/box_blocks.png");
    box1->setPosition(STVisibleRect::getPosition(722, 583));
    box2->setPosition(box1->getPosition());
    addChild(box1, 8);
    addChild(box2, 10);
    blockRect = box1->boundingBox();
    blockRect.origin = blockRect.origin+ccp(0, RectYDelta);
    blockRect.size = CCSizeMake(blockRect.size.width, blockRect.size.height - RectYDelta);
    
    CCSprite* classify = CCSprite::create("sorting/toys_into/classify_blocks.png");
    classify->setAnchorPoint(ccp(0, 0.5f));
    classify->setPosition(ccp(box1->getPositionX() + box1->getContentSize().width / 2.0 + 20, box1->getPositionY()));
    addChild(classify , 10);
    
    vector<ToyPosition> blocks = DataContainer::getInstance()->getBlocks();
    allToyCount += blocks.size();
    srand((unsigned)time(0));
    for (vector<ToyPosition>::size_type i = 0; i < blocks.size(); ++i) {
        char filename[128];
        sprintf(filename, "sorting/toys_into/blocks_%d.png", (int)i+1);
        MovableItem* pItem = MovableItem::create(filename);
        pItem->setPosition(STVisibleRect::getPosition(blocks[i].pos1.x, blocks[i].pos1.y));
        pItem->setStartLocation(pItem->getPosition());
        pItem->setStartPos(STVisibleRect::getPosition(blocks[i].pos2.x, blocks[i].pos2.y));
        pItem->setTouchable(true);
        pItem->setTouchEndHandleType(kMovableItemTouchEndStop);
        pItem->setTag(kBlocksTagAtOne + (int)i);
        pItem->setMovableItemDelegate(this);
        int zOrder =  rand() % 10 + 1;
        addChild(pItem, zOrder);
        pItem->startZorder = zOrder;
    }
}

void SortToys::adddolls(){


    CCSprite* box1 = CCSprite::create("sorting/toys_into/box_dolls_0.png");
    CCSprite* box2 = CCSprite::create("sorting/toys_into/box_dolls.png");
    box1->setPosition(STVisibleRect::getPosition(722, 583 - BoxYDelta));
    box2->setPosition(box1->getPosition());
    addChild(box1, 8);
    addChild(box2, 10);
    dollsRect = box1->boundingBox();
    dollsRect.origin = dollsRect.origin+ccp(0, RectYDelta);
    dollsRect.size = CCSizeMake(dollsRect.size.width, dollsRect.size.height - RectYDelta);
    CCSprite* classify = CCSprite::create("sorting/toys_into/classify_dolls.png");
    classify->setAnchorPoint(ccp(0, 0.5f));
    classify->setPosition(ccp(box1->getPositionX() + box1->getContentSize().width / 2.0 + 20, box1->getPositionY()));
    addChild(classify , 10);
    
    vector<ToyPosition> dolls = DataContainer::getInstance()->getDolls();
    allToyCount += dolls.size();
    srand((unsigned)time(0));
    for (vector<ToyPosition>::size_type i = 0; i < dolls.size(); ++i) {
        char filename[128];
        sprintf(filename, "sorting/toys_into/dolls_%d.png", (int)i+1);
        MovableItem* pItem = MovableItem::create(filename);
        pItem->setPosition(STVisibleRect::getPosition(dolls[i].pos1.x, dolls[i].pos1.y));
        pItem->setStartLocation(pItem->getPosition());
        pItem->setStartPos(STVisibleRect::getPosition(dolls[i].pos2.x, dolls[i].pos2.y));
        pItem->setTouchable(true);
        pItem->setTouchEndHandleType(kMovableItemTouchEndStop);
        pItem->setTag(kDollsTagAtOne + (int)i);
        pItem->setMovableItemDelegate(this);
        int zOrder =  rand() % 10 + 1;
        addChild(pItem, zOrder);
        pItem->startZorder = zOrder;
    }
}

void SortToys::addcars(){
    CCSprite* box1 = CCSprite::create("sorting/toys_into/box_cars_0.png");
    CCSprite* box2 = CCSprite::create("sorting/toys_into/box_cars.png");
    box1->setPosition(STVisibleRect::getPosition(722, 583 - BoxYDelta - BoxYDelta));
    box2->setPosition(box1->getPosition());
    addChild(box1, 8);
    addChild(box2, 10);
    carRect = box1->boundingBox();
    carRect.origin = carRect.origin+ccp(0, RectYDelta);
    carRect.size = CCSizeMake(carRect.size.width, carRect.size.height - RectYDelta);
    CCSprite* classify = CCSprite::create("sorting/toys_into/classify_cars.png");
    classify->setAnchorPoint(ccp(0, 0.5f));
    classify->setPosition(ccp(box1->getPositionX() + box1->getContentSize().width / 2.0 + 20, box1->getPositionY()));
    addChild(classify , 10);
    
    vector<ToyPosition> cars = DataContainer::getInstance()->getCars();
    allToyCount += cars.size();
    srand((unsigned)time(0));
    for (vector<ToyPosition>::size_type i = 0; i < cars.size(); ++i) {
        char filename[128];
        sprintf(filename, "sorting/toys_into/cars_%d.png", (int)i+1);
        MovableItem* pItem = MovableItem::create(filename);
        pItem->setPosition(STVisibleRect::getPosition(cars[i].pos1.x, cars[i].pos1.y));
        pItem->setStartLocation(pItem->getPosition());
        pItem->setStartPos(STVisibleRect::getPosition(cars[i].pos2.x, cars[i].pos2.y));
        pItem->setTouchable(true);
        pItem->setTouchEndHandleType(kMovableItemTouchEndStop);
        pItem->setTag(kCarsTagAtOne + (int)i);
        pItem->setMovableItemDelegate(this);
        int zOrder =  rand() % 10 + 1;
        addChild(pItem, zOrder);
        pItem->startZorder = zOrder;
    }
}

void SortToys::ItemDidBackToStartLocation(MovableItem *pItem) {
    bool flag = false;
    if (abs(pItem->getTag() - kBlocksTagAtOne) <= 5) {
        if (blockRect.containsPoint(pItem->getPosition())) {
            flag = true;
        }
    }else if (abs(pItem->getTag() - kDollsTagAtOne) <= 5) {
        if (dollsRect.containsPoint(pItem->getPosition())) {
            flag = true;
        }
    }else if (abs(pItem->getTag() - kCarsTagAtOne) <= 5) {
        if (carRect.containsPoint(pItem->getPosition())) {
            flag = true;
        }
    }
    if (flag == false) {
        pItem->runAction(CCSequence::create(CCMoveTo::create(0.3f, pItem->getStartLocation()), CCCallFuncO::create(this, callfuncO_selector(SortToys::setZorderforItem), pItem),NULL));
    }else {
        pItem->startZorder = 9;
        pItem->setTouchable(false);
        pItem->runAction(CCSequence::create(CCMoveTo::create(0.3f, pItem->getStartPos()), CCCallFuncO::create(this, callfuncO_selector(SortToys::setZorderforItem), pItem),CCCallFunc::create(this, callfunc_selector(SortToys::checkToyCount)),NULL));
    }
}
void SortToys::setZorderforItem(MovableItem *pItem) {
    pItem->setZOrder(pItem->startZorder);
}

void SortToys::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    CCRect itemRect = pItem->boundingBox();
    itemRect.origin = itemRect.origin + detla;
    if (STVisibleRect::JudgeContain(STVisibleRect::getMovableRect(), itemRect)) {
        pItem->setPosition(pItem->getPosition() + detla);
    }
}

void SortToys::itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch) {
    pItem->stopAllActions();
    pItem->setZOrder(11);
}

void SortToys::checkToyCount(){
    SortRoomLayer* layer = dynamic_cast<SortRoomLayer*>(_parent);
    if (layer->theOrder == SortRoomLayer::kRandom) {
        layer->theOrder = SortRoomLayer::kSort;
    }
    allToyCount = allToyCount - 1;
    if (allToyCount <= 0) {
        WellDoneLayer* wellDonLayer = WellDoneLayer::createWithBoolen(true);
        wellDonLayer->setDelegate(this);
        wellDonLayer->showINtheNode(this);
    }
}

void SortToys::onNextBtnClicked(){
    GameLayerBase::onNextBtnClicked();
    CCDirector::sharedDirector()->popScene();
}

void SortToys::onResetBtnClicked(){
    GameLayerBase::onResetBtnClicked();
    resetpItems(kBlocksTagAtOne, DataContainer::getInstance()->getBlocks().size());
    resetpItems(kDollsTagAtOne, DataContainer::getInstance()->getDolls().size());
    resetpItems(kCarsTagAtOne, DataContainer::getInstance()->getCars().size());
}

void SortToys::resetpItems(int tag, int count) {
    srand((unsigned)time(0));
    for (int i = tag; i < count; ++i) {
        MovableItem* pItem = (MovableItem*)getChildByTag(tag + i);
        pItem->setTouchable(true);
        pItem->setPosition(pItem->getStartLocation());
        pItem->startZorder = rand() % 10 + 1;
        pItem->setZOrder(pItem->startZorder);
    }
    allToyCount += count;
}

