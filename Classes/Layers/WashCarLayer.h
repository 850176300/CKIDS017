//
//  WashCarLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#ifndef __CKIDS017__WashCarLayer__
#define __CKIDS017__WashCarLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "MovableItem.h"
#include "CarItem.h"
#include "ScrollMenu.h"
USING_NS_CC;
using namespace std;
class WashCar: public GameLayerBase, public MovableItemDelegate{
    enum ItemTags{
        kTripTag = 6111,
        kGasTags,
        kgasPariticlesTags,
        kBlowTags,
        kHoseTags,
        kSpongeTags,
    };
    
    enum ToolStates{
        kGasToolStep = 61,
        kBlowToolStep ,
        kHoseToolStep,
        kSpongeToolStep,
        kCleanToolStep,
        kHose2ToolStep,
        kWaxToolStep,
    };
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(WashCar);
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void itemTouchDidBegan(ItemBase *pItem, cocos2d::CCTouch *pTouch);
    virtual void onEnterTransitionDidFinish();
    void blowHandTip(bool startLocation = false);
    void finishblowstep();
private:
    ScrollMenu* washMenu;
    CCMenu* toolMenu ;//menu 工具
    ToolStates currenState;
    CarItem* myCar;
    void playHandTip();
    void setTouchItemCanTouch(MovableItem* pItem);//设置移动的元素可以被移动
    bool hasShowHandTip;
    CCSprite* garageDoor;//车库的门
    float maxDeltaY;//链子最大的y偏移
    //添加工具栏，只起指示作用
    void addtooltips();
    void moveToolTip();
    void performState();//根据当前的步骤做出反应
//1.添加汽油
    void addgasTool();
    MovableItem* gasTool;
    CCSprite* gasBox;//加油箱
    float gasmaxy , gasminy;
    CCParticleSystemQuad* oilP;
    void checkoilin();//判断是否将油加进去了
//2.车胎充气
    void addblowTool();
    MovableItem* blowTool;//充气工具
    float blowmaxX, blowminX;
    void playBlowAnimation();//播放充气动画
    void firstPlayhandTip();
//3.水枪
    MovableItem* hoseTool;//水枪工具
    CCParticleSystemQuad* waterParticle;
    float minhosey, maxhosey;//水枪移动的最大y和最小y
    void addhoseTools();
//4.涂抹工具
    MovableItem* spongeTool;//涂抹工具
    void addSpongeTool();
    
};
#endif /* defined(__CKIDS017__WashCarLayer__) */
