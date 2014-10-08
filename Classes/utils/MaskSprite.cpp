//
//  MaskSprite.cpp
//  Doctor2
//
//  Created by tanshoumei on 13-9-15.
//
//

#include "MaskSprite.h"

MaskSprite* MaskSprite::create(const char *asName)
{
    MaskSprite* pRet = new MaskSprite;
    pRet->initWithFile(asName);
    pRet->autorelease();
    return pRet;
}

bool MaskSprite::initWithTexture(cocos2d::CCTexture2D *pTexture, const cocos2d::CCRect &rect, bool rotated)
{
    CCSprite::initWithTexture(pTexture, rect, rotated);
    
    _maskTexture = pTexture;
    
    CCGLProgram* program = new CCGLProgram;
    program->initWithVertexShaderFilename("PositionTextureColor.vert", "Mask.frag");
    setShaderProgram(program);
    program->autorelease();
    CHECK_GL_ERROR_DEBUG();
    
    program->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    program->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    program->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    CHECK_GL_ERROR_DEBUG();
    
    getShaderProgram()->link();
    CHECK_GL_ERROR_DEBUG();
    
    getShaderProgram()->updateUniforms();
    CHECK_GL_ERROR_DEBUG();
    
    _textureLocation = glGetUniformLocation( getShaderProgram()->getProgram(), "u_texture");
//    _maskLocation = glGetUniformLocation( getShaderProgram()->getProgram(), "u_mask");
    CHECK_GL_ERROR_DEBUG();
    
    setContentSize(pTexture->getContentSize());
    return true;
}

void MaskSprite::draw()
{
//    CC_PROFILER_START_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
    
//    CCAssert(!m_pobBatchNode, "If CCSprite is being rendered by CCSpriteBatchNode, CCSprite#draw SHOULD NOT be called");
    
//    CC_NODE_DRAW_SETUP();
    
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_PosColorTex );
    ccGLBlendFunc( m_sBlendFunc.src, m_sBlendFunc.dst );
    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();
    
    
    //
    // Attributes
    //
    glActiveTexture(GL_TEXTURE0);
    glBindTexture( GL_TEXTURE_2D,  getTexture()->getName() );
    glUniform1i(_textureLocation, 0);
    
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture( GL_TEXTURE_2D,  _maskTexture->getName() );
//    glUniform1i(_maskLocation, 1);

    
    
#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;
    
    // vertex
    int diff = offsetof( ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));
    
    // texCoods
    diff = offsetof( ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*)(offset + diff));
    
    // color
    diff = offsetof( ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));
    
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    CHECK_GL_ERROR_DEBUG();
    
    glActiveTexture(GL_TEXTURE0);
        
    CC_INCREMENT_GL_DRAWS(1);
    
//    CC_PROFILER_STOP_CATEGORY(kCCProfilerCategorySprite, "CCSprite - draw");
}