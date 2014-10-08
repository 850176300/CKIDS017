//
//  MenuSprite.cpp
//  BBQParty
//
//  Created by liuwei on 14-8-21.
//
//

#include "MenuSprite.h"

MenuSprite* MenuSprite::createWithTwoFile(string file1, string file2) {
    MenuSprite *pRet = new MenuSprite();
    CCSprite* normal = CCSprite::create(file1.c_str());
    CCSprite* selected = CCSprite::create(file2.c_str());
    pRet->initWithNormalSprite(normal, selected, NULL, NULL, NULL);
    pRet->autorelease();
    return pRet;
}

MenuSprite::MenuSprite(){
    isSelected = false;
}



void MenuSprite::activate(){
//    if (isSelected != true) {
//        isSelected = true;
//    }
//    if (isSelected) {
//        this->selected();
//    }else {
//        this->unselected();
//    }
    CCMenuItem::activate();
}

void MenuSprite::setSelected(bool selected) {
    isSelected = selected;
    if (isSelected) {
        this->selected();
    }else {
        this->unselected();
    }
}




