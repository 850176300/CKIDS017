//
//  SortMuralsLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-11.
//
//

#include "SortMuralsLayer.h"
#include "DataContainer.h"
#include "CleanRoomLayer.h"
#define CENTERWIDTH 284
CCScene* SortMuralsLayer::scene(cocos2d::CCObject *pObj) {
    CCScene* scene = CCScene::create();
    
    SortMuralsLayer* layer = SortMuralsLayer::createWithObj(pObj);
    
    scene->addChild(layer);
    
    return scene;
}

SortMuralsLayer* SortMuralsLayer::createWithObj(cocos2d::CCObject *pObj) {
    SortMuralsLayer* pRet = new SortMuralsLayer();
    if (pRet && pRet->initWithObj(pObj)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool SortMuralsLayer::initWithObj(cocos2d::CCObject *pObj) {
    count = 0;
    _parent = pObj;
    _parent->retain();
    if (GameLayerBase::initWithBgFileName(PaintBGPath)) {
        for (int i = 0; i < 3; ++i) {
            char file1[128],file2[128];
            sprintf(file1, "cleaning/painting/painting_%d_1.png", i+1);
            sprintf(file2, "cleaning/painting/painting_%d.png", i+1);
            CCSprite* sprite1 = CCSprite::create(file1);
            MovableItem* item1 = MovableItem::create(file2);
            CCPoint pos = ccp(STVisibleRect::getCenterOfScene().x + (i - 1)*( 80 + sprite1->getContentSize().width/2.0 + CENTERWIDTH*0.5f), STVisibleRect::getCenterOfScene().y+50);
            sprite1->setPosition(pos);
            item1->setPosition(pos);
            item1->setStartLocation(pos);
            item1->setTag(kMurals1Tag + i);
            item1->setMovableItemDelegate(this);
            item1->setTouchable(true);
            item1->setTouchEndHandleType(kMovableItemTouchEndStop);
            
            DeltaPositioin deltaPos = DataContainer::getInstance()->getdeltaTypeAt(i);
            item1->setPosition(pos + deltaPos.deltaPos);
            item1->setRotation(deltaPos.deltaRotate);
            addChild(sprite1);
            addChild(item1, 10);
        }
        return true;
    }
    return false;
}

void SortMuralsLayer::ItemDidBackToStartLocation(MovableItem *pItem) {
    CCRect containRect;
    containRect.origin = pItem->getPosition() - ccp(50, 50);
    containRect.size = CCSizeMake(100, 100);
    if (containRect.containsPoint(pItem->getStartLocation())) {
        pItem->setTouchable(false);
        
        pItem->runAction(CCSequence::create(CCSpawn::create(CCMoveTo::create(0.3f, pItem->getStartLocation()), CCRotateTo::create(0.3f, 0), NULL), CCCallFunc::create(this, callfunc_selector(SortMuralsLayer::updateCount)),NULL));
    }else {
        DeltaPositioin deltaP = DataContainer::getInstance()->getdeltaTypeAt(pItem->getTag() - kMurals1Tag);
        pItem->runAction(CCMoveTo::create(0.3f, pItem->getStartLocation() + deltaP.deltaPos));
    }
}

void SortMuralsLayer::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    CCRect boundingBox = pItem->boundingBox();
    boundingBox.origin = boundingBox.origin + detla;
    if (STVisibleRect::JudgeContain(STVisibleRect::getMovableRect(), boundingBox)) {
        pItem->setPosition(pItem->getPosition() + detla);
    }
}

void SortMuralsLayer::itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch) {
    pItem->setZOrder(15);
}

void SortMuralsLayer::updateCount(){
    count = count + 1;
    if (count >= 3) {
        GameLayerBase::showNextBtn();
        CleanRoomLayer* layer = dynamic_cast<CleanRoomLayer*>(_parent);
        layer->setMuralsStatues(kSort);
    }
}

void SortMuralsLayer::onNextBtnClicked(){
    GameLayerBase::onNextBtnClicked();
    CCDirector::sharedDirector()->popScene();
}