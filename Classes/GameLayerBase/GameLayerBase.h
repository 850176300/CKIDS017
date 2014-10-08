//
//  GameLayerBase.h
//  LibDoctor
//
//  Created by tanshoumei on 13-10-14.
//
//

#ifndef __LibDoctor__GameLayerBase__
#define __LibDoctor__GameLayerBase__

#include <iostream>
//#include "NormalStruct.h"
#include "SuperGlobal.h"
#include "KeypadDispatchCenter.h"
#include "ShowDialog.h"
#include "SoundPlayer.h"
#include "SMMenu.h"
#include "MyItemSprite.h"
#include "STVisibleRect.h"
#include "GameController.h"
#include "STAds.h"
#include "STSystemFunction.h"
#define kNoticeOnShopUpdate "ShopUpdateEvents"
USING_NS_ST;
enum
{
    //背景z order
    kGameLayerZBg = 0,
    //游戏元素z order,分上下两层(目前分两层就够用了)
    kGameLayerZEleBottom,
    kGameLayerZEleUp,
    //按钮类z order
    kGameLayerZUI
};

enum GameLayerBaseTags{
    kBaseNextBtn = 111,
    kBaseBackBtn,
    kBaseFavBtn,
    KBaseHomeBtn,
    kBaseListBtn,
    kBaseResetBtn,
    kBaseMapBtn,
};

/*
 游戏baseLayer, 其特点:
 1. 有可折叠的公共按钮(reset, home, music)；
 2. 有一居中放置的背景图片
 */
class GameLayerBase: public CCLayer, public KeypadDelegate
{
public:
    GameLayerBase();
    ~GameLayerBase();
    bool isShowAds;
    virtual bool init();
    virtual bool initWithBgFileName(const char* apFileName, bool showAds = true);
    virtual void onEnter();
    virtual void onExit();
    virtual void onNextBtnClicked();
    virtual void onBackBtnClicked();
    virtual void onHomeBtnClicked();
    virtual void onFavBtnClicked();
    virtual void onMapBtnClicked();
    virtual void onListBtnClicked();
    virtual void onResetBtnClicked();
    virtual void showListBtn();
    virtual void showNextBtn();
    virtual void showBackBtn();
    virtual void showHomeBtn();
    virtual void showFavBtn();
    virtual void ShowMapBtn();
    virtual void ShowResetBtn();
    void hiddenNextBtn(bool visible);
    void hiddenBackBtn(bool visible);
    void hiddenHomeBtn(bool visible);
    void hiddenFavBtn(bool visible);
    void hiddenListBtn(bool visible);
    void hiddenMapBtn(bool visible);
    void hiddenResetBtn(bool visible);
    bool isNextBenHasBeenShow();
//    virtual void onShopUpdate();
    virtual void keyBackClicked();
    void setShowAds(bool isShow);
public:
    CCSprite* m_pBg;
    
private:
    void addflyingItems();
    SMMenu* listmenu;
    bool isShowNext;
    bool isShowBack;
    bool isShowHome;
    bool isShowFav;
    bool isShowMap;
    bool isShowList;
    bool isShowReset;
//    bool isShowMaterial;
};
#endif /* defined(__LibDoctor__GameLayerBase__) */
