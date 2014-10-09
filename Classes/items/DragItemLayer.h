//
//  DragItemLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-9-28.
//
//

#ifndef __CKIDS017__DragItemLayer__
#define __CKIDS017__DragItemLayer__

#include <iostream>
#include "cocos2d.h"
#include "ItemBase.h"
using namespace cocos2d;

//delegate
class DragItemLayerDelegate{
public:
    virtual void onitemClicked(ItemBase* item) = 0;
};

class ClipLayer : public CCLayer{
public:
    virtual bool init();
    CREATE_FUNC(ClipLayer);
    virtual void visit();
private:
    bool m_bClippingToBounds;
    bool m_bScissorRestored;
    CCRect m_tParentScissorRect;
    void beforeDraw();
    void afterDraw();
    CCRect getViewRect();
};

class DragItemLayer: public CCLayer{
public:
    enum Direction{
        kDragLayerHorizontal = 1,
        kDragLayerVertical,
    };
public:
    static DragItemLayer* createWithArray(Direction direc,CCArray* arr);
    static DragItemLayer* create(Direction direc,ItemBase* item,...);
    static DragItemLayer* createWithItems(Direction direc,ItemBase* firstItem, va_list args);
    
    DragItemLayer(){};
    ~DragItemLayer(){
        CC_SAFE_RELEASE(itemArray);
    };
    
    bool initWithArray(Direction direc,CCArray* arr);
    
public:
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onEnter();
    virtual void onExit();

    void setFrame(const char* framePath, float widthSpace = 20, float heightSpace = 10,CCPoint pos = ccp(0, 0));
    CCPoint convertToWorld(CCPoint resPos);
    void addItemtoContainer(ItemBase* pitem);
    void reloadChildren(ItemBase* pItem);
    void scrolltoLeft(float dt = 0);
    void scrolltoRight(float dt = 0);
private:
    CCArray* itemArray;
    ClipLayer* _frame;//边框，添加背景图片和_container
    CCLayer* _container;
    Direction _direction;//方向设置变量
    CCPoint _contentOffset;//滑动偏移量
    CCSize _scrollSize;//可滑动区域
    CCSize _distanceSize;//偏离size
    CCPoint performDistance;//统计已经移动的偏移距离
    bool _canScroll;//scroll view可不可以滑动
    bool canMove;
    CCPoint beganPos;//开始点击的点
    void moveEnd(CCTouch *pTouch, CCEvent *pEvent);
    bool isbDraging;
    void deaccelerateScrolling(float dt);
    //定义出来touch事件分发
    void _dispatchTouch(CCTouch* pTouch);
    void _touchBeginSchedule(float dt);
    bool m_bTouchDispatched;
    CCTouch* m_pBeginTouch;
    float m_fTimeTouchBegin;
    bool m_bTouchDecided;
    bool m_bTouchMoved;
    CCPoint m_tTouchBeginPt;
    //clicked 委托
    DragItemLayerDelegate* pDelegate;
    
};
#endif /* defined(__CKIDS017__DragItemLayer__) */
