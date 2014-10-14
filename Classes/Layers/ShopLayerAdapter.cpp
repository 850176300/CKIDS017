//
//  ShopLayerAdapter.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-14.
//
//

#include "ShopLayerAdapter.h"
#include "STVisibleRect.h"
USING_NS_ST;
ShopLayerAdapter::ShopLayerAdapter(){
    _shopLayer = ShopLayer::create();
    _shopLayer->setPosition(STVisibleRect::getOriginalPoint());
    _shopLayer->retain();
}

ShopLayerAdapter::~ShopLayerAdapter(){
    CC_SAFE_RELEASE(_shopLayer);
}

void ShopLayerAdapter::showShopInNode(cocos2d::CCNode *pNode) {
    _shopLayer->showinNode(pNode);
}


