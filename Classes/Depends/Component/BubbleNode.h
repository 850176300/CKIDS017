//
//  BubbleNode.h
//  BHUG023-Princess_Makeove_Salon
// 洗脸的泡泡效果
//  Created by liuhailong1 on 13-10-30.
//
//

#ifndef __BubbleNode__
#define __BubbleNode__
#include "cocos2d.h"
#include "../Application/Heads.h"
USING_NS_CC;

class BubbleNode:public CCLayerColor
{
public:
    BubbleNode(const char* bubbleFile);
    ~BubbleNode();
    static BubbleNode* create(const char* bubbleFile);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void setDuration(float);
    void setTransparent(bool);
    //泡泡出来/消失的间隔时间,单位毫秒
    void setInterval(long );
    void touchToRemove();
    //调用此方法后，如果之前是真假泡泡，将变为减少泡泡，反之，如果之前是减少，调用后将变为增加
    void convertMode();
    //获取泡泡总数
    int getBubbleCount();
    //在touch 事件触发时调用此借口
    void setCallback(CCObject* target, SEL_CallFuncND selector);
    void removeBubble(CCSprite*);
    void removeBubble(CCPoint);
    //设置泡泡的最大数目，如果超过该数目，泡泡将不再增加，0为不限制，默认为0
    void setMaxBubbles(int);
    //返回当前模式：true，增加模式，false，减少模式
    bool isAddBubble();
     void addBubble(CCPoint);
protected:
   
   
    void actionCallback(CCNode*, void*);
protected:
    CCRect nodeRect;
    long preTime;
    CCArray* bubbles;
    const char* bubbleFile;
    //动画缩放时间
    float duration;
    
    long bubbleInterval;
    bool beTransparent;
    bool beRemove;
    
    int maxBubbles;
    CCSpriteBatchNode* batchNode;
    
    CCObject*       listenerObject;
    SEL_CallFuncND    selector;
};

#endif /* defined(__BHUG023_Princess_Makeove_Salon__BubbleNode__) */
