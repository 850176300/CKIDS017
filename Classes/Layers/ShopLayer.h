//
//  ShopLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#ifndef __CKIDS017__ShopLayer__
#define __CKIDS017__ShopLayer__

#include <iostream>

#include "cocos2d.h"
#include "ScrollMenu.h"
#include "MyItemSprite.h"
USING_NS_CC;
class ShopLayer : public CCLayerColor{
    
public:
    CREATE_FUNC(ShopLayer);
    virtual bool init();
    void showinNode(CCNode* pNode);
    void removeFromNode();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    void add
private:
    MyItemSprite* restoreBtn;
    MyItemSprite* closeBtn;
    ScrollMenu* iapScrollMenu;
    CCLayer* boxLayer;
    float startY;
    void onResetoreClicked();
    CCMenu* createiapMenu(float posX);
    void onBuyItem(CCObject* pObj);
    void setTouchdisEnable();
};
#endif /* defined(__CKIDS017__ShopLayer__) */
