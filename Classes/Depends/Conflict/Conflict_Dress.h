#ifndef __CONFLICT_DRESS_H__
#define __CONFLICT_DRESS_H__
#include <string> 
#include "../Conflict/ConflictInterface.h"
#include "../Extension/ExtensionScene.h"
#include "../Extension/ContentLayer.h"

using namespace std;

class Conflict_Dress:public Conflict
{
public:
	Conflict_Dress();
	~Conflict_Dress();
	virtual void doConflict(ExtensionScene*,ContentLayer* contentLayer,ComponentInfo* com);
	int getCategoryID(string category);

};

#endif