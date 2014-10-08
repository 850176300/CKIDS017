//
//  Field.h
//  CKIDS017
//
//  Created by liuwei on 14-9-16.
//
//

#ifndef __CKIDS017__Field__
#define __CKIDS017__Field__

#include <iostream>
#include <sstream>
#include "cocos2d.h"
#include "Scribble.h"
#include "DaubSprite.h"
using namespace std;
USING_NS_CC;

enum FieldTags{
    kHoleTag = 222,
    kSeedTag,
    kTreeTag,
    kInsects1,
    kInsects2,
};

class FieldDelegate {
public:
    virtual void theFieldmudFinished() = 0;
    virtual void theHoleDugFinished() = 0;
};

class Field : public CCLayer {
public:
    static Field* create(int index);
    bool init(int index);
    void setDelegate(FieldDelegate* delegate);
    void mudPaint(CCPoint preLocation, CCPoint currenPoint);
    void setmubeaserPercent(float percent);
    void addhole();
    bool changeHole();
    void setSelectSeed(int index);
    void addSeed();
    bool getisAddSeed();
    void plantSeed();
    CCRect getWaterRect();
//    bool hasPlantSeed();
    bool hadPlantSeed;//外部直接控制
    virtual void onEnter();
    void firstGrowUp();
    void addTree();
    bool firstGrowUpFinished;//第一阶段生长是否完成
    bool lastGrowUpFinished;//最后阶段的生长
    void addInsects(float dt);
    bool checkHaspad(CCPoint pp);
    void insectDisAppear();
    void secondGrow();
    void lastGrowUp();
private:
    FieldDelegate* pDelegate;
    int index;
    Scribble* _scribble;
    DaubSprite* mudSprite;
    float easerPercent;
    int holeCount;
    int seedCount;
    int seedIndex;//选择的种子类型
    int firstCount;//记录第一阶段生长。
    CCSize treeSize;//保存树的size
    bool hadAddSeed;
    CCRect waterRect;
    void addmud();//第一步，添加枯树叶的图层。
    FieldTags selectInsectTag;
    int waterCount;//最后阶段的浇水记录
};
#endif /* defined(__CKIDS017__Field__) */
