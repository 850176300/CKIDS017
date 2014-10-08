#ifndef __CONETNT_LAYER_H__
#define __CONETNT_LAYER_H__
#include <string>
#include "cocos2d.h"
#include "../Application/Heads.h"
USING_NS_CC;
using namespace std;

class ContentLayer:public CCLayerColor{
public:

    static ContentLayer * create();

    void onDress(ComponentInfo item);
    void onDress(int componentId);
    void offDress(int categoryID);
    void resetModel(vector<ComponentInfo> items);
    void setDefault(vector<ComponentInfo> items);
    void setDressPosition(CCNode* node,CCPoint pos);
    
    void layoutToTop();
    void layoutToBottom();
    void layoutToLeft();
    void layoutToRight();
	CCSprite* getSprite(string categoryName,ComponentTexture tex);
    string parentPath;
protected:
   
    string getDressPath(string categoryName);
};


#endif