
#ifndef _GRIDVIEW_ITEMCLICK_CALLBACK_H
#define _GRIDVIEW_ITEMCLICK_CALLBACK_H
#include "cocos2d.h"

USING_NS_CC;
class GridViewItemClickCallBack {
public:
    virtual void onGridItemClick(CCObject* obj, int index) = 0;
};

#endif
