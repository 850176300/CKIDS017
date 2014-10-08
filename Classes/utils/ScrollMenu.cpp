

#include "ScrollMenu.h"

USING_NS_CC;
USING_NS_CC_EXT;


ScrollMenu::ScrollMenu():m_Menu(NULL)
	,m_TouchBeginAtPoint(CCPointZero)
	,m_TouchEndAtPoint(CCPointZero)
	,m_ScrollEnable(true)
{

}

ScrollMenu::~ScrollMenu()
{

}

bool ScrollMenu::init()
{
	CCScrollView::init();

	CCLayer* pContainer = CCLayer::create();
	pContainer->setAnchorPoint(CCPointZero);

// 	CCLayerColor* pLayerColor = CCLayerColor::create(ccc4(200,0,0,255));
// 	pContainer->addChild(pLayerColor);
// 	pLayerColor->setPosition(CCPointZero);

	this->setContainer(pContainer);
	//
	m_Menu = CCMenu::create();
	m_Menu->setPosition(CCPointZero);
	m_Menu->setTouchEnabled(true);
	pContainer->addChild(m_Menu);


	this->setTouchPriority(-128);
	return true;
}

void ScrollMenu::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -129, true);
}

bool ScrollMenu::ccTouchBegan( CCTouch* touch, CCEvent* event )
{
	m_Menu->setTouchEnabled(false);
	m_TouchBeginAtPoint = touch->getLocation();
//    m_Menu->ccTouchBegan(touch,event);
	return CCScrollView::ccTouchBegan(touch,event);
}

void ScrollMenu::ccTouchCancelled( CCTouch *touch, CCEvent* event )
{
	CCScrollView::ccTouchCancelled(touch,event);
}

void ScrollMenu::ccTouchEnded( CCTouch* touch, CCEvent* event )
{
	m_Menu->setTouchEnabled(false);
	CCScrollView::ccTouchEnded(touch,event);
	m_TouchEndAtPoint = touch->getLocation();

	switch ( getDirection() )
	{
	case  kCCScrollViewDirectionHorizontal:
		{
			float distance = fabsf(m_TouchBeginAtPoint.x-m_TouchEndAtPoint.x);
 			if ( distance < 10 )
 			{
 				bool isBeenTouch = m_Menu->ccTouchBegan(touch,event);

  				if ( isBeenTouch )
  				{
 					this->scheduleOnce(SEL_SCHEDULE(&ScrollMenu::touchEnd),0.2f);
 				}
 			}
		}
		break;
	case kCCScrollViewDirectionVertical:
		{
			float distance = fabsf(m_TouchBeginAtPoint.y - m_TouchEndAtPoint.y);
			if ( distance < 10 )
			{
				bool isBeenTouch = m_Menu->ccTouchBegan(touch,event);
				if ( isBeenTouch )
				{
					this->scheduleOnce(SEL_SCHEDULE(&ScrollMenu::touchEnd),0.2f);
				}
			}
		}
		break;
	default:
		CCAssert(0,"ScrollMenu support kCCScrollViewDirectionHorizontal or kCCScrollViewDirectionVertical only !");
		break;
	}

}

void ScrollMenu::ccTouchMoved( CCTouch* touch, CCEvent* event )
{
	if ( m_ScrollEnable == false )
	{
		return ;
	}
	CCScrollView::ccTouchMoved(touch,event);
}

// 
 void ScrollMenu::touchEnd( float delta )
 {
 	m_Menu->ccTouchEnded(NULL,NULL);
 }

 void ScrollMenu::setMenu( cocos2d::CCMenu* pMenu )
 {
	 if ( m_Menu != NULL )
	 {
		 pMenu->setTouchEnabled(false);
		 pMenu->setTouchPriority(-128);
		 m_Menu->removeFromParent();
		 m_Menu = pMenu;
		 m_Menu->setTouchEnabled(true);
		 m_Menu->setPosition(CCPointZero);
		 getContainer()->addChild(m_Menu);
	 }
 }

 // 
