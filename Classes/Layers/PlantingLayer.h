//
//  PlantingLayer.h
//  CKIDS017
//
//  Created by liuwei on 14-9-15.
//
//

#ifndef __CKIDS017__PlantingLayer__
#define __CKIDS017__PlantingLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameLayerBase.h"
#include "Field.h"
#include "MovableItem.h"
#include "SnailLayer.h"
#include "WellDoneLayer.h"
USING_NS_CC;

enum PlantingLayerTags{
    kLeftFieldTag = 2201,
    kMiddleFieldTag = 2202,
    kRightFieldTag = 2203,
    kMubfieldTag = 2221,
    kBabyTags,
    kDugfieldTag,
    kSeedfieldTag,
    kPlantSeedShovelTag,
    kKettlefieldTag,
    kWaterParticleTag,
    kSunTimerProgress1,
    kSunTimerProgress2,
    kSunSpriteTag,
    kLittleSunTag,
    kCloudtag,
    kSnailTags,
    kBottleTopTags,
};

enum PlantingLayerStates{
    kMubing = 0,
    kDuging,
    kSelectSeed,
    kPlantSeed,
    kFirstGrow,
    kInsectShow,
    kSecondGrow,
    kThirdGrow,
    kWatering,
    kWellDone,
};
class PlantingLayer : public GameLayerBase , public FieldDelegate, public MovableItemDelegate, public WellDoneLayerDelegate{
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(PlantingLayer);
    void addlittleSun();
    void onSunClicked();
    void onCloudeClicked();
    virtual void onEnterTransitionDidFinish();
    virtual void onEnter();
    virtual void onExit();
    virtual void ItemDidBackToStartLocation(MovableItem* pItem);
    virtual void itemDidMoved(MovableItem* pItem, CCPoint detla);
    virtual void itemTouchDidBegan(ItemBase* pItem, CCTouch *pTouch);
    virtual void theFieldmudFinished();
    virtual void theHoleDugFinished();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    virtual void onLeftButtonClicked(TapType type);
    virtual void onResetButtonClicked();
private:
    Field* leftField;
    Field* middleField;
    Field* rightField;
    Field* currentField;
    CCSprite* parter;
    PlantingLayerStates currentState;
    void addBaby();
    void performStateChanged();
    void setItemCanMove(MovableItem* pItem);
    /**耕地*/
    MovableItem* rake;
    void addFields();
    void playMubTip();
    void playmubHandAnimation(float dt);
    /**挖洞*/
    MovableItem* shovel;
    void playShovel();
    void playpitHandAnimation(float dt);
    /**选种*/
    SMMenu* theMenu;
    MovableItem* seedItem;
    void showAllSeed();
    void selectTheSeed(CCObject* pObj);
    void showhandTip();
    void settheMenuenble();
    void showhandMoving();
    void theSeedputonField(CCPoint afterPP);
    /**盖土*/
    MovableItem* theShovel;
    void showShovel();
    void playMovingAction();
    void thePlantSeedField(CCPoint afterPP);
    /**洒水 55，136*/
    void showKettle();
    void showkettleTip(float dt);
    MovableItem* kettle;
    void updateField();
    //虫子出现
    int insectsCount;
    void showInsects();
    void addTouchDelegate();
    void removeTouchDelegate();
    void addbatAtPoint(CCPoint location, bool isHit);
    //第二生长阶段
    void showSunAndProgress();
    bool startCloud;
    void addlittleSun1();
    void progressAction(CCNode* pNode, void *upOrdown);
    void updateForCheck();
    void playSunAnimation();
    void createSunsby(int atPos);
    void secondGrowNow();
    //第三阶段生长(将装蜗牛的瓶子分成两个部分加入)
    void showFirstSnail();
    SnailLayer* snailLayer;
    void showTipForSnail(CCSprite *snail);//播放手指指向蜗牛动画
    void addallSnails();//在所有的植物周围添加蜗牛
    void updateForShowSnail();
    int addSnailCount;
    //最后一阶段的浇水，这样才能生长成功
    void addKettleLast();//直接运用上面的洒水工具
    void showWellDone();
};
#endif /* defined(__CKIDS017__PlantingLayer__) */
