//
//  CarItem.h
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#ifndef __CKIDS017__CarItem__
#define __CKIDS017__CarItem__

#include <iostream>
#include "cocos2d.h"
#include "SuperGlobal.h"
#include "DaubSprite.h"
#include "Scribble.h"

USING_NS_CC;

class CarItem: public CCLayerColor{
    enum CarItemTAG {
        kTire1TAG=61,
        kTire2TAG,
    };
public:
    ~CarItem(){CC_SAFE_DELETE(_scribble); CC_SAFE_DELETE(_paintScribble);};
    static CarItem* create();
    virtual bool init();
    void moveByDistance(float dt, CCPoint distance);
    void changeTiresState1();//改变轮胎的状态
    void changeTiresState2();//......
#pragma mark 洗车和修车的步骤
//1.加气步骤
    void addGas();
    void showGas();
    void hideGas();
    void removeGas();
    void judgeByPoint(CCPoint pos);//判断当前加油枪时候加进去油了
    bool getisFull();//判断汽油是否加满
//2.给车胎充气
    void addTireTip();//显示车胎加气提示
    void checkTireToolin(CCPoint pos);
    bool checkisSelected();//判断当前有没有选择轮胎
//3.水枪洗车
    void addhoseBubble();//添加水枪留下的痕迹
    void changeBubbleState();//改变水痕的透明度
    bool isHoseStepFinished();//判断水枪操作是否完成
//4.涂抹工具
    void addspongePainter();//添加涂抹图层
    void spongePanit(CCPoint prelocation, CCPoint location);
private:
    int currentZorder;
    CCSprite* mainCar;//主体---车
    CarItemType currenCar;//当前用户选择的车型
#pragma mark 轮胎变量定义
    CCSprite* tires1;
    CCSprite* tires2;
    DaubSprite* dirtyLayer;//脏东西的一层
    Scribble* _scribble;//画笔定义
    CCSprite* tireTip;//放大加油的定义
    CCSprite* tireOnTip;//提示框中的轮胎
    CCSprite* currentSelectTire;//当前选择加油的轮胎
    int tireCount;
    int tireIndex;
    bool tire1Finished;
    bool tire2Finished;
#pragma mark 加油的油孔定义
    CCSprite* gasSprite;//加油的油孔
    int gasCount;//计数用
    int gasIndex;//标志当前油箱的油
    bool gasisFull;//标志油已加满
#pragma mark 水枪操作定义
    CCSprite* waterBubble;//水痕迹定义
    bool hoseStepFinished;//水枪冲洗操作是否完成
#pragma mark 涂抹过程工具定义
    DaubSprite* sponePaniter;
    Scribble* _paintScribble;
private:
    void addTires1();//添加前面轮胎
    void addTires2();//..后面...
    void addDirtyLayer();
    void tireUpdate();//更新车胎的状态
    
};
#endif /* defined(__CKIDS017__CarItem__) */
