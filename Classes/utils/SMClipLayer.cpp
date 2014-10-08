//
//  SMClipLayer.cpp
//  Doctor
//
//  Created by tanshoumei on 13-8-29.
//
//

#include "SMClipLayer.h"
#include "VisibleRect.h"

SMClipLayer* SMClipLayer::createWithViewRect(cocos2d::CCRect aRect)
{
    SMClipLayer* pLayer = new SMClipLayer();
    pLayer->initWithViewRect(aRect);
    pLayer->autorelease();
    return pLayer;
}

bool SMClipLayer::initWithViewRect(cocos2d::CCRect aRect)
{
    if(!CCLayer::init())
        return false;
    m_ViewRect = aRect;
    m_bClipEnable = true;
    return true;
}

void SMClipLayer::enableClip(bool abValue)
{
    m_bClipEnable = abValue;
}

void SMClipLayer::setClipRect(cocos2d::CCRect aRect)
{
    m_ViewRect = aRect;
}

CCRect SMClipLayer::getClipRect()
{
    return m_ViewRect;
}

/**
 * clip this view so that outside of the visible bounds can be hidden.
 */
void SMClipLayer::beforeDraw()
{
    if (m_bClipEnable)
    {
		// TODO: This scrollview should respect parents' positions
        
        glEnable(GL_SCISSOR_TEST);
        float s = this->getScale();
        float height = m_ViewRect.size.height * s;
        CCEGLView::sharedOpenGLView()->setScissorInPoints(m_ViewRect.origin.x*s, m_ViewRect.origin.y*s, m_ViewRect.size.width*s, height);
        //glScissor((GLint)screenPos.x, (GLint)screenPos.y, (GLsizei)(m_tViewSize.width*s), (GLsizei)(m_tViewSize.height*s));
		
    }
}

/**
 * retract what's done in beforeDraw so that there's no side effect to
 * other nodes.
 */
void SMClipLayer::afterDraw()
{
    if (m_bClipEnable)
    {
        glDisable(GL_SCISSOR_TEST);
    }
}

void SMClipLayer::visit()
{
	// quick return if not visible
	if (!isVisible())
    {
		return;
    }
    
	kmGLPushMatrix();
	
    if (m_pGrid && m_pGrid->isActive())
    {
        m_pGrid->beforeDraw();
        this->transformAncestors();
    }
    
	this->transform();
    this->beforeDraw();
    
	if(m_pChildren)
    {
		ccArray *arrayData = m_pChildren->data;
		unsigned int i=0;
		
		// draw children zOrder < 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode *child =  (CCNode*)arrayData->arr[i];
			if ( child->getZOrder() < 0 )
            {
				child->visit();
			}
            else
            {
				break;
            }
		}
		
		// this draw
		this->draw();
		
		// draw children zOrder >= 0
		for( ; i < arrayData->num; i++ )
        {
			CCNode* child = (CCNode*)arrayData->arr[i];
			child->visit();
		}
        
	}
    else
    {
		this->draw();
    }
    
    this->afterDraw();
	if ( m_pGrid && m_pGrid->isActive())
    {
		m_pGrid->afterDraw(this);
    }
    
	kmGLPopMatrix();
}
