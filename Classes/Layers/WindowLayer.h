//
//  WindowLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-10-10.
//
//

#ifndef __CKIDS017__WindowLayer__
#define __CKIDS017__WindowLayer__

#include <iostream>
#include "GameLayerBase.h"
#include "cocos2d.h"
#include "Scribble.h"
#include "DaubSprite.h"
USING_NS_CC;

class WindowLayer : public GameLayerBase {
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(WindowLayer);
private:
    Scribble* _scribble;
    DaubSprite* dust;
    void addDust();
};
#endif /* defined(__CKIDS017__WindowLayer__) */
