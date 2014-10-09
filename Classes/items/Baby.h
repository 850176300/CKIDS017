//
//  Baby.h
//  CKIDS017
//
//  Created by liuwei on 14-9-12.
//
//

#ifndef __CKIDS017__Baby__
#define __CKIDS017__Baby__

#include <iostream>
#include "cocos2d.h"
#include "TouchNodeTon.h"

USING_NS_CC;
using namespace std;
enum BabyTags{
    kLockTag = 111,
};

class BabyDelegate {
public:
    virtual void onBabyClicked(int index) = 0;
};

class Baby : public TouchNode{
private:
    string normal;
    string close;
    string smile;
    int indexTag;
    BabyDelegate* pDelegate;
    
    int numofRunningActions;
    bool isSmiling;
    void stopSmile();
public:
    static Baby* createWithParams(int index, string prefix = "select_figure/");
    bool initWithParams(int index, string prefix);
    void setTouchPriority(int priority);
    void setTouchDelegate(BabyDelegate* delegate);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onEnter();
    virtual void onExit();
    void runAnimation();
    
};

#endif /* defined(__CKIDS017__Baby__) */
