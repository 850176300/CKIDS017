
//
//  MyItemSprite.cpp
//  BBQParty
//
//  Created by liuwei on 14-9-11.
//
//

#include "MyItemSprite.h"

MyItemSprite* MyItemSprite::menuItems(const char *filename,bool needAutoChangeEnabler/* = true*/) {
    CCSprite* normalSpr = CCSprite::create(filename);
    CCSprite* selectSpr = CCSprite::create(filename);
    selectSpr->setColor(ccGRAY);
    MyItemSprite* item = new MyItemSprite();
    item->setChangeEnabler(needAutoChangeEnabler);
    if (item && item->initWithNormalSprite(normalSpr, selectSpr, NULL, NULL, NULL)) {
        item->autorelease();
        return item;
    }else {
        CC_SAFE_DELETE(item);
        return NULL;
    }
//    return item;
}

void MyItemSprite::setChangeEnabler(bool enabler) {
    autoChangeEnabler = enabler;
}
void MyItemSprite::activate(){
    CCMenuItem::activate();
    if (getParent()) {
        ((CCMenu*)getParent())->setEnabled(false);
        this->scheduleOnce(schedule_selector(MyItemSprite::setMenuEnable), 0.5f);
    }
    if (autoChangeEnabler) {
        setEnabled(false);
        this->scheduleOnce(schedule_selector(MyItemSprite::setEnbleTrue), 0.5f);
    }
    
}

void MyItemSprite::setMenuEnable(){
    if (getParent()) {
        ((CCMenu*)getParent())->setEnabled(true);
    }
}

void MyItemSprite::setEnbleTrue(){
    setEnabled(true);
}