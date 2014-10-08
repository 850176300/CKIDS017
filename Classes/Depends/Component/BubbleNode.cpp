//
//  BubbleNode.cpp
//  BHUG023-Princess_Makeove_Salon
//
//  Created by liuhailong1 on 13-10-30.
//
//

#include "BubbleNode.h"

BubbleNode::BubbleNode(const char* _bubbleFile){
    bubbles=CCArray::create();
    bubbles->retain();
    bubbleFile=_bubbleFile;
    //默认动画执行事件
    duration=0.3f;
    bubbleInterval=150;
    beTransparent=true;
    beRemove=false;
    listenerObject=NULL;
    selector=NULL;
    maxBubbles=0;
    batchNode = CCSpriteBatchNode::create(Util::getUIFilePath(_bubbleFile).c_str());
    batchNode->setPosition(CCPointZero);
    
    this->addChild(batchNode);
    
}
BubbleNode::~BubbleNode(){
    bubbles->release();
}

BubbleNode* BubbleNode::create(const char* bubbleFile){
    BubbleNode* bubble=new BubbleNode(bubbleFile);
    //bubble->initWithColor(ccc4(255, 150, 200, 150));
    bubble->init();
    bubble->setTouchEnabled(true);
    bubble->setTouchMode(kCCTouchesOneByOne);
    bubble->autorelease();
    return bubble;
}

void BubbleNode::addBubble(CCPoint position){
   
    if(maxBubbles!=0&&bubbles->count()>=maxBubbles)
    {
        return;
    }
    CCSprite* bubble=CCSprite::createWithTexture(batchNode->getTexture());
    bubble->setPosition(position);
    bubble->setScale(0.01f);
    batchNode->addChild(bubble);
    bubbles->addObject(bubble);
    
    CCSpawn* actions;
    CCScaleTo* scale=CCScaleTo::create(duration, 1);
    if(beTransparent)
    {
        CCFadeIn *fade=CCFadeIn::create(duration);
        actions=CCSpawn::create(scale, fade,NULL);
    }else{
        actions=CCSpawn::create(scale, NULL);
    }
   
   
    bubble->runAction(actions);
}
void BubbleNode::removeBubble(CCSprite* bubble){
    bubbles->removeObject(bubble);
    CCSpawn* actions;
    CCScaleTo* scale=CCScaleTo::create(duration, 0.01);
    if(beTransparent)
    {
        CCFadeOut *fade=CCFadeOut::create(duration);
        actions=CCSpawn::create(scale, fade,NULL);
    }else{
        actions=CCSpawn::create(scale, NULL);
    }
    
    CCSequence* seq=CCSequence::create(actions,	CCCallFuncND::create(this, callfuncND_selector(BubbleNode::actionCallback), (void*)bubble),NULL);
    bubble->runAction(seq);
    
}
void BubbleNode::convertMode(){
    beRemove=beRemove?false:true;
}
void BubbleNode::removeBubble(CCPoint point){
    long nowTime=Util::getCurrentTime();
    if(abs(nowTime-preTime)<bubbleInterval)
    {
        return;
    }
    CCPoint localPosi=convertToNodeSpace(point);
    for (int i=bubbles->count()-1; i>=0; i--) {
        CCSprite* bubble=(CCSprite*)bubbles->objectAtIndex(i);
        if(bubble->boundingBox().containsPoint(localPosi))
        {
            removeBubble(bubble);
            break;
        }
    }
}
void BubbleNode::actionCallback(CCNode* node, void* args){
    removeChild(node);
    
}
void BubbleNode::setDuration(float _duration){
    duration=_duration;
}

bool BubbleNode::isAddBubble(){
    return !beRemove;
}

void BubbleNode::setInterval(long _interval){
    bubbleInterval=_interval;
}
void BubbleNode::setTransparent(bool _transparent){
    beTransparent=_transparent;
}
int BubbleNode::getBubbleCount(){
    return bubbles->count();
}
void BubbleNode::setCallback(CCObject* target, SEL_CallFuncND _selector){
    listenerObject=target;
    selector=_selector;
}
void BubbleNode::setMaxBubbles(int _maxBubbles){
    maxBubbles=_maxBubbles;
}
bool BubbleNode::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    CCPoint posi=this->getParent()->convertToNodeSpace(pTouch->getLocation());
   if(boundingBox().containsPoint(posi))
   {
       if(listenerObject!=NULL&&selector!=NULL){
           int lTouchType = CCTOUCHBEGAN;
           (listenerObject->*selector)(this,(void*)&lTouchType);
       }
       if(beRemove)
       {
           removeBubble(pTouch->getLocation());
       }else{
           addBubble(this->convertToNodeSpace(pTouch->getLocation()));
       }
       
       preTime=Util::getCurrentTime();
       return true;
   }
    return false;
}
void BubbleNode::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent){
    long moveTime=Util::getCurrentTime();
    CCPoint posi=this->getParent()->convertToNodeSpace(pTouch->getLocation());
    if(listenerObject!=NULL&&selector!=NULL){
        int lTouchType = CCTOUCHMOVED;
        (listenerObject->*selector)(this,(void*)&lTouchType);
    }
    if(beRemove)
    {
        removeBubble(pTouch->getLocation());
    }else  if(abs(moveTime-preTime)>=bubbleInterval&&boundingBox().containsPoint(posi))
    {
        
       addBubble(this->convertToNodeSpace(pTouch->getLocation()));
       preTime=moveTime;
        
    }
}
void BubbleNode::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if(listenerObject!=NULL&&selector!=NULL){
        int lTouchType = CCTOUCHENDED;
        (listenerObject->*selector)(this,(void*)&lTouchType);
    }
}
void BubbleNode::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
    ccTouchEnded(pTouch,pEvent);
//    if(listenerObject!=NULL&&selector!=NULL){
//        (listenerObject->*selector)(this,(void*)CCTOUCHCANCELLED);
//    }
}
