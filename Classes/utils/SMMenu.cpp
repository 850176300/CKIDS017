//
//  SMMenu.cpp
//  LibDoctor
//
//  Created by tanshoumei on 13-11-11.
//
//

#include "SMMenu.h"
#define NotifyGLViewWillLoseFocus "NotifyGLViewWillLoseFocus"

SMMenu* SMMenu::create()
{
    return SMMenu::create(NULL, NULL);
}

SMMenu* SMMenu::create(CCMenuItem* item, ...)
{
    va_list args;
    va_start(args,item);
    
    SMMenu *pRet = SMMenu::createWithItems(item, args);
    
    va_end(args);
    
    return pRet;
}

SMMenu* SMMenu::createWithArray(CCArray* pArrayOfItems)
{
    SMMenu *pRet = new SMMenu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

SMMenu* SMMenu::createWithItems(CCMenuItem* item, va_list args)
{
    CCArray* pArray = NULL;
    if( item )
    {
        pArray = CCArray::create(item, NULL);
        CCMenuItem *i = va_arg(args, CCMenuItem*);
        while(i)
        {
            pArray->addObject(i);
            i = va_arg(args, CCMenuItem*);
        }
    }
    
    return SMMenu::createWithArray(pArray);
}

SMMenu* SMMenu::createWithItem(CCMenuItem* item)
{
    return SMMenu::create(item, NULL);
}

void SMMenu::onEnter()
{
    CCMenu::onEnter();
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(SMMenu::_loseFocus), NotifyGLViewWillLoseFocus, NULL);
}

void SMMenu::onExit()
{
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(this, NotifyGLViewWillLoseFocus);
    CCMenu::onExit();
}

void SMMenu::_loseFocus(cocos2d::CCObject *apObj)
{
    if(m_eState == kCCMenuStateTrackingTouch)
    {
        ccTouchCancelled(NULL, NULL);        
    }
}