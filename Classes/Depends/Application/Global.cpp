#include "Global.h"

float contentScale=1.0f;
CCSize screenSize;
int resourceType=SF_RESOURCES_1024_768;
float blankArea_width=0;
float blankArea_height=0;
#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
string iapkeys [6] = {"com.hugsnhearts.android_first_kiss.billing_unlock_all",
    "com.hugsnhearts.android_first_kiss.billing_unlock_all_characters",
    "com.hugsnhearts.android_first_kiss.billing_unlock_all_blink_makeup",
    "com.hugsnhearts.android_first_kiss.billing_unlock_all_amazing_hairstyles",
    "com.hugsnhearts.android_first_kiss.billing_unlock_all_dazzling_decorations",
    "com.hugsnhearts.android_first_kiss.billing_unlock_all_sweet_clothes_shoes"};
#else
string iapkeys [6] = {"com.hugsnhearts.firstkisssalon.unlockall",
    "com.hugsnhearts.firstkisssalon.unlockallcharacters",
    "com.hugsnhearts.firstkisssalon.unlockallblinkmakeup",
    "com.hugsnhearts.firstkisssalon.unlockallamazinghairstyle",
    "com.hugsnhearts.firstkisssalon.unlockalldecorations",
    "com.hugsnhearts.firstkisssalon.unlockallclothesshoes"};
#endif
map<int,Category> categories;
map<int,IAPBean> IAPs;
bool soundOn=true;
bool closeAds=true;
CCSize design_size;






