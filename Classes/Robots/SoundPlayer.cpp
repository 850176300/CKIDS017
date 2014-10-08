//
//  SoundPlayer.cpp
//  Doctor
//
//  Created by tanshoumei on 13-8-23.
//
//

#include "SoundPlayer.h"
//#include "MathUtil.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

#define RoleCount 4

SoundPlayer::SoundPlayer():
m_uiShakeEffectId(0),
m_uiGermEffectId(0),
m_uiSwabEffectId(0),
m_ballonEffectId(0),
m_fryEffectId(0),
m_striEffectiD(0),
m_drinkID(0),
hasBackGroundMusic(false)
{

    canPlaySound = CCUserDefault::sharedUserDefault()->getBoolForKey("isSoundOpen", true);

    canPlayMusic = CCUserDefault::sharedUserDefault()->getBoolForKey("isMusicOpen", true);
    
    if (canPlayMusic) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.8f);
    }else {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
    }
    if (canPlaySound) {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    }else {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
    }
    
}

void SoundPlayer::switchMusic(){
    canPlayMusic = !canPlayMusic;
    CCUserDefault::sharedUserDefault()->setBoolForKey("isMusicOpen", canPlayMusic);
    CCUserDefault::sharedUserDefault()->flush();
    if (canPlayMusic) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.8f);
    }else {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
    }
    if (canPlaySound) {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    }else {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
    }
}
void SoundPlayer::switchSound(){
    canPlaySound = !canPlaySound;
    CCUserDefault::sharedUserDefault()->setBoolForKey("isSoundOpen", canPlaySound);
    CCUserDefault::sharedUserDefault()->flush();
    if (canPlayMusic) {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.8f);
    }else {
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.0f);
    }
    if (canPlaySound) {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(1.0f);
    }else {
        SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.0f);
    }
}

void SoundPlayer::switchVolume(){
    switchMusic();
    switchSound();
}

bool SoundPlayer::isMusicOpen(){
    return canPlayMusic;
}
bool SoundPlayer::isSoundOpen(){
    return canPlaySound;
}

void SoundPlayer::playBackGroundMusic()
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/bg_mlabs023.mp3", true);
    hasBackGroundMusic = true;
}

void SoundPlayer::pauseBackGroundMusic()
{
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

void SoundPlayer::resumeBackGroundMusic()
{
    if (hasBackGroundMusic == false) {
        playBackGroundMusic();
        return;
    }
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void SoundPlayer::stopBackGroundMusic()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}

void SoundPlayer::stopAllEffect()
{    
    m_uiShakeEffectId = 0;
    m_uiGermEffectId = 0;
    m_uiSwabEffectId = 0;
    
//
    if (m_fryEffectId || m_striEffectiD) {
        if (m_fryEffectId) {
            SimpleAudioEngine::sharedEngine()->pauseEffect(m_fryEffectId);
        }
        if (m_striEffectiD) {
            SimpleAudioEngine::sharedEngine()->pauseEffect(m_striEffectiD);
        }
    }else {
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
    }
    
}

void SoundPlayer::playCommonButtonClickEffect()
{
//    SimpleAudioEngine::sharedEngine()->playEffect("OtherButton.caf");
}

void SoundPlayer::playNextClickedEffect()
{
    SimpleAudioEngine::sharedEngine()->playEffect("sound/next page.mp3");
}

void SoundPlayer::playResetClickedEffect()
{
    SimpleAudioEngine::sharedEngine()->playEffect("sound/reset.mp3");
}

void SoundPlayer::playPlayClickedEffect()
{
    SimpleAudioEngine::sharedEngine()->playEffect("sound/start.mp3");
}


void SoundPlayer::previousGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/previous page.mp3");
}

void SoundPlayer::deleteEffect(){
     SimpleAudioEngine::sharedEngine()->playEffect("sound/delete.mp3");
}
void SoundPlayer::cuthotdogGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/cut.mp3");
}

void SoundPlayer::eatthingsGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/eat.mp3");
}

void SoundPlayer::addeggGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/addegg.caf");
}

void SoundPlayer::addWaterGroundMusic(){
    CCLog("play the drink effect");
    m_drinkID = SimpleAudioEngine::sharedEngine()->playEffect("sound/drink.mp3");
}

void SoundPlayer::stopDrinkMusic()
{
    CCLog("stop play the drink effect");
    if (m_drinkID) {
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
    }
    m_drinkID = 0;
}
void SoundPlayer::startFryGroundMusic(){
    m_fryEffectId = SimpleAudioEngine::sharedEngine()->playEffect("sound/barbeque.mp3", true);
}

void SoundPlayer::stopfryGroundMusic(){
    if (m_fryEffectId) {
        SimpleAudioEngine::sharedEngine()->stopAllEffects();
    }
    m_fryEffectId = 0;
}

void SoundPlayer::resumeAllEffect(){
    if (m_fryEffectId) {
        SimpleAudioEngine::sharedEngine()->playEffect("sound/barbeque.mp3", true);
    }
    if (m_striEffectiD) {
        SimpleAudioEngine::sharedEngine()->playEffect("sound/blender.mp3", true);
    }
}

void SoundPlayer::cowEffect(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/cow.mp3");
}
void SoundPlayer::getMeatEffect(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/get meat.mp3");
}
void  SoundPlayer::getFruitEffct(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/fruit drop.mp3");
}

void SoundPlayer::basketEffect(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/basket.mp3");
}

void SoundPlayer::smileGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/childern happy.mp3");
}

void SoundPlayer::gamerightGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/game_right.mp3");
}

void SoundPlayer::gamewrongGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/game_wrong.mp3");
}

void SoundPlayer::jumpGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/jump.mp3");
}


void SoundPlayer::selectGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/select.mp3");
}


void SoundPlayer::sandGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/sand.mp3");
}

void SoundPlayer::shovelGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/shovel.mp3");
}

void SoundPlayer::ballGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/ball.mp3");
}

void SoundPlayer::ballonGroundMusic(){
    m_ballonEffectId = SimpleAudioEngine::sharedEngine()->playEffect("sound/ballon.mp3");
}

void SoundPlayer::applaudGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/applaud.mp3");
}

void SoundPlayer::addingreGrounMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/add.mp3");
}

void SoundPlayer::striGroundMusic(){
    m_striEffectiD = SimpleAudioEngine::sharedEngine()->playEffect("sound/blender.mp3",true);
}

void SoundPlayer::stopStriGroundMusic(){
    if (m_striEffectiD) {
        SimpleAudioEngine::sharedEngine()->stopEffect(m_striEffectiD);
    }
    m_striEffectiD = 0;
}

void SoundPlayer::drinkGroundMusic(){
    SimpleAudioEngine::sharedEngine()->playEffect("sound/drinking.mp3");
}

