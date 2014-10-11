//
//  DataContainer.h
//  CKIDS017
//
//  Created by liuwei on 14-9-12.
//
//

#ifndef __CKIDS017__DataContainer__
#define __CKIDS017__DataContainer__

#include <iostream>
#include <vector>
#include "SingleTon.h" 
#include "SuperGlobal.h"
using namespace std;
class DataContainer: public SingleTon<DataContainer> {
    friend class SingleTon<DataContainer>;
public:
    void loadDatas();
    string getBabyByIndex(int index);
    bool getBabyisFree(int index);
    vector<LockItem> getAllSeed();//只有get方法
    vector<DryClothe> getallDryClothes();
    void sortTypes();
    DeltaPositioin getdeltaTypeAt(int index);
private:
    vector<LockItem> seeds;
    vector<LockItem> babys;
    vector<DryClothe> dryClothes;
    vector<DeltaPositioin> deltaTypes;
    int deltaOrder[3];
private:
    void loadBabys();
    void loadDryClothes();
    void loadDeltaFiles();
};
#endif /* defined(__CKIDS017__DataContainer__) */
