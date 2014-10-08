//
//  CCRenderTextureExt.h
//  GIRLS_Framework_part
//
//  Created by renhong on 10/14/13.
//
//

#ifndef __GIRLS_Framework_part__CCRenderTextureExt__
#define __GIRLS_Framework_part__CCRenderTextureExt__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CCRenderTextureExt {
    
    
public:
    static ccColor4B readPixel(CCRenderTexture *pRenderTexture, GLint pX, GLint pY);
};

#endif /* defined(__GIRLS_Framework_part__CCRenderTextureExt__) */
