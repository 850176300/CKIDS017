//
//  DaubSprite.h

//
//  Created by chenxi1 on 13-10-23.
//
//

#ifndef ____DaubSprite__
#define ____DaubSprite__

#include "cocos2d.h"
#include "Scribble.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class DaubSprite: public CCRenderTexture,public CCTargetedTouchDelegate {
    
    Scribble *scribble;
    CCSprite *sprite;
    bool isDaub;
    
    long _total;
    float _alphaTestValue;
protected:
    long calcute(CCImage *pImage);
    
public:
    DaubSprite();
    virtual ~DaubSprite();

    //标志类变量
    bool eraserFinished;
    bool paintFinished;
    static DaubSprite* create( Scribble *scribble,CCSprite *sprite);
    static DaubSprite* create(CCSize size, Scribble *scribble,CCSprite *sprite);
    bool initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat, GLuint uDepthStencilFormat);

    virtual void onEnter();
    virtual void onExit();
    virtual void paint(CCPoint lTouchPoint,CCPoint lpreTouchPoint);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    virtual CCObject* copyWithZone(CCZone *pZone);
    virtual void touchDelegateRetain();
    virtual void touchDelegateRelease();
    
    void setEnableDaub(bool isDaub);
    virtual void changeTarget(CCSprite *lTarget,bool mClean = true);
    void show();
    int width,height,resWidth,resHeight,offsetX,offsetY;
    
    float paintPercent();
    float easePercent();

};

#endif 
