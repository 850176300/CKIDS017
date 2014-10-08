//
//  DrinkSprite.h
//  BBQParty
//
//  Created by liuwei on 14-8-25.
//
//

#ifndef __BBQParty__DrinkSprite__
#define __BBQParty__DrinkSprite__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;
class DrinkSprite : public CCSprite,public CCTouchDelegate {
public:
    DrinkSprite();
    ~DrinkSprite();
    static DrinkSprite* create(const char* pszFile, const char* maskFile);
    static DrinkSprite* create(CCTexture2D* texture, const char* maskFile);
    
public:
    bool initWithFileAndmask(const char *pszFilename, const char* maskFile);
    bool initWithTextureAndmask(cocos2d::CCTexture2D *pTexture, const char* maskFile);
    virtual void onEnter();
    virtual void onExit();
    void startDrink();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
private:
    virtual void update(float dt);
    CCRenderTexture *render_;
    CCSprite *brush_;
    bool beenFinished;
    float height;//高度
    void playEffect();
};
#endif /* defined(__BBQParty__DrinkSprite__) */
