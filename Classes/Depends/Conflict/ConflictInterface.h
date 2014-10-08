#ifndef __CONFLICT_INTERFACE_H__
#define __CONFLICT_INTERFACE_H__
#include "cocos2d.h"
#include "../Application/Global.h"
#include "../Extension/ExtensionScene.h"
#include "../Extension/ContentLayer.h"


USING_NS_CC;
class ExtensionScene;
class ContentLayer;
class Conflict
{
public:
	virtual void doConflict(ExtensionScene* ,ContentLayer* ,ComponentInfo*)=0;
};

#endif