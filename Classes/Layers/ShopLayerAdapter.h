//
//  ShopLayerAdapter.h
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#ifndef __CKIDS017__ShopLayerAdapter__
#define __CKIDS017__ShopLayerAdapter__

#include <iostream>
#include "SingleTon.h"
#include "ShopLayer.h"
class ShopLayerAdapter: public SingleTon<ShopLayerAdapter>{
    friend class SingleTon<ShopLayerAdapter>;
public:
    ShopLayerAdapter();
    ~ShopLayerAdapter();
    void showShopInNode(CCNode* pNode);
private:
    ShopLayer* _shopLayer;
};
#endif /* defined(__CKIDS017__ShopLayerAdapter__) */
