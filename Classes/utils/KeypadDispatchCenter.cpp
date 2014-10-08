//
//  KeypadDispatchCenter.cpp
//  HUGS108-IcePrincess Spa
//
//  Created by tanshoumei on 14-7-17.
//
//

#include "KeypadDispatchCenter.h"
static KeypadDispatchCenter* s_KeypadDispatchCenter = NULL;

KeypadDispatchCenter* KeypadDispatchCenter::getInstance()
{
    if(!s_KeypadDispatchCenter)
        s_KeypadDispatchCenter = new KeypadDispatchCenter;
    return s_KeypadDispatchCenter;
}

KeypadDispatchCenter::KeypadDispatchCenter()
{
    m_pDelegates = CCArray::create();
    m_pDelegates->retain();
}

KeypadDispatchCenter::~KeypadDispatchCenter()
{
    CC_SAFE_RELEASE_NULL(m_pDelegates);
}

void KeypadDispatchCenter::addDelegate(CCObject *apDelegate)
{
    m_pDelegates->addObject(apDelegate);
}

void KeypadDispatchCenter::removeDelegate(cocos2d::CCObject *apDelegate)
{
    m_pDelegates->removeObject(apDelegate);
}

void KeypadDispatchCenter::keyBackClicked()
{
    for (int i = m_pDelegates->count() - 1; i >= 0; --i) {
        KeypadDelegate* lpDelegate = dynamic_cast<KeypadDelegate*>(m_pDelegates->objectAtIndex(i));
        if(lpDelegate)
        {
            lpDelegate->keyBackClicked();
            break;
        }
    }
}