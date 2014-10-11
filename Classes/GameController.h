//
//  GameController.h
//  BBQParty
//
//  Created by liuwei on 14-7-31.
//
//

#ifndef __BBQParty__GameController__
#define __BBQParty__GameController__

#include <iostream>
#include <vector>
#include "SingleTon.h"
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

enum ModelIndex {
    kGirlOne = 0,
    kBoyOne = 1,
    kGirlTwo = 2,
    kBoyTwo = 2
};
class GameController: public SingleTon<GameController> {
    friend class SingleTon<GameController>;
private:
    ModelIndex chooseIndex;
    bool isRemovedAD;
public:
    GameController();
    ~GameController();
    void setisRemoveAD(bool isRemove);
    bool isRemoveADS();
    void setChooseIndex(int index);
    ModelIndex getChooseIndex();
public:
    float getBannerHeight();
//显示所有界面，实现界面的跳转
public:
    void gotoMainMenu(bool LorR = false);
    void gotoChooseRole(bool LorR = false);
    void gotoHouseLayer(bool LorR = false);
    void gotoPlanting(bool reset = false);
    void gotoWashClothes(bool reset = false);
    void gotoDryClothes(bool reset = false);
    void gotoCleanRoom(bool reset = false);
    void gotoRoomWindow(CCObject* pObj);
};

#endif /* defined(__BBQParty__GameController__) */
