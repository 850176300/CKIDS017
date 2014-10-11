//
//  WindowLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-10.
//
//

#include "WindowLayer.h"
#include "CleanRoomLayer.h"
CCScene* WindowLayer::scene(cocos2d::CCObject *pObj){
    CCScene* scene = CCScene::create();

    WindowLayer* layer = WindowLayer::createWithObj(pObj);
    
    scene->addChild(layer);
    
    return scene;
}

WindowLayer* WindowLayer::createWithObj(cocos2d::CCObject *pObj) {
    WindowLayer* pRet = new WindowLayer();
    if (pRet && pRet->initWithobj(pObj)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool WindowLayer::initWithobj(cocos2d::CCObject *pObj){
    _parent = pObj;
    _parent->retain();
    if (GameLayerBase::initWithBgFileName(WindowBGPath)) {
        CCSprite* window = CCSprite::create("bg/bg_cleaning_window.png");
        window->setPosition(STVisibleRect::getCenterOfScene());
        addChild(window, 1);
        
        addDust();
        this->scheduleOnce(schedule_selector(WindowLayer::addMopTool), 0.5f);
        return true;
    }
    return false;
}

void WindowLayer::addDust(){
    _scribble = new Scribble(CCSprite::create("burshes/solid_brush.png"));
    _scribble->setBrushShader();
    _scribble->setTargetSolid(true);
    _scribble->setTargetAlphaTestValue(0.0f);
    _scribble->setBrushType(eScribbleBrushTypeEaser);
    
    dust = DaubSprite::create(_scribble, CCSprite::create("cleaning/window/dust.png"));
    dust->setPosition(STVisibleRect::getCenterOfScene());
    dust->show();
    addChild(dust, 1);
}

void WindowLayer::addMopTool(){
    MovableItem* broom1 = MovableItem::create("cleaning/tool/atomizing.png");
    broom1->setMovableItemDelegate(this);
    broom1->setTouchable(true);
    broom1->setTouchEndHandleType(kMovableItemTouchEndStop);
    broom1->setPosition(ccp(STVisibleRect::getOriginalPoint().x - 500, STVisibleRect::getCenterOfScene().y));
    addChild(broom1, 10);
    
    broom1->runAction(CCMoveBy::create(0.3f, ccp(600, 0)));
}

void WindowLayer::ItemDidBackToStartLocation(MovableItem *pItem) {
    if (dust->easePercent() >= 0.98) {
        CCParticleSystemQuad* paritcles = CCParticleSystemQuad::create("particles/windowstar.plist");
        paritcles->setPosition(STVisibleRect::getCenterOfScene());
        addChild(paritcles ,11);
        pItem->setTouchable(false);
        pItem->runAction(CCSequence::create(CCMoveBy::create(0.5f, ccp(-STVisibleRect::getGlvisibleSize().width, 0)), CCCallFunc::create(this, callfunc_selector(GameLayerBase::showNextBtn)), CCCallFunc::create(pItem, callfunc_selector(MovableItem::removeFromParent)),NULL));
    }
}

void WindowLayer::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    if (STVisibleRect::getMovableRect().containsPoint(pItem->getPosition() + detla + ccp(pItem->getContentSize().width/2.0, 0))) {
        pItem->setPosition(pItem->getPosition()+detla);
    }
    CCPoint startP = pItem->getPosition() - detla;
    CCPoint endP = pItem->getPosition();
    dust->paint(endP, startP);
}

void WindowLayer::itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch) {
    pItem->setStartPos(pItem->getPosition());
    CCParticleSystemQuad* paritcles = CCParticleSystemQuad::create("particles/ragparticles.plist");
    paritcles->setPosition(pItem->getPosition()+ccp(pItem->getContentSize().width*0.01, pItem->getContentSize().height*0.4));
    addChild(paritcles ,11);
}

void WindowLayer::onNextBtnClicked(){
//    CCDirector::sharedDirector()-
    CleanRoomLayer* layer = dynamic_cast<CleanRoomLayer*>(_parent);
    layer->setWindowStatues(kClean);
    CCDirector::sharedDirector()->popScene();
}

