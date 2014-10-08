

#ifndef comment_ScrollMenu
#define comment_ScrollMenu

#include "cocos-ext.h"
#include "cocos2d.h"


class ScrollMenu:public cocos2d::extension::CCScrollView
{
public:
	ScrollMenu();
	~ScrollMenu();
	virtual bool init();

	CREATE_FUNC(ScrollMenu);
	void setMenu(cocos2d::CCMenu* pMenu);
	CC_SYNTHESIZE(bool,m_ScrollEnable,ScrollEnable);
public:
	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
private:
	void touchEnd(float delta);
	cocos2d::CCMenu* m_Menu;
	cocos2d::CCPoint m_TouchBeginAtPoint;
	cocos2d::CCPoint m_TouchEndAtPoint;
};
#endif