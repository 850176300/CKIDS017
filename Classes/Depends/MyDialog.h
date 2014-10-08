#ifndef __MYDIALOG_H__
#define __MYDIALOG_H__
#include "cocos2d.h"
#include "ExtensionLayer.h"
#include "DialogCallback.h"
#include "KeypadDispatchCenter.h"
USING_NS_CC;


class MyDialog:public ExtensionLayer, public KeypadDelegate{
public:
	//just one btn
    static const int DIALOG_TYPE_SINGLE=1;
    static const int DIALOG_TYPE_NEGATIVE=2;
	MyDialog();
	virtual ~MyDialog();
	virtual bool init();
	static MyDialog* create(CCSize ,void*,int);
	virtual void setContentText(const char* text);
	virtual void setPositiveBtnText(const char*);
	virtual void setNegativeBtnText(const char*);
	virtual void setTitleText(const char*);
	void onClick(CCObject*);
	void refreshPosition();
    void setCallback(DialogCallback* callback);
    virtual void onEnter();
    virtual void onExit();
    virtual void keyBackClicked();
public:

  //  CCMenuItemSprite* positive;
 //   CCMenuItemSprite* negative;
protected:
	void onBack();
	void dismiss();
    void justDismiss();
	CCLabelTTF* title_label;
	CCLayer* contentLayer;
	CCLabelTTF* content_label;
	CCLabelTTF* positive_label;
	CCLabelTTF* negative_label;
	CCNode* parent;
	SEL_MenuHandler selector;
    bool mTouch;
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
private:
    DialogCallback* callback;
	CCSize dialogSize;
	int dialogType;
	void* args;
    


};
#endif