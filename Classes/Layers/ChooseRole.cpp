//
//  ChooseRole.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-12.
//
//

#include "ChooseRole.h"
#include "DataContainer.h"

CCScene* ChooseRole::scene(){
    CCScene* scene = CCScene::create();
    
    ChooseRole* layer = ChooseRole::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool ChooseRole::init(){
    if (GameLayerBase::initWithBgFileName(ChooseRoleBGPath)) {
        createCrollView();
        CCSprite* selete1 = CCSprite::create("bg/bg_select_1.png");
        selete1->setAnchorPoint(ccp(0, 0));
        selete1->setPosition(ccpAdd(STVisibleRect::getOriginalPoint(), ccp(-0, -00)));
        addChild(selete1);
        
        CCSprite* select2 = CCSprite::create("bg/bg_select_2.png");
        select2->setAnchorPoint(ccp(1.0, 0));
        select2->setPosition(ccpAdd(STVisibleRect::getPointOfSceneRightBottom(), ccp(00, 0)));
        addChild(select2);
        return true;
    }
    return false;
}

void ChooseRole::createCrollView(){
    scrollView = DRScrollView::create(STVisibleRect::getGlvisibleSize());
    scrollView->setTouchPriority(kCCMenuHandlerPriority-1);
    scrollView->setDirection(kCCScrollViewDirectionHorizontal);
    
    
    float deperate = 262.0;
    CCPoint startPP = ccp(STVisibleRect::getGlvisibleSize().width > (deperate*BABYNUMBER -60) ? (STVisibleRect::getGlvisibleSize().width - deperate*BABYNUMBER + 60)/2.0 + deperate /2.0:154.50 , 363);
    CCNode* container = CCNode::create();
    for (int i = 0; i < BABYNUMBER; ++i) {
        Baby* baby = Baby::createWithParams(i);
        baby->setPosition(ccpAdd(startPP, ccpAdd(STVisibleRect::getOriginalPoint(), ccp((deperate - 20)*i, 0))));
        baby->setTouchDelegate(this);
        baby->runAction(CCSequence::create(CCDelayTime::create(0.1f+0.2f*i), CCCallFunc::create(baby, callfunc_selector(Baby::runAnimation))));
        container->addChild(baby);
        if (i == 0) {
            baby->setPosition(ccpAdd(baby->getPosition(), ccp(0, 17)));
        }
    }
    container->setContentSize(CCSizeMake(deperate*BABYNUMBER, STVisibleRect::getGlvisibleSize().height));
    scrollView->setContentSize(container->getContentSize());
    scrollView->setContainer(container);
    addChild(scrollView);
    
    scrollView->setContentOffset(ccp(STVisibleRect::getGlvisibleSize().width, 0));
    scrollView->setContentOffsetInDuration(ccp(0, 0), 1.0f);
}

void ChooseRole::onBabyClicked(int index) {
    CCLog("the baby been clicked");
    if (DataContainer::getInstance()->getBabyisFree(index)) {
        scrollView->setTouchEnabled(false);
        CCDirector::sharedDirector()->getTouchDispatcher()->removeAllDelegates();
        GameController::getInstance()->setChooseIndex(index);
        GameController::getInstance()->gotoHouseLayer();
    }else {
        
    }
}


void ChooseRole::onEnter(){
    GameLayerBase::onEnter();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void ChooseRole::onEnterTransitionDidFinish(){
    GameLayerBase::onEnterTransitionDidFinish();
}

void ChooseRole::onExit(){
    GameLayerBase::onExit();
}












