//
//  MenuSprite.h
//  BBQParty
//
//  Created by liuwei on 14-8-21.
//
//

#ifndef __BBQParty__MenuSprite__
#define __BBQParty__MenuSprite__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class MenuSprite : public CCMenuItemSprite{
private:
    bool isSelected;

public:
    MenuSprite();
    virtual void activate();
    static MenuSprite* createWithTwoFile(string file1, string file2);
    bool getIsSelected(){return isSelected;}
    void setSelected(bool selected);
};
#endif /* defined(__BBQParty__MenuSprite__) */
