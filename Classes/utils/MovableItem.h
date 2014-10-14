//
//  MovableItem.h
//  LibDoctor
//
//  Created by tanshoumei on 13-10-14.
//
//

#ifndef __LibDoctor__MovableItem__
#define __LibDoctor__MovableItem__

#include <iostream>
#include "ItemBase.h"
using namespace std;
/*
 可移动工具.
 一、起点：需设置，和初始位置一样。
 二、移动范围，需要设置，默认屏幕内。
 三、触摸结束处理
 1.移动到哪就在哪停下；
 2.移动到哪，惯性前移然后停下；
 3.无论移动到哪，回到起点位置；
 */

enum MovableItemTouchEndType{
    //触摸结束原地停下
    kMovableItemTouchEndStop,
    //触摸结束惯性前移
    kMovableItemTouchEndInertia,
    //触摸结束回到起点
    kMovableItemTouchEndBackStart
};

enum MovableItemState
{
    //静止状态
    kMovableItemStateStill,
    //随手触摸移动状态
    kMovableItemStateHandMoving,
    //放手返回初始位置状态
    kMovableItemStateBackMoving
};

//MovableItem回调代理类
class MovableItem;
class MovableItemDelegate: public ItemTouchDelegate
{
public:
    //物体回到初始位置回调
    virtual void ItemDidBackToStartLocation(MovableItem* pItem){}
    //物体被点击，但未移动，可用于工具点击事件
    virtual void itemDidClicked(MovableItem* pItem){}
    //响应applicationEnterForground, applicationbecomeActinve
    virtual void itemDidBecomActive(MovableItem* pItem){}
    //响应move事件
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla){}
    
};

class MovableItem: public ItemBase {
public:
    //creator
    static MovableItem* create(const char* apName);
    static MovableItem* createWithTexture(CCTexture2D* texture);
    //constructor.
    MovableItem();
    ~MovableItem();
    
    virtual void onEnter();
    virtual void onExit();
    
    virtual bool initWithFile(const char *pszFilename);
    virtual bool initWithTexture(cocos2d::CCTexture2D *pTexture);
    //override.
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    //根据移动的坐标改变工具的位置
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    //触摸结束处理
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void setMovableItemDelegate(MovableItemDelegate* apDelegate);
    
    //工具起始位置
    void setStartLocation(const CCPoint aPt);
    CCPoint getStartLocation();
    
    //设置静止的名称
    void setStillName(std::string asName);
    //手移动状态的图片名称
    void setMovingName(std::string asName);
    
    //设置选中的音效
    void setSelectSoundEffect(std::string asName);
    //设置移动过程的音效
    void setMovingSoundEffect(std::string asName);
    //设置移动音效是否需要重复播放，默认为重复播放
    void setMovingSoundEffectLoop(bool aLoop);
    
    //移动限制区域
    void setMoveRect(const CCRect aRect);
    
    //触摸结束处理类型
    void setTouchEndHandleType(const int aType);
    
    //回到起始点
    void backToStartLocation();
    
    //变身之手移动状态
    void changeToMoving();
    
    //移动范围
    CCRect getmovableRect();
    
    void setTouchable(bool abValue);
    
    //自由设置的属性值
    bool isFlipX;
    int startZorder;
protected:
    //程序激活通知
    virtual void _onApplicationWillEnterForeground(cocos2d::CCObject *apObj);
    //触摸结束干的事情
    virtual void _touchEndDoing();
    //停止所有音效
    void _stopSoundEffect();
protected:
    //惯性前移
    void _inertiaFront();
    //变身之回到初始状态
    void _changeToInit();
    //变身之归位途中
    void _changeToBacking();
    //物体归位完成回调
    void _itemBackEnd();
protected:
    MovableItemDelegate* m_pMovableItemDelegate;
    //起点坐标
    CCPoint m_tStartLocation;
    //移动区域
    CCRect m_tMoveRect;
    //保存当前运动(1.回到起点，或者2.惯性前移)指针，开始新的move action时，可以方便的停止旧的，防止多个move action混杂
    CCActionInterval* m_pMove;
    //触摸结束处理类型
    int m_iTouchEndType;
    //初始状态名称
    string m_sInitName;
    //手移动状态名称
    string m_sMovingName;
    //选中音效
    string m_sSelectSoundEffect;
    //选中音效播放id,用于停止音效使用。<=0表示未播放
    unsigned int m_uiSelectEffectId;
    //移动音效
    string m_sMovingSoundEffect;
    //移动音效播放id,用于停止音效使用。<=小于0表示未播放
    unsigned int m_uiMovingEffectId;
    //物体当前状态
    int m_enState;
    //移动音效重复性
    bool m_bMovingLoop;
};

#endif /* defined(__LibDoctor__MovableItem__) */
