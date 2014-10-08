//
//  MyItemSprite.h
//  BBQParty
//
//  Created by liuwei on 14-9-11.
//
//

#ifndef __BBQParty__MyItemSprite__
#define __BBQParty__MyItemSprite__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class MyItemSprite : public CCMenuItemSprite{
public:
    static MyItemSprite* menuItems(const char* filename, bool needAutoChangeEnabler = true);
public:
    void setChangeEnabler(bool enabler);
    virtual void activate();
private:
    bool autoChangeEnabler;
    void setEnbleTrue();
    void setMenuEnable();
};
#endif /* defined(__BBQParty__MyItemSprite__) */
