//
//  SelectCarLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-13.
//
//

#include "SelectCarLayer.h"
#include "cocos-ext.h"
#include "DataContainer.h"

USING_NS_CC_EXT;

CCScene* SelectCar::scene(){
    CCScene* scene = CCScene::create();
    
    SelectCar* layer = SelectCar::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool SelectCar::init(){
    if (GameLayerBase::initWithBgFileName(SelectCarBGPath)) {
        hasPlayAnimation = false;
        startx = 0;
        addScrollView();
        return true;
    }
    return false;
}

void SelectCar::addScrollView(){
    theScroll = ScrollMenu::create();
    theScroll->setViewSize(STVisibleRect::getGlvisibleSize());
    theScroll->setDirection(kCCScrollViewDirectionHorizontal);
    theScroll->setMenu(createMenu());
    theScroll->setPosition(STVisibleRect::getOriginalPoint());
    theScroll->setContentSize(CCSizeMake(startx, STVisibleRect::getGlvisibleSize().height));
    addChild(theScroll);
    
    theScroll->setContentOffset(ccp(STVisibleRect::getGlvisibleSize().width - startx, 0));
    
}

void SelectCar::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    if (hasPlayAnimation == false) {
        hasPlayAnimation = true;
        theScroll->setContentOffsetInDuration(ccp(0, 0), 1.0f);
    }
}

CCMenu* SelectCar::createMenu(){
    vector<CarItemType> allcars = DataContainer::getInstance()->getallCars();


    CCArray* allMenus = CCArray::createWithCapacity(allcars.size());
    for (vector<LockItem>::size_type i = 0; i < allcars.size(); ++i) {
        MyItemSprite* item = MyItemSprite::menuItems(("washing_cars/select_cars/"+allcars[i].itemName+".png").c_str());
        item->setAnchorPoint(ccp(0, 0));
        item->setPosition(ccp(startx, 30));
        if (allcars[i].isFree == false) {
            CCSprite* lock = CCSprite::create("ui/suo.png");
            lock->setAnchorPoint(ccp(1.0, 0));
            lock->setPosition(ccp(item->getContentSize().width-15, 15));
            item->addChild(lock);
            lock->setTag(theLockTagforAll);
        }
        item->setTag(i);
        item->setTarget(this, menu_selector(SelectCar::onItemClicked));
        startx += item->getContentSize().width + 30;
        allMenus->addObject(item);
    }
    
    return CCMenu::createWithArray(allMenus);
}

void SelectCar::onItemClicked(cocos2d::CCObject *pObj){
    MyItemSprite* menuItem = dynamic_cast<MyItemSprite*>(pObj);
    if (menuItem->getChildByTag(theLockTagforAll)) {//表示这个item加了锁按钮。说明它被锁住了

    }else {
        GameController::getInstance()->setSelectedCarIndex(menuItem->getTag());
        CCPoint thePoint = menuItem->getPosition()+ theScroll->getContentOffset() + ccp(STVisibleRect::getOriginalPoint().x, 0);
        CCLog("the position is %s", GetPointString(thePoint));
        CCSprite* selectedCar = CCSprite::createWithTexture(((CCSprite*)menuItem->getNormalImage())->getTexture());
        selectedCar->setAnchorPoint(ccp(0, 0));
        selectedCar->setPosition(thePoint + STVisibleRect::getOriginalPoint());
        addChild(selectedCar, 10);
        menuItem->setOpacity(0);
        theScroll->setTouchEnabled(false);
        theScroll->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(0, -STVisibleRect::getGlvisibleSize().height)), CCCallFunc::create(theScroll, callfunc_selector(ScrollMenu::removeFromParent)), NULL));
        selectedCar->runAction(CCSequence::create(CCDelayTime::create(0.5f), CCMoveBy::create(0.2f, ccp(0, -50)), CCMoveTo::create(0.5f, ccp(STVisibleRect::getPointOfSceneRightBottom().x, selectedCar->getPositionY()-50)),CCCallFunc::create(this, callfunc_selector(SelectCar::changeScene)), NULL));
        
    }
}

void SelectCar::changeScene(){
    GameController::getInstance()->gotoWashCar();
}













