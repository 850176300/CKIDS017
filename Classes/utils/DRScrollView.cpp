#include "DRScrollView.h"
#include "TouchNodeTon.h"

DRScrollView::DRScrollView(void)
{
}


DRScrollView::~DRScrollView(void)
{
}

DRScrollView* DRScrollView::create(CCSize size)
{
	DRScrollView * pScroll = new DRScrollView;
	pScroll->initWithSize(size);
	pScroll->autorelease();
	return pScroll;
}

bool DRScrollView::initWithSize(CCSize size)
{
	if(CCScrollView::initWithViewSize(size, NULL))
	{
		m_pDrScorllViewDelegate = NULL;
        m_pTouchDispatchByScrollView = NULL;
		m_fVerticalRaioTop = m_fVerticalRaioBottom = 0.1;
		m_fScrollMinX = m_fScrollMinY = 5;
		return true;
	}
	return false;
}

void DRScrollView::SetDRScrollViewDelegate(DRScrollViewDelegate *pDelegate)
{
	m_pDrScorllViewDelegate = pDelegate;
}

void DRScrollView::SetVerticalRatioTop(float fRdtio)
{
	m_fVerticalRaioTop = fRdtio;
}

void DRScrollView::SetVerticalRatioBottom(float fRdtio)
{
	m_fVerticalRaioBottom = fRdtio;
}

void DRScrollView::setContentSize(const CCSize & size)
{
	if (this->getContainer() != NULL)
	{
		this->getContainer()->setContentSize(size);
		this->updateInset();
	}
}

void DRScrollView::updateInset()
{
	if (this->getContainer() != NULL)
	{
		m_fMaxInset = this->maxContainerOffset();
		m_fMaxInset = ccp(m_fMaxInset.x + m_tViewSize.width * 0.2,
			m_fMaxInset.y + m_tViewSize.height * m_fVerticalRaioBottom);
		m_fMinInset = this->minContainerOffset();
		m_fMinInset = ccp(m_fMinInset.x - m_tViewSize.width * 0.2,
			m_fMinInset.y - m_tViewSize.height * m_fVerticalRaioTop);
	}
}

bool DRScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	m_bScrolled = false;
    m_bTouchMoved = false;
    m_pTouches->removeAllObjects();
	bool ret = CCScrollView::ccTouchBegan(pTouch, pEvent);
	m_TouchBeginPos = pTouch->getLocation();
	if(ret && m_pDrScorllViewDelegate)
		m_pDrScorllViewDelegate->scrollViewTouchBegin(pTouch->getLocation());
	return ret;
}

void DRScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCScrollView::ccTouchMoved(pTouch, pEvent);
	if(getDirection() == kCCScrollViewDirectionHorizontal){
		if(fabs(pTouch->getLocation().x - m_TouchBeginPos.x) >= m_fScrollMinX)
			m_bScrolled = true;
	}
	else if(getDirection() == kCCScrollViewDirectionVertical)
		if(fabs(pTouch->getLocation().y - m_TouchBeginPos.y) >= m_fScrollMinY)
			m_bScrolled = true;
	if(m_bScrolled && m_pDrScorllViewDelegate)
		m_pDrScorllViewDelegate->scrollViewWillScroll();
}

void DRScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
//    m_Menu->setTouchEnabled(false);
	CCScrollView::ccTouchEnded(pTouch,pEvent);
	CCPoint m_TouchEndAtPoint = pTouch->getLocation();
    
	switch ( getDirection() )
	{
        case  kCCScrollViewDirectionHorizontal:
		{
			float distance = fabsf(m_TouchBeginPos.x-m_TouchEndAtPoint.x);
 			if ( distance < 10 )
 			{
 				bool isBeenTouch = false;
                CCObject* pObj;
                TouchNode* selectOne;
                CCARRAY_FOREACH(getContainer()->getChildren(), pObj){
                    selectOne = dynamic_cast<TouchNode*>(pObj);
                    CCPoint touchPP = getContainer()->convertToNodeSpace(selectOne->getPosition());

                    CCRect goalRect = CCRectMake(touchPP.x - selectOne->getContentSize().width/2.0, touchPP.y - selectOne->getContentSize().height/2.0, selectOne->getContentSize().width, selectOne->getContentSize().height);
                    if (goalRect.containsPoint(getContainer()->convertToNodeSpace(m_TouchEndAtPoint))) {
                        isBeenTouch = selectOne->ccTouchBegan(pTouch, pEvent);
                    }
                    
                    if (isBeenTouch) {
                        break;
                    }
                };
                
  				if ( isBeenTouch )
  				{
 					selectOne->ccTouchEnded(NULL, NULL);
 				}
 			}
		}
            break;
        case kCCScrollViewDirectionVertical:
		{
			float distance = fabsf(m_TouchBeginPos.y - m_TouchEndAtPoint.y);
			if ( distance < 10 )
			{
 				bool isBeenTouch = false;
                CCObject* pObj;
                TouchNode* selectOne;
                CCARRAY_FOREACH(getContainer()->getChildren(), pObj){
                    selectOne = dynamic_cast<TouchNode*>(pObj);
                    CCPoint touchPP = getContainer()->convertToNodeSpace(selectOne->getPosition());
                    
                    CCRect goalRect = CCRectMake(touchPP.x - selectOne->getContentSize().width/2.0, touchPP.y - selectOne->getContentSize().height/2.0, selectOne->getContentSize().width, selectOne->getContentSize().height);
                    if (goalRect.containsPoint(getContainer()->convertToNodeSpace(m_TouchEndAtPoint))) {
                        isBeenTouch = selectOne->ccTouchBegan(pTouch, pEvent);
                    }
                    
                    if (isBeenTouch) {
                        break;
                    }
                };
                
  				if ( isBeenTouch )
  				{
 					selectOne->ccTouchEnded(NULL, NULL);
 				}
			}
		}
            break;
        default:
            CCAssert(0,"ScrollMenu support kCCScrollViewDirectionHorizontal or kCCScrollViewDirectionVertical only !");
            break;
	}
	if(m_pDrScorllViewDelegate)
		m_pDrScorllViewDelegate->scrollViewTouchEnd(pTouch->getLocation());
}

bool DRScrollView::getIsScrolled()
{
    return m_bScrolled;
}

void DRScrollView::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, getTouchPriority(), true);
}
