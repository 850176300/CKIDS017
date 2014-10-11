//
//  MainMenu.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-12.
//
//

#include "MainMenu.h"
#include "Baby.h"
CCScene* MainMenu::scene(){
    CCScene* scene = CCScene::create();
    
    MainMenu* layer = MainMenu::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool MainMenu::init(){
    if (GameLayerBase::initWithBgFileName(MainMenuBGPath, false)) {
        MyItemSprite* startBtn = MyItemSprite::menuItems(MainMenuPlayPath);
        startBtn->setPosition(MainMenuStartPos);
        startBtn->setTarget(this, menu_selector(MainMenu::onBtnClicked));
        startBtn->setTag(kMMStarttag);
        
        stringstream soundStream;
        if (SoundPlayer::getInstance()->isMusicOpen()) {
            soundStream<<MainMenuSoundOnPath;
        }else {
            soundStream<<MainMenuSoundOffPath;
        }
        MyItemSprite* soundBtn = MyItemSprite::menuItems(soundStream.str().c_str());
        soundBtn->setTarget(this, menu_selector(MainMenu::onBtnClicked));
        soundBtn->setTag(kMMSoundTag);
        soundBtn->setPosition(MainMenuSoundPos);
        
        MyItemSprite* shopBtn = MyItemSprite::menuItems(MainMenuShopPath);
        shopBtn->setPosition(ccpAdd(MainMenuSoundPos, ccp(-MainMenuButtonSep, 0)));
        shopBtn->setTarget(this, menu_selector(MainMenu::onBtnClicked));
        shopBtn->setTag(kMMShopTag);
        

        
        MyItemSprite* moregameBtn = MyItemSprite::menuItems(MainMenuMoreGamePath);
        moregameBtn->setPosition(ccpAdd(MainMenuSoundPos, ccp(MainMenuButtonSep, 0)));
        moregameBtn->setTarget(this, menu_selector(MainMenu::onBtnClicked));
        moregameBtn->setTag(kMMMoreTag);
        
        
        if (WithOutShop) {
            soundBtn->setPosition(shopBtn->getPosition());
            SMMenu* allBtns = SMMenu::create(startBtn,soundBtn, moregameBtn, NULL);
            allBtns->setAnchorPoint(ccp(0, 0));
            allBtns->setPosition(ccp(0, 0));
            addChild(allBtns, 10);
        }else {
            SMMenu* allBtns = SMMenu::create(startBtn,shopBtn,soundBtn, moregameBtn, NULL);
            allBtns->setAnchorPoint(ccp(0, 0));
            allBtns->setPosition(ccp(0, 0));
            addChild(allBtns, 10);
        }
        //添加渲染场景node
        CCSprite* logoSprite = CCSprite::create("ui/home_logo_1.png");
        logoSprite->setAnchorPoint(ccp(0, 1.0));
        logoSprite->setPosition(ccpAdd(STVisibleRect::getPointOfSceneLeftUp(), ccp(20, 100)));
        addChild(logoSprite, 9);
        
        //旋转光圈。
        logo2Sprite = CCSprite::create("ui/home_logo_2.png");
        logo2Sprite->setPosition(ccpAdd(logoSprite->getPosition(), ccp(250, -260)));
        addChild(logo2Sprite, 8);
        
        
       
        return true;
    }
    return false;
}


void MainMenu::onEnter(){
    GameLayerBase::onEnter();
//    CCTextureCache::sharedTextureCache()->removeUnusedTextures();
}

void MainMenu::onExit(){
    GameLayerBase::onExit();
    
}

void MainMenu::onEnterTransitionDidFinish(){
    GameLayerBase::onEnterTransitionDidFinish();
    CCRepeatForever* foreverAction = CCRepeatForever::create(CCRotateBy::create(4.0f, 360));
    logo2Sprite->runAction(foreverAction);
}

void MainMenu::onBtnClicked(cocos2d::CCObject *pObj) {
    CCNode* pNode = dynamic_cast<CCNode*>(pObj);
    switch (pNode->getTag()) {
        case kMMStarttag:
        {
            GameController::getInstance()->gotoChooseRole();
        }
            break;
        case kMMSoundTag:
        {
            SoundPlayer::getInstance()->switchVolume();
            stringstream soundStream;
            if (SoundPlayer::getInstance()->isMusicOpen()) {
                soundStream<<MainMenuSoundOnPath;
            }else {
                soundStream<<MainMenuSoundOffPath;
            }
            CCSprite* btnSprite = CCSprite::create(soundStream.str().c_str());
            CCSprite* btnSprite1 = CCSprite::create(soundStream.str().c_str());
            btnSprite1->setColor(ccGRAY);
            MyItemSprite* soundButton = dynamic_cast<MyItemSprite*>(pObj);
            soundButton->setNormalImage(btnSprite);
            soundButton->setSelectedImage(btnSprite1);
        }
            break;
        case kMMShopTag:
        {
//            Baby* baby = Baby::createWithParams(0);
//            baby->setPosition(ccp(200, 200));
//            addChild(baby, 12);
        }
            break;
        case kMMMoreTag:
        {
            STSystemFunction st;
            st.showMoreGame();
        }
            break;
        default:
            break;
    }
}
