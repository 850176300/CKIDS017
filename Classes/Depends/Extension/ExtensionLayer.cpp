#include "ExtensionLayer.h"

static bool isOneLoop = false;

void ExtensionLayer::onEnter()
{
	isOneLoop = false;
	CCLayerColor::onEnter();

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
}

void ExtensionLayer::onExit()
{

	CCLayerColor::onExit();
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool ExtensionLayer::ccTouchBegan(CCTouch* pTouch, CCEvent* pEvent)
{
	if (isOneLoop)
		return true;
	isOneLoop = true;

	if (mMenu&&mMenu!=NULL) {
		mTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
	}
	return true;
}

void ExtensionLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (mTouchedMenu) {
		if (mMenu&&mMenu!=NULL) {
			mMenu->ccTouchMoved(pTouch, pEvent);
		}
	}
}

void ExtensionLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (mTouchedMenu) {
		if (mMenu&&mMenu!=NULL) {
			mMenu->ccTouchEnded(pTouch, pEvent);
		}
		mTouchedMenu = false;
	}

	isOneLoop = false;
}

void ExtensionLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
	if (mTouchedMenu) {
		if (mMenu&&mMenu!=NULL) {
			mMenu->ccTouchEnded(pTouch, pEvent);
		}
		mTouchedMenu = false;
	}

	isOneLoop = false;
}