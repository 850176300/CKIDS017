#include "AppDelegate.h"
#include "STVisibleRect.h"
//#include "HelloWorldScene.h"
#include "GameController.h"
#include "DataContainer.h"
#define SCENEWIDTH 1024
#define SCENEHEIGHT 768
USING_NS_CC;
USING_NS_ST;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    
    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    cocos2d::CCDirector::sharedDirector()->setProjection(cocos2d::kCCDirectorProjection2D);
    
    
    STVisibleRect::setupVisibleRect(pEGLView->getFrameSize(), CCSizeMake(SCENEWIDTH, SCENEHEIGHT));
    
    CCSize realDesignSize = STVisibleRect::getRealDesignSize();
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(realDesignSize.width, realDesignSize.height, kResolutionNoBorder);
    // create a scene. it's an autorelease object
    
    DataContainer::getInstance()->loadDatas();
    GameController::getInstance()->gotoWashCar();
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
