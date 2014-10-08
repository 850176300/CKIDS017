//
//  SnailLayer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-23.
//
//

#include "SnailLayer.h"
#include "cocos-ext.h"
#include "SuperGlobal.h"

USING_NS_CC_EXT;
#define PTM_RATIO 32
SnailLayer::SnailLayer():theWorld(NULL){
    
}

bool SnailLayer::init(){
    if (CCLayer::init()) {
        addBottle();
        initTheWorld();
        scheduleUpdate();
        CCTextureCache::sharedTextureCache()->addImage("planting/snail.png");
        return true;
    }
    return false;
}

CCRect SnailLayer::getConfilctRect(){
    CCPoint original = this->convertToWorldSpace(bottle->convertToWorldSpace(CCPoint((203-100)/2.0, 298-70)));
    CCRect rect = CCRectMake(original.x, original.y, 100, 50);
//    CCLog("the conflict rect is %s", GetRectString(rect));
    return rect;
}


void SnailLayer::draw(){
    CCLayer::draw();
    
#if CC_ENABLE_BOX2D_INTEGRATION
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    
    kmGLPushMatrix();
    
    theWorld->DrawDebugData();
    
    kmGLPopMatrix();
#endif
}

void SnailLayer::addBottle(){
    bottle = CCSprite::create("planting/bottle.png");
    bottle->setAnchorPoint(ccp(0, 0));
    bottle->setPosition(BottlePointDelta);
    addChild(bottle);
}

void SnailLayer::initTheWorld(){
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    theWorld = new b2World(gravity);
    theWorld->SetAllowSleeping(true);
    
    theWorld->SetContinuousPhysics(true);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);
    
    b2Body* groundBody = theWorld->CreateBody(&groundBodyDef);
    
    b2EdgeShape groundBox;
    
    CCSize contentSize = bottle->getContentSize();
    CCPoint bottomPP = bottle->getPosition();
    
    bottomPP = ccp(bottomPP.x + 30, bottomPP.y+30);
    contentSize = CCSizeMake(contentSize.width-60, contentSize.height);
    // bottom
    groundBox.Set(b2Vec2(bottomPP.x/PTM_RATIO,bottomPP.y/PTM_RATIO), b2Vec2((bottomPP.x+contentSize.width)/PTM_RATIO,bottomPP.y/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(bottomPP.x/PTM_RATIO,(bottomPP.y+contentSize.height)/PTM_RATIO), b2Vec2((bottomPP.x + contentSize.width)/PTM_RATIO,(bottomPP.y + contentSize.height)/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // left
    groundBox.Set(b2Vec2(bottomPP.x/PTM_RATIO,bottomPP.y/PTM_RATIO), b2Vec2(bottomPP.x/PTM_RATIO,(bottomPP.y + contentSize.height)/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // right
    groundBox.Set(b2Vec2((bottomPP.x + contentSize.width)/PTM_RATIO,bottomPP.y/PTM_RATIO), b2Vec2((bottomPP.x + contentSize.width)/PTM_RATIO,(bottomPP.y + contentSize.height)/PTM_RATIO));
    groundBody->CreateFixture(&groundBox,0);
}

void SnailLayer::update(float dt) {
    int velocityIterations = 8;
    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    theWorld->Step(dt, velocityIterations, positionIterations);
}

void SnailLayer::addSnail(cocos2d::CCPoint atPos, bool needFlip /* = false*/) {
    CCTexture2D* spriteTexture = CCTextureCache::sharedTextureCache()->textureForKey("planting/snail.png");
    if (spriteTexture == NULL) {
        spriteTexture = CCTextureCache::sharedTextureCache()->addImage("planting/snail.png");
    }
    CCLOG("Add snail %s",GetPointString(atPos));
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(atPos.x/PTM_RATIO, atPos.y/PTM_RATIO);
    b2Body *body = theWorld->CreateBody(&bodyDef);
    
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(.5f, .5f);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    body->CreateFixture(&fixtureDef);
#if CC_ENABLE_BOX2D_INTEGRATION
    CCPhysicsSprite *sprite = CCPhysicsSprite::createWithTexture(spriteTexture);
    sprite->setFlipX(needFlip);
    addChild(sprite);
    sprite->setB2Body(body);
    sprite->setPTMRatio(PTM_RATIO);
    sprite->setPosition( ccp( atPos.x, atPos.y) );
#endif
}




