#include "ContentLayer.h"


ContentLayer * ContentLayer::create()
{
	ContentLayer * pLayer = new ContentLayer();
	
	if(pLayer && pLayer->initWithColor(ccc4(150,100,200,0)))
	{
		pLayer->autorelease();
		pLayer->setContentSize(CCSize2(design_size.width,design_size.height));
		pLayer->ignoreAnchorPointForPosition(false);
		pLayer->setAnchorPoint(ccp(0.5,0.5));
		pLayer->setPosition(ccp(CCDirector::sharedDirector()->getVisibleSize().width/2,CCDirector::sharedDirector()->getVisibleSize().height/2));
        pLayer->parentPath="";

		return pLayer;
	}
	

	CC_SAFE_DELETE(pLayer);
	return NULL;
}

void ContentLayer::onDress(ComponentInfo item)
{
//        DataManager* dataManager=DataManager::sharedDataManager();
//        Category category=dataManager->getCategory(item.categoryID);

        Category category=categories[item.categoryID];
        CCNode* node;
        
//        int tag = item.categoryID;
//        int count = 1;
    for(int i=0;i<item.textures.size();i++){
        int tag  =1000*i + item.categoryID;
        while ((node = getChildByTag(tag))!= NULL){
             removeChildByTag(tag);
        }
    }
//        while ((node = getChildByTag(tag))!= NULL) {
//            removeChildByTag(tag);
//            tag =1000*count + item.categoryID;
//            count++;
//        }
    
        vector<ComponentTexture> texs=item.textures;
        for (int i=0; i<texs.size(); i++) {
            CCSprite* comSprite=ContentLayer::getSprite(category.name,texs[i]);
            int tag =1000*i + item.categoryID;
            comSprite->setTag(tag);
            comSprite->setScale(item.scale);
            addChild(comSprite, texs[i].zOrder);
            
        }
        
	
}

void ContentLayer::onDress(int componentId){
    DataManager* pDataManager=DataManager::sharedDataManager();
    ComponentInfo mComponentInfo=pDataManager->getComponentInfo(componentId);
    ContentLayer::onDress(mComponentInfo);
}

CCSprite* ContentLayer::getSprite(string category,ComponentTexture tex){
    CCSprite* sprite =Util::getContentSprite((parentPath+ category+"/"+tex.imageName+".png").c_str());
	sprite->retain();
    sprite->setZOrder(tex.zOrder);
    ContentLayer::setDressPosition(sprite, tex.position);
    return sprite;
}

string ContentLayer::getDressPath(string category){
    return NULL;
}

void ContentLayer::offDress(int categoryID){
    CCNode* node;
    int tag = categoryID;
    int count = 1;
    while ((node = getChildByTag(tag))!= NULL) {
        removeChildByTag(tag);
        tag =1000*count+categoryID;
        count++;
    }
}

void ContentLayer::resetModel(vector<ComponentInfo> items){
    ContentLayer::setDefault(items);
}

void ContentLayer::setDefault(vector<ComponentInfo> items){
    DataManager* dataManager=DataManager::sharedDataManager();
    vector<Category> categorys=dataManager->getAllCategory();
    for (int i=0; i<categorys.size(); i++) {
        int result=0;
        Category category=categorys[i];
        for (int j=0; j<items.size(); j++) {
            ComponentInfo item=items[j];
            if (item.categoryID==category.id) {
                result=1;
                ContentLayer::onDress(item);
            }
        }
        if (!result) {
            offDress(category.id);
        }
    }
}

void ContentLayer::setDressPosition(CCNode* node,CCPoint pos){
//    
    node->setAnchorPoint(ccp(0.5, 0.5));
//    node->setPosition(ccp2(pos.x, pos.y));
//    node->setPosition(ccpAdd(ccp2(pos.x, pos.y), ccp(node->getContentSize().width/2, node->getContentSize().height/2)) );
    node->setPosition(ccpAdd(ccp2(pos.x/2, 1024-pos.y/2), ccp(node->getContentSize().width/2, 0-node->getContentSize().height/2)) );
}

void ContentLayer::layoutToTop()
{
	CCPoint p=CCEGLView::sharedOpenGLView()->getVisibleOrigin();
	setPosition(ccp(getPosition().x,getPosition().y+blankArea_height));
}

void ContentLayer::layoutToBottom()
{
	

	setPosition(ccp(getPosition().x,0));
}

void ContentLayer::layoutToLeft()
{
	setPosition(ccp(0,getPosition().y));
}

void ContentLayer::layoutToRight()
{
	CCPoint p=CCEGLView::sharedOpenGLView()->getVisibleOrigin();
	setPosition(ccp(getPosition().x+blankArea_width,getPosition().y));
}
