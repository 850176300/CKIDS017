//
//  Field.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-16.
//
//
//将每一块地申请为一个对象，对这个对象进行操作
#include "Field.h"
#include "DataContainer.h"
#include "Insects.h"
#define FieldSize CCSizeMake(448,168)
#define PERNUMBER 50

Field* Field::create(int index) {
    Field* pRet = new Field();
    if (pRet && pRet->init(index)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool Field::init(int index){
    if (CCLayer::init()) {
        this->index = index;
        setContentSize(FieldSize);
        addmud();
        firstGrowUpFinished =false;
        lastGrowUpFinished = false;
        firstCount = 0;
        waterCount = 0;
        return true;
    }
    return false;
}

void Field::onEnter(){
    CCLayer::onEnter();
    waterRect = CCRectMake(getPositionX()-30, getPositionY()-30, 60, 60);
}

CCRect Field::getWaterRect(){
    
    return waterRect;
}


void Field::addmud(){
    easerPercent = 0.98;
    _scribble = new Scribble(CCSprite::create("burshes/mub_brush.png"));
    _scribble->setBrushShader();
    _scribble->setTargetSolid(true);
    _scribble->setTargetAlphaTestValue(0.0f);
    _scribble->setBrushType(eScribbleBrushTypeEaser);
    
    char file[128];
    sprintf(file, "planting/broken_mud_%d.png", this->index);
    CCSprite* mud = CCSprite::create(file);
    mudSprite = DaubSprite::create(_scribble, mud);
    mudSprite->setPosition(ccp(FieldSize.width/2.0, FieldSize.height/2.0));
    mudSprite->show();
    addChild(mudSprite, 1);
}

void Field::setDelegate(FieldDelegate *delegate) {
    if (pDelegate != NULL) {
        pDelegate = NULL;
    }
    pDelegate = delegate;
}

void Field::setmubeaserPercent(float percent) {
    easerPercent = percent;
}

void Field::mudPaint(cocos2d::CCPoint preLocation, cocos2d::CCPoint currenPoint) {
    float percent = mudSprite->easePercent();
    CCLog("the paint percent is %.2f", percent);
    if (percent < easerPercent && mudSprite != NULL) {
        mudSprite->paint(preLocation, currenPoint);
    }else {
        if (pDelegate) {
            pDelegate->theFieldmudFinished();
        }
        CC_SAFE_DELETE(_scribble);
    }
}

void Field::addhole(){
//    if (mudSprite) {
//        mudSprite->removeFromParent();
//    }
    holeCount = -1;
    CCSprite* hole = CCSprite::create("planting/pit_0.png");
    hole->setTag(kHoleTag);
    hole->setPosition(ccp(FieldSize.width/2.0, FieldSize.height/2.0));
    addChild(hole, 2);
    hole->setScale(0);
}

bool Field::changeHole(){
    holeCount++;
    if (holeCount > 3) {
        return false;
    }else {
        CCSprite* hole = (CCSprite*)getChildByTag(kHoleTag);
        if (hole->getScale() < 1.0f) {
            hole->runAction(CCScaleTo::create(0.2f, 1.0f));
        }else {
            stringstream s;
            s<<"planting/pit_"<<holeCount<<".png";
            hole->setTexture(CCSprite::create(s.str().c_str())->getTexture());
        }
        if (holeCount == 3) {
            return false;
        }else {
            return true;
        }
    }
}

void Field::setSelectSeed(int index) {
    seedIndex = index;
    hadAddSeed = false;
}

void Field::addSeed(){
    CCSprite* seed = CCSprite::create("planting/seed_0.png");
    seed->setPosition(ccp(FieldSize.width/2.0, FieldSize.height/2.0));
    seed->setTag(kSeedTag);
    addChild(seed, 3);
    seedCount = 0;
    hadAddSeed = true;
    hadPlantSeed = false;
}

bool Field::getisAddSeed(){
    return hadAddSeed;
}

void Field::plantSeed(){
    if (getChildByTag(kSeedTag)) {
        getChildByTag(kSeedTag)->setZOrder(2);
    }
    CCSprite* hole = (CCSprite*)getChildByTag(kHoleTag);
    hole->setZOrder(3);
    seedCount++;
    stringstream s;
    s<<"planting/seed_"<<seedCount<<".png";
    CCLog("the plant seed picture is %s", s.str().c_str());
    hole->setTexture(CCSprite::create(s.str().c_str())->getTexture());
    if (seedCount == 3) {
        removeChildByTag(kSeedTag);
    }
}

void Field::addTree(){
    CCImage* tempImage = new CCImage();
    tempImage->initWithImageFile(("planting/"+DataContainer::getInstance()->getAllSeed()[seedIndex].itemName + "_1.png").c_str());
    CCTextureCache::sharedTextureCache()->addUIImage(tempImage, "treeImage");
    tempImage->release();
    CCSprite* tree = CCSprite::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("treeImage"));
    treeSize = tree->getContentSize();
    CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("treeImage"), CCRectMake(0, 0, treeSize.width, 0));
    tree->setDisplayFrame(frame);
    tree->setPosition(ccp(FieldSize.width/2.0, FieldSize.height/2.0+treeSize.height/2.0));
    addChild(tree, 4);
    tree->setTag(kTreeTag);
}

void Field::firstGrowUp(){
    firstCount++;
    if (firstCount / PERNUMBER == 1) {
        CCSprite* hole = (CCSprite*)getChildByTag(kHoleTag);
        hole->setTexture(CCSprite::create("planting/soil_1.png")->getTexture());
    }else if (firstCount / PERNUMBER == 2) {
        CCSprite* hole = (CCSprite*)getChildByTag(kHoleTag);
        hole->setTexture(CCSprite::create("planting/soil_2.png")->getTexture());
    }else if (firstCount / PERNUMBER == 3) {
        CCSprite* hole = (CCSprite*)getChildByTag(kHoleTag);
        hole->setTexture(CCSprite::create("planting/soil_3.png")->getTexture());
        if (firstCount % PERNUMBER < PERNUMBER) {
            CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("planting/soil_3.png");
            CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(texture, CCRectMake(0, 0, hole->getContentSize().width, getContentSize().height*(1.0 - firstCount%PERNUMBER/(1.0*PERNUMBER))));
            hole->setDisplayFrame(frame);
            hole->setPosition(ccpAdd(hole->getPosition(), ccp(0, 0.5f*hole->getContentSize().height*1/(1.0*PERNUMBER))));
            hole->setScaleX(1-0.8/PERNUMBER);
        }
    }else if (firstCount / PERNUMBER == 4) {
        //长成小树苗
        CCSprite* tree = (CCSprite*)getChildByTag(kTreeTag);
        CCSpriteFrame* frame = CCSpriteFrame::createWithTexture(CCTextureCache::sharedTextureCache()->textureForKey("treeImage"), CCRectMake(0, 0, treeSize.width, firstCount%50/(1.0*PERNUMBER)*treeSize.height));
        tree->setDisplayFrame(frame);
    }else if (firstCount / PERNUMBER == 5) {
        firstGrowUpFinished = true;
    }
}

void Field::addInsects(float dt){
    CCSprite* tree  = NULL;
    if (getChildByTag(kTreeTag)) {
        tree = (CCSprite*)getChildByTag(kTreeTag);
    }else {//当没有存在树枝，就创建一个tree
        tree = CCSprite::create(("planting/"+DataContainer::getInstance()->getAllSeed()[seedIndex].itemName + "_1.png").c_str());
        tree->setAnchorPoint(ccp(0.5f, 0));
        tree->setPosition(ccp(FieldSize.width/2.0, FieldSize.height/2.0));
        addChild(tree, 4);
    }
    Insects *insect1 = Insects::createWithParam(1);
    Insects* insect2 = Insects::createWithParam(2);
    insect1->setAnchorPoint(ccp(1.0, 1.0));
    insect2->setAnchorPoint(ccp(0, 1.0f));

    insect1->setOpacity(0);
    insect2->setOpacity(0);
//    insect1->setScale(0);
//    insect2->setScale(0);
    insect1->setPosition(convertToNodeSpace(tree->convertToWorldSpace(ccp(130, tree->getContentSize().height-122))));
    insect2->setPosition(convertToNodeSpace(tree->convertToWorldSpace(ccp(158, tree->getContentSize().height-103))));
    addChild(insect1, 5);
    addChild(insect2, 5);
    
    insect1->setTag(kInsects1);
    insect2->setTag(kInsects2);
    
    selectInsectTag = kHoleTag;
    insect1->runAction(CCSequence::create(CCFadeIn::create(0.3f),CCDelayTime::create(dt), CCCallFunc::create(insect1, callfunc_selector(Insects::runAnimation)), NULL));
    insect2->runAction(CCSequence::create(CCFadeIn::create(0.3f),CCDelayTime::create(dt+0.1f), CCCallFunc::create(insect2, callfunc_selector(Insects::runAnimation)), NULL));
}

bool Field::checkHaspad(cocos2d::CCPoint pp) {
    bool flag = false;
    if (getChildByTag(kInsects1)) {
        flag = getChildByTag(kInsects1)->boundingBox().containsPoint(pp);
        if (flag == true) {
            selectInsectTag = kInsects1;
            return true;
        }
    }
    if (getChildByTag(kInsects2)) {
        flag = getChildByTag(kInsects2)->boundingBox().containsPoint(pp);
        if (flag == true) {
            selectInsectTag = kInsects2;
            return true;
        }
    }
    return false;
}

void Field::insectDisAppear(){
    if (selectInsectTag == kInsects1 || selectInsectTag == kInsects2) {
        if (getChildByTag(selectInsectTag)) {
            CCSprite* insect = (CCSprite*)getChildByTag(selectInsectTag);
            insect->runAction(CCSequence::create(CCDelayTime::create(0.3f),CCFadeOut::create(0.2f), CCCallFunc::create(insect, callfunc_selector(CCSprite::removeFromParent)), NULL));
        }
    }
}

void Field::secondGrow(){
    CCSprite* tree  = NULL;
    if (getChildByTag(kTreeTag)) {
        tree = (CCSprite*)getChildByTag(kTreeTag);
    }else {//当没有存在树枝，就创建一个tree
        tree = CCSprite::create(("planting/"+DataContainer::getInstance()->getAllSeed()[seedIndex].itemName + "_1.png").c_str());
        tree->setAnchorPoint(ccp(0.5f, 0));
        tree->setPosition(ccp(FieldSize.width/2.0, FieldSize.height/2.0));
        addChild(tree, 4);
    }
    tree->setTexture(CCSprite::create(("planting/"+DataContainer::getInstance()->getAllSeed()[seedIndex].itemName + "_2.png").c_str())->getTexture());
    
}

void Field::lastGrowUp(){
    waterCount++;
    if (waterCount/100 >= 1) {
        CCSprite* tree  = NULL;
        if (getChildByTag(kTreeTag)) {
            tree = (CCSprite*)getChildByTag(kTreeTag);
        }else {//当没有存在树枝，就创建一个tree
            tree = CCSprite::create(("planting/"+DataContainer::getInstance()->getAllSeed()[seedIndex].itemName + "_2.png").c_str());
            tree->setAnchorPoint(ccp(0.5f, 0));
            tree->setPosition(ccp(FieldSize.width/2.0, FieldSize.height/2.0));
            addChild(tree, 4);
        }
        tree->setTexture(CCSprite::create(("planting/"+DataContainer::getInstance()->getAllSeed()[seedIndex].itemName + "_3.png").c_str())->getTexture());
        lastGrowUpFinished = true;
    }
}
