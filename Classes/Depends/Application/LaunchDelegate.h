#ifndef  _LAUNCH_DELEGATE_H_
#define  _LAUNCH_DELEGATE_H_

#include "cocos2d.h"

USING_NS_CC;
/**
@brief    The cocos2d Application.

The reason for implement as private inheritance is to hide some interface call by CCDirector.
*/
class  LaunchDelegate : public cocos2d::CCApplication
{
public:
    LaunchDelegate();
    virtual ~LaunchDelegate();

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

	virtual CCSize getDesignSize();
    virtual bool isSupportHD();
	virtual void onStart()=0;
};

#endif // _APP_DELEGATE_H_

