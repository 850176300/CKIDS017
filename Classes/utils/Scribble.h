//
//  Scribble.h
//  GIRLS_Framework_part
//
//  Created by renhong on 9/12/13.
//
//

#ifndef __GIRLS_Framework_part__Scribble__
#define __GIRLS_Framework_part__Scribble__
#include <cocos2d.h>
#include <iostream>
#include <string>
using namespace cocos2d;
using namespace std;

#define kCCShader_PositionTextureColorAlphaTest_Scribble "CCShader_PositionTextureColorAlphaTest_Scribble"
#define kCCUniformSampler_s_Scribble "CC_Texture1"

typedef enum
{
    eScribbleBrushTypeBrush,
    eScribbleBrushTypeEaser
}ScribbleBrushType;

class Scribble {
private:
    CCSprite *_brush;
    ScribbleBrushType _brushType;
private:
    CCGLProgram *loadDefaultShader(const GLchar *pShaderString);
    
public:
    Scribble(CCSprite *pBrush);
    ~Scribble();
    void antiAliasing(CCRenderTexture *pRenderTexture);
    void disAntiAliasing(CCRenderTexture *pRenderTexture);
    
    void paint(CCSprite *pTarget, CCRenderTexture *pCanvas, CCPoint pPosition);
    void paint(CCSprite *pTarget, CCRenderTexture *pCanvas, CCPoint pStartPosition, CCPoint pEndPosition);
    void paint(CCSprite *pTarget, CCRenderTexture *pCanvas, vector<CCPoint> pWorldPositions);
    
    void setBrush(CCTexture2D *pBrushTexture);
    inline CCSprite *getBrush(){return _brush;}
    void setBrushShader();
    void setBrushType(ScribbleBrushType pType = eScribbleBrushTypeBrush);
    void setBrushAlphaTestValue(float pAlphaValue);
    
    void setTargetSolid(bool pIsSolid);
    void setTargetAlphaTestValue(float pAlphaValue);
    
    void removeTargetObserver(CCRenderTexture *pTarget);
    
protected:
    void setPaintPosition(CCSprite *pTarget, CCSprite *pBrush, CCPoint pWorldPosition);
    void setTargetTexureSize(CCSize pSize);
    void setTargetTexture(CCTexture2D *pTexture);
    void setBrushTexSize();
};

#endif /* defined(__GIRLS_Framework_part__Scribble__) */
