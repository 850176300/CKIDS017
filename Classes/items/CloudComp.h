//
//  CloudComp.h
//  CKIDS017
//
//  Created by liuwei on 14-9-22.
//
//

#ifndef __CKIDS017__CloudComp__
#define __CKIDS017__CloudComp__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CloudComp : public CCComponent{
public:
    CloudComp();
private:
    bool shouldScaleLittle;
    float px,py;
    virtual void update(float dt);
};
#endif /* defined(__CKIDS017__CloudComp__) */
