//
//  CocosHelper.cpp
//  LibDoctor
//
//  Created by tanshoumei on 13-10-16.
//
//

#include "CocosHelper.h"

CCNode* CocosHelper::openCcbNode(const char * pCCBFileName, const char * pCCNodeName, CCNodeLoader * pCCNodeLoader)
{
    CCNodeLoaderLibrary * ccNodeLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
    if(pCCNodeName != NULL && pCCNodeLoader != NULL) {
        ccNodeLoaderLibrary->registerCCNodeLoader(pCCNodeName, pCCNodeLoader);
    }
    cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(ccNodeLoaderLibrary);
    ccbReader->autorelease();
    CCNode * node = ccbReader->readNodeGraphFromFile(pCCBFileName);
    return node;
}

CCSprite* CocosHelper::getSpriteFromAnimate( const CCAnimate* apAni, const int aFrameInx /*= 0*/)
{
    CCSprite* pRet = NULL;
    if( apAni )
    {
        CCArray * pFrames = apAni->getAnimation()->getFrames();
        if(pFrames && pFrames->count() > aFrameInx )
        {
            CCSpriteFrame* pFrame = ((CCAnimationFrame*)(pFrames->objectAtIndex(0)))->getSpriteFrame();
            pRet = CCSprite::createWithSpriteFrame(pFrame);
        }
    }
    return pRet;
}

CCSprite* CocosHelper::spriteCreateWithNoCache(const char* pName)
{
    CCImage* pimg = new CCImage;
    pimg->initWithImageFile(pName);
    CCTexture2D* pTex = new CCTexture2D;
    pTex->initWithImage(pimg);
    CCSprite* pSpr = CCSprite::createWithTexture(pTex);
    pimg->release();
    pTex->release();
    return pSpr;
}

//void CocosHelper::AddNode(CCNode* apNode, CCNode* apParent, const CCPoint& aPt, const int aZorder, const int aTag)
//{
//    if(apNode && apParent)
//    {
//        apParent->addChild(apNode, aZorder, aTag);
//        apNode->setPosition(aPt);
//    }
//}

void CocosHelper::AddNodeAutoAdapte(CCNode* apNode, CCNode* apParent, const CCPoint& aPt, const int aZorder, const int aTag)
{
    if(apNode && apParent)
    {
        apParent->addChild(apNode, aZorder, aTag);
        STVisibleRect::setPosition(apNode, aPt.x, aPt.y);
    }
}

//根据sprite file name添加精灵到指定位置
CCSprite* CocosHelper::AddSprite( const char* apFileName, CCNode* apParent, const int aZorder, const int aTag)
{
    CCSprite *spr = CCSprite::create(apFileName);
    apParent->addChild(spr, aZorder, aTag);
    return spr;
}

//根据sprite file name添加精灵到指定位置.（不会将texture缓存）
CCSprite* CocosHelper::AddSpriteNoCache( const char* apFileName, CCNode* apParent, const int aZorder, const int aTag)
{
    CCSprite *spr = spriteCreateWithNoCache(apFileName);
    apParent->addChild(spr, aZorder, aTag);
    return spr;
}

//根据sprite frame name添加精灵到指定位置
CCSprite* CocosHelper::AddSpriteByFrame( const char* apFileName, CCNode* apParent, const int aZorder, const int aTag)
{
    CCSpriteFrame* pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(apFileName);
    if(pFrame)
    {
        CCSprite* spr = CCSprite::createWithSpriteFrame(pFrame);
        apParent->addChild(spr, aZorder, aTag);
        return spr;
    }
    return NULL;
}

//将字符串转换成CCRect，可设置数字间分隔符，默认为","
CCRect CocosHelper::stringToRect(std::string aStr, const char* sp /*= ","*/)
{
    int nums[4] = {0};
    const char *tokenPtr = strtok((char*)aStr.c_str(), sp);
    int inx = 0;
    while (NULL != tokenPtr && inx < 4) {
        nums[inx++] = atoi(tokenPtr);
        tokenPtr = strtok(NULL, sp);
    }
    return CCRectMake(nums[0], nums[1], nums[2], nums[3]);
}

//将字符串转换成CCPoint，可设置数字间分隔符，默认为","
CCPoint CocosHelper::stringToPoint(std::string aStr, const char* sp /*= ","*/)
{
    int nums[2] = {0};
    const char *tokenPtr = strtok((char*)aStr.c_str(), sp);
    int inx = 0;
    while (NULL != tokenPtr && inx < 2) {
        nums[inx++] = atoi(tokenPtr);
        tokenPtr = strtok(NULL, sp);
    }
    return CCPointMake(nums[0], nums[1]);
}

//判断点是否在node之内，可用于touch判断
bool CocosHelper::isPointInNode(CCNode* apNode, const CCPoint& aPtWorld)
{
    if(apNode)
    {
        CCRect rect;
        rect.origin = apNode->convertToWorldSpace(CCPointZero);
        rect.size = apNode->getContentSize();
        if(rect.containsPoint(aPtWorld))
            return true;
    }
    return false;
}

CCRect CocosHelper::getNodeRectInWorld(CCNode* apNode)
{
    CCRect rect;
    rect.origin = apNode->convertToWorldSpace(CCPointZero);
    rect.size = apNode->getContentSize();
    return rect;
}

//node content rect center
CCPoint CocosHelper::getNodeCenterLocal(CCNode* apNode)
{
    CCPoint pt;
    if(apNode){
        pt.x = apNode->getContentSize().width * .5;
        pt.y = apNode->getContentSize().height * .5;
    }
    return pt;
}

//根据一张图，生成一个按钮item,其选中效果为变暗，和UIButton差不多
CCMenuItemSprite* CocosHelper::menuItemSprite(const char* aName)
{
    CCSprite* normalSpr = CCSprite::create(aName);
    CCSprite* selectSpr = CCSprite::create(aName);
    selectSpr->setColor(ccGRAY);
    CCMenuItemSprite* item = CCMenuItemSprite::create(normalSpr, selectSpr);
    return item;
}

//当前系统时间(毫秒)
long CocosHelper::milliSecondNow()
{
    struct cc_timeval now;
    CCTime::gettimeofdayCocos2d(&now, NULL);
    return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void CocosHelper::setTouchPriority(cocos2d::CCTouchDelegate *apTouchNode, const int aValue)
{
    if(apTouchNode)
    {
        CCTouchHandler* pHandler = CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(apTouchNode);
        if(pHandler)
            pHandler->setPriority(aValue);
    }
}