#ifndef __EXTENSION_LAYER_H__
#define __EXTENSION_LAYER_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

/*
 此layer不常用，只要是为了解决cocos2dX里按钮事件优先级太高的问题
 如果要使用此layer，按钮一定要加到mMenu里
 */
class ExtensionLayer:public CCLayerColor
{
public:
	virtual void onEnter();
    virtual void onExit();

	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);  
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent); 
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
	

protected:
	CCMenu* mMenu;
	bool mTouchedMenu;
};
#endif