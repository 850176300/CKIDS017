//
//  DataContainer.cpp
//  CKIDS017
//
//  Created by liuwei on 14-9-12.
//
//

#include "DataContainer.h"
#include "libjson.h"
#include "JSONNode.h"
#include "SuperGlobal.h"

#define JSON_ITEM_KEY "item"
#define JSON_ITEM_ISFREE "isFree"
#define JSON_CLOTHE_NAME "itemName"
#define JSON_CLOTHE_LEFTP "leftPoint"
#define JSON_CLOTHE_RIGHTP "rightPoint"
#define JSON_DELTA_POINT "deltaPoint"
#define JSON_DELTA_ROTATE "deltaRoate"

void DataContainer::loadDatas(){
    LockItem item1 = {"blueberry", true};
    seeds.push_back(item1);
    LockItem item2 = {"rose", true};
    seeds.push_back(item2);
    LockItem item3 = {"tomato", true};
    seeds.push_back(item3);
    loadBabys();
    loadDryClothes();
    loadDeltaFiles();
}

#pragma mark 加载所有babys的数据
void DataContainer::loadBabys(){
    unsigned long size;
	unsigned char* ret = CCFileUtils::sharedFileUtils()->getFileData(BabysJsonPath, "r", &size);
	
	if(ret && size > 0)
	{
		char* jsonData = new char[size + 1];
		for(int i = 0; i < size; i++) jsonData[i] = ret[i];
		jsonData[size] = '\0';
        
        if(!json_is_valid(jsonData)) return;
        
        JSONNode* mainNode = (JSONNode*)json_parse(jsonData);
        if(!mainNode) return;
        
        JSONNode::json_iterator itorMain = mainNode->begin();
        while(itorMain != mainNode->end())
        {
            //            if(JSON_KEY_TOOLS == (*itorMain)->name())
            {
                JSONNode::json_iterator itorArray = (*itorMain)->begin();
                while (itorArray != (*itorMain)->end())
                {
                    LockItem tConfig;
                    JSONNode::json_iterator itorLevel = (*itorArray)->begin();
                    while(itorLevel != (*itorArray)->end())
                    {
                        if(JSON_ITEM_KEY == (*itorLevel)->name()){
							tConfig.itemName = 	(*itorLevel)->as_string();
                        }
                        else if(JSON_ITEM_ISFREE == (*itorLevel)->name()){
							if ( (*itorLevel)->as_bool() == true) {
                                tConfig.isFree = true;
                            }else {
                                //                                CCLog("the true");
                                tConfig.isFree =false;
                            }
                        }
                        ++itorLevel;
                    }
                    
                    ++itorArray;
                    babys.push_back(tConfig);
                }
            }
            ++itorMain;
        }
        
        JSONNode::deleteJSONNode(mainNode);
		delete[] jsonData;
	}
    CCLog("the babys counts is %d", (int)babys.size());
    //对应getFileData,此接口是要手动清理内存的
	if(!ret) delete[] ret;
}


string DataContainer::getBabyByIndex(int index) {
    CCAssert(index < babys.size(), "查找的baby index必须比baby size要小");
    return babys[index].itemName;
}

bool DataContainer::getBabyisFree(int index) {
    CCAssert(index < babys.size(), "查找的baby index必须比baby size要小");
    return babys[index].isFree;
}

vector<LockItem> DataContainer::getAllSeed(){
    return seeds;
}

#pragma mark 加载晾衣服的时候衣服模型
void DataContainer::loadDryClothes() {
    unsigned long size;
	unsigned char* ret = CCFileUtils::sharedFileUtils()->getFileData(DryClothePath, "r", &size);
	
	if(ret && size > 0)
	{
		char* jsonData = new char[size + 1];
		for(int i = 0; i < size; i++) jsonData[i] = ret[i];
		jsonData[size] = '\0';
        
        if(!json_is_valid(jsonData)) return;
        
        JSONNode* mainNode = (JSONNode*)json_parse(jsonData);
        if(!mainNode) return;
        
        JSONNode::json_iterator itorMain = mainNode->begin();
        while(itorMain != mainNode->end())
        {
            //            if(JSON_KEY_TOOLS == (*itorMain)->name())
            {
                JSONNode::json_iterator itorArray = (*itorMain)->begin();
                while (itorArray != (*itorMain)->end())
                {
                    DryClothe tConfig;
                    JSONNode::json_iterator itorLevel = (*itorArray)->begin();
                    while(itorLevel != (*itorArray)->end())
                    {
                        if(JSON_CLOTHE_NAME == (*itorLevel)->name()){
							tConfig.clotheName = 	(*itorLevel)->as_string();
                        }
                        else if(JSON_CLOTHE_LEFTP == (*itorLevel)->name()){
							string left = (*itorLevel)->as_string();
                            tConfig.leftPoint = CCPointFromString(left.c_str());
                        }
                        else if (JSON_CLOTHE_RIGHTP == (*itorLevel)->name()) {
                            string right = (*itorLevel)->as_string();
                            tConfig.rightPoint = CCPointFromString(right.c_str());
                        }
                        ++itorLevel;
                    }
                    
                    ++itorArray;
                    dryClothes.push_back(tConfig);
                }
            }
            ++itorMain;
        }
        
        JSONNode::deleteJSONNode(mainNode);
		delete[] jsonData;
	}
    CCLog("the babys counts is %d", (int)babys.size());
    //对应getFileData,此接口是要手动清理内存的
	if(!ret) delete[] ret;
}

vector<DryClothe> DataContainer::getallDryClothes(){
    return dryClothes;
}

#pragma mark 加载壁画偏离的数据，总共有三种类型，然后随机分配给每一个壁画
void DataContainer::loadDeltaFiles(){
    unsigned long size;
	unsigned char* ret = CCFileUtils::sharedFileUtils()->getFileData(DeltaDataPath, "r", &size);
	
	if(ret && size > 0)
	{
		char* jsonData = new char[size + 1];
		for(int i = 0; i < size; i++) jsonData[i] = ret[i];
		jsonData[size] = '\0';
        
        if(!json_is_valid(jsonData)) return;
        
        JSONNode* mainNode = (JSONNode*)json_parse(jsonData);
        if(!mainNode) return;
        
        JSONNode::json_iterator itorMain = mainNode->begin();
        while(itorMain != mainNode->end())
        {
            //            if(JSON_KEY_TOOLS == (*itorMain)->name())
            {
                JSONNode::json_iterator itorArray = (*itorMain)->begin();
                while (itorArray != (*itorMain)->end())
                {
                    DeltaPositioin tConfig;
                    JSONNode::json_iterator itorLevel = (*itorArray)->begin();
                    while(itorLevel != (*itorArray)->end())
                    {
                        if(JSON_DELTA_POINT == (*itorLevel)->name()){
							string pos = 	(*itorLevel)->as_string();
                            tConfig.deltaPos = CCPointFromString(pos.c_str());
                        }
                        else if(JSON_DELTA_ROTATE == (*itorLevel)->name()){
							tConfig.deltaRotate = (*itorLevel)->as_float();
                        }
                        ++itorLevel;
                    }
                    
                    ++itorArray;
                    deltaTypes.push_back(tConfig);
                }
            }
            ++itorMain;
        }
        
        JSONNode::deleteJSONNode(mainNode);
		delete[] jsonData;
	}
    CCLog("the babys counts is %d", (int)babys.size());
    //对应getFileData,此接口是要手动清理内存的
	if(!ret) delete[] ret;
}

void DataContainer::sortTypes(){
    srand((unsigned)time(0));
    vector<DeltaPositioin> types;
    for (int i = 3; i > 0; --i) {
        int r = rand() % i;
        DeltaPositioin delta1;
        delta1 = deltaTypes[r];
        types.push_back(delta1);
        deltaTypes.erase(deltaTypes.begin() + r);
    }
    deltaTypes.clear();
    deltaTypes = types;
    types.clear();
}

DeltaPositioin DataContainer::getdeltaTypeAt(int index) {
    CCAssert(index < 3 && index >= 0, "index 超出了范围，请检测");
    return deltaTypes[index];
}

