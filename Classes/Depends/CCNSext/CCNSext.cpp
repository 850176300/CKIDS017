//
//  CCNSext.cpp
//  GIRLS_Framework_part
//
//  Created by renhong on 9/5/13.
//
//

#include "CCNSext.h"
#include <string>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <cocos2d.h>
using namespace cocos2d;

NS_CC_BEGIN
typedef std::vector<std::string> strArray;

// string toolkit
static inline void split(std::string src, const char* token, strArray& vect)
{
    int nend=0;
    int nbegin=0;
    while(nend != -1)
    {
        nend = src.find(token, nbegin);
        if(nend == -1)
            vect.push_back(src.substr(nbegin, src.length()-nbegin));
        else
            vect.push_back(src.substr(nbegin, nend-nbegin));
        nbegin = nend + strlen(token);
    }
}

static bool split4WithForm(const char* pStr, strArray& strs)
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!pStr);
        
        // string is empty
        std::string content = pStr;
        CC_BREAK_IF(content.length() == 0);
        
        int nPosLeft  = content.find('{');
        int nPosRight = content.find('}');
        
        // don't have '{' and '}'
        CC_BREAK_IF(nPosLeft == (int)std::string::npos || nPosRight == (int)std::string::npos);
        // '}' is before '{'
        CC_BREAK_IF(nPosLeft > nPosRight);
        
        std::string pointStr = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
        // nothing between '{' and '}'
        CC_BREAK_IF(pointStr.length() == 0);
        
        int nPos1 = pointStr.find('{');
        int nPos2 = pointStr.find('}');
        // contain '{' or '}'
        CC_BREAK_IF(nPos1 != (int)std::string::npos || nPos2 != (int)std::string::npos);
        
        split(pointStr, ",", strs);
        if (strs.size() != 4 || strs[0].length() == 0 || strs[1].length() == 0 || strs[2].length() == 0 || strs[3].length() == 0)
        {
            strs.clear();
            break;
        }
        
        bRet = true;
    } while (0);
    
    return bRet;
}

static bool split3WithForm(const char* pStr, strArray& strs)
{
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!pStr);
        
        // string is empty
        std::string content = pStr;
        CC_BREAK_IF(content.length() == 0);
        
        int nPosLeft  = content.find('{');
        int nPosRight = content.find('}');
        
        // don't have '{' and '}'
        CC_BREAK_IF(nPosLeft == (int)std::string::npos || nPosRight == (int)std::string::npos);
        // '}' is before '{'
        CC_BREAK_IF(nPosLeft > nPosRight);
        
        std::string pointStr = content.substr(nPosLeft + 1, nPosRight - nPosLeft - 1);
        // nothing between '{' and '}'
        CC_BREAK_IF(pointStr.length() == 0);
        
        int nPos1 = pointStr.find('{');
        int nPos2 = pointStr.find('}');
        // contain '{' or '}'
        CC_BREAK_IF(nPos1 != (int)std::string::npos || nPos2 != (int)std::string::npos);
        
        split(pointStr, ",", strs);
        if (strs.size() != 3 || strs[0].length() == 0 || strs[1].length() == 0 || strs[2].length() == 0)
        {
            strs.clear();
            break;
        }
        
        bRet = true;
    } while (0);
    
    return bRet;
}


ccColor4B CCColor4BFromString(const char* pszContent)
{
    ccColor4B ret = ccc4(0, 0, 0, 0);
    
    do
    {
        strArray strs;
        CC_BREAK_IF(!split4WithForm(pszContent, strs));
        
        int lRed  = atoi(strs[0].c_str());
        int lGreen = atoi(strs[1].c_str());
        int lBlue = atoi(strs[2].c_str());
        int lAlpha = atoi(strs[3].c_str());
        //the rgba color must in [0,255]
        bool lColorIn0_255 = (lRed >= 0 && lRed < 256) && (lGreen >= 0 && lGreen < 256) && (lBlue >= 0 && lBlue < 256) && (lAlpha >= 0 && lAlpha < 256);
        CCAssert(lColorIn0_255, "RGBA less than 255");
        if (lColorIn0_255) {
            ret = ccc4(lRed, lGreen, lBlue, lAlpha);
        }
    } while (0);
    
    return ret;
}

ccColor3B CCColor3BFromString(const char* pszContent)
{
    ccColor3B ret = ccc3(0, 0, 0);
    
    do
    {
        strArray strs;
        CC_BREAK_IF(!split3WithForm(pszContent, strs));
        
        int lRed  = atoi(strs[0].c_str());
        int lGreen = atoi(strs[1].c_str());
        int lBlue = atoi(strs[2].c_str());
        //the rgba color must in [0,255]
        bool lColorIn0_255 = (lRed >= 0 && lRed < 256) && (lGreen >= 0 && lGreen < 256) && (lBlue >= 0 && lBlue < 256);
        CCAssert(lColorIn0_255, "RGB less than 255");
        if (lColorIn0_255) {
            ret = ccc3(lRed, lGreen, lBlue);
        }
    } while (0);
    
    return ret;
}
NS_CC_END