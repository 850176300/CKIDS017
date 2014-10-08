//
//  LittleSunComp.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-19.
//
//

#include "LittleSunComp.h"
#include "STVisibleRect.h"

USING_NS_ST;
LittleSunComp::LittleSunComp(){
    setName("LittleSunComp");
    srand(unsigned(time(0)));
    px = (rand() % 10 + 1)*20;
    py = 0;
    shouldScaleLittle = false;
}

void LittleSunComp::update(float dt) {
    CCNode* parent = getOwner();
    if (parent == NULL) {
        return;
    }
    parent->setPosition(parent->getPosition() + ccp(px*dt, -py*dt));
    if (parent->getPositionY() < STVisibleRect::getCenterOfScene().y - 50) {
        shouldScaleLittle = true;
    }
    float scale = parent->getScale();
    if (scale <= 1.0 && shouldScaleLittle == false) {
        scale += 0.04f;
    }
    if (shouldScaleLittle == true) {
        scale -= 0.05;
        if (scale <= 0) {
            scale = 0;
            parent->unscheduleUpdate();
        }
    }
    px = px - 10*dt;
    if (px < 0) {
        px = 0;
    }
    srand(unsigned(time(0)));
    py += (rand() % 20 + 30)*dt;
    parent->setScale(scale);
    if (scale == 0) {
        parent->removeFromParent();
    }
}


