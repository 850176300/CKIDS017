#ifndef __GLOBAL_HH__
#define __GLOBAL_HH__
#include "cocos2d.h"
#include <string>
#include <Map>

using namespace std;

USING_NS_CC;
//design resolution
extern CCSize design_size;

//scene change time
static const float SCENE_MOVING_TIME=0.25;

//menu type
static const int MENU_TYPE_1=1;
static const int MENU_TYPE_2=2;
static const int MENU_TYPE_3=3;
static const int MENU_TYPE_4=4;
static const int MENU_TYPE_5=5;
static const int MENU_TYPE_6=6;

extern float blankArea_width;
extern float blankArea_height;
extern  float contentScale;
extern CCSize screenSize;
extern int resourceType;
extern bool soundOn;
extern bool closeAds;


#define SF_RESOURCES_1024_768            0
#define SF_RESOURCES_2048_1536           1

#define ccp2(X,Y)(resourceType==SF_RESOURCES_2048_1536? (CCPointMake((float)(X)*2, (float)(Y)*2)):(CCPointMake((float)(X), (float)(Y))))
#define CCSize2(width, height)( resourceType==SF_RESOURCES_2048_1536?CCSize((float)(width*2), (float)(height*2)):CCSize((float)(width), (float)(height)))


/************************************************************************/
/* just for UILayer                                                     */
/************************************************************************/
//#define pUI(X,Y) (CCPointMake((X)/(design_size.width/screenSize.width),(Y)/(design_size.height/screenSize.height)))
#define pUI(X,Y) (ccp((X)/(design_size.width/screenSize.width),(Y)/(design_size.height/screenSize.height)))

//fonts
static const std::string font_felt =
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
"Gotham-Ultra";
#else
"fonts/Gotham-otf";
#endif
#define fontsize(size) (resourceType==SF_RESOURCES_2048_1536) ? (float)(size) * 2 : size

typedef enum
{
    eColorTypeRGB = 0,
    eColorTypeHSV
}ColorType;

struct ComponentInfo
{
	int componentID;
    int categoryID;
	string imageName;
	float scale;
	bool visible;
	ccColor3B color;
	ColorType colorType;
	int opacity;
	vector<struct ComponentTexture> textures;
	//struct ComponentTexture *textures;
    int iapID;
};

struct ComponentTexture
{
	string imageName;
	int zOrder;
	CCPoint position;

} ;


struct Category
{
	string name;
	int id;
	string normalImage;
	string selectedImage;
    string disabledImage;
    int iapID;
};

struct StringBean
{

	int id;
	string Description;
	string Comment;
	string Language;
};

struct IAPBean
{

	int id;
	string key;
	int buyNumber;
};

extern map<int,Category> categories;
extern map<int,IAPBean> IAPs;
extern string iapkeys[];
inline float scribbleTargetScaleRate();

inline float scribbleTargetScaleRate(){
    return (SF_RESOURCES_1024_768 == resourceType) ? 2.0 : 4.0;
}

inline float contentSizeScaleRate();

inline float contentSizeScaleRate(){
    return (SF_RESOURCES_1024_768 == resourceType) ? 1.0 : 2.0;
}

inline CCSize renderTextureSize(CCSprite *pSprite){
    CCSize lSpriteSize = pSprite->getContentSize();
    float lWidth = lSpriteSize.width;
    float lHeight = lSpriteSize.height;
    
    
    const float lFitSize = 370;//min 353
    
    if (lWidth < lFitSize) {
        lWidth = lFitSize;
    }
    if (lHeight < lFitSize) {
        lHeight = lFitSize;
    }
    
    return CCSizeMake(lWidth, lHeight);
}
#endif