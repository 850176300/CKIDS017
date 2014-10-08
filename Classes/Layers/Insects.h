//
//  Insects.h
//  CKIDS017
//
//  Created by liuwei on 14-9-18.
//
//

#ifndef __CKIDS017__Insects__
#define __CKIDS017__Insects__

#include <iostream>
#include <sstream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;
class Insects: public CCSprite{
public:
    static Insects* createWithParam(int index);
    bool initWithParam(int index);
    void runAnimation();
private:
    int index;
    string strs[3];
    
};
#endif /* defined(__CKIDS017__Insects__) */
