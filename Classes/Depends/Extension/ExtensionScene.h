#ifndef __EXTENSION_SCENE_H__
#define __EXTENSION_SCENE_H__
#include "cocos2d.h"
#include "../Extension/ContentLayer.h"
#include "../Conflict/ConflictInterface.h"
#include "../Application/Global.h"
#include "../Application/Util.h"

USING_NS_CC;
class Conflict;
class ExtensionScene:public cocos2d::CCScene
{
public:
	ExtensionScene();
	~ExtensionScene();
	bool initScene();
    //添加一个Node到BGLayer，等同于bgLayer.addChild(child)
	void addChildToBgLayer(CCNode* child);
	//添加一个Node到UILayer，等同于uiLayer.addChild(child)
    void addChildToUILayer(CCNode* child);
	//添加一个Node到contentLayer，等同于contentLayer.addChild(child)
    void addChildToContentLayer(CCNode* child);
	//移动contentLayer到屏幕的顶部
    void contentToTop();
	//移动contentLayer到屏幕的底部
    void contentToBottom();
	//移动contentLayer到屏幕的左边
    void contentToLeft();
	//移动contentLayer到屏幕的右边
    void contentToRight();
	//设置contentLayer的位置
    void setContentPosition(CCPoint);
	//往model身上穿衣服
    void onDress(ComponentInfo item);
	//往model身上穿衣服
    void onDress(int componentId);
    //脱掉model身上的衣服
    void offDress(int categoryID);
    //
    void resetModel();
    //
    void setDefault();
    
   
  
	//set conflict interface
	void setConflictInterface(Conflict*);
	void controlMenuCallback(CCObject*);
protected:
	
	CCLayer* bgLayer;
	CCLayer* uiLayer;
	ContentLayer* contentLayer;
	Conflict* conflict;
private:

};

#endif