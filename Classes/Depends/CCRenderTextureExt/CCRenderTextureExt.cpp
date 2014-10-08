//
//  CCRenderTextureExt.cpp
//  GIRLS_Framework_part
//
//  Created by renhong on 10/14/13.
//
//

#include "CCRenderTextureExt.h"


ccColor4B CCRenderTextureExt::readPixel(CCRenderTexture *pRenderTexture, GLint pX, GLint pY){
    GLubyte *pTempData = NULL;
    
    do{
        if(! (pTempData = new GLubyte[4])){
            break;
        }
        
        pRenderTexture->begin();
        glPixelStorei(GL_PACK_ALIGNMENT, 1);
        glReadPixels(pX,pY,1, 1,GL_RGBA,GL_UNSIGNED_BYTE, pTempData);
        pRenderTexture->end();
        
    } while (0);
    ccColor4B lColor = {pTempData[0], pTempData[1], pTempData[2], pTempData[3]};
    CC_SAFE_DELETE_ARRAY(pTempData);
    
    return lColor;
}