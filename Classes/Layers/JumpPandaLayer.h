//
//  JumpPandaLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-13.
//
//

#ifndef __CKIDS017__JumpPandaLayer__
#define __CKIDS017__JumpPandaLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "MovableItem.h"

USING_NS_CC;
class LabelFx : public CCLabelTTF{
public:
    static LabelFx* createShaderLabel(const char* string, const char* fontName, float fontSize,const ccColor3B &color3, ccColor3B &shadercolor,float lineWidth);
    void setLabelString(const char* string);
    bool initTheLabel(const char* string, const char* fontName, float fontSize,const ccColor3B &color3, ccColor3B &shadercolor,float lineWidth);
private:
    CCLabelTTF* down;
    CCLabelTTF* up;
    CCLabelTTF* left;
    CCLabelTTF* right;
    float lineWidth;//描边宽度
};
class JumpPanda : public GameLayerBase ,public MovableItemDelegate{
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(JumpPanda);
    virtual void onEnterTransitionDidFinish();
    virtual void onNextBtnClicked();
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void onResetButtonClicked();
    virtual void onRestartClick();
private:
    CCSprite* panda;//熊猫
    MovableItem* jumpItem;//移动的平台来接熊猫
    LabelFx* timerLabel;
    void showTip();
    void resetTheGame();
    void updatePos(float dt);
    //熊猫下落时候的速度和角度定义
    float speed;
    float angle;
//    float at;//加速度
    int timerCount;//记录update数量来计时
    int currentTimer;//记录当前时间
};

#endif /* defined(__CKIDS017__JumpPandaLayer__) */
