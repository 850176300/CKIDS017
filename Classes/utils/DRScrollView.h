#ifndef _DR_SCROLL_VIEWDELEGATE_H_
#define _DR_SCROLL_VIEWDELEGATE_H_

#include "cocos-ext.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d::extension;

//滚动层回调接口
class DRScrollViewDelegate
{
public:
	virtual ~DRScrollViewDelegate() {}
    //触摸开始
	virtual void scrollViewTouchBegin(CCPoint worldPoint) {};
    //即将滚动。说明本次触摸是触发滚动，而非触发其他按钮的点击事件
	virtual void scrollViewWillScroll(){};
    //触摸结束。
	virtual void scrollViewTouchEnd(CCPoint worldPoint){};
};

/*
 DRScrollView与CCScrollView不同之处在于，当触摸在一个按钮(CCMenuItem)上面时，如果此时手指滑动到一定距离，是会触发层的滚动，而不是按钮的点击。
 **/
class DRScrollView: public CCScrollView
{
public:
	DRScrollView(void);
	~DRScrollView(void);

	static DRScrollView* create(CCSize size);
	bool initWithSize(CCSize size);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	//virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void setContentSize(const CCSize & size);

	void SetVerticalRatioTop(float fRdtio);
	void SetVerticalRatioBottom(float fRdtio);

	virtual void updateInset();

	virtual void SetDRScrollViewDelegate(DRScrollViewDelegate *pDelegate);

	virtual void registerWithTouchDispatcher();
    
    bool getIsScrolled();

private:
	float m_fVerticalRaioTop;
	float m_fVerticalRaioBottom;

	DRScrollViewDelegate *m_pDrScorllViewDelegate;

	bool m_bScrolled;
	float m_fScrollMinY;
	float m_fScrollMinX;
	CCPoint m_TouchBeginPos;
    CCTouch* m_pTouchDispatchByScrollView;
	//float m_fHorizonRatio;
};

#endif