//
//  ControlMenu.h
//  BHUG023-Princess_Makeove_Salon
//
//  Created by liuhailong1 on 13-10-25.
//
//

#ifndef __SHRINK_MENU__
#define __SHRINK_MENU__


#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class ShrinkMenuCallback{
public:
    virtual void onMenuClick(int index) = 0;
    virtual void onOpening() = 0;
    virtual void onClosing() = 0;
};

class ShrinkMenu:public CCLayerColor{
public:
    static const int LANDSCAPE=1;
    static const int PORTRAIT=2;
    ShrinkMenu();
    ~ShrinkMenu();
    static ShrinkMenu* create(int orientation);
    void createMenu(int count, ... );
    void setDuration(float _duration);
    void setMenuCallback(ShrinkMenuCallback*);
    void setPadding(float);
    void doOpenWithDuration();
    void doCloseWithDuration();
    void doOpen();
    void doClose();
protected:
    
    void controlMenuCallback(CCObject*);
    void actionCallback(CCNode*, void*);
private:
   
    CCActionInterval*  getAction(CCNode*);
private:
    CCArray* menuItems;
    map<CCObject*, CCPoint> originalPos;
    ShrinkMenuCallback* menuCallback;
    
    int orientation;
    bool isOpen;
    bool isLock;
    
    CCMenuItemSprite* mainItem;
    CCMenu* mainMenu;

    CCSprite*  bgBar;
    float duration;
    float menuWidth;
    float menuHeight;
    float padding;
    
};



#endif