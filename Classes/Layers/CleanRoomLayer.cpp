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
#include "DataContainer.h"
#include "WellDoneLayer.h"
#include "TipLayer.h"
CCScene* CleanRoomLayer::scene(){
    CCScene* scene = CCScene::create();
    
    CleanRoomLayer* layer = CleanRoomLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool CleanRoomLayer::init(){
    doneCount = 0;
    if (GameLayerBase::initWithBgFileName(CleanRoomBGPath)) {
        _muralState = kRandom;
        _winState = kDirty;
        DataContainer::getInstance()->sortTypes();
        addAllMurals();
        addallDust();
        addAlltools();
        addCleanerDust();
        addBroom2Items();
        addModItems();
        addWindowDust();
        addtip();
        return true;
    }
    return false;
}

void CleanRoomLayer::onEnter(){
    GameLayerBase::onEnter();
    if (_winState == kClean) {
        _winState = kCleaned;
        if (dustonWind) {
            dustonWind->removeFromParent();
            dustonWind = NULL;
        }
        if (this->getChildByTag(kRagToolTags)) {
            MovableItem* pItem = dynamic_cast<MovableItem*>(this->getChildByTag(kRagToolTags));
            this->ItemDidBackToStartLocation(pItem);
        }
    }
    if (_muralState == kSort) {
        _muralState = kSorted;
        item1->setEnabled(false);
        item2->setEnabled(false);
        item3->setEnabled(false);
        item1->setPosition(STVisibleRect::getPosition(254.5, 660.5));
        item2->setPosition(STVisibleRect::getPosition(419.6, 660.5));
        item3->setPosition(STVisibleRect::getPosition(594.5, 660.0));
        item1->setRotation(0);
        item2->setRotation(0);
        item3->setRotation(0);
        checkisDone();
    }
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

void CleanRoomLayer::addtip(){
    CCSprite* sprite = CCSprite::create("ui/prompt/clean_your_room.png");
    TipLayer *layer = TipLayer::createWithNode(sprite);
    layer->addToNode(this);
}


#pragma mark 添加所有壁画
void CleanRoomLayer::addAllMurals(){
    item1 = MyItemSprite::menuItems("cleaning/painting/painting_1.png");
    item2 = MyItemSprite::menuItems("cleaning/painting/painting_2.png");
    item3 = MyItemSprite::menuItems("cleaning/painting/painting_3.png");
    
    item1->setScale(0.45f);
    item2->setScale(0.45f);
    item3->setScale(0.45f);
    
    item1->setPosition(STVisibleRect::getPosition(254.5, 660.5));
    item2->setPosition(STVisibleRect::getPosition(419.6, 660.5));
    item3->setPosition(STVisibleRect::getPosition(594.5, 660.0));
    
    item1->setTarget(this, menu_selector(CleanRoomLayer::onPaintClicked));
    item2->setTarget(this, menu_selector(CleanRoomLayer::onPaintClicked));
    item3->setTarget(this, menu_selector(CleanRoomLayer::onPaintClicked));
    
    DeltaPositioin pos1 = DataContainer::getInstance()->getdeltaTypeAt(0);
    DeltaPositioin pos2 = DataContainer::getInstance()->getdeltaTypeAt(1);
    DeltaPositioin pos3 = DataContainer::getInstance()->getdeltaTypeAt(2);
    
    item1->setPosition(item1->getPosition() + pos1.deltaPos);
    item1->setRotation(pos1.deltaRotate);
    
    item2->setPosition(item2->getPosition() + pos2.deltaPos);
    item2->setRotation(pos2.deltaRotate);
    
    item3->setPosition(item3->getPosition() + pos3.deltaPos);
    item3->setRotation(pos3.deltaRotate);
    
    SMMenu* theMenu = SMMenu::create(item1, item2, item3, NULL);
    theMenu->setAnchorPoint(CCPointZero);
    theMenu->setPosition(CCPointZero);
    addChild(theMenu, 1);
    theMenu->setTouchPriority(kCCMenuHandlerPriority - 1);
}

void CleanRoomLayer::onPaintClicked(){
    GameController::getInstance()->gotoRoomMurals(this);
}

                     
#pragma mark tool1-笤帚
void CleanRoomLayer::addallDust(){
    _scribble = new Scribble(CCSprite::create("burshes/solid_brush.png"));
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
//

    
    spider1 = CCSprite::create("cleaning/spider_web_2.png");
    spider1->setAnchorPoint(ccp(0.5f, 1.0f));
    spider1->setPosition(ccp(STVisibleRect::getPosition(333.0, 660.5).x, STVisibleRect::getPointOfSceneLeftUp().y+50));
    addChild(spider1, 10);
    
    spider2 = CCSprite::create("cleaning/spider_web_1.png");
    spider2->setAnchorPoint(ccp(0, 0.5));
    spider2->setPosition(ccp(STVisibleRect::getOriginalPoint().x+20, STVisibleRect::getPosition(70.5, 291.0).y));
    addChild(spider2, 10);
    
    spider3 = CCSprite::create("cleaning/spider_web_3.png");
    spider3->setAnchorPoint(ccp(1.0f, 0.5f));
    spider3->setPosition(ccp(STVisibleRect::getPointOfSceneRightBottom().x, STVisibleRect::getPosition(9980, 423).y));
    addChild(spider3, 10);
    
//    CC_SAFE_DELETE(_scribble);
}

#pragma mark tool2-吸尘器
void CleanRoomLayer::addCleanerDust(){
    dust5 = CCSprite::create("cleaning/dust_4.png");
//    dust5->setAnchorPoint(ccp(0.5f, 1.0f));
    dust5->setPosition(STVisibleRect::getPosition(439, 162.5)+ccp(0, GameController::getInstance()->getBannerHeight()+50));
    addChild(dust5, 1);

    dust6 = CCSprite::create("cleaning/dust_2.png");
    dust6->setPosition(STVisibleRect::getPosition(732.5, 321.0));
    addChild(dust6, 1);
    
    dust7 = CCSprite::create("cleaning/dust_3.png");
    dust7->setPosition(STVisibleRect::getPosition(831.0, 421.5));
    addChild(dust7,1);
}

#pragma mark tool3-扫把
void CleanRoomLayer::addBroom2Items(){
    dust8 = DaubSprite::create(_scribble, CCSprite::create("cleaning/dust_1.png"));
    dust8->setAnchorPoint(ccp(1.0f, 0.0f));
    dust8->setPosition(ccpAdd(STVisibleRect::getPointOfSceneRightBottom(), ccp(-180, 70)));
    dust8->show();
    addChild(dust8, 1);
    
    paper1 = CCSprite::create("cleaning/paper_1.png");
    paper1->setPosition(STVisibleRect::getPosition(501, 202.5));
    addChild(paper1, 1);
    
    paper2 = CCSprite::create("cleaning/paper_2.png");
    paper2->setPosition(STVisibleRect::getPosition(581.5, 187.5));
    addChild(paper2, 1);
    
    paper3 = CCSprite::create("cleaning/paper_3.png");
    paper3->setPosition(ccpAdd(STVisibleRect::getPointOfSceneRightBottom(), ccp(-150, 70)));
    addChild(paper3, 1);
}

#pragma mark tool4--拖把
void CleanRoomLayer::addModItems(){
    water1 = CCSprite::create("cleaning/waterlogging_2.png");
    water1->setPosition(STVisibleRect::getPosition(363.5, 269));
    addChild(water1,1);
    
    water2 = CCSprite::create("cleaning/waterlogging_1.png");
    water2->setPosition(STVisibleRect::getPosition(659.5, 108.5) + ccp(0, GameController::getInstance()->getBannerHeight()));
    addChild(water2, 1);
}

#pragma mark tool5---喷壶
void CleanRoomLayer::addWindowDust(){
    dustonWind = CCSprite::create("cleaning/dust_9.png");
    dustonWind->setPosition(m_pBg->convertToWorldSpace(ccp(863.0, 617.0)));
    dustonWind->setScale(STVisibleRect::getRealDesignScale());
    addChild(dustonWind, 1);
}

void CleanRoomLayer::ItemDidBackToStartLocation(MovableItem *pItem) {
    toolsLayer->runAction(CCSequence::create(CCMoveTo::create(0.1f, STVisibleRect::getOriginalPoint()), CCCallFuncO::create(this, callfuncO_selector(CleanRoomLayer::showtoolLayer), pItem),NULL));
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
                dust3->eraserFinished == true && dust4->eraserFinished == true &&
                spider3->getOpacity() == 0 && spider2->getOpacity() == 0 &&
                spider1->getOpacity() == 0) {
                pItem->setTouchable(false);
                CCSprite* draw = CCSprite::create("ui/prompt/draw.png");
                draw->setPosition(ccp(pItem->getContentSize().width/2.0, pItem->getContentSize().height/2.0));
                pItem->addChild(draw);
                spider1->removeFromParent();
                spider2->removeFromParent();
                spider3->removeFromParent();
                dust1->removeFromParent();
                dust2->removeFromParent();
                dust3->removeFromParent();
                dust4->removeFromParent();
                checkisDone();
            }
        }
            break;
        case kVacuumToolTags:
        {
            if (dust5->getOpacity() == 0 && dust6->getOpacity() == 0 && dust7->getOpacity() == 0) {
                pItem->setTouchable(false);
                CCSprite* draw = CCSprite::create("ui/prompt/draw.png");
                draw->setPosition(ccp(pItem->getContentSize().width/2.0, pItem->getContentSize().height/2.0));
                pItem->addChild(draw);
                dust7->removeFromParent();
                dust6->removeFromParent();
                dust5->removeFromParent();
                checkisDone();
            }
        }
            break;
        case kBroom2ToolTags:
        {
            if (dust8->easePercent() > 0.95 && paper1->getScale() <= 0 &&
                paper2->getScale() <= 0 && paper3->getScale() <= 0) {
                pItem->setTouchable(false);
                CCSprite* draw = CCSprite::create("ui/prompt/draw.png");
                draw->setPosition(ccp(pItem->getContentSize().width/2.0, pItem->getContentSize().height/2.0));
                pItem->addChild(draw);
                dust8->removeFromParent();
                paper1->removeFromParent();
                paper2->removeFromParent();
                paper3->removeFromParent();
                checkisDone();
            }
        }
            break;
        case kMopToolTags:
        {
            if ((water1->getScale() <= 0 && water1->getOpacity() <= 0) &&
                (water2->getScale() <= 0 && water2->getOpacity() <= 0)) {
                pItem->setTouchable(false);
                CCSprite* draw = CCSprite::create("ui/prompt/draw.png");
                draw->setPosition(ccp(pItem->getContentSize().width/2.0, pItem->getContentSize().height/2.0));
                pItem->addChild(draw);
                water1->removeFromParent();
                water2->removeFromParent();
                checkisDone();
            }
        }
            break;
        case kRagToolTags:
        {
            if (_winState == kCleaned) {
                pItem->setTouchable(false);
                CCSprite* draw = CCSprite::create("ui/prompt/draw.png");
                draw->setPosition(ccp(pItem->getContentSize().width/2.0, pItem->getContentSize().height/2.0));
                pItem->addChild(draw);
                checkisDone();
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
            if (spider3->boundingBox().containsPoint(endP)) {
                float opacity = spider3->getOpacity();
                opacity -= 5;
                if (opacity <= 0) {
                    opacity = 0;
                }
                spider3->setOpacity(opacity);
            }else if (spider2->boundingBox().containsPoint(endP)) {
                float opacity = spider2->getOpacity();
                opacity -= 5;
                if (opacity <= 0) {
                    opacity = 0;
                }
                spider2->setOpacity(opacity);
            }else if (spider1->boundingBox().containsPoint(endP)) {
                float opacity = spider1->getOpacity();
                opacity -= 5;
                if (opacity <= 0) {
                    opacity = 0;
                }
                spider1->setOpacity(opacity);
            }
        }
            break;
        case kVacuumToolTags:
        {
            CCPoint endP = pItem->getPosition() + ccp(pItem->getContentSize().width/2.0, 0);
            if (dust5->boundingBox().containsPoint(endP)) {
                float opacity = dust5->getOpacity();
                opacity -= 5;
                if (opacity <= 0) {
                    opacity = 0;
                }
                dust5->setOpacity(opacity);
            }else if (dust6->boundingBox().containsPoint(endP)) {
                float opacity = dust6->getOpacity();
                opacity -= 5;
                if (opacity <= 0) {
                    opacity = 0;
                }
                dust6->setOpacity(opacity);
            }else if (dust7->boundingBox().containsPoint(endP)) {
                float opacity = dust7->getOpacity();
                opacity -= 5;
                if (opacity <= 0) {
                    opacity = 0;
                }
                dust7->setOpacity(opacity);
            }
        }
            break;
        case kBroom2ToolTags:
        {
            CCRect toolRect = CCRectMake(pItem->getPositionX(), pItem->getPositionY() - pItem->getContentSize().height/2.0, pItem->getContentSize().width, 80);
            CCPoint startP = pItem->getPosition() - detla + ccp(pItem->getContentSize().width/2.0, - pItem->getContentSize().height / 2.0);
            CCPoint endP = pItem->getPosition() + ccp(pItem->getContentSize().width/2.0, - pItem->getContentSize().height / 2.0);
            dust8->paint(endP, startP);
            if (toolRect.containsPoint(paper3->getPosition())) {
                float scale = paper3->getScale();
                scale -= 1/51.0f;
                if (scale < 0) {
                    scale = 0;
                }
                paper3->setScale(scale);
            }
            if (toolRect.containsPoint(paper2->getPosition())) {
                float scale = paper2->getScale();
                scale -= 1/51.0f;
                if (scale < 0) {
                    scale = 0;
                }
                paper2->setScale(scale);
            }
            if (toolRect.containsPoint(paper1->getPosition())) {
                float scale = paper1->getScale();
                scale -= 1/51.0f;
                if (scale < 0) {
                    scale = 0;
                }
                paper1->setScale(scale);
            }
        }
            break;
        case kMopToolTags:
        {
            CCRect toolRect = CCRectMake(pItem->getPositionX(), pItem->getPositionY() - pItem->getContentSize().height/2.0, pItem->getContentSize().width, 80);
            if (toolRect.containsPoint(water1->getPosition())) {
                float opacity = water1->getOpacity();
                float scale = water1->getScale();
                opacity -= 5;
                scale -= 1/51.0;
                if (opacity <= 0) {
                    opacity = 0;
                }
                if (scale <= 0) {
                    scale = 0;
                }
                water1->setOpacity(opacity);
                water1->setScale(scale);
            }
            if (toolRect.containsPoint(water2->getPosition())) {
                float opacity = water2->getOpacity();
                float scale = water2->getScale();
                opacity -= 5;
                scale -= 1/51.0;
                if (opacity <= 0) {
                    opacity = 0;
                }
                if (scale <= 0) {
                    scale = 0;
                }
                water2->setOpacity(opacity);
                water2->setScale(scale);
            }

        }
            break;
        case kRagToolTags:
        {
            
            if (dustonWind->boundingBox().containsPoint(pItem->getPosition()) && _winState == kDirty) {
//                this->ItemDidBackToStartLocation(pItem);
                pItem->setTouchable(false);
                GameController::getInstance()->gotoRoomWindow(this);
            }
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
    toolsLayer->runAction(CCMoveTo::create(0.3f, STVisibleRect::getOriginalPoint()+ccp(-500, 0)));

}

void CleanRoomLayer::setWindowStatues(WindowStatues state) {
    _winState = state;
}

void CleanRoomLayer::setMuralsStatues(MuralsStatues state) {
    _muralState = state;
}

void CleanRoomLayer::checkisDone(){
    doneCount = doneCount + 1;
    if (doneCount >= 6) {
        WellDoneLayer* layer = WellDoneLayer::createWithBoolen(true);
        layer->showINtheNode(this);
    }
}
