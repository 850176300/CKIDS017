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

class CarItem: public CCNode{
public:
    static CarItem* create();
    virtual bool init();
    void moveByDistance(float dt, CCPoint distance);
    void addTires1();//添加前面轮胎
    void addTires2();//..后面...
    void changeTiresState1();//改变轮胎的状态
    void changeTiresState2();//......
    
private:
    LockItem currenCar;//当前用户选择的车型
#pragma mark 轮胎变量定义
    CCSprite* tires1;
    CCSprite* tires2;
};
#endif /* defined(__CKIDS017__CarItem__) */
