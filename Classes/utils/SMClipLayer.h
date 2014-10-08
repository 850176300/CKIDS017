//
//  SMClipLayer.h
//  Doctor
//
//  Created by tanshoumei on 13-8-29.
//
//

#ifndef __Doctor__SMClipLayer__
#define __Doctor__SMClipLayer__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;
/*
 可裁切层，设定区域，让该Layer只显示区域内的视图
 *局限：可见区域是以左下角为固定参考点，还未根据当前层的位置作相对计算。
 **/
class SMClipLayer: public CCLayer
{
public:
    static SMClipLayer* createWithViewRect(CCRect aRect);
    bool initWithViewRect(CCRect aRect);
    //set clip state. It's enabled when initinized.
    void enableClip(bool abValue);
    //设定可视区域()
    void setClipRect(CCRect aRect);
    //获取可视区域
    CCRect getClipRect();
protected:
    void beforeDraw();
    void afterDraw();
    virtual void visit();
protected:
    CCRect m_ViewRect;
    bool m_bClipEnable;
};

#endif /* defined(__Doctor__SMClipLayer__) */
