//
//  SuperGlobal.h
//  CKIDS017
//
//  Created by liuwei on 14-9-12.
//
//

//此头文件，用来包含所有的宏定义。比如结构体定义、每个页面固定不变的参量赋值，以方便后面的reskin更新。该文件包含在pch文件中。其他文件不需要在去手动包含
#ifndef CKIDS017_SuperGlobal_h
#define CKIDS017_SuperGlobal_h

#include <iostream>
#include <sstream>
#include "cocos2d.h"
#include "STVisibleRect.h"
USING_NS_CC;
USING_NS_ST;
using namespace std;

//#define \
//foo(x) \
//({ \
//int xx = (x); \
//int result = (xx > 32) ? xx : (2*xx); \
//result; \
//})
#define \
GetPointString(point) \
({\
stringstream s;\
s<<"{x:"<<point.x<<",y:"<<point.y<<"}";\
s.str().c_str();\
})\

#define \
GetSizeString(size) \
({\
stringstream s;\
s<<"{width:"<<size.width<<",height:"<<size.height<<"}";\
s.str().c_str();\
})\

#define \
GetRectString(rect) \
({\
stringstream s;\
s<<"{original.x:"<<rect.origin.x<<",original.y:"<<rect.origin.y<<", size.width:"<<rect.size.width<<",size.height:"<<rect.size.height<<"}";\
s.str().c_str();\
})\

#define NeedShop 0
#define isAndroid (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define WithOutShop (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID && NeedShop == 0)
#define BABYNUMBER 4

typedef struct LockItem{
    string itemName;
    bool isFree;
}LockItem;

typedef struct FixItem {
    int tag;
    bool beenFixed;
}FixItem;

typedef struct DryClothe{
    string clotheName;
    CCPoint leftPoint;
    CCPoint rightPoint;
}DryClothe;

typedef struct CarItemType{
    string itemName;
    bool isFree;
    CCPoint wheel1Pos;
    CCPoint wheel2Pos;
    CCPoint carPos;
}CarItemType;

typedef struct DeltaPositioin {
    CCPoint deltaPos;
    float deltaRotate;
}DeltaPositioin;

typedef struct ToyPosition{
    CCPoint pos1;
    CCPoint pos2;
}ToyPosition;

typedef struct IapItem{
    string iapKey;
    string itemPng;//资源图片
}IapItem;

#define theLockTagforAll 11111


#pragma "MainMenu Layer"

#define MainMenuBGPath "bg/bg_play.jpg"
#define MainMenuPlayPath "ui/home_btn_play.png"
#define MainMenuShopPath "ui/home_btn_shop.png"
#define MainMenuSoundOnPath "ui/home_btn_sound_on.png"
#define MainMenuSoundOffPath "ui/home_btn_sound_off.png"
#define MainMenuMoreGamePath "ui/home_btn_moregames.png"
#define MainMenuSoundPos ccp(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y+80)
#define MainMenuStartPos ccp(STVisibleRect::getCenterOfScene().x, STVisibleRect::getOriginalPoint().y+324)
#define MainMenuButtonSep 192.0
#define MainMenuKidLogo ccp(595.5, 610.5)


#pragma mark "ChooseRole Layer"
#define ChooseRoleBGPath "bg/bg_select_figure.jpg"
#define BabysJsonPath "datas/babys.json"
#define DryClothePath "datas/dryclothes.json"
#define DeltaDataPath "datas/murals.json"


#pragma mark "House Layer"
#define HouseLayerBGPath "bg/bg_select_game.jpg"

#define FirstHousePP ccp(473.50+112, 356.50-10)
#define HouseSeperateX (543.5-346.5)
#define HouseSeperateY (-395.5+239.5)

#pragma mark "planting Layer"
#define PlantingBGPath "bg/bg_planting.jpg"
#define InsectNUM 6
#define SunTotal 20.0
#define BottlePointDelta ccp(200, 150)
#define SnailCounts 12


#pragma mark "washClothes layer"
#define WashBGPath "bg/bg_washing_clothes.jpg"
#define NodeSize CCSizeMake(258*1.35, 242*1.35) //放置每个种类衣服的size
#define ClothesCount 12

#pragma mark "DryClothe Layer"
#define DryClothesBGPath "bg/bg_drying.jpg"
#define ContainerHeight (189+29)
#define ContainerOffset 100

#pragma mark "cleanRoomLayer"
#define CleanRoomBGPath "bg/bg_cleaning.jpg"
#define WindowBGPath "bg/bg_cleaning_window.jpg"
#define PaintBGPath "bg/bg_painting.jpg"

#pragma mark "SortRoom Layer"
#define SortRoomLayerPath "sorting/room/bg_room.jpg"
#define JumpBGPath "sorting/jump/bg_jump.jpg"
#define SortToyBGPath "sorting/toys_into/bg_toys_into.jpg"
#define BlocksPath "datas/blocks.json"
#define CarsPath "datas/cars.json"
#define DollsPath "datas/dolls.json"
//#define ToysNum 15

#pragma mark "SelectCarLayer"
#define SelectCarBGPath "bg/bg_select_cars.jpg"
#define CarFilePath "datas/carsdata.json"

#pragma mark "WashCarLayer"
#define WashCarBGPath "bg/bg_garage.jpg"

#pragma mark "ShopLayer"
#define ShopFrameBGPath "ui/shop/bg_shop.png"
#define RestorePng "ui/shop/btn_restore.png"
#define ClosePng "ui/shop/btn_close.png"
#define IapDataPath "datas/shopinfo.json"
#endif

