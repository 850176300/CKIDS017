//
//  ShopLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#include "ShopLayer.h"

bool ShopLayer::init(){
    if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 150))) {
        return true;
    }
    return false;
}




