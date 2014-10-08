#include "ExtensionScene.h"
#include <stdio.h>
#include <stdarg.h>

ExtensionScene::ExtensionScene():conflict(NULL)
{

}


ExtensionScene::~ExtensionScene()
{

//	if (conflict)
//	{
//
//		delete conflict;
//	}
}

bool ExtensionScene::initScene()
{
	
	bgLayer=CCLayer::create();
	bgLayer->setScale((1/CCEGLView::sharedOpenGLView()->getScaleX())*contentScale);
	bgLayer->setZOrder(10);
	addChild(bgLayer);
	uiLayer=CCLayer::create();
	uiLayer->setZOrder(90);
	addChild(uiLayer);
	contentLayer=ContentLayer::create();
	contentLayer->setZOrder(20);
	addChild(contentLayer);

	return true;
}

void ExtensionScene::addChildToBgLayer( CCNode* child )
{
	bgLayer->addChild(child);
}

void ExtensionScene::addChildToUILayer( CCNode* child )
{
	uiLayer->addChild(child);
}

void ExtensionScene::addChildToContentLayer( CCNode* child )
{
	contentLayer->addChild(child);
}

void ExtensionScene::contentToTop()
{
	contentLayer->layoutToTop();
}

void ExtensionScene::contentToBottom()
{
	contentLayer->layoutToBottom();
}

void ExtensionScene::contentToLeft()
{
	contentLayer->layoutToLeft();
}

void ExtensionScene::contentToRight()
{
	contentLayer->layoutToRight();
}

void ExtensionScene::onDress(ComponentInfo item)
{
    Category mCategory=categories[item.categoryID];
    if(mCategory.name=="bg"){
        bgLayer->removeChildByTag(item.categoryID);
        
        CCSprite* bgSprite=Util::getContentSprite(("bg/"+item.textures[0].imageName+".png").c_str());
        bgSprite->setTag(item.categoryID);
        bgSprite->setPosition(ccp(bgLayer->getContentSize().width/2,bgLayer->getContentSize().height/2));
        bgLayer->addChild(bgSprite);
        return;
    }
	//do conflict
	if (conflict!=NULL)
	{
		conflict->doConflict(this,contentLayer,&item);
	}
    
    contentLayer->onDress(item);
    
//	addChildToContentLayer();
}

void ExtensionScene::onDress(int componentId){
    DataManager* pDataManager=DataManager::sharedDataManager();
    ComponentInfo mComponentInfo=pDataManager->getComponentInfo(componentId);
    onDress(mComponentInfo);
}

void ExtensionScene::offDress(int categoryID){
    Category mCategory=categories[categoryID];
    if(mCategory.name=="bg"){
        bgLayer->removeChildByTag(categoryID);
        return;
    }
    contentLayer->offDress(categoryID);
}

void ExtensionScene::resetModel(){
    DataManager* dataManager=DataManager::sharedDataManager();
    vector<ComponentInfo> defaultItems=dataManager->getAllDefaultDress();
    contentLayer->resetModel(defaultItems);
}

void ExtensionScene::setDefault(){
    DataManager* dataManager=DataManager::sharedDataManager();
    vector<ComponentInfo> defaultItems=dataManager->getAllDefaultDress();
    contentLayer->setDefault(defaultItems);
}

void ExtensionScene::setContentPosition( CCPoint p)
{
	contentLayer->setPosition(p);
}

void ExtensionScene::setConflictInterface( Conflict* conflict)
{
	this->conflict=conflict;
}



