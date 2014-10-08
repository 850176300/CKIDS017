//
//  DaubSprite.cpp

//
//  Created by chenxi1 on 13-10-23.
//
//

#include "DaubSprite.h"


DaubSprite::DaubSprite():width(0),height(0),resHeight(0),offsetX(0),offsetY(0),_total(1){
    
}

DaubSprite::~DaubSprite(){
    sprite->release();
}

DaubSprite* DaubSprite::create( Scribble *scribble,CCSprite *sprite){
    DaubSprite *pRet = new DaubSprite();
    CCSize size = sprite->getContentSize();
    CCLog("sprite->getContentSize(%f,%f)",size.width, size.height);
    if(pRet && pRet->initWithWidthAndHeight(size.width, size.height, kCCTexture2DPixelFormat_RGBA8888, 0))
    {
        pRet->scribble=scribble;
        pRet->sprite=sprite;
        pRet->sprite->retain();
        pRet->resWidth =size.width;
        pRet->resHeight =size.height;
        CCSize size = pRet->getContentSize();
        if (pRet->resWidth<size.width) {
            pRet->offsetX =pRet->resWidth-size.width;
        }
        if(pRet->resHeight<size.height){
            pRet->offsetY =size.height-pRet->resHeight;
        }
        pRet->isDaub=false;
//        pRet->setContentSize(renderTextureSize(w, h));
        scribble->removeTargetObserver(pRet);
        pRet->changeTarget(sprite);
        pRet->show();
         pRet->_total =  pRet->calcute(pRet->newCCImage());
        pRet->clear(0, 0, 0, 0);
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}
DaubSprite* DaubSprite::create(CCSize size, Scribble *scribble,CCSprite *sprite){
    DaubSprite *pRet = new DaubSprite();
//    CCSize size = sprite->getContentSize();
    if(pRet && pRet->initWithWidthAndHeight(size.width, size.height, kCCTexture2DPixelFormat_RGBA8888, 0))
    {
        pRet->scribble=scribble;
        pRet->sprite=sprite;
        pRet->sprite->retain();
        pRet->resWidth =size.width;
        pRet->resHeight =size.height;
        CCSize size = pRet->getContentSize();
        if (pRet->resWidth<size.width) {
            pRet->offsetX =pRet->resWidth-size.width;
        }
        if(pRet->resHeight<size.height){
            pRet->offsetY =size.height-pRet->resHeight;
        }
        pRet->isDaub=false;
        //        pRet->setContentSize(renderTextureSize(w, h));
        scribble->removeTargetObserver(pRet);
        pRet->changeTarget(sprite);
        pRet->show();
        pRet->_total =  pRet->calcute(pRet->newCCImage());
        pRet->clear(0, 0, 0, 0);
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

 bool DaubSprite::initWithWidthAndHeight(int w, int h, CCTexture2DPixelFormat eFormat, GLuint uDepthStencilFormat){
    const float lFitSize = 370;//min 353
    
    if (w < lFitSize) {
        w = lFitSize;
        
    }
  this->   width = w;
    
    if (h < lFitSize) {
        h = lFitSize;
    }
   this-> height = h;
    return CCRenderTexture::initWithWidthAndHeight(w, h,eFormat,uDepthStencilFormat);
   
    
}

void DaubSprite::onEnter(){
    if (isDaub) {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    }
    
    CCRenderTexture::onEnter();
    
//    CCSize size=getContentSize();
//    soundRect=CCRect(blankArea_height+getPositionX()-size.width/2, getPositionY()-size.height/2, size.width, size.height);
}

void DaubSprite::onExit(){
    if (isDaub) {
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    }
    CCRenderTexture::onExit();
}

bool DaubSprite::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
  
    
    return true;
}

void DaubSprite::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
//    CCPoint pos=pTouch->getLocation();
    
    this->paint(pTouch->getLocation(), pTouch->getPreviousLocation());
    CCLog("the easera percent is %.2f", easePercent());
}

void DaubSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){

}

void DaubSprite::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){

}

CCObject* DaubSprite::copyWithZone(CCZone *pZone){
    this->retain();
    return this;
}

void DaubSprite::touchDelegateRetain()
{
    this->retain();
}

void DaubSprite::touchDelegateRelease()
{
    this->release();
}

void DaubSprite::setEnableDaub(bool isDaub){
    if (this->isDaub == isDaub) {
        return;
    }
    this->isDaub=isDaub;
    if (isDaub) {
        CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, false);
    }else{
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    }
}

void DaubSprite::paint(CCPoint lTouchPoint,CCPoint lpreTouchPoint){
    scribble->paint(sprite, this, lTouchPoint,lpreTouchPoint);
}
void DaubSprite::changeTarget(CCSprite *lTarget,bool mClean){
    lTarget->retain();
    CCSize size =  this->getContentSize();
    lTarget->setPosition( ccp(width/2+offsetX,height/2+offsetY)  );
    this->sprite = lTarget;

    if(mClean){
        CCRenderTexture::clear(0,0,0,0);
    }
}
void DaubSprite::show(){
    if(this->sprite==NULL){
        return;
    }
    this->begin();
    this->sprite->visit();
    this->end();
}
long DaubSprite::calcute(CCImage *pImage){
    long lCounter = 0;
    for (long i = 0; i < pImage->getHeight(); ++i) {
        for (long j = 0; j < pImage->getWidth(); ++j) {
            unsigned char *lData = pImage->getData();
            long lPixcelIndex = i * pImage->getWidth() + j;
            unsigned char lRed = lData[lPixcelIndex * 4];
            unsigned char lGreen = lData[lPixcelIndex * 4 + 1];
            unsigned char lBlue = lData[lPixcelIndex * 4 + 2];
            unsigned char lAlpha = lData[lPixcelIndex * 4 + 3];
            if (lAlpha > 10) {
                if (lRed > 0 || lGreen > 0 || lBlue > 0) {
                    ++lCounter;
                }
            }
        }
    }
//    CCLog("texture img count %ld",lCounter);
//    CCLog("texture total count %ld",_total);
    
    return lCounter;
}
float DaubSprite::paintPercent(){
    return this->calcute(this->newCCImage()) / (this->_total * 1.0);
}
float DaubSprite::easePercent(){
    return 1-this->calcute(this->newCCImage()) / (this->_total * 1.0);
}