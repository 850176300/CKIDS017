//
//  ChooseRole.h
//  CKIDS017
//
//  Created by liuwei on 14-9-12.
//
//

#ifndef __CKIDS017__ChooseRole__
#define __CKIDS017__ChooseRole__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "DRScrollView.h"
#include "Baby.h"
USING_NS_CC;
class ChooseRole : public GameLayerBase, public BabyDelegate, public DRScrollViewDelegate
{
    
private:
    DRScrollView* scrollView;
    void createCrollView();
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(ChooseRole);
    virtual void onBabyClicked(int index);
    
    virtual void onEnterTransitionDidFinish();
    virtual void onEnter();
    virtual void onExit();
};
#endif /* defined(__CKIDS017__ChooseRole__) */
