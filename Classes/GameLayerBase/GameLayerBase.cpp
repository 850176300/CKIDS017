//
//  GameLayerBase.cpp
//  LibDoctor
//
//  Created by tanshoumei on 13-10-14.
//
//

#include "GameLayerBase.h"
#include "CocosHelper.h"
//#include "DeviceTool.h"






GameLayerBase::GameLayerBase()
{
    
}

GameLayerBase::~GameLayerBase(){
    CCLog("the class %s consturctor========", __FUNCTION__);
    
}

bool GameLayerBase::init(){
    if (CCLayer::init()) {
        isShowBack = false;
        isShowFav = false;
        isShowHome = false;
        isShowNext = false;
        isShowMap = false;
        isShowList = false;
        isShowReset = false;
    
        return true;
    }
    return false;
}

bool GameLayerBase::initWithBgFileName(const char *apFileName, bool showAds /*= true*/)
{
    if(CCLayer::init())
    {
        //场景背景
        m_pBg = CocosHelper::AddSprite(apFileName, this, kGameLayerZBg, 0);
        STVisibleRect::setPosition(m_pBg, STVisibleRect::getDesignSize().width * .5f, STVisibleRect::getDesignSize().height * .5f);
        m_pBg->setScale(STVisibleRect::getRealDesignScale());
//        if (showAds) {
//            AdvertiseAdapter::showBannerAd();
//        }else{
//            AdvertiseAdapter::hideBannerAd();
//        }
        
        isShowAds = showAds;
        if (showAds) {
            CCLog("show the banner %s", __FUNCTION__);
        }else {
            CCLog("donnot need show banner %s", __FUNCTION__);
        }
        isShowBack = false;
        isShowFav = false;
        isShowHome = false;
        isShowNext = false;
        isShowMap = false;
        isShowList = false;
        isShowReset = false;

//        this->setKeypadEnabled(true);
        return true;
    }
    return false;
}

void GameLayerBase::setShowAds(bool isShow) {
    isShowAds = isShow;
}
void GameLayerBase::onEnter(){
    CCLayer::onEnter();
    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
    KeypadDispatchCenter::getInstance()->addDelegate(this);
    STAds* ads = new STAds();
    if (isShowAds) {
        showHomeBtn();
        if (!GameController::getInstance()->isRemoveADS()) {
            CCLog("show banner ============= %s", __FUNCTION__);
            ads->requestAds();
        }else {
            ads->removeAds();
        }
    }else{
        ads->removeAds();
    }
    delete ads;
    
}

void GameLayerBase::onExit(){
    KeypadDispatchCenter::getInstance()->removeDelegate(this);
    CCLayer::onExit();
}
void GameLayerBase::showBackBtn(){
    if (isShowBack) {
        hiddenBackBtn(true);
        return;
    }
    isShowBack = true;
    MyItemSprite* btn = MyItemSprite::menuItems("ui/btn_back.png");
    btn->setPosition(ccp(10+STVisibleRect::getOriginalPoint().x+btn->getContentSize().width/2.0, STVisibleRect::getCenterOfScene().y));
    btn->setTarget(this, menu_selector(GameLayerBase::onBackBtnClicked));
    
    SMMenu* menu = SMMenu::create(btn, NULL);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    menu->setTag(kBaseBackBtn);
    addChild(menu, 200);
    menu->setTouchPriority(-130);
}

void GameLayerBase::showHomeBtn(){
    if (isShowHome) {
//        hiddenHomeBtn(true);
        return;
    }
    isShowHome = true;
    MyItemSprite* btn = MyItemSprite::menuItems("ui/btn_home.png");
    btn->setPosition(ccp(-10+STVisibleRect::getPointOfSceneRightUp().x-btn->getContentSize().width*0.5, STVisibleRect::getPointOfSceneRightUp().y - 15 - btn->getContentSize().height/2.0));
    btn->setTarget(this, menu_selector(GameLayerBase::onHomeBtnClicked));
    
    SMMenu* menu = SMMenu::create(btn, NULL);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    menu->setTag(KBaseHomeBtn);
    addChild(menu, 200);
    menu->setTouchPriority(-130);
}
void GameLayerBase::ShowResetBtn(){
    if (isShowReset) {
        hiddenResetBtn(true);
        return;
    }
    isShowReset = true;
    MyItemSprite* btn = MyItemSprite::menuItems("btn_reset.png");
    btn->setPosition(ccp(-10+STVisibleRect::getPointOfSceneRightUp().x-btn->getContentSize().width*0.5, STVisibleRect::getPointOfSceneRightUp().y - 15 - btn->getContentSize().height/2.0));
    btn->setTarget(this, menu_selector(GameLayerBase::onResetBtnClicked));
    
    SMMenu* menu = SMMenu::create(btn, NULL);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    menu->setTag(kBaseResetBtn);
    addChild(menu, 200);
    menu->setTouchPriority(-130);
}

void GameLayerBase::showNextBtn(){
    hiddenBackBtn(false);
    if (isShowNext) {
        CCLog("======next button return!======");
        hiddenNextBtn(true);
        return;
    }
    CCLog("=====show the next button===");
    isShowNext = true;
    MyItemSprite* btn = MyItemSprite::menuItems("ui/btn_next.png");
    btn->setAnchorPoint(ccp(0.5f, 0));
    btn->setPosition(ccp(-10+STVisibleRect::getPointOfSceneRightUp().x-btn->getContentSize().width/2.0, STVisibleRect::getPointOfSceneRightBottom().y+15));
    btn->setTarget(this, menu_selector(GameLayerBase::onNextBtnClicked));
    
    SMMenu* menu = SMMenu::create(btn, NULL);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    menu->setTag(kBaseNextBtn);
    addChild(menu, 200);
    menu->setTouchPriority(-130);
//    CCSequence* sequence = CCSequence::create(CCScaleTo::create(0.2f, 0.9f), CCScaleTo::create(0.2f, 1.0f), NULL);
//    btn->runAction(CCRepeatForever::create(sequence));
    
}


void GameLayerBase::showFavBtn(){
    if (isShowFav) {
        hiddenFavBtn(true);
        return;
    }
    isShowFav = true;
    MyItemSprite* btn = MyItemSprite::menuItems("start/btn_fav.png");
    btn->setPosition(ccp(-25+STVisibleRect::getPointOfSceneRightUp().x-btn->getContentSize().width*1.5, STVisibleRect::getPointOfSceneRightUp().y - 15 - btn->getContentSize().height/2.0));
    btn->setTarget(this, menu_selector(GameLayerBase::onFavBtnClicked));
    
    SMMenu* menu = SMMenu::create(btn, NULL);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    menu->setTag(kBaseFavBtn);
    addChild(menu, 200);
    menu->setTouchPriority(-130);
}

void GameLayerBase::ShowMapBtn(){
    showListBtn();
    if (isShowMap) {
        return;
    }
    isShowMap = true;
    MyItemSprite* mapBtn = MyItemSprite::menuItems("btn_map.png");
    mapBtn->setAnchorPoint(ccp(1.0, 0));
    mapBtn->setPosition(ccpAdd(STVisibleRect::getPointOfSceneRightBottom(), ccp(-5, 5)));
    mapBtn->setTarget(this, menu_selector(GameLayerBase::onMapBtnClicked));
    
    SMMenu* menu = SMMenu::create(mapBtn, NULL);
    menu->setAnchorPoint(ccp(0, 0));
    menu->setPosition(ccp(0, 0));
    menu->setTag(kBaseMapBtn);
    addChild(menu, 200);
    menu->setTouchPriority(-130);
    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) {
        menu->setPosition(ccpAdd(menu->getPosition(), ccp(0, GameController::getInstance()->getBannerHeight())));
    }
}

void GameLayerBase::showListBtn(){
    if (isShowList) {
        hiddenListBtn(true);
        return;
    }
    isShowList = true;
    MyItemSprite* listBtn = MyItemSprite::menuItems("btn_list.png");
    listBtn->setPosition(ccpAdd(STVisibleRect::getOriginalPoint(), ccp(5+97/2.0, 5+97/2.0)));
    listBtn->setTarget(this, menu_selector(GameLayerBase::onListBtnClicked));

    listmenu = SMMenu::create(listBtn, NULL);
    listmenu->setAnchorPoint(ccp(0, 0));
    listmenu->setPosition(ccp(0, 0));
    addChild(listmenu, 200);
    listmenu->setTouchPriority(-130);
    listmenu->setTag(kBaseListBtn);
    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) {
        listmenu->setPosition(ccpAdd(listmenu->getPosition(), ccp(0, GameController::getInstance()->getBannerHeight())));
    }
}

void GameLayerBase::onResetBtnClicked(){
    CCLog("===onResetBtnClicked===");
    SoundPlayer::getInstance()->playResetClickedEffect();
}

void GameLayerBase::onListBtnClicked(){
    CCLog("===onListBtnClicked===");

}

void GameLayerBase::onNextBtnClicked(){
    CCLog("===onNextBtnClicked===");
    SoundPlayer::getInstance()->playNextClickedEffect();
}

void GameLayerBase::onBackBtnClicked(){
    CCLog("===onBackBtnClicked===");
    SoundPlayer::getInstance()->stopAllEffect();
    SoundPlayer::getInstance()->stopfryGroundMusic();
    SoundPlayer::getInstance()->stopStriGroundMusic();
    SoundPlayer::getInstance()->previousGroundMusic();
}

void GameLayerBase::onHomeBtnClicked(){
    CCLog("===onHomeBtnClicked===");

    SoundPlayer::getInstance()->selectGroundMusic();
}

void GameLayerBase::onFavBtnClicked(){

    CCLog("===onFavBtnClicked===");
    SoundPlayer::getInstance()->selectGroundMusic();
}

void GameLayerBase::onMapBtnClicked(){
    CCLog("===onMapBtnClicked===");

    SoundPlayer::getInstance()->stopAllEffect();
    SoundPlayer::getInstance()->stopfryGroundMusic();
    SoundPlayer::getInstance()->stopStriGroundMusic();
    SoundPlayer::getInstance()->selectGroundMusic();

}

void GameLayerBase::hiddenNextBtn(bool visible)
{
    if (this->getChildByTag(kBaseNextBtn)) {
        this->getChildByTag(kBaseNextBtn)->setVisible(visible);
    }
}
void GameLayerBase::hiddenBackBtn(bool visible)
{
    if (this->getChildByTag(kBaseBackBtn)) {
        this->getChildByTag(kBaseBackBtn)->setVisible(visible);
    }
}
void GameLayerBase::hiddenHomeBtn(bool visible){
    if (this->getChildByTag(KBaseHomeBtn)) {
        this->getChildByTag(KBaseHomeBtn)->setVisible(visible);
    }
}
void GameLayerBase::hiddenFavBtn(bool visible){
    if (this->getChildByTag(kBaseFavBtn)) {
        this->getChildByTag(kBaseFavBtn)->setVisible(visible);
    }
}

void GameLayerBase::hiddenResetBtn(bool visible){
    if (this->getChildByTag(kBaseResetBtn)) {
        this->getChildByTag(kBaseResetBtn)->setVisible(visible);
    }
}

void GameLayerBase::hiddenListBtn(bool visible) {
    if (this->getChildByTag(kBaseListBtn)) {
        this->getChildByTag(kBaseListBtn)->setVisible(visible);
    }
}
void GameLayerBase::hiddenMapBtn(bool visible) {
    if (this->getChildByTag(kBaseMapBtn)) {
        this->getChildByTag(kBaseMapBtn)->setVisible(visible);
    }
}

bool GameLayerBase::isNextBenHasBeenShow(){
    return isShowNext;
}




//void GameLayerBase::onShopUpdate() {
//    CCLog("recieve the shop update Events");
//}

void GameLayerBase::keyBackClicked(){
    
    CCLog("the key back  Clicked");
    
    SoundPlayer::getInstance()->stopfryGroundMusic();
    SoundPlayer::getInstance()->stopStriGroundMusic();
}