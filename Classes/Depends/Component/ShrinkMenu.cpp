//
//  ControlMenu.cpp
//  BHUG023-Princess_Makeove_Salon
//
//  Created by liuhailong1 on 13-10-25.
//
//

#include "ShrinkMenu.h"
#include <stdio.h>
#include <stdarg.h>
#include "../Application/Heads.h"

ShrinkMenu::ShrinkMenu():orientation(PORTRAIT),isLock(false),isOpen(true),duration(0.25),menuCallback(NULL),menuHeight(0.0),menuWidth(0.0),padding(0.0)
{
    menuItems=CCArray::create();
    menuItems->retain();
}
ShrinkMenu::~ShrinkMenu(){
    menuItems->release();
    originalPos.clear();
}
ShrinkMenu* ShrinkMenu::create(int _orientation)
{
    ShrinkMenu* menu =new ShrinkMenu();
    menu->init();
	
    menu->orientation=_orientation;
    menu->autorelease();
    
	return menu;
}

void ShrinkMenu::createMenu(int count, ... )
{
    if(count<=0)
		return;
    
    //背景条
    bgBar=Util::getUISprite("shrinkbg.png");
    bgBar->setAnchorPoint(ccp(0.5,0.5));
    
    CCClippingNode	*clipper = CCClippingNode::create();
    addChild(clipper);
    clipper->addChild(bgBar);
    
    
    mainItem = CCMenuItemSprite::create(Util::getUISprite("control.png"),Util::getUISprite("control.png"), this, menu_selector(ShrinkMenu::controlMenuCallback));
    mainItem->setUserData((void*)99);
    mainItem->setPosition(ccp(mainItem->getContentSize().width/2,mainItem->getContentSize().height/2));
   
    mainMenu=CCMenu::create(mainItem,NULL);
	mainMenu->setTouchMode(kCCTouchesOneByOne);
    mainMenu->setPosition(ccp2(0, 0));
    addChild(mainMenu);
    
   setContentSize(mainItem->getContentSize());
    
    
	va_list vl ;
	va_start(vl, count);

	for(int i=0; i<count; ++i)
	{
		char* p = va_arg(vl, char*);
		string file1=".png";
		string file2="_h.png";
        CCLOG("---menuHeight:%s  %f",p,menuHeight);
		CCMenuItemSprite* item = CCMenuItemSprite::create(Util::getUISprite((p+file1).c_str()),Util::getUISprite((p+file2).c_str()), this, menu_selector(ShrinkMenu::controlMenuCallback));
        if(orientation==PORTRAIT)
        {
            menuHeight+=padding;
        }else if(orientation==LANDSCAPE)
        {
            menuWidth+=padding;
        }
		if (p=="music"&&!soundOn)
		{
			item->setNormalImage(Util::getUISprite("music_off.png"));
			item->setSelectedImage(Util::getUISprite("music_off_h.png"));
		}
		item->setUserData((void*)i);
		if(orientation==PORTRAIT){
            item->setPosition(ccp(mainItem->getContentSize().width/2, -menuHeight-item->getContentSize().height/2));
        }else{
             item->setPosition(ccp(menuWidth+item->getContentSize().width/2+mainItem->getContentSize().width, mainItem->getContentSize().height/2));
        }
        
		menuHeight+=item->getContentSize().height;
		menuWidth+=item->getContentSize().width;
		menuItems->addObject(item);

        originalPos.insert(pair<CCObject*,CCPoint>(item,item->getPosition()));
        
	}
	va_end( vl );
    //与背景条边框的间隔
    if(orientation==PORTRAIT)
    {
        menuHeight+=padding;
    }else if(orientation==LANDSCAPE)
    {
        menuWidth+=padding;
    }
    
    //设置剪切区域
    CCDrawNode *stencil = CCDrawNode::create();
    CCPoint rectangle[4];
    
    if(orientation==LANDSCAPE)
    {
        bgBar->setPosition(ccp(mainItem->getContentSize().width+menuWidth-bgBar->getContentSize().width/2,mainItem->getContentSize().height/2));
        clipper->setContentSize(CCSizeMake(mainItem->getContentSize().width/2+menuWidth, mainItem->getContentSize().height));
        rectangle[0] = ccp(mainItem->getContentSize().width/2, -clipper->getContentSize().height);
        rectangle[1] = ccp(clipper->getContentSize().width+mainItem->getContentSize().width/2, -clipper->getContentSize().height);
        rectangle[2] = ccp(clipper->getContentSize().width+mainItem->getContentSize().width/2, mainItem->getContentSize().height);
        rectangle[3] = ccp(mainItem->getContentSize().width/2, mainItem->getContentSize().height);
        
    }else{
        bgBar->setPosition(ccp(mainItem->getContentSize().width/2,bgBar->getContentSize().height-menuHeight-bgBar->getContentSize().height/2));
        clipper->setContentSize(CCSizeMake(mainItem->getContentSize().width, mainItem->getContentSize().height/2+menuHeight));
        rectangle[0] = ccp(0, -clipper->getContentSize().height+mainItem->getContentSize().height/2);
        rectangle[1] = ccp(clipper->getContentSize().width, -clipper->getContentSize().height+mainItem->getContentSize().height/2);
        rectangle[2] = ccp(clipper->getContentSize().width, mainItem->getContentSize().height/2);
        rectangle[3] = ccp(0, mainItem->getContentSize().height/2);
    }
   
    originalPos.insert(pair<CCObject*,CCPoint>(bgBar,bgBar->getPosition()));

    
    ccColor4F white = {1, 1, 1, 1};
    stencil->drawPolygon(rectangle, 4, white, 1, white);

    clipper->setStencil(stencil);
   
	CCMenu* mMenu=CCMenu::createWithArray(menuItems);
	mMenu->setTouchMode(kCCTouchesOneByOne);
    mMenu->setPosition(ccp2(0, 0));
    clipper->addChild(mMenu);

}

void ShrinkMenu::setPadding(float _padding){
    padding=_padding;
}

void ShrinkMenu::controlMenuCallback(CCObject* obj){
    if(isLock)
    {
        return;
    }
    CCMenuItem* menuItem=(CCMenuItem*)obj;
    int tag=(int)menuItem->getUserData();
    if(tag==99)
    {
        
            if(isOpen)
                doCloseWithDuration();
            else
                doOpenWithDuration();

    }else if(menuCallback!=NULL)
    {
        menuCallback->onMenuClick(tag);
    }
    
}
void ShrinkMenu::doOpenWithDuration(){
    if(isOpen)
        return;
    isLock=true;
    for (int i=0;i<menuItems->count(); i++) {
        
        CCMenuItemSprite* menuItem=(CCMenuItemSprite*)menuItems->objectAtIndex(i);
        CCPoint posi=originalPos[menuItem];
        CCActionInterval*  actionTo = CCMoveTo::create(duration, posi);
        menuItem->runAction(actionTo);
        
    }
    CCActionInterval*  bgAction = CCMoveTo::create(duration, originalPos[bgBar]);
    bgBar->runAction(CCSequence::create(bgAction,CCCallFuncND::create(this, callfuncND_selector(ShrinkMenu::actionCallback), (void*)2), NULL));
    if(menuCallback!=NULL)
    {
        menuCallback->onOpening();
    }

}
void ShrinkMenu::doCloseWithDuration(){
    if(!isOpen)
        return;
    isLock=true;
    for (int i=0;i<menuItems->count(); i++) {
        CCMenuItemSprite* menuItem=(CCMenuItemSprite*)menuItems->objectAtIndex(i);
        menuItem->runAction((CCActionInterval*)getAction(menuItem));
    
    }

    bgBar->runAction(CCSequence::create(getAction(bgBar),CCCallFuncND::create(this, callfuncND_selector(ShrinkMenu::actionCallback), (void*)1), NULL));
    if(menuCallback!=NULL)
    {
        menuCallback->onClosing();
    }
}

void ShrinkMenu::doOpen(){
    if(isOpen)
        return;
    isLock=true;
    for (int i=0;i<menuItems->count(); i++) {
        
        CCMenuItemSprite* menuItem=(CCMenuItemSprite*)menuItems->objectAtIndex(i);
        CCPoint posi=originalPos[menuItem];
        
        menuItem->setPosition(posi);
        
    }
    bgBar->setPosition(originalPos[bgBar]);
    bgBar->runAction(CCSequence::create(CCCallFuncND::create(this, callfuncND_selector(ShrinkMenu::actionCallback), (void*)2), NULL));
    if(menuCallback!=NULL)
    {
        menuCallback->onOpening();
    }
}
void ShrinkMenu::doClose(){
    if(!isOpen)
        return;
    isLock=true;
    for (int i=0;i<menuItems->count(); i++) {
        CCMenuItemSprite* menuItem=(CCMenuItemSprite*)menuItems->objectAtIndex(i);
        
        if(orientation==LANDSCAPE)
        {

            menuItem->setPosition(ccp(mainItem->getPositionX()-menuItem->getContentSize().width/2,mainItem->getPositionY()));
        }else{
            menuItem->setPosition(ccp(mainItem->getPositionX(),mainItem->getPositionY()+menuItem->getContentSize().height/2));
        }
    }
    if(orientation==LANDSCAPE)
    {
        
        bgBar->setPosition(ccp(mainItem->getPositionX()-bgBar->getContentSize().width/2,mainItem->getPositionY()));
    }else{
        bgBar->setPosition(ccp(mainItem->getPositionX(),mainItem->getPositionY()+bgBar->getContentSize().height/2));
    }
    bgBar->runAction(CCSequence::create(CCCallFuncND::create(this, callfuncND_selector(ShrinkMenu::actionCallback), (void*)1), NULL));
    if(menuCallback!=NULL)
    {
        menuCallback->onClosing();
    }
}

void ShrinkMenu::actionCallback(CCNode* node, void* _tag){
    isLock=false;
    int tag=(int)_tag;
    if(tag==1)//close action finished
    {

        isOpen=false;
    }else{//open action finished
        isOpen=true;
    }
}

CCActionInterval* ShrinkMenu::getAction(CCNode* node)
{
    if(orientation==LANDSCAPE)
    {
        return CCMoveTo::create(duration, ccp(mainItem->getPositionX()-node->getContentSize().width/2,mainItem->getPositionY()));
    }else{
        return CCMoveTo::create(duration, ccp(mainItem->getPositionX(),mainItem->getPositionY()+node->getContentSize().height/2));
    }
}

void ShrinkMenu::setMenuCallback(ShrinkMenuCallback* _callback){
    menuCallback=_callback;
}
