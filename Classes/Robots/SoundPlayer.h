//
//  SoundPlayer.h
//  Doctor
//
//  Created by tanshoumei on 13-8-23.
//
//

#ifndef __Doctor__SoundPlayer__
#define __Doctor__SoundPlayer__

#include <iostream>
#include "SingleTon.h"


class SoundPlayer: public SingleTon<SoundPlayer>
{
    friend class SingleTon<SoundPlayer>;
private:
    SoundPlayer();
public:
    //背景音乐
    void playBackGroundMusic();
    void pauseBackGroundMusic();
    void resumeBackGroundMusic();
    void stopBackGroundMusic();
    
    void deleteEffect();
    void previousGroundMusic();
    void cowEffect();
    void cuthotdogGroundMusic();
    void eatthingsGroundMusic();
    void getMeatEffect();
    void getFruitEffct();
    void basketEffect();
    void addeggGroundMusic();
    void addWaterGroundMusic();
    void startFryGroundMusic();
    void stopfryGroundMusic();
    void gamerightGroundMusic();
    void gamewrongGroundMusic();
    void jumpGroundMusic();
    void selectGroundMusic();
    void sandGroundMusic();
    void shovelGroundMusic();
    void ballGroundMusic();
    void ballonGroundMusic();
    void applaudGroundMusic();
    void addingreGrounMusic();
    void smileGroundMusic();
    void striGroundMusic();
    void stopStriGroundMusic();
    void drinkGroundMusic();
    
    void stopAllEffect();
    void resumeAllEffect();

    void playPlayClickedEffect();
    void playCommonButtonClickEffect();
    void playNextClickedEffect();
    void playResetClickedEffect();
    void switchMusic();
    void switchSound();
    void switchVolume();
    bool isMusicOpen();
    bool isSoundOpen();
    void stopDrinkMusic();
private:
    unsigned int m_uiShakeEffectId;
    unsigned int m_uiGermEffectId;
    //棉签音效id
    unsigned int m_uiSwabEffectId;
    unsigned int m_fryEffectId;
    unsigned int m_ballonEffectId;
    unsigned int m_striEffectiD;
    unsigned int m_drinkID;
    bool hasBackGroundMusic;
    bool canPlayMusic;
    bool canPlaySound;
//    bool haveVolume;
    
    
};

#define SoundPlayerInstance SoundPlayer::getInstance()

#endif /* defined(__Doctor__SoundPlayer__) */
