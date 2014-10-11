//
//  GameController.cpp
//  BBQParty
//
//  Created by liuwei on 14-7-31.
//
//

#include "GameController.h"
#include "STAds.h"
#include "MainMenu.h"
#include "ChooseRole.h"
#include "HouseLayer.h"
#include "PlantingLayer.h"
#include "WashClothes.h"
#include "DryClothes.h"
#include "CleanRoomLayer.h"
#include "WindowLayer.h"
#include "SortMuralsLayer.h"

GameController::GameController(){
    chooseIndex = kGirlOne;
    isRemovedAD = CCUserDefault::sharedUserDefault()->getBoolForKey("isRemovedAD", false);
}

GameController::~GameController(){
    
}

void GameController::setChooseIndex(int index) {
    chooseIndex = (ModelIndex)index;
}

ModelIndex GameController::getChooseIndex(){
    return chooseIndex;
}

void GameController::setisRemoveAD(bool isRemove) {
    isRemovedAD = isRemove;
    CCUserDefault::sharedUserDefault()->setBoolForKey("isRemovedAD", isRemovedAD);
    CCUserDefault::sharedUserDefault()->flush();
}

bool GameController::isRemoveADS(){
    return isRemovedAD;
}

float GameController::getBannerHeight() {
    float bannerSize[2] = {0, 0};
    if (!isRemovedAD) {
        STAds ad;
        ad.getBannerSize(bannerSize);
    }
//    CCLog("=======the banner size width is %.2f, and the height is %.2f", bannerSize[0], bannerSize[1]);
    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) {
        return bannerSize[1]-20;
    }
    return bannerSize[1];
}

#pragma show all layers
void GameController::gotoMainMenu(bool LorR /*= false */){
    CCScene* pScene = MainMenu::scene();
    CCTransitionScene* transition = NULL;
    if (LorR) {
        transition = CCTransitionMoveInL::create(0.5f, pScene);
    }else {
        transition = CCTransitionMoveInR::create(0.5f, pScene);
    }
    if (LorR == false) {
        CCDirector::sharedDirector()->runWithScene(pScene);
    }else {
        if( CCDirector::sharedDirector()->getRunningScene() )
            CCDirector::sharedDirector()->replaceScene(transition);
        else
            CCDirector::sharedDirector()->runWithScene(transition);
    }
    
}

void GameController::gotoChooseRole(bool LorR /*= false */){
    CCScene* pScene = ChooseRole::scene();
    CCTransitionScene* transition = NULL;
    if (LorR) {
        transition = CCTransitionMoveInL::create(0.5f, pScene);
    }else {
        transition = CCTransitionMoveInR::create(0.5f, pScene);
    }

    if( CCDirector::sharedDirector()->getRunningScene() )
        CCDirector::sharedDirector()->replaceScene(transition);
    else
        CCDirector::sharedDirector()->runWithScene(transition);
}

void GameController::gotoHouseLayer(bool LorR /*= false*/) {
    CCScene* pScene = HouseLayer::scene(LorR);
    CCTransitionScene* transition = NULL;
    if (LorR) {
        transition = CCTransitionMoveInL::create(0.5f, pScene);
    }else {
        transition = CCTransitionMoveInR::create(0.5f, pScene);
    }
    
    if( CCDirector::sharedDirector()->getRunningScene() )
        CCDirector::sharedDirector()->replaceScene(transition);
    else
        CCDirector::sharedDirector()->runWithScene(transition);
}


void GameController::gotoPlanting(bool reset /*=false*/){
    CCScene* pScene = PlantingLayer::scene();
    if (reset == true) {
        if( CCDirector::sharedDirector()->getRunningScene() )
            CCDirector::sharedDirector()->replaceScene(pScene);
        else
            CCDirector::sharedDirector()->runWithScene(pScene);
    }else {
        CCTransitionScene* transition = CCTransitionMoveInR::create(0.5f, pScene);
        if( CCDirector::sharedDirector()->getRunningScene() )
            CCDirector::sharedDirector()->replaceScene(transition);
        else
            CCDirector::sharedDirector()->runWithScene(transition);
    }
}

void GameController::gotoWashClothes(bool reset /*=false*/) {
    CCScene* pScene = WashClothes::scene();
    if (reset == true) {
        if( CCDirector::sharedDirector()->getRunningScene() ){
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
        else{
            CCDirector::sharedDirector()->runWithScene(pScene);
        }
    }else {
        CCTransitionScene* transition = CCTransitionMoveInR::create(0.5f, pScene);
        if( CCDirector::sharedDirector()->getRunningScene() )
        {
            CCDirector::sharedDirector()->replaceScene(transition);
        }
        else{
            CCDirector::sharedDirector()->runWithScene(transition);
        }
    }
}

void GameController::gotoDryClothes(bool reset /*=false*/){
    CCScene* pScene = DryClothes::scene();
    if (reset == true) {
        if( CCDirector::sharedDirector()->getRunningScene() ){
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
        else{
            CCDirector::sharedDirector()->runWithScene(pScene);
        }
    }else {
        CCTransitionScene* transition = CCTransitionMoveInR::create(0.5f, pScene);
        if( CCDirector::sharedDirector()->getRunningScene() )
        {
            CCDirector::sharedDirector()->replaceScene(transition);
        }
        else{
            CCDirector::sharedDirector()->runWithScene(transition);
        }
    }
}

void GameController::gotoCleanRoom(bool reset) {
    CCScene* pScene = CleanRoomLayer::scene();
    if (reset == true) {
        if( CCDirector::sharedDirector()->getRunningScene() ){
            CCDirector::sharedDirector()->replaceScene(pScene);
        }
        else{
            CCDirector::sharedDirector()->runWithScene(pScene);
        }
    }else {
        CCTransitionScene* transition = CCTransitionMoveInR::create(0.5f, pScene);
        if( CCDirector::sharedDirector()->getRunningScene() )
        {
            CCDirector::sharedDirector()->replaceScene(transition);
        }
        else{
            CCDirector::sharedDirector()->runWithScene(transition);
        }
    }
}

void GameController::gotoRoomWindow(cocos2d::CCObject *pObj){
    CCScene* pScene = WindowLayer::scene(pObj);
    CCTransitionScene* transition = CCTransitionMoveInR::create(0.5f, pScene);
    CCDirector::sharedDirector()->pushScene(transition);
}


void GameController::gotoRoomMurals(cocos2d::CCObject *pObj) {
    CCScene* pScene = SortMuralsLayer::scene(pObj);
    CCTransitionScene* transition = CCTransitionMoveInR::create(0.5f, pScene);
    CCDirector::sharedDirector()->pushScene(transition);
}
