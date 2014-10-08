//
//  WellDoneLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-9-24.
//
//

#ifndef __CKIDS017__WellDoneLayer__
#define __CKIDS017__WellDoneLayer__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;
enum TapType{
    kHomeType,
    kRestartType,
};

class WellDoneLayerDelegate{
public:
    virtual void onLeftButtonClicked(TapType type)=0;
    virtual void onResetButtonClicked()=0;
};

class WellDoneLayer: public CCLayerColor{
public:
    static WellDoneLayer* createWithBoolen(bool isSucceed);
    virtual bool initWithBoolen(bool isSucceed);
    void setDelegate(WellDoneLayerDelegate* pDelegate);
    void showINtheNode(CCNode* parent);
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent) {return true;};
private:
    CCNode* itemsNode;//包含标题和按钮
    CCSprite* logoSprite;//logo图片
    bool boolenParm;
    WellDoneLayerDelegate* theDelegate;
    void onLeftBtnClicked();
    void onResetBtnClicked();
    void addParticle();
};
#endif /* defined(__CKIDS017__WellDoneLayer__) */
