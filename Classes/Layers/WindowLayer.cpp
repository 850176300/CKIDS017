//
//  WindowLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-10-10.
//
//

#include "WindowLayer.h"

CCScene* WindowLayer::scene(){
    CCScene* scene = CCScene::create();

    WindowLayer* layer = WindowLayer::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool WindowLayer::init(){
    if (GameLayerBase::initWithBgFileName(WindowBGPath)) {
        CCSprite* window = CCSprite::create("bg/bg_cleaning_window.png");
        window->setPosition(STVisibleRect::getCenterOfScene());
        addChild(window, 1);
        
        addDust();
        return true;
    }
    return false;
}

void WindowLayer::addDust(){
    _scribble = new Scribble(CCSprite::create("burshes/solid_brush.png"));
    _scribble->setBrushShader();
    _scribble->setTargetSolid(true);
    _scribble->setTargetAlphaTestValue(0.0f);
    _scribble->setBrushType(eScribbleBrushTypeEaser);
    
    dust = DaubSprite::create(_scribble, CCSprite::create("cleaning/window/dust.png"));
    dust->setPosition(STVisibleRect::getCenterOfScene());
    dust->show();
    addChild(dust, 1);
}
