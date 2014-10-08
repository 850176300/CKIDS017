//
//  DataManager.h
//  GIRLS_Framework_part
//
//  Created by renhong on 9/16/13.
//
//

#ifndef __GIRLS_Framework_part__DataManager__
#define __GIRLS_Framework_part__DataManager__

#include <iostream>
#include "Heads.h"
#include "../DataBase/DatabaseCore/Database.h"

class DataManager {
private:
    static DataManager *_sharedDataManager;
    string _dbFile;
protected:
    inline Category parseCategory(Records *pRecords);
    inline ComponentInfo parseComponent(Records *pRecords);
    inline ComponentTexture parseComponentTexture(Records *pRecords);
public:
    static DataManager *sharedDataManager();
    bool setDBFile(string pDBFile);
    vector<int> getVersionInfo();
    Category getCategory(int pCategoryID);
    Category getCategory(string pCategoryName, string pTag = "");
    vector<Category>getAllCategory();
    vector<Category>getCategoryByTag(string tag);
    ComponentInfo getComponentInfo(int pComponentID);
    ComponentInfo getComponentInfo(string pComponentName, int pCategoryID = 0);
    vector<ComponentInfo> getComponentInfos(int pCategoryID);
    vector<ComponentInfo> getAllComponentInfos();
    vector<ComponentInfo> getAllDefaultDress();
    vector<ComponentInfo> getDefaultDresses(int pCategoryID);
    ComponentInfo getDefaultDress(int pID);
    
    string getLanguage(string pDescription, string pType);
    
    inline IAPBean parseIAP(Records *pRecords);
    
    vector<IAPBean> getAllIAPs();
    IAPBean getIAP(int pIAPID);
    IAPBean getIAP(string pIAPKey);
    bool updateIAP(int pIAPID, int pBuyNumber);
    bool updateIAP(string pIAPKey, int pBuyNumber);
    bool executeSql(string sql);
};

#endif /* defined(__GIRLS_Framework_part__DataManager__) */
