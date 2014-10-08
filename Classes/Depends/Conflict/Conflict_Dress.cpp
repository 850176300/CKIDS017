#include "Conflict_Dress.h"

Conflict_Dress::Conflict_Dress()
{

}

Conflict_Dress::~Conflict_Dress()
{

}

void Conflict_Dress::doConflict(ExtensionScene* dressScene,ContentLayer* contentLayer,ComponentInfo* com)
{
	//get category ID from  database
	int top=2,bottom=3,dress=4;//test:getCategoryID("dress")
	//int dressID=1;//test:getCategoryID("dress")
	if (com->categoryID==dress)
	{
		//remove top and bottom sprite from content layer
		contentLayer->removeChildByTag(top);
		contentLayer->removeChildByTag(bottom);
	} 
	else if(com->categoryID==top)
	{
		//remove dress sprite from content layer
        if (contentLayer->getChildByTag(dress)) {
            contentLayer->removeChildByTag(dress);
            contentLayer->onDress(23);
        }

		//add default bottom sprite to content layer
//		dressScene->onDress();
	}else if(com->categoryID==bottom)
	{
		//remove dress sprite from content layer
        if (contentLayer->getChildByTag(dress)) {
            contentLayer->removeChildByTag(dress);
            contentLayer->onDress(13);
        }
		//add default top sprite to content layer
		//		dressScene->onDress();
	}
}

int Conflict_Dress::getCategoryID( string category )
{
	return 0;
}


