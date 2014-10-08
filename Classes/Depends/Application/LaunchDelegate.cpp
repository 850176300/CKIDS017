#include "LaunchDelegate.h"
#include "Heads.h"
#include<math.h>
#include "DataManager.h"

USING_NS_CC;

LaunchDelegate::LaunchDelegate() {

}

LaunchDelegate::~LaunchDelegate() 
{
}

bool LaunchDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
	


    pDirector->setOpenGLView(pEGLView);
	screenSize=pDirector->getWinSizeInPixels();
	if(isSupportHD())
    {
        switch (CCApplication::sharedApplication()->getTargetPlatform())
        {
            case kTargetIpad:
            {
                //retina iPad£¨use HD resources
                if(screenSize.width > 2000 || screenSize.height > 2000)
                {
                    resourceType=SF_RESOURCES_2048_1536;
                }else
                {
                    resourceType=SF_RESOURCES_1024_768;
                }
            }
                break;
            default:
                resourceType=SF_RESOURCES_1024_768;
        }
    }else{
        resourceType=SF_RESOURCES_1024_768;
    }
   
    
	design_size=getDesignSize();

    CCSize realSize = CCSize2(design_size.width, design_size.height);

	float rate_width=screenSize.width/realSize.width;
	float rate_height=screenSize.height/realSize.height;

	float minScale=rate_width>rate_height?rate_height:rate_width;
	contentScale=rate_width>rate_height?rate_width:rate_height;
    CCLog("contentScale--->%f",contentScale);
	screenSize=CCSize(screenSize.width/minScale,screenSize.height/minScale);
    CCLog("screenSize--->%f,%f",screenSize.width,screenSize.height);
   

	
	
	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(screenSize.width, screenSize.height, kResolutionShowAll);


	blankArea_width=fabs((screenSize.width-realSize.width)/2);
	blankArea_height=fabs((screenSize.height-realSize.height)/2);

//	screenSize=CCSize(screenWidth,screenHeight);

	//float screenHeight =screenSize.height*1/CCEGLView::sharedOpenGLView()->getScaleY()>design_size.height*1/contentScale?design_size.height*1/contentScale:screenSize.height*1/CCEGLView::sharedOpenGLView()->getScaleY();
	
	

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

   onStart();
    
    return true;
}
bool LaunchDelegate::isSupportHD(){
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void LaunchDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void LaunchDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

cocos2d::CCSize LaunchDelegate::getDesignSize()
{
	return CCSize(640,960);
}
