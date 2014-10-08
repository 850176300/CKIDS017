//
//  MainMenu.h
//  CKIDS017
//
//  Created by liuwei on 14-9-12.
//
//

#ifndef __CKIDS017__MainMenu__
#define __CKIDS017__MainMenu__

#include <iostream>
#include <sstream>
#include "GameLayerBase.h"


enum MainMenuTags{
    kMMStarttag = 1110,
    kMMShopTag,
    kMMSoundTag,
    kMMMoreTag,
};
class MainMenu: public GameLayerBase{
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(MainMenu);
    virtual void onEnterTransitionDidFinish();
    virtual void onEnter();
    virtual void onExit();
private:
    CCSprite* logo2Sprite;
    void onBtnClicked(CCObject* pObj);
};
#endif /* defined(__CKIDS017__MainMenu__) */
