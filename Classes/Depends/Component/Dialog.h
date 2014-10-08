#ifndef __DIALOG_H__
#define __DIALOG_H__
#include "cocos2d.h"
#include "../Extension/ExtensionLayer.h"
#include "DialogCallback.h"
USING_NS_CC;

class Dialog:public ExtensionLayer{
public:
	//just one btn
    static const int DIALOG_TYPE_SINGLE=1;
    static const int DIALOG_TYPE_NEGATIVE=2;
	Dialog();
	virtual ~Dialog();
	virtual bool init();
	static Dialog* create(CCSize ,void*,int);
	virtual void setContentText(const char* text);
	virtual void setPositiveBtnText(const char*);
	virtual void setNegativeBtnText(const char*);
	virtual void setTitleText(const char*);
	void onClick(CCObject*);
	void refreshPosition();
    void setCallback(DialogCallback* callback);

protected:
	void onBack();
	void dismiss();
	CCLabelTTF* title_label;
	CCLayer* contentLayer;
	CCLabelTTF* content_label;
	CCLabelTTF* positive_label;
	CCLabelTTF* negative_label;
	CCNode* parent;
	SEL_MenuHandler selector;
private:
    DialogCallback* callback;
	CCSize dialogSize;
	int dialogType;
	void* args;


};
#endif