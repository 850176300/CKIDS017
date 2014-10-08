//
//  MaskSprite.h
//  Doctor2
//
//  Created by tanshoumei on 13-9-15.
//
//

#ifndef __Doctor2__MaskSprite__
#define __Doctor2__MaskSprite__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

class MaskSprite: public CCSprite
{
public:
    static MaskSprite* create(const char* asName);
    
    virtual bool initWithTexture(CCTexture2D *pTexture, const CCRect& rect, bool rotated);
    
    virtual void draw();
    
private:
    GLuint	_textureLocation;
	GLuint	_maskLocation;
    CCTexture2D * _maskTexture;
};

#endif /* defined(__Doctor2__MaskSprite__) */
