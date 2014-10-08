//
//  CocosHelper.h
//  Burgers
//
//  Created by tanshoumei on 13-6-26.
//
//

#ifndef Burgers_CocosHelper_h
#define Burgers_CocosHelper_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "STVisibleRect.h"

using namespace std;

USING_NS_CC;
USING_NS_ST;
using namespace cocos2d::extension;

#define CH_RETURN_IF(cond) if(cond) return;

class CocosHelper {
public:
    /*
     根据ccbi文件，生成CCNode.
     pCCBFileName: ccbi文件名
     pCCNodeName: 此CCNode注册的名字，
     **/
    static CCNode* openCcbNode(const char * pCCBFileName, const char * pCCNodeName, cocos2d::extension::CCNodeLoader * pCCNodeLoader);
    /*
     从CCAniamte中获取CCSprite
     aFrameInx: 帧索引，返回相应的帧生成CCSprite。
     **/
    static CCSprite* getSpriteFromAnimate( const CCAnimate* apAni, const int aFrameInx = 0);
    
    //实例化CCSprite对象，不添加纹理缓存
    static CCSprite* spriteCreateWithNoCache(const char* pName);
    
    //添加node到指定坐标, 提供的坐标会根据屏幕适配变化。
    static void AddNodeAutoAdapte(CCNode* apNode, CCNode* apParent, const CCPoint& aPt, const int aZorder, const int aTag);
    
    //根据sprite file name添加精灵到指定位置
    static CCSprite* AddSprite( const char* apFileName, CCNode* apParent, const int aZorder, const int aTag);
    
    //根据sprite file name添加精灵到指定位置.（不会将texture缓存）
    static CCSprite* AddSpriteNoCache( const char* apFileName, CCNode* apParent, const int aZorder, const int aTag);

    //根据sprite frame name添加精灵到指定位置
    static CCSprite* AddSpriteByFrame( const char* apFileName, CCNode* apParent, const int aZorder, const int aTag);
    
    //将字符串转换成CCRect，可设置数字间分隔符，默认为","
    static CCRect stringToRect(std::string aStr, const char* sp = ",");
    
    //将字符串转换成CCPoint，可设置数字间分隔符，默认为","
    static CCPoint stringToPoint(std::string aStr, const char* sp = ",");
    
    //判断点是否在node之内，可用于touch判断
    static bool isPointInNode(CCNode* apNode, const CCPoint& aPtWorld);
    
    static CCRect getNodeRectInWorld(CCNode* apNode);
    
    //node content rect center
    static CCPoint getNodeCenterLocal(CCNode* apNode);
    
    //根据一张图，生成一个按钮item,其选中效果为变暗，和UIButton差不多
    static CCMenuItemSprite* menuItemSprite(const char* aName);
    
    //设置节点的触摸优秀级
    static void setTouchPriority(CCTouchDelegate* apTouchNode, const int aValue);

    //当前系统时间(毫秒)
    static long milliSecondNow();
};

#endif
