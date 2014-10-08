//
//  SMMenu.h
//  LibDoctor
//
//  Created by tanshoumei on 13-11-11.
//
//

#ifndef __LibDoctor__SMMenu__
#define __LibDoctor__SMMenu__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

//CCMenu的问题：当按着一个menu item的时候，此时全屏广告弹出，待关闭全屏广告，发现menu还是处于被按中的状态，此不能再操作。
//SMMenu就是解决此问题而诞生的，无其他额外功能

class SMMenu: public CCMenu
{
public:
    /** creates an empty CCMenu */
    static SMMenu* create();
    
    /** creates a CCMenu with CCMenuItem objects */
    static SMMenu* create(CCMenuItem* item, ...);
    
    /** creates a CCMenu with a CCArray of CCMenuItem objects */
    static SMMenu* createWithArray(CCArray* pArrayOfItems);
    
    /** creates a CCMenu with it's item, then use addChild() to add
     * other items. It is used for script, it can't init with undetermined
     * number of variables.
     */
    static SMMenu* createWithItem(CCMenuItem* item);
    
    /** creates a CCMenu with CCMenuItem objects */
    static SMMenu* createWithItems(CCMenuItem *firstItem, va_list args);
    
    virtual void onEnter();
    virtual void onExit();
    
protected:
    void _loseFocus(CCObject* apObj);
};

#endif /* defined(__LibDoctor__SMMenu__) */
