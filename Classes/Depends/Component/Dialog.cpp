#include "Dialog.h"
#include "../Application/Heads.h"
#include "SimpleAudioEngine.h"

static const float btn_padding=
#if (resourceType==SF_RESOURCES_2048_1536)
50*2;
#else
50;
#endif


Dialog::Dialog() :callback(NULL)
{
    
}

Dialog::~Dialog()
{

}

Dialog* Dialog::create(CCSize size,void* _args,int type)
{
	Dialog* dialog =new Dialog();
	dialog->autorelease();
	dialog->dialogType=type;
	dialog->dialogSize=size;

	dialog->args=_args;
	dialog->init();
	return dialog;
}
bool Dialog::init()
{
	if (CCLayerColor::initWithColor(ccc4(0, 0, 0, 150)))
    {
        
        
	//	setContentSize(CCSize2(design_size.width,design_size.height));
		CCSize size=CCDirector::sharedDirector()->getVisibleSize();
		
		contentLayer=CCLayerColor::create();
		contentLayer->setContentSize(dialogSize);
		contentLayer->ignoreAnchorPointForPosition(false);
		contentLayer->setAnchorPoint(ccp(0.5,0.5));
		contentLayer->setPosition(ccp(size.width/2,size.height/2));
		contentLayer->setScale(0.1);
		addChild(contentLayer);
		CCRect rect = CCRectMake(0,0,150,150);
		CCRect rect_inside = CCRectMake(50,50,50,50);
		CCScale9Sprite* bg = cocos2d::extension::CCScale9Sprite::create("UI/dialog_bg.png", rect,rect_inside);
		bg->setPreferredSize(dialogSize);
		bg->setAnchorPoint(ccp(0.5,0.5));
		bg->setPosition(ccp(contentLayer->getContentSize().width/2, contentLayer->getContentSize().height/ 2.0f));
		contentLayer->addChild(bg);
		
		title_label = CCLabelTTF::create("",font_felt.c_str(), fontsize(40));
		title_label->setPosition(ccp(contentLayer->getContentSize().width/2,bg->getContentSize().height*0.9));
		bg->addChild(title_label);

		content_label = CCLabelTTF::create("",font_felt.c_str(), fontsize(30));
		content_label->setDimensions(CCSize(dialogSize.width*0.8,dialogSize.height*0.8));
        

		content_label->setAnchorPoint(ccp(0.5,1));
		content_label->setColor(ccc3(255,255,218));
		bg->addChild(content_label);
           
        
		CCMenuItemSprite* positive= CCMenuItemSprite::create(Util::getUISprite("dialog_btn.png"),Util::getUISprite("dialog_btn.png"), this,
                                                             menu_selector(Dialog::onClick));
		positive->setUserData((void*)99);
        //	positive->setPosition(ccp2(220,70));
		positive->setAnchorPoint(ccp(0.5,0.5));
        
		positive_label = CCLabelTTF::create("",font_felt.c_str(), fontsize(30), positive->getContentSize(), kCCTextAlignmentCenter,
                                        kCCVerticalTextAlignmentCenter);
		positive_label->setPosition(ccp(positive->getContentSize().width/2,positive->getContentSize().height/2));
		positive_label->setAnchorPoint(ccp(0.5,0.5));
		positive_label->setColor(ccc3(255,255,218));
		positive->addChild(positive_label);
        
        
		CCMenuItemSprite* negative= CCMenuItemSprite::create(Util::getUISprite("dialog_btn.png"), Util::getUISprite("dialog_btn.png"),  this,
                                                             menu_selector(Dialog::onClick));
		negative->setUserData((void*)MENU_TYPE_1);
        //	negative->setPosition(ccp2(50,70));
		negative->setAnchorPoint(ccp(0.5,0.5));
        
		negative_label = CCLabelTTF::create("",font_felt.c_str(), fontsize(30),negative->getContentSize(),kCCTextAlignmentCenter,
                                            kCCVerticalTextAlignmentCenter);
		negative_label->setPosition(ccp(negative->getContentSize().width/2,negative->getContentSize().height/2));
		negative_label->setAnchorPoint(ccp(0.5,0.5));
		negative_label->setColor(ccc3(255,255,218));
        
		negative->addChild(negative_label);
        
		if(dialogType==DIALOG_TYPE_SINGLE)
		{
			mMenu = CCMenu::create(positive,  NULL );
		}else
		{
			mMenu = CCMenu::create(positive,negative,  NULL );
		}
		
		mMenu->alignItemsHorizontallyWithPadding(btn_padding);
		mMenu->setPosition(ccp(dialogSize.width/2,dialogSize.height*0.2));
        
		bg->addChild( mMenu );
        
		contentLayer->runAction(CCScaleTo::create(0.3,1));
		refreshPosition();

		return true;
	}
    
	return false;
}
void Dialog::setCallback(DialogCallback* _callback)
{
    callback=_callback;
}
void Dialog::onBack()
{
    getParent()->removeChild(this,true);
	
    //call method of parent
//	if(callback!=NULL)
//		(*reinterpret_cast<callbackPointer>(callback))(parent,args);
    if(callback!=NULL)
        callback->onPositiveClick(args);
}
void Dialog::dismiss()
{
    getParent()->removeChild(this,true);

    
    if(callback!=NULL)
        callback->onNegativeClick(args);
}

void Dialog::onClick(CCObject* obj)
{

	if(!mMenu->isEnabled())
		return;
	mMenu->setEnabled(false);
    CCControlButton* btn=(CCControlButton*)obj;
	int type=(int)btn->getUserData();
	if(type==MENU_TYPE_1)
	{
		
		CCFiniteTimeAction* action = CCSequence::create(CCScaleTo::create(0.3,0.01),CCCallFunc::create(this, callfunc_selector(Dialog::dismiss)) , NULL);
		
		contentLayer->runAction(action);
        
	}else
	{
		CCFiniteTimeAction* action = CCSequence::create(CCScaleTo::create(0.3,0.01),CCCallFunc::create(this, callfunc_selector(Dialog::onBack)) , NULL);
		
		contentLayer->runAction(action);
	}
}


void Dialog::setPositiveBtnText(const char* text)
{
    positive_label->setString(text);
}
void Dialog::setNegativeBtnText(const char* text)
{
    negative_label->setString(text);
}
void Dialog::setContentText(const char* text)
{
    content_label->setString(text);
	refreshPosition();
}

void Dialog::setTitleText( const char* text)
{
	title_label->setString(text);
	refreshPosition();
}

void Dialog::refreshPosition()
{
	content_label->setPosition(ccp(dialogSize.width/2,dialogSize.height*0.8-title_label->getContentSize().height));
}

