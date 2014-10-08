//
//  WashClothes.h
//  CKIDS017
//
//  Created by liuwei on 14-9-24.
//
//

#ifndef __CKIDS017__WashClothes__
#define __CKIDS017__WashClothes__

#include <iostream>
#include "GameLayerBase.h"
#include "cocos2d.h"
#include "MovableItem.h"
USING_NS_CC;

class WashClothes: public GameLayerBase, public MovableItemDelegate{
    enum WashClothesTAGs{
        kcolourClothesTag = 3331,
        kwhiteClothesTag = 33331,
        kLaundryTag1 = 331,
        kLaundryTag2,
        kSortedColorClothes,
        kSortedWhiteClohtes,
        kPowderParticleTag,
        kWashDoneColorClothes,
        kWashDoneWhiteClothes,
    };
    
    enum WashStep{
        kSortClothes = 31,
        kWashClothe1,//彩色衣服
        kWashClothe2,//白色衣服
        kWashWellDone,
    };
    
    enum WashingStep{
        kwashing1 = 311,
        kwashing2,
        kwashdone,
    };
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(WashClothes);
    virtual void onEnter();
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    virtual void itemTouchDidBegan(ItemBase* pItem, CCTouch *pTouch);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
private:
    WashStep currentStep;
    int movedCount;
    MovableItem* laundry1;//洗衣液的定义
    MovableItem* laundry2;
    vector<CCPoint> clothePP1;//将所有坐标保存
    vector<CCPoint> clothePP2;//
    CCRect colorRect;//彩色衣服的放置矩形框
    CCRect whiteRect;//白色衣服的放置矩形框
    CCLayer* colorNode;//将彩色衣服放置在node中
    CCLayer* whiteNode;//将白色衣服放置在node中
    void perFormByStep();
    void loadAllPoint();
    void addAllClothes();
    void addplant();
    void setItemcanMove(MovableItem* pItem);
    void setMenuItemCanTouch(CCMenuItem* pItem);
    void backtoStartZorder(MovableItem* pItem);
    void addTwoBasket();
    void addBaby();
    void showTip();
    void sortedSucceed();//整理衣服完毕
    //洗衣机进入场景
    CCSprite* washer;
    MyItemSprite* powderContainer;//洗衣粉容器
    MyItemSprite* powerButton;
    CCSprite* washerDoor;//洗衣机门
    void powderClicked();
    void powerBtnClicked();
    void runCloseAnimation();
    void runOpenAnimation();
    void handTip(CCDelayTime* delay,cocos2d::CCNode *pNode, CCAction* pAction);//手指提示玩家去移动衣服
    //洗衣粉跳动的动画
    void loopJumpAction(CCSprite* goalNode, int index);
    void updatepowder();
    int powderCount;
    CCRect drawerRect;//装洗衣粉的抽屉区域
    void restorePowderContainer();
    void updateWashing(float dt);
    CCSpeed* washSpeed;
    bool flag;//表示加速还是减速转动
    int washCount;//记录洗衣机洗衣服的次数
    WashingStep washingStepNow;
    bool colorClotesWashDone;
    bool whiteClothesWashDone;
    void playWellDone();
    void showWellDoneLayer();
};
#endif /* defined(__CKIDS017__WashClothes__) */
