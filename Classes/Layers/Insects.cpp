//
//  Insects.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-18.
//
//

#include "Insects.h"

Insects* Insects::createWithParam(int index) {
    Insects* pRet = new Insects();
    if (pRet && pRet->initWithParam(index)) {
        pRet->autorelease();
        return pRet;
    }else {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

bool Insects::initWithParam(int index) {
    stringstream s;
    s<<"planting/bug_"<<index;
    for (int i = 0; i < 3; ++i) {
        char filename[128];
        sprintf(filename, "%s_%d.png", s.str().c_str(), 1+i);
        strs[i] = filename;
    }
    if (CCSprite::initWithFile(strs[0].c_str())) {
        return true;
    }
    return false;
}


void Insects::runAnimation(){
    CCAnimation* animation = CCAnimation::create();
    animation->addSpriteFrameWithFileName(strs[0].c_str());
    animation->addSpriteFrameWithFileName(strs[1].c_str());
    animation->addSpriteFrameWithFileName(strs[2].c_str());
    
    animation->setLoops(-1);
    animation->setDelayPerUnit(0.3f);
    
    CCAnimate* pAction = CCAnimate::create(animation);
    
    runAction(pAction);
    
}


