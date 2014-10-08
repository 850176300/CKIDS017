#include "MyDialog.h"
#include "SimpleAudioEngine.h"
#include "Util.h"
#include "Global.h"
#include "SoundPlayer.h"


static const float btn_padding=
#if (resourceType==SF_RESOURCES_2048_1536)
50*2;
#else
50;
#endif
static const std::string DIALOGFONT =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Gotham-Ultra";
#else
"fonts/com_gotham-ultra.ttf";
#endif

//static const int MENU_TYPE_1=1;
//static const int MENU_TYPE_2=2;

MyDialog::MyDialog() :callback(NULL)
{
    
}

MyDialog::~MyDialog()
{
    
}
void MyDialog::onEnter(){
    CCLayer::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority - 15,true);
    
}
void MyDialog::onExit(){
    CCLayer::onExit();
    //    setTouchEnabled(false);
    //    setTouchPriority(0);
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
}

MyDialog* MyDialog::create(CCSize size,void* _args,int type)
{
	MyDialog* dialog =new MyDialog();
	dialog->autorelease();
	dialog->dialogType=type;
	dialog->dialogSize=size;

	dialog->args=_args;
	dialog->init();
	return dialog;
}
bool MyDialog::init()
{
	if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)))
    {
        
        
	//	setContentSize(CCSize2(design_size.width,design_size.height));
		CCSize size=CCDirector::sharedDirector()->getVisibleSize();
		
		contentLayer=CCLayerColor::create();
	//	contentLayer->setContentSize(dialogSize);
		contentLayer->ignoreAnchorPointForPosition(false);
		contentLayer->setAnchorPoint(ccp(0.5,0.5));
		contentLayer->setPosition(ccp(size.width/2,size.height/2));
		contentLayer->setScale(0.1);
		addChild(contentLayer);
		
		CCSprite* bg = CCSprite::create("dialog/popup.png");
		bg->setPosition(ccp(contentLayer->getContentSize().width/2+CCDirector::sharedDirector()->getVisibleOrigin().x, contentLayer->getContentSize().height/ 2.0f+CCDirector::sharedDirector()->getVisibleOrigin().y));
		contentLayer->addChild(bg);
		
		title_label = CCLabelTTF::create("",DIALOGFONT.c_str(), 40);
        title_label->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		title_label->setPosition(ccp(bg->getContentSize().width/2,bg->getContentSize().height*0.83));
        title_label->setColor(ccc3(1, 75, 119));
		bg->addChild(title_label);

		content_label = CCLabelTTF::create("",DIALOGFONT.c_str(), 30);
		content_label->setDimensions(CCSize(bg->getContentSize().width*0.8,bg->getContentSize().height*0.5));
        content_label->setVerticalAlignment(kCCVerticalTextAlignmentCenter);
		//content_label->setAnchorPoint(ccp(0.5,0.5));
		content_label->setColor(ccc3(1,75,119));
        content_label->setPosition(ccp(bg->getContentSize().width/2,bg->getContentSize().height*0.6));
		bg->addChild(content_label);
           
        
        CCSprite* pp1 = CCSprite::create("dialog/ui02_btn_no.png");
        CCSprite* pp2 = CCSprite::create("dialog/ui02_btn_no.png");
        pp2->setColor(ccGRAY);
		CCMenuItemSprite* positive= CCMenuItemSprite::create(pp1,pp2, this,
                                                             menu_selector(MyDialog::onClick));
		positive->setUserData((void*)&MENU_TYPE_1);
        
	//	positive->setAnchorPoint(ccp(0.5,0.5));
        
		positive_label = CCLabelTTF::create("",DIALOGFONT.c_str(), 30, positive->getContentSize(), kCCTextAlignmentCenter,
                                        kCCVerticalTextAlignmentCenter);
		positive_label->setPosition(ccp(positive->getContentSize().width/2,positive->getContentSize().height/2));
		positive_label->setAnchorPoint(ccp(0.5,0.5));
		positive_label->setColor(ccc3(255,255,218));
		positive->addChild(positive_label);
        
        
        CCSprite* p111 = CCSprite::create("dialog/ui02_btn_yes.png");
        CCSprite* p222 = CCSprite::create("dialog/ui02_btn_yes.png");
        p222->setColor(ccGRAY);
		CCMenuItemSprite* negative= CCMenuItemSprite::create(p111, p222,  this,menu_selector(MyDialog::onClick));
		negative->setUserData((void*)&MENU_TYPE_2);
        
	//	negative->setAnchorPoint(ccp(0.5,0.5));
        
		negative_label = CCLabelTTF::create("",DIALOGFONT.c_str(), 30,negative->getContentSize(),kCCTextAlignmentCenter,
                                            kCCVerticalTextAlignmentCenter);
		negative_label->setPosition(ccp(negative->getContentSize().width/2,negative->getContentSize().height/2));
		negative_label->setAnchorPoint(ccp(0.5,0.5));
		negative_label->setColor(ccc3(255,255,218));
        
		negative->addChild(negative_label);
        
		if(dialogType==DIALOG_TYPE_SINGLE)
		{
            CCSprite* pp11 = CCSprite::create("dialog/ui02_btn_ok.png");
            CCSprite* pp22 = CCSprite::create("dialog/ui02_btn_ok.png");
            pp22->setColor(ccGRAY);
            positive->setNormalImage(pp11);
            positive->setSelectedImage(pp22);
            positive->setPosition(ccp(bg->getContentSize().width/2,75));

			mMenu = CCMenu::create(positive,  NULL );
		}else
		{
            positive->setPosition(ccp(bg->getContentSize().width/2-positive->getContentSize().width/2-10,75));
            negative->setPosition(ccp(bg->getContentSize().width/2+positive->getContentSize().width/2+10,75));
			mMenu = CCMenu::create(positive,negative,  NULL );
		}
		
		mMenu->setPosition(ccp(0,0));
        
		bg->addChild( mMenu );
        
		contentLayer->runAction(CCScaleTo::create(0.3,1));
		refreshPosition();
        KeypadDispatchCenter::getInstance()->addDelegate(this);
		return true;
	}
    
	return false;
}
void MyDialog::setCallback(DialogCallback* _callback)
{
    callback=_callback;
}
void MyDialog::onBack()
{
    KeypadDispatchCenter::getInstance()->removeDelegate(this);
    getParent()->removeChild(this,true);
	
    //call method of parent
//	if(callback!=NULL)
//		(*reinterpret_cast<callbackPointer>(callback))(parent,args);
    if(callback!=NULL)
        callback->onPositiveClick(args);
}
void MyDialog::dismiss()
{
    KeypadDispatchCenter::getInstance()->removeDelegate(this);
    getParent()->removeChild(this,true);

    
    if(callback!=NULL)
        callback->onNegativeClick(args);
}

void MyDialog::onClick(CCObject* obj)
{

    SoundPlayer::getInstance()->selectGroundMusic();
	if(!mMenu->isEnabled())
		return;
//    SoundUtil::getInstance()->playSound("Sounds/ui/button_common.mp3");
	mMenu->setEnabled(false);
    CCControlButton* btn=(CCControlButton*)obj;
	int type=*((int*)btn->getUserData());
	if(type==MENU_TYPE_1)
	{
		
		CCFiniteTimeAction* action = CCSequence::create(CCScaleTo::create(0.3,0.0),CCCallFunc::create(this, callfunc_selector(MyDialog::dismiss)) , NULL);
		
		contentLayer->runAction(action);
        
	}else
	{
		CCFiniteTimeAction* action = CCSequence::create(CCScaleTo::create(0.3,0.0),CCCallFunc::create(this, callfunc_selector(MyDialog::onBack)) , NULL);
		
		contentLayer->runAction(action);
	}
}

void MyDialog::keyBackClicked(){
    CCFiniteTimeAction* action = CCSequence::create(CCScaleTo::create(0.3,0.0),CCCallFunc::create(this, callfunc_selector(MyDialog::justDismiss)) , NULL);
    
    contentLayer->runAction(action);
}

void MyDialog::justDismiss(){
    KeypadDispatchCenter::getInstance()->removeDelegate(this);
    getParent()->removeChild(this, true);
}

void MyDialog::setPositiveBtnText(const char* text)
{
    positive_label->setString(text);
}
void MyDialog::setNegativeBtnText(const char* text)
{
    negative_label->setString(text);
}
void MyDialog::setContentText(const char* text)
{
    content_label->setString(text);
	refreshPosition();
}

void MyDialog::setTitleText( const char* text)
{
	title_label->setString(text);
	refreshPosition();
}

void MyDialog::refreshPosition()
{
	//content_label->setPosition(ccp(dialogSize.width/2,dialogSize.height*0.8-title_label->getContentSize().height));
}
bool MyDialog::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    mTouch = false;
    if(mMenu->ccTouchBegan(pTouch, pEvent)){
        mTouch = true;
    }
    return true;
}

void MyDialog::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    if(mTouch){
        mMenu->ccTouchMoved(pTouch, pEvent);
    }
}
void MyDialog::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    if(mTouch){
        mMenu->ccTouchEnded(pTouch, pEvent);
    }
    mTouch = false;
}
void MyDialog::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    
}

