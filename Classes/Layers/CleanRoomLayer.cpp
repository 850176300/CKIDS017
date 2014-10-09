//
//  CleanRoomLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-9.
//
//

#include "CleanRoomLayer.h"
#include "DragItemLayer.h"
#include "Scribble.h"

CCScene* CleanRoomLayer::scene(){
    CCScene* scene = CCScene::create();
    
    CleanRoomLayer* layer = CleanRoomLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool CleanRoomLayer::init(){
    if (GameLayerBase::initWithBgFileName(CleanRoomBGPath)) {
        addallDust();
        addAlltools();
        return true;
    }
    return false;
}

void CleanRoomLayer::addAlltools(){
    string toolStrs[5] = {"cleaning/tool/dusting.png","cleaning/tool/cleaner.png","cleaning/tool/atomizing.png","cleaning/tool/besom.png","cleaning/tool/mop.png"};
    CCArray* tools = CCArray::createWithCapacity(5);
    for (int i = 4; i>=0; --i) {
        MovableItem* broom1 = MovableItem::create(toolStrs[i].c_str());
        broom1->setMovableItemDelegate(this);
        broom1->setTouchable(true);
        broom1->setTouchEndHandleType(kMovableItemTouchEndStop);
        broom1->setTag(kBroomToolTags+i);
        tools->addObject(broom1);
    }
    toolsLayer = DragItemLayer::createWithArray(DragItemLayer::kDragLayerVertical, tools);
    toolsLayer->setFrame("ui/cleaning_menu.png");
    toolsLayer->setPosition(STVisibleRect::getOriginalPoint());
    addChild(toolsLayer, 10);
    
    
}

void CleanRoomLayer::addallDust(){
    Scribble*  _scribble = new Scribble(CCSprite::create("burshes/solid_brush.png"));
    _scribble->setBrushShader();
    _scribble->setTargetSolid(true);
    _scribble->setTargetAlphaTestValue(0.0f);
    _scribble->setBrushType(eScribbleBrushTypeEaser);
    
    dust1 = DaubSprite::create(_scribble, CCSprite::create("cleaning/dust_5.png"));
    dust1->setAnchorPoint(ccp(0, 0.5));
    dust1->setPosition(ccp(STVisibleRect::getOriginalPoint().x+120, STVisibleRect::getPosition(110.50, 451.5).y));
    dust1->show();
    addChild(dust1, 10);
    
    dust2 = DaubSprite::create(_scribble, CCSprite::create("cleaning/dust_6.png"));
    dust2->setPosition(STVisibleRect::getPosition(301.0, 515.5));
    dust2->show();
    addChild(dust2);
    
    dust3 = DaubSprite::create(_scribble, CCSprite::create("cleaning/dust_8.png"));
    dust3->setAnchorPoint(ccp(0.5f, 1.0f));
    dust3->setPosition(ccp(STVisibleRect::getPosition(403.5, 697.0).x, STVisibleRect::getPointOfSceneLeftUp().y-70));
    dust3->show();
    addChild(dust3, 1);
    
    dust4 = DaubSprite::create(_scribble, CCSprite::create("cleaning/dust_7.png"));
    dust4->setAnchorPoint(ccp(0.5f, 1.0f));
    dust4->setPosition(STVisibleRect::getPosition(527.5, 572.5));
    dust4->show();
    addChild(dust4, 1);
    
    dust5 = DaubSprite::create(_scribble, CCSprite::create("cleaning/dust_4.png"));
    dust5->setAnchorPoint(ccp(0.5f, 1.0f));
    dust5->setPosition(STVisibleRect::getPosition(439, 162.5));
    dust5->show();
    addChild(dust5, 1);
    
    dust6 = DaubSprite::create(_scribble, CCSprite::create("cleaning/dust_1.png"));
    dust6->setAnchorPoint(ccp(1.0f, 0.5f));
    dust6->setPosition(ccp(STVisibleRect::getPointOfSceneRightUp().x-20, STVisibleRect::getPosition(897, 127.5).y));
    dust6->show();
    addChild(dust6, 1);
}


void CleanRoomLayer::ItemDidBackToStartLocation(MovableItem *pItem) {
    toolsLayer->runAction(CCSequence::create(CCMoveBy::create(0.1f, ccp(500, 0)), CCCallFuncO::create(this, callfuncO_selector(CleanRoomLayer::showtoolLayer), pItem),NULL));
}

void CleanRoomLayer::showtoolLayer(MovableItem *pItem) {
    pItem->removeFromParentAndCleanup(false);
    toolsLayer->addItemtoContainer(pItem);
    CleanRoomLayerTags tag = (CleanRoomLayerTags)pItem->getTag();
    switch (tag) {
        case kBroomToolTags:
        {
            if (dust1->easePercent() > 0.95) {
                dust1->eraserFinished = true;
            }
            if (dust2->easePercent() > 0.95) {
                dust2->eraserFinished = true;
            }
            if (dust3->easePercent() > 0.95) {
                dust3->eraserFinished = true;
            }
            if (dust4->easePercent() > 0.95) {
                dust4->eraserFinished = true;
            }
            if (dust1->eraserFinished == true && dust2->eraserFinished == true &&
                dust3->eraserFinished == true && dust4->eraserFinished == true) {
                pItem->setTouchable(false);
                CCSprite* draw = CCSprite::create("ui/prompt/draw.png");
                draw->setPosition(ccp(pItem->getContentSize().width/2.0, pItem->getContentSize().height/2.0));
                pItem->addChild(draw);
            }
        }
            break;
            
        default:
            break;
    }
}
void CleanRoomLayer::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    if (STVisibleRect::getMovableRect().containsPoint(pItem->getPosition() + detla + ccp(pItem->getContentSize().width/2.0, 0))) {
        pItem->setPosition(pItem->getPosition()+detla);
    }
    switch (pItem->getTag()) {
        case kBroomToolTags:
        {
            CCPoint startP = pItem->getPosition() - detla + ccp(pItem->getContentSize().width/2.0, 0);
            CCPoint endP = pItem->getPosition() + ccp(pItem->getContentSize().width/2.0, 0);
            dust1->paint(endP, startP);
            dust2->paint(endP, startP);
            dust3->paint(endP, startP);
            dust4->paint(endP, startP);
            dust5->paint(endP, startP);
            dust6->paint(endP, startP);
        }
            break;
            
        default:
            break;
    }
}

void CleanRoomLayer::itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch) {
    
    pItem->removeFromParentAndCleanup(false);
    pItem->setStartPos(pItem->getPosition());
    pItem->setPosition(toolsLayer->convertToWorld(pItem->getPosition()));
    this->addChild(pItem, 10);
    toolsLayer->runAction(CCMoveBy::create(0.3f, ccp(-500, 0)));

}

