//
//  DryClothes.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-26.
//
//

#include "DryClothes.h"
#include "DataContainer.h"

CCScene* DryClothes::scene(){
    CCScene* scene = CCScene::create();
    
    DryClothes* layer = DryClothes::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool DryClothes::init(){
    if (GameLayerBase::initWithBgFileName(DryClothesBGPath)) {
        CCArray* dragItems = CCArray::createWithCapacity(6);
        CCNode* _littlecontainer = CCNode::create();
        CCPoint alongPoint = ccp(0, ContainerHeight);
        CCSize _contentS = CCSizeMake(0, ContainerHeight);
        vector<DryClothe> allClothe = DataContainer::getInstance()->getallDryClothes();
        srand((unsigned)time(0));
        for (vector<DryClothe>::size_type i = 0; i < allClothe.size(); ++i) {
            char file[128];
            sprintf(file, "drying/clothes/%s.png", allClothe[i].clotheName.c_str());
            MovableItem* item = MovableItem::create(file);
            item->setTouchable(true);
            item->setTouchEndHandleType(kMovableItemTouchEndStop);
            item->setMovableItemDelegate(this);
            item->setTag(kClotheEntryFirst + i + 1);
            dragItems->addObject(item);
            
            LittleClothe* clothe = LittleClothe::createWithClothe(allClothe[i]);
            clothe->setTag(kClotheModelFirst + i + 1);
            clothe->setAnchorPoint(ccp(0, 1.0));
            clothe->setPosition(alongPoint);
            alongPoint = alongPoint + ccp(clothe->getContentSize().width+ContainerOffset, 0);
            _contentS.width = alongPoint.x;
            _littlecontainer->addChild(clothe);
        }
        _contentS.width -= 20;
        _littlecontainer->setContentSize(_contentS);
//        _littlecontainer->setPosition(ccp(0, 200));
//        addChild(_littlecontainer, 10);
        
        dragLayer = DragItemLayer::createWithArray(DragItemLayer::kDragLayerHorizontal, dragItems);
        dragLayer->setFrame("ui/drying_menu.png");
        dragLayer->setPosition(STVisibleRect::getOriginalPoint());
        addChild(dragLayer, 10);
//        dragLayer->setFrame("ui/drying_menu.png");
        
        littleClotheScrollView = CCScrollView::create(CCSizeMake(STVisibleRect::getGlvisibleSize().width, ContainerHeight));
        littleClotheScrollView->setContainer(_littlecontainer);
        littleClotheScrollView->setTouchEnabled(false);
        littleClotheScrollView->setPosition(ccpAdd(STVisibleRect::getPointOfSceneLeftUp(), ccp(0, -300)));
        addChild(littleClotheScrollView, 9);
        
        CCSprite* stringSpr = CCSprite::create("drying/string.png");
        stringSpr->setPosition(ccp(STVisibleRect::getCenterOfScene().x, STVisibleRect::getPointOfSceneLeftUp().y - 120));
        stringSpr->setScale(STVisibleRect::getRealDesignScale());
        addChild(stringSpr, 8);
        return true;
    }
    return false;
}

void DryClothes::ItemDidBackToStartLocation(MovableItem *pItem) {
//    pItem->removeFromParentAndCleanup(false);
//    dragLayer->addItemtoContainer(pItem);
    dragLayer->reloadChildren(pItem);
}

void DryClothes::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    pItem->setPosition(pItem->getPosition()+detla);
}

void DryClothes::itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch){
    pItem->removeFromParentAndCleanup(false);
    pItem->setStartPos(pItem->getPosition());
    pItem->setPosition(dragLayer->convertToWorld(pItem->getPosition()));
    this->addChild(pItem, 10);
}

#pragma mark edit listtSC
LittleClothe* LittleClothe::createWithClothe(DryClothe clothe) {
    LittleClothe* pRet = new LittleClothe();
    if (pRet && pRet->initWithClothe(clothe)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_RELEASE(pRet);
        return NULL;
    }
}

bool LittleClothe::initWithClothe(DryClothe clothe) {
//
    int r = rand();
    if (CCNode::init()) {
        char clamp1[128], clamp2[128], clothename[128];
        sprintf(clamp1, "drying/clamp/clamp_%d.png", r%2+1);
        sprintf(clamp2, "drying/clamp/clamp_%d.png", (r%4)%2+3);
        sprintf(clothename, "drying/clothes/%s_1.png", clothe.clotheName.c_str());
        ignoreAnchorPointForPosition(false);
        
        CCSprite* leftClamp = CCSprite::create(clamp1);
        CCSprite* rightClamp = CCSprite::create(clamp2);
        CCSprite* clotheSprite = CCSprite::create(clothename);
        
        setContentSize(CCSizeMake(clotheSprite->getContentSize().width, clothe.leftPoint.y+leftClamp->getContentSize().height/2.0));
        clotheSprite->setAnchorPoint(ccp(0, 0));
        clotheSprite->setPosition(ccp(0, 0));
        addChild(clotheSprite,1);
        
        leftClamp->setPosition(clotheSprite->convertToWorldSpace(clothe.leftPoint));
        rightClamp->setPosition(clotheSprite->convertToWorldSpace(clothe.rightPoint));
        addChild(leftClamp, 2);
        addChild(rightClamp, 2);
        
        clotheContentSize = clotheSprite->getContentSize();
        return true;
    }
    return false;
}

CCRect LittleClothe::getclotheBouning(){
    CCPoint original = this->convertToWorldSpace(ccp(0, 0));
    return CCRectMake(original.x, original.y, clotheContentSize.width, clotheContentSize.height);
}

void LittleClothe::additem(MovableItem *pItem) {
    
}
