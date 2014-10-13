//
//  JumpPandaLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-13.
//
//

#include "JumpPandaLayer.h"
#include "TipLayer.h"

CCScene* JumpPanda::scene() {
    CCScene* scene = CCScene::create();
    
    JumpPanda* layer = JumpPanda::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool JumpPanda::init(){
    if (GameLayerBase::initWithBgFileName(JumpBGPath)) {
        panda = CCSprite::create("sorting/jump/jump_toy.png");
        panda->setAnchorPoint(ccp(0.5, 0));
        panda->setPosition(STVisibleRect::getCenterOfScene() + ccp(0, STVisibleRect::getGlvisibleSize().height / 2.0 + 50));
        addChild(panda, 10);
        
        jumpItem = MovableItem::create("sorting/jump/jump_1.png");
        jumpItem->setAnchorPoint(ccp(0.5, 1.0f));
        jumpItem->setPosition(STVisibleRect::getCenterOfScene()+ccp(0, -50));
        jumpItem->setTouchable(false);
        jumpItem->setTouchEndHandleType(kMovableItemTouchEndStop);
        jumpItem->setMovableItemDelegate(this);
        addChild(jumpItem, 1);
        
        CCSprite* timerSprite = CCSprite::create("ui/prompt/time.png");
        timerSprite->setAnchorPoint(ccp(1.0, 0.5f));
        timerSprite->setPosition(ccp(-10+STVisibleRect::getPointOfSceneRightUp().x-102 - 15, STVisibleRect::getPointOfSceneRightUp().y - 15 - 109/2.0));

        addChild(timerSprite, 11);
        
        ccColor3B c1 = {96,16,133};
        timerLabel = LabelFx::createShaderLabel("00:30", "fonts/impact.ttf", 38, ccWHITE, c1,5);
        timerLabel->setPosition(timerSprite->convertToWorldSpace(ccp(timerSprite->getContentSize().width/2.0+25, timerSprite->getContentSize().height/2.0-5)));
        addChild(timerLabel, 11);
        
        showNextBtn();
        currentTimer = 30;
        timerCount = 0;
        speed = -100;
        angle = 15;
        panda->setRotation(angle);
//        CCLog("the panda position is %s", GetPointString(panda->getPosition()));
        return true;
    }
    return false;
}

void JumpPanda::onEnterTransitionDidFinish(){
    CCLayer::onEnterTransitionDidFinish();
    scheduleOnce(schedule_selector(JumpPanda::showTip), 0.5f);
}

void JumpPanda::showTip(){
    jumpItem->setTouchable(true);
    CCSprite* tip = CCSprite::create("ui/prompt/jump.png");
    TipLayer* layer = TipLayer::createWithNode(tip);
    layer->addToNode(this);
    schedule(schedule_selector(JumpPanda::updatePos), 1/30.0, kCCRepeatForever, 4.0f);
}

void JumpPanda::onNextBtnClicked() {
    GameLayerBase::onNextBtnClicked();
    CCDirector::sharedDirector()->popScene();
}

void JumpPanda::itemDidMoved(MovableItem *pItem, cocos2d::CCPoint detla) {
    float afterX = pItem->getPositionX() + detla.x;
    
    if (afterX > STVisibleRect::getOriginalPoint().x && afterX < STVisibleRect::getPointOfSceneRightBottom().x) {
        pItem->setPositionX(afterX);
    }
}

void JumpPanda::updatePos(float dt) {
// CCLog("the panda position is %s", GetPointString(panda->getPosition()));
    float speedx = speed * tan(angle * M_PI / 180.0);
    panda->setPosition(panda->getPosition() + ccp(speedx*1/30.0, speed*1/30.0));
    if (speed > 0 && panda->getPositionY() > STVisibleRect::getPointOfSceneLeftUp().y + 10) {
        srand((unsigned)time(0));
        angle = rand() % 61 - 30;
        panda->setRotation(angle);
        panda->setPositionY(STVisibleRect::getPointOfSceneLeftUp().y + 10);
        speed = -300;
    }
    speed = speed - 150*dt;
    CCRect pandaRect;
    pandaRect.origin = jumpItem->getPosition() + ccp(-jumpItem->getContentSize().width / 2.0+50, -350);
    pandaRect.size = CCSizeMake(286, 164);
    if (pandaRect.containsPoint(panda->getPosition() + ccp(0, -panda->getContentSize().height/2.0)) && speed < 0) {
        speed = -1 * speed;
        
        jumpItem->setTexture(CCSprite::create("sorting/jump/jump_2.png")->getTexture());
        runAction(CCSequence::create(CCDelayTime::create(0.2f), CCCallFuncO::create(jumpItem, callfuncO_selector(CCSprite::setTexture), CCSprite::create("sorting/jump/jump_1.png")->getTexture()), NULL));
    }else {
        if (panda->getPositionY() - fabs(panda->getContentSize().width * tan(angle * M_PI / 180.0))*0.5f < jumpItem->getPositionY() - 300) {
            //gameover。
            unschedule(schedule_selector(JumpPanda::updatePos));
            WellDoneLayer* layer = WellDoneLayer::createWithBoolen(false);
            layer->setDelegate(this);
            layer->showINtheNode(this);
        }
    }
    ++timerCount;
    if (timerCount * dt >= 1) {
        currentTimer--;
        char time[128];
        sprintf(time, "00:%d", currentTimer);
        timerLabel->setLabelString(time);
        timerCount = 0;
    }
    if (currentTimer == 0) {
        unschedule(schedule_selector(JumpPanda::updatePos));
        WellDoneLayer* layer = WellDoneLayer::createWithBoolen(true);
        layer->setDelegate(this);
        layer->showINtheNode(this);
    }
}

void JumpPanda::resetTheGame(){
    panda->setPosition(STVisibleRect::getCenterOfScene() + ccp(0, STVisibleRect::getGlvisibleSize().height / 2.0 + 50));
    speed = -100;
    angle = 15;
    currentTimer = 30;
    timerCount = 0;
    jumpItem->setPosition(STVisibleRect::getCenterOfScene()+ccp(0, -50));
    timerLabel->setLabelString("00:30");
    schedule(schedule_selector(JumpPanda::updatePos), 1/30.0, kCCRepeatForever, 0.5f);
}

#pragma mark welldonelayer delegate
void JumpPanda::onResetButtonClicked(){
    GameLayerBase::onResetBtnClicked();
    resetTheGame();
}
void JumpPanda::onRestartClick(){
    GameLayerBase::onRestartClick();
    resetTheGame();
    
}

#pragma mark 描边字体
LabelFx*  LabelFx::createShaderLabel(const char *string, const char *fontName, float fontSize, const ccColor3B &color3, ccColor3B &shadercolor, float lineWidth)
{
    //正文CCLabelTTF
    LabelFx* pRet = new LabelFx();
    if (pRet && pRet->initTheLabel(string, fontName, fontSize, color3, shadercolor, lineWidth)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }

}

bool LabelFx::initTheLabel(const char *string, const char *fontName, float fontSize, const ccColor3B &color3, ccColor3B &shadercolor, float lineWidth) {
    if (CCLabelTTF::initWithString(string, fontName, fontSize)) {
        this->lineWidth = lineWidth;
        //描边CCLabelTTF 上
        up = CCLabelTTF::create(string, fontName, fontSize);
        up->setColor(shadercolor);
        up->setPosition(ccp(getContentSize().width*0.5, getContentSize().height*0.5+lineWidth));
        addChild(up,-1);
        up->setOpacity(200);
        
        //描边CCLabelTTF 下
        down = CCLabelTTF::create(string, fontName, fontSize);
        down->setColor(shadercolor);
        down->setPosition(ccp(getContentSize().width*0.5, getContentSize().height*0.5-lineWidth));
        addChild(down,-1);
        down->setOpacity(200);
        
        //描边CCLabelTTF 左
        left = CCLabelTTF::create(string, fontName, fontSize);
        left->setPosition(ccp(getContentSize().width*0.5-lineWidth, getContentSize().height*0.5));
        left->setColor(shadercolor);
        addChild(left,-1);
        left->setOpacity(200);
        
        //描边CCLabelTTF 右
        right = CCLabelTTF::create(string, fontName, fontSize);
        right->setColor(shadercolor);
        right->setPosition(ccp(getContentSize().width*0.5+lineWidth,getContentSize().height*0.5));
        addChild(right,-1);
        right->setOpacity(200);
        
        return true;
    }
    return false;
}

void LabelFx::setLabelString(const char *string) {
    setString(string);
    up->setString(string);
    down->setString(string);
    right->setString(string);
    left->setString(string);
    up->setPosition(ccp(getContentSize().width*0.5, getContentSize().height*0.5+lineWidth));
    down->setPosition(ccp(getContentSize().width*0.5, getContentSize().height*0.5-lineWidth));
    left->setPosition(ccp(getContentSize().width*0.5-lineWidth, getContentSize().height*0.5));
    right->setPosition(ccp(getContentSize().width*0.5+lineWidth,getContentSize().height*0.5));
}


