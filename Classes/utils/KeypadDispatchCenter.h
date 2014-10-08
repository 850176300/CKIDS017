//
//  KeypadDispatchCenter.h
//  HUGS108-IcePrincess Spa
//
//  Created by tanshoumei on 14-7-17.
//
//

#ifndef __HUGS108_IcePrincess_Spa__KeypadDispatchCenter__
#define __HUGS108_IcePrincess_Spa__KeypadDispatchCenter__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class KeypadDelegate
{
public:
    // The back key clicked
    virtual void keyBackClicked() {};
};

class KeypadDispatchCenter:public CCObject, public CCKeypadDelegate
{
public:
    static KeypadDispatchCenter* getInstance();
    
    KeypadDispatchCenter();
    ~KeypadDispatchCenter();
    
    void addDelegate(CCObject* apDelegate);
    void removeDelegate(CCObject* apDelegate);
    
    // The back key clicked
    virtual void keyBackClicked();
    
    // The menu key clicked. only available on wophone & android
    virtual void keyMenuClicked() {};
protected:
    CCArray* m_pDelegates;
};

#endif /* defined(__HUGS108_IcePrincess_Spa__KeypadDispatchCenter__) */
