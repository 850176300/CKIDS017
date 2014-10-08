#ifndef _STVISIBLE_H_
#define _STVISIBLE_H_

#include "cocos2d.h"
#include "STMacro.h"

NS_ST_BEGIN
USING_NS_CC;

class STVisibleRect {
public:
	// initialization for STVisibleRect
	static void setupVisibleRect(CCSize frameSize, CCSize designSize);

	// initialization offset for STVisibleRect
	static void initRetainOffset(int left, int top, int right, int bottom);
    
    static int getRetainOffsetTop();

	// real design size(bigger than the designed size of game)
	static CCSize& getRealDesignSize();
	
	// the designed size of game
	static CCSize& getDesignSize();
    
    //the center of design frame.
    static CCPoint getDesignCeneter();
	
	// get frame size(can consider as screen size)
	static CCSize& getFrameSize();

	// the margin of top and left according to frame size
	static CCPoint& getTopLeftOffset();

	// the offset between game designed size and real design size
	static CCPoint getDesignOffset();

	// the ratio = RealDesignSize / DesignSize
	static float getRealDesignScale();
    
    //将给定的坐标转化成屏幕适配后的坐标
    static CCPoint getPosition(float x, float y, bool bTop = false, bool bBottom = false, bool bLeft = false);
    //the center coordindate of the screen
    static CCPoint getCenterOfScene();
    static CCPoint getPointOfSceneRightBottom();
    static CCPoint getPointOfSceneRightUp();
    static CCPoint getPointOfSceneLeftUp();

	// adjust CCNode's position(attention:top & bottom feature)
    //居右还未测
	static void setPosition(CCNode* node, float x, float y, bool bTop = false, bool bBottom = false, bool bLeft = false, bool bRight = false);

	// adjust CCNode's position
	static void setPositionWithRetainOffset(CCNode* node, float x, float y, bool bTop = false, bool bBottom = false);
    
    //get cocos2dx visible size
    static CCSize getGlvisibleSize();
    
    //get movable Rect
    static CCRect getMovableRect();
    
    //get oringinal Point
    static CCPoint getOriginalPoint();
    //judge rect Contain other one
    static bool JudgeContain(CCRect rect1, CCRect rect2);
    
    //caculate point by anchor point
    static CCPoint conformByAnchorPoint(CCNode *pNode ,CCPoint p1, CCPoint anchorP1, CCPoint p2 = ccp(0.5f, 0.5f));
    
    
};

NS_ST_END
#endif