#include "STVisibleRect.h"
#include "STAds.h"
#include "GameController.h"
USING_NS_CC;
USING_NS_ST;

static CCSize s_FrameSize;
static CCSize s_DesignSize;
static CCSize s_RealDesignSize;
static CCPoint s_TopLeftOffset;
static CCPoint s_DesignOffset;
static float s_RealDesignScale = 1.0f;

static int s_RetainOffsetLeft = 0;
static int s_RetainOffsetTop = 0;
static int s_RetainOffsetRight = 0;
static int s_RetainOffsetBottom = 0;

void STVisibleRect::setupVisibleRect(CCSize frameSize, CCSize designSize)
{
	s_DesignSize = designSize;
	s_FrameSize = frameSize;

	float scaleX = (float) frameSize.width / s_DesignSize.width;
	float scaleY = (float) frameSize.height / s_DesignSize.height;

	// MAX(scaleX, scaleY);
	float scale = 0.0f;
	if (scaleX > scaleY)
	{
		scale = scaleX / scaleY;
		s_TopLeftOffset = ccp(s_DesignSize.width * (scale - 1.0f) / 2.0f, 0);
	}
	else
	{
		scale = scaleY / scaleX;
		s_TopLeftOffset = ccp(0, s_DesignSize.height * (scale - 1.0f) / 2.0f);
	}

	s_RealDesignScale = scale;
	s_RealDesignSize = CCSize(s_DesignSize.width * scale, s_DesignSize.height * scale);

	s_DesignOffset = ccp((s_RealDesignSize.width - s_DesignSize.width) / 2.0f,
		(s_RealDesignSize.height - s_DesignSize.height) / 2.0f);
}

void STVisibleRect::initRetainOffset(int left, int top, int right, int bottom)
{
	s_RetainOffsetLeft = left * s_RealDesignSize.width / s_FrameSize.width;
	s_RetainOffsetTop = top * s_RealDesignSize.height / s_FrameSize.height;
	s_RetainOffsetRight = right * s_RealDesignSize.width / s_FrameSize.width;
	s_RetainOffsetBottom = bottom * s_RealDesignSize.height / s_FrameSize.height;
    CCNotificationCenter::sharedNotificationCenter()->postNotification("NotifyRetainOffset");
}

int STVisibleRect::getRetainOffsetTop()
{
    return s_RetainOffsetTop;
}
CCPoint STVisibleRect::getPosition(float x, float y, bool bTop, bool bBottom, bool bLeft) {
//    CCLog("the design offset x:%.2f, y:%.2f", s_DesignOffset.x, s_DesignOffset.y);
    float posX = x + s_DesignOffset.x;
	float posY = y + s_DesignOffset.y;
    
	if(bTop)
		posY += s_DesignOffset.y;
	else if(bBottom)
		posY -= s_DesignOffset.y;
    
    if(bLeft)
        posX -= s_DesignOffset.x;

    return ccp(posX, posY);
}
void STVisibleRect::setPosition(CCNode* node, float x, float y, bool bTop, bool bBottom, bool bLeft, bool bRight)
{
	float posX = x + s_DesignOffset.x;
	float posY = y + s_DesignOffset.y;

	if(bTop)
		posY += s_DesignOffset.y;
	else if(bBottom)
		posY -= s_DesignOffset.y;
    
    if(bLeft)
        posX -= s_DesignOffset.x;
    if (bRight) {
        posX += s_DesignOffset.x;
    }
    
	node->setPosition(ccp(posX, posY));
}

void STVisibleRect::setPositionWithRetainOffset(CCNode* node, float x, float y, bool bTop, bool bBottom)
{
	float posX = x + s_DesignOffset.x;
	float posY = y + s_DesignOffset.y;

	if(bTop)
	{
		posY += (s_TopLeftOffset.y - s_RetainOffsetTop);
	}

	if(bBottom)
	{
		posY -= (s_TopLeftOffset.y - s_RetainOffsetBottom);
	}

	node->setPosition(ccp(posX, posY));
}

CCSize& STVisibleRect::getRealDesignSize()
{
	return s_RealDesignSize;
}

CCSize& STVisibleRect::getDesignSize()
{
	return s_DesignSize;
}

CCPoint STVisibleRect::getDesignCeneter()
{
    return ccp(s_DesignSize.width * .5f, s_DesignSize.height * .5f);
}

CCSize& STVisibleRect::getFrameSize()
{
	return s_FrameSize;
}

float STVisibleRect::getRealDesignScale()
{
	return s_RealDesignScale;
}

CCPoint& STVisibleRect::getTopLeftOffset()
{
	return s_TopLeftOffset;
}

CCPoint STVisibleRect::getDesignOffset()
{
	return s_DesignOffset;
}

CCPoint STVisibleRect::getCenterOfScene()
{
//    float scaleX = CCDirector::sharedDirector()->getOpenGLView()->getScaleX();
//    float scaleY = CCDirector::sharedDirector()->getOpenGLView()->getScaleY();
//    return ccp(getDesignOffset().x + s_FrameSize.width * .5f / scaleX, getDesignOffset().y + s_FrameSize.height* .5f / scaleY);
    CCPoint oringnalP = CCDirector::sharedDirector()->getVisibleOrigin();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    return ccp(oringnalP.x + visibleSize.width/2.0, oringnalP.y+visibleSize.height/2.0);
}

CCPoint STVisibleRect::getPointOfSceneRightBottom()
{
    return ccpAdd(getOriginalPoint(), ccp(getGlvisibleSize().width, 0));
}

CCPoint STVisibleRect::getPointOfSceneRightUp(){
    return ccpAdd(getOriginalPoint(), ccp(getGlvisibleSize().width, getGlvisibleSize().height));
}

CCPoint STVisibleRect::getPointOfSceneLeftUp()
{
//    float scaleX = CCDirector::sharedDirector()->getOpenGLView()->getScaleX();
//    float scaleY = CCDirector::sharedDirector()->getOpenGLView()->getScaleY();
//    return ccp(getDesignOffset().x + s_FrameSize.width / scaleX, getDesignOffset().y + s_FrameSize.height / scaleY);
    return ccpAdd(getOriginalPoint(), ccp(0, getGlvisibleSize().height));
}

CCSize STVisibleRect::getGlvisibleSize(){
    return CCDirector::sharedDirector()->getVisibleSize();
}

CCRect STVisibleRect::getMovableRect(){
    float bannerSize = GameController::getInstance()->getBannerHeight();
//    if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) {
//        return CCRectMake(CCDirector::sharedDirector()->getVisibleOrigin().x, CCDirector::sharedDirector()->getVisibleOrigin().y, CCDirector::sharedDirector()->getVisibleSize().width, CCDirector::sharedDirector()->getVisibleSize().height-bannerSize);
//    }
//    else {
        return CCRectMake(CCDirector::sharedDirector()->getVisibleOrigin().x, CCDirector::sharedDirector()->getVisibleOrigin().y+bannerSize, CCDirector::sharedDirector()->getVisibleSize().width, CCDirector::sharedDirector()->getVisibleSize().height-bannerSize);
//    }
    
}


bool STVisibleRect::JudgeContain(cocos2d::CCRect rect1, cocos2d::CCRect rect2) {
    return !((rect1.origin.x >= rect2.origin.x) || (rect1.origin.y >= rect2.origin.y) ||
                      ( rect1.origin.x + rect1.size.width <= rect2.origin.x + rect2.size.width) ||
                    ( rect1.origin.y + rect1.size.height <= rect2.origin.y + rect2.size.height));
}

CCPoint STVisibleRect::getOriginalPoint(){
    return CCDirector::sharedDirector()->getVisibleOrigin();
}

//p2 表示转换之前的锚点，p1 应该对应的锚点
CCPoint STVisibleRect::conformByAnchorPoint(cocos2d::CCNode *pNode,cocos2d::CCPoint p1, cocos2d::CCPoint anchorP1,CCPoint p2/* = ccp(0.5f, 0.5f)*/) {
    CCPoint delta = ccp((anchorP1.x - p2.x)*pNode->getContentSize().width, (anchorP1.y-p2.y)*pNode->getContentSize().height);
    return ccpAdd(p1, delta);
}




