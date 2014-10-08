//
//  Scribble.cpp
//  GIRLS_Framework_part
//
//  Created by renhong on 9/12/13.
//
//

#include "Scribble.h"

inline static void setShaderPrograms(CCNode *n, CCGLProgram *p) {
    n->setShaderProgram(p);
    if (!n->getChildren()) return;
    CCObject *c;
    CCARRAY_FOREACH(n->getChildren(), c)
    {
        CCNode *lNode = static_cast<CCNode *>(c);
        if (lNode) {
            setShaderPrograms(lNode, p);
        }
    }
}

Scribble::Scribble(CCSprite *pBrush) : _brush(pBrush), _brushType(eScribbleBrushTypeBrush)
{
    _brush->retain();
}

Scribble::~Scribble()
{
    _brush->release();
}

void Scribble::antiAliasing(CCRenderTexture *pRenderTexture){
    pRenderTexture->getSprite()->getTexture()->setAntiAliasTexParameters();
}

void Scribble::disAntiAliasing(CCRenderTexture *pRenderTexture){
    pRenderTexture->getSprite()->getTexture()->setAliasTexParameters();
}

CCGLProgram *Scribble::loadDefaultShader(const GLchar *pShaderString)
{
    
    //    const GLchar * ccPositionTextureColor2_vert =
    //#include "ccShader_PositionTexture2Color_vert.h"
    //
    // Position Texture Color alpha test
    CCGLProgram *p = new CCGLProgram();
    p->initWithVertexShaderByteArray(ccPositionTextureColor_vert, pShaderString);
    
    p->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    p->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    p->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    
    p->link();
    p->updateUniforms();
    
    CHECK_GL_ERROR_DEBUG();
    
    CCShaderCache::sharedShaderCache()->addProgram(p, kCCShader_PositionTextureColorAlphaTest_Scribble);
    
    return (CCGLProgram *)p->autorelease();
}

void Scribble::setBrush(CCTexture2D *pBrushTexture)
{
    CCSpriteFrame *lFrame = CCSpriteFrame::createWithTexture(pBrushTexture, CCRectMake(0, 0, pBrushTexture->getContentSize().width, pBrushTexture->getContentSize().height));
    _brush->setDisplayFrame(lFrame);
    this->setBrushTexSize();
}

void Scribble::setBrushShader()
{
    CCGLProgram *lProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColorAlphaTest_Scribble);
    if (NULL == lProgram) {
        const GLchar * ccPositionTextureColorAlphaTest_Scribble_frag =
#include "ccShader_PositionTextureColorAlphaTest_Scribble.h"//"ccShader_PositionTextureColorAlphaTest_2TextureAlphaTest_frag.h"
        lProgram = this->loadDefaultShader(ccPositionTextureColorAlphaTest_Scribble_frag);
    }
    if (NULL != lProgram) {
        if (this->getBrush()->getShaderProgram() != lProgram) {
            setShaderPrograms(this->getBrush(), lProgram);
            
            this->setBrushAlphaTestValue(0.0);
            this->setTargetAlphaTestValue(0.1);
            this->setTargetSolid(true);
            this->setBrushTexSize();
        }
    }
}

void Scribble::setBrushType(ScribbleBrushType pType)
{
    _brushType = pType;
    CCSprite *lBrush = this->getBrush();
    switch (pType) {
        case eScribbleBrushTypeBrush:{
            ccBlendFunc f = {GL_ONE, GL_ONE_MINUS_SRC_ALPHA };
            lBrush->setBlendFunc(f);
            break;
        }
        case eScribbleBrushTypeEaser:{
            ccBlendFunc f = {GL_ZERO,GL_ONE_MINUS_SRC_ALPHA };
            lBrush->setBlendFunc(f);
            break;
        }
        default:
            break;
    }
    
}

void Scribble::setBrushAlphaTestValue(float pAlphaValue)
{
    CCAssert(pAlphaValue <= 1.0f && pAlphaValue >= 0.0f, "Apha value must in [0.0,1.0]");
    CCSprite *lBrush = this->getBrush();
    CCGLProgram *lProgram = lBrush->getShaderProgram();
    lProgram->use();
    GLint lAlphaValueLocation = glGetUniformLocation(lProgram->getProgram(), kCCUniformAlphaTestValue);
    //lProgram->setUniformLocationWith1f(lAlphaValueLocation, 0.5f);
    glUniform1f(lAlphaValueLocation, pAlphaValue);
}

void Scribble::setBrushTexSize()
{
    CCSprite *lBrush = this->getBrush();
    CCGLProgram *lShaderProgram = lBrush->getShaderProgram();
    
    lBrush->getShaderProgram()->updateUniforms();
    //set brush texture size
    GLuint lTexSizeLocation = glGetUniformLocation(lShaderProgram->getProgram(), "v_texSize");
    lShaderProgram->setUniformLocationWith2f(lTexSizeLocation, lBrush->getContentSize().width, lBrush->getContentSize().height);
}

void Scribble::setTargetSolid(bool pIsSolid)
{
    CCSprite *lBrush = this->getBrush();
    CCGLProgram *lProgram = lBrush->getShaderProgram();
    lProgram->use();
    GLuint lPenSolidLocation = glGetUniformLocation(lProgram->getProgram(), "v_solid");
    glUniform1i(lPenSolidLocation, pIsSolid);
}

void Scribble::setTargetAlphaTestValue(float pAlphaValue)
{
    CCAssert(pAlphaValue <= 1.0f && pAlphaValue >= 0.0f, "Apha value must in [0.0,1.0]");
    CCGLProgram *lShaderProgram = this->getBrush()->getShaderProgram();
    lShaderProgram->use();
    GLuint lPenAlphaLocation = glGetUniformLocation(lShaderProgram->getProgram(), "CC_alpha_value1");
    glUniform1f(lPenAlphaLocation, pAlphaValue);
}

void Scribble::setTargetTexureSize(CCSize pSize)
{
    CCSprite *lBrush = this->getBrush();
    CCGLProgram *lShaderProgram = lBrush->getShaderProgram();
    
    lBrush->getShaderProgram()->updateUniforms();
    //set the size of target texture
    GLuint lTexSize1Location = glGetUniformLocation(lShaderProgram->getProgram(), "v_texSize1");
    lShaderProgram->setUniformLocationWith2f(lTexSize1Location, pSize.width, pSize.height );
}

void Scribble::setTargetTexture(CCTexture2D *pTexture)
{
    CCSprite *lBrush = this->getBrush();
    CCGLProgram *lShaderProgram = lBrush->getShaderProgram();
    //set the texture of target
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, pTexture->getName());
    GLuint lCCUniformSamplerS2Location = glGetUniformLocation(lShaderProgram->getProgram(), kCCUniformSampler_s_Scribble);
    lBrush->getShaderProgram()->setUniformLocationWith1i(lCCUniformSamplerS2Location, 1);
}

void Scribble::setPaintPosition(CCSprite *pTarget, CCSprite *pBrush, CCPoint pWorldPosition)
{
    CCSprite *lBrush = this->getBrush();
    CCGLProgram *lShaderProgram = lBrush->getShaderProgram();
    //set the coord of pen at the target
    GLuint lCoordLocation = glGetUniformLocation(lShaderProgram->getProgram(), "v_texCoord1");
    float lX = (pWorldPosition.x - pTarget->getPosition().x + pTarget->getContentSize().width / 2.0 - lBrush->getContentSize().width / 2.0) / pTarget->getContentSize().width;
    float lY = 1.0 - (pWorldPosition.y - pTarget->getPosition().y + pTarget->getContentSize().height / 2.0 + lBrush->getContentSize().height / 2.0) / pTarget->getContentSize().height;
    lShaderProgram->setUniformLocationWith2f(lCoordLocation, lX,lY);
}

void Scribble::paint(CCSprite *pTarget, CCRenderTexture *pCanvas, CCPoint pStartPosition, CCPoint pEndPosition)
{
    CCSprite *lBrush = this->getBrush();
    float lDistance = ccpDistance(pStartPosition, pEndPosition);
    int lDis = (int)lDistance;
    int lDelta = lBrush->getContentSize().width / 4.0 * lBrush->getScaleX();//5.0 * pBrush->getScale();  5.0 * pBrush->getScale();//
    
    //pCanvas->begin();
    vector<CCPoint> lPositions;
    for (int i = 0; i < lDis; i += lDelta) {
        float lDelta = float(i) / lDistance;
        float lDifX = pEndPosition.x - pStartPosition.x;
        float lDifY = pEndPosition.y - pStartPosition.y;
        
        CCPoint lPosition = ccp(pStartPosition.x + (lDifX * lDelta), pStartPosition.y + (lDifY * lDelta));
        lPositions.push_back(lPosition);
    }
    this->paint(pTarget, pCanvas, lPositions);
}

void Scribble::paint(CCSprite *pTarget, CCRenderTexture *pCanvas, CCPoint pPosition)
{
    vector<CCPoint> lPositions;
    lPositions.push_back(pPosition);
    this->paint(pTarget, pCanvas, lPositions);
}

void Scribble::paint(CCSprite *pTarget, CCRenderTexture *pCanvas, vector<CCPoint> pWorldPositions)
{
    CCSprite *lBrush = this->getBrush();
    
    //set size of target texture
    this->setTargetTexureSize(CCSizeMake(pTarget->getContentSize().width, pTarget->getContentSize().height));
    
    //set the texture of target
    this->setTargetTexture(pTarget->getTexture());
    
    pCanvas->begin();
    for (int i = 0; i < pWorldPositions.size(); ++i) {
        CCPoint lPosition = pCanvas->getSprite()->convertToNodeSpace(pWorldPositions.at(i));
        lPosition.y = pCanvas->getSprite()->getContentSize().height - lPosition.y;
        //set the coord of pen at the target
        this->setPaintPosition(pTarget, lBrush, lPosition);
        //draw
        lBrush->setPosition(lPosition);
        if (eScribbleBrushTypeBrush == _brushType) {//if it is brush, because of the target may be transparent, so we need open alpha blend
            glBlendFunc(GL_ONE, GL_ZERO);
        }
        else if(eScribbleBrushTypeEaser == _brushType){
            glBlendFunc(GL_ZERO, GL_ZERO);
        }
        
        lBrush->visit();
        
        if (eScribbleBrushTypeBrush == _brushType) {//if it is brush, because of the target may be transparent, so we need close alpha blend after draw
            glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        }
        else if(eScribbleBrushTypeEaser == _brushType){
            glBlendFunc(GL_ZERO,GL_ONE_MINUS_SRC_ALPHA);
        }
    }
    pCanvas->end();
}

void Scribble::removeTargetObserver(CCRenderTexture *pTarget){
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(pTarget, EVENT_COME_TO_BACKGROUND);
    CCNotificationCenter::sharedNotificationCenter()->removeObserver(pTarget, EVENT_COME_TO_FOREGROUND);
}