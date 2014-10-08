//
//  LittleSunComp.h
//  CKIDS017
//
//  Created by liuwei on 14-9-19.
//
//

#ifndef __CKIDS017__LittleSunComp__
#define __CKIDS017__LittleSunComp__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class LittleSunComp: public CCComponent{
public:
    LittleSunComp();
private:
    float px;
    float py;
    bool shouldScaleLittle;
    virtual void update(float dt);
    
};
#endif /* defined(__CKIDS017__LittleSunComp__) */
