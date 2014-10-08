#include "Util.h"
#include <string>


using namespace std;
bool Util::isExistFile(const char *pszFileName)
{
	FILE *fp = fopen(pszFileName, "rb");
    if(fp == NULL)
        return false;
    fclose(fp);
    return true;
}

const char* Util::getLanguageType()
{
	ccLanguageType currentLanguageType = CCApplication::sharedApplication()->getCurrentLanguage();
//	char *path;
    switch (currentLanguageType)
    {
    case kLanguageChinese:
		return "zh";
    case kLanguageFrench:
		return "fr";
    case kLanguageGerman:
		return "de";
    case kLanguageItalian:
		return "it";
    case kLanguageRussian:
		return "ru";
    case kLanguageSpanish:
		return "es";
	case kLanguageKorean:
		return "ko";
	default:
		return "en";
	
    }
}

CCSprite* Util::getUISprite(const char* fileName)
{
	CCSprite* sprite=NULL;
	
	sprite=CCSprite::create(getUIFilePath(fileName).c_str());

	return sprite;
}

bool Util::loadUITexture(const char* language,const char* file)
{
	string plist="UI";
	string plist_resolution="UI";
	string plist_lang="UI";

	if(resourceType==SF_RESOURCES_2048_1536)
	{
		plist.append("-HD");
		plist_resolution.append("-HD");

	}

	if(language!=0)
	{
		plist.append("-");
		plist.append(language);
		plist_lang.append("-");
		plist_lang.append(language);


	}
	plist.append("/");
	plist.append(file);
	plist_lang.append("/");
	plist_lang.append(file);
	plist_resolution.append("/");
	plist_resolution.append(file);




	if(!CCFileUtils::sharedFileUtils()->isFileExist(plist.append(".png").c_str())||!Util::isExistFile(plist.append(".plist").c_str()))
	{
		if (!CCFileUtils::sharedFileUtils()->isFileExist(plist_resolution.append(".png").c_str())||!CCFileUtils::sharedFileUtils()->isFileExist(plist_resolution.append(".plist").c_str()))
		{
			if (!CCFileUtils::sharedFileUtils()->isFileExist(plist_lang.append(".png").c_str())||!Util::isExistFile(plist_lang.append(".plist").c_str()))
			{
				plist="UI/";
				plist.append(file);
				plist.append(".plist");
			}else
			{
				plist=plist_lang;
			}
		}else
		{
			plist=plist_resolution;
		}
	}
	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plist.append(".png").c_str(),plist.append(".plist").c_str());

	return true;
}

CCSprite* Util::getContentSprite( const char* fileName )
{
	CCSprite* sprite=NULL;
	
 
	sprite=CCSprite::create(getContentFilePath(fileName).c_str());

	return sprite;
}
CCTexture2D* Util::getContentTexture( const char* fileName )
{
	return CCTextureCache::sharedTextureCache()->addImage(getContentFilePath(fileName).c_str());
}
CCTexture2D* Util::getUITexture( const char* fileName )
{
	return CCTextureCache::sharedTextureCache()->addImage(getUIFilePath(fileName).c_str());
}
std::string Util::getContentFilePath( const char* fileName )
{
	const char* language=getLanguageType();
	string path="Content";
	string path_resolution="Content";
	string path_lang="Content";
	if(resourceType==SF_RESOURCES_2048_1536)
	{
		path.append("-HD");
		path_resolution.append("-HD");
        
        
	}
    
	if(language!=0)
	{
		path.append("-");
		path.append(language);
		path_lang.append("-");
		path_lang.append(language);
	}
	path.append("/");
	path.append(fileName);
	path_lang.append("/");
	path_lang.append(fileName);
	path_resolution.append("/");
	path_resolution.append(fileName);
    
	if(!CCFileUtils::sharedFileUtils()->isFileExist(path.c_str()))
	{
        
        bool lRes = CCFileUtils::sharedFileUtils()->isFileExist(path_resolution);
		if(!lRes)
		{
            
			if(!CCFileUtils::sharedFileUtils()->isFileExist(path_lang.c_str()))
			{
				path="Content/";
				path.append(fileName);
			}else
			{
				path=path_lang;
			}
		}else
		{
			path=path_resolution;
		}
	}
	return path;
}
std::string Util::getUIFilePath( const char* fileName )
{
	const char* language=getLanguageType();
	string path="UI";
	string path_resolution="UI";
	string path_lang="UI";
	if(resourceType==SF_RESOURCES_2048_1536)
	{
		path.append("-HD");
		path_resolution.append("-HD");
        

	}
    
	if(language!=0)
	{
		path.append("-");
		path.append(language);
		path_lang.append("-");
		path_lang.append(language);
	}
	path.append("/");
	path.append(fileName);
	path_lang.append("/");
	path_lang.append(fileName);
	path_resolution.append("/");
	path_resolution.append(fileName);

	if(!CCFileUtils::sharedFileUtils()->isFileExist(path.c_str()))
	{

        bool lRes = CCFileUtils::sharedFileUtils()->isFileExist(path_resolution);
		if(!lRes)
		{

			if(!CCFileUtils::sharedFileUtils()->isFileExist(path_lang.c_str()))
			{
				path="UI/";
				path.append(fileName);
			}else
			{
				path=path_lang;
			}
		}else
		{
			path=path_resolution;
		}
	}

	return path;
}
long Util::getCurrentTime()     
{      
	struct timeval tv;      
	gettimeofday(&tv,NULL);      
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;      
}    

bool Util::isIAP( ComponentInfo* com)
{
	if(com->iapID!=0)
	{

		map<int,IAPBean>::iterator iter=IAPs.find(com->iapID);
		if(iter!=IAPs.end())
		{
			IAPBean iap=iter->second;
			if (iap.buyNumber<=0)
			{
				return true;
			}
		}
	}

	return false;
}

bool Util::isIAP( Category* cat)
{
	if(cat->iapID!=0)
	{

		map<int,IAPBean>::iterator iter=IAPs.find(cat->iapID);
		if(iter!=IAPs.end())
		{
			IAPBean iap=iter->second;
			if (iap.buyNumber<=0)
			{
				return true;
			}
		}
	}
	return false;
}




std::string Util::replaceStr(std::string &str, const char *string_to_replace, const char *new_string)
{
	int index = str.find(string_to_replace);
	while(index != std::string::npos)
	{
		str.replace(index, strlen(string_to_replace), new_string);
		index = str.find(string_to_replace, index + strlen(new_string));
	}
	return str;
}
int Util:: randomNum(int start,int end){
    
//    srand((int)clock());
    return CCRANDOM_0_1()*end+start;
}
