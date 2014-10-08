//
//  DataManager.cpp
//  GIRLS_Framework_part
//
//  Created by renhong on 9/16/13.
//
//

#include "DataManager.h"
#include "../DataBase/DatabaseHelper/DatabaseHelper.h"
#include "../DataBase/DatabaseCore/Database.h"

const string gcGirlsDBName = "DB/Girls.sqlite";

DataManager *DataManager::_sharedDataManager = NULL;
DataManager * DataManager::sharedDataManager()
{
    if (NULL == _sharedDataManager) {
        _sharedDataManager = new DataManager();
    }
    
    return _sharedDataManager;
}

bool DataManager::setDBFile(string pDBFile)
{
    bool lCreateRes = DatabaseHelper::sharedDatabaseHelper()->createDatabase(pDBFile);
    assert(lCreateRes);
    if (lCreateRes) {
        _dbFile = pDBFile;
    }
    
    return lCreateRes;
}

vector<int> DataManager::getVersionInfo()
{
    assert(_dbFile.length() > 0);
    vector<int> lVersions;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "DBVersion");
            while (lRecords->next()) {
                int lVer = lRecords->intForField("Version");
                lVersions.push_back(lVer);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getVersionInfo Exception %s", pException.what());
    }
    
    return lVersions;
}

inline Category DataManager::parseCategory(Records *pRecords)
{
    Category lCategory;
    try {
        lCategory.name = pRecords->textForField("Name");
        lCategory.id = pRecords->intForField("ID");
        lCategory.normalImage = pRecords->textForField("NormalImageName");
        lCategory.selectedImage = pRecords->textForField("SelectedImageName");
        lCategory.disabledImage = pRecords->textForField("DisabledImageName");
        lCategory.iapID = pRecords->intForField("IAPID");
    } catch (exception pException) {
        CCLOG("DataManager::parseCategory Exception %s", pException.what());
    }

    return lCategory;
}

Category DataManager::getCategory(int pCategoryID)
{
    assert(_dbFile.length() > 0);
    
    Category lCategory;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            ostringstream lOs;
            lOs << pCategoryID;
            
            lConditions.insert(make_pair("ID", lOs.str()));
            lOs.str("");
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "Category");
            if (lRecords->next()) {
                lCategory = this->parseCategory(lRecords);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getCategory Exception %s", pException.what());
    }
    
    return lCategory;
}

Category DataManager::getCategory(string pCategoryName, string pTag/* = ""*/)
{
    assert(_dbFile.length() > 0);
    Category lCategory;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            lConditions.insert(make_pair("Name", pCategoryName));
            if (pTag.length() > 0) {
                lConditions.insert(make_pair("Tag", pTag));
            }
            
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "Category");
            if (lRecords->next()) {
                lCategory = this->parseCategory(lRecords);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getCategory Exception %s", pException.what());
    }
    
    return lCategory;
}

vector<Category> DataManager::getAllCategory()
{
    assert(_dbFile.length() > 0);
    vector<Category> lAllCategory;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            string lSqlstring = "SELECT * FROM Category ORDER BY idx ASC";
            Records *lRecords = Database::sharedDatabase()->query(lSqlstring);
            while (lRecords->next()) {
                Category lItem = this->parseCategory(lRecords);
                lAllCategory.push_back(lItem);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getAllCategory Exception %s", pException.what());
    }
    
    return lAllCategory;
}

inline ComponentInfo DataManager::parseComponent(Records *pRecords)
{
    ComponentInfo lComponentInfo;
    try {
        lComponentInfo.componentID = pRecords->intForField("ID");
        lComponentInfo.imageName = pRecords->textForField("ImageName");
        lComponentInfo.scale = pRecords->floatForField("Scale");
        lComponentInfo.visible = static_cast<bool>(pRecords->intForField("Visible"));
        lComponentInfo.color = CCColor3BFromString(pRecords->textForField("Color").c_str());
        lComponentInfo.colorType = static_cast<ColorType>(pRecords->intForField("ColorType"));
        lComponentInfo.opacity = pRecords->intForField("Opacity");
        lComponentInfo.categoryID = pRecords->intForField("CategoryID");
        lComponentInfo.iapID = pRecords->intForField("IAPID");
    } catch (exception pException) {
        CCLOG("DataManager::parseComponent Exception %s", pException.what());
    }
    
    return lComponentInfo;
}

inline ComponentTexture DataManager::parseComponentTexture(Records *pRecords)
{
    ComponentTexture lComponentTexture;
    try {
        lComponentTexture.imageName = pRecords->textForField("ImageName");
        lComponentTexture.zOrder = pRecords->intForField("ZOrder");
        lComponentTexture.position = CCPointFromString(pRecords->textForField("Position").c_str());
    } catch (exception pException) {
        CCLOG("DataManager::parseComponentTexture Exception %s", pException.what());
    }
    
    return lComponentTexture;
}

ComponentInfo DataManager::getComponentInfo(int pComponentID)
{
    assert(_dbFile.length() > 0);
    ComponentInfo lComponentInfo;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            /*
             // 联表查询
             string lSqlFormatString = "SELECT Component.*, ComponentTexture.*, Component.ID AS Component_ID, ComponentTexture.ID AS ComponentTexture_ID, Component.ImageName AS Component_ImageName, ComponentTexture.ImageName AS ComponentTexture_ImageName FROM Component,ComponentTexture WHERE Component.ID=%d AND ComponentTexture.ComponentID=Component.ID";
             char lSqlString[512];
             sprintf(lSqlString, lSqlFormatString.c_str(), pComponentID);
             Records *lRecords = Database::sharedDatabase()->query(lSqlString);
             while (lRecords->next()) {
             CCLOG("Component ID %d",lRecords->intForField("Component_ID"));
             CCLOG("ComponentTexture ID %d",lRecords->intForField("ComponentTexture_ID"));
             CCLOG("ComponentTexture ComponentID %d",lRecords->intForField("ComponentID"));
             CCLOG("Component ImageName %s",lRecords->textForField("Component_ImageName").c_str());//
             CCLOG("ComponentTexture ImageName %s",lRecords->textForField("ComponentTexture_ImageName").c_str());//
             }
             delete lRecords;
             */
            
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            ostringstream lOs;
            lOs << pComponentID;
            
            lConditions.insert(make_pair("ID", lOs.str()));
            lOs.str("");
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "Component");
            if (lRecords->next()) {
                lComponentInfo = this->parseComponent(lRecords);
                
                vector<string> lFields;
                lFields.push_back("*");
                map<string, string> lConditions;
                ostringstream lOs;
                lOs << pComponentID;
                
                lConditions.insert(make_pair("ComponentID", lOs.str()));
                lOs.str("");
                Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "ComponentTexture");
                vector<ComponentTexture> lComponentTextures;
                while (lRecords->next()) {
                    ComponentTexture lTexture = this->parseComponentTexture(lRecords);
                    lComponentTextures.push_back(lTexture);
                }
                lComponentInfo.textures = lComponentTextures;
                delete lRecords;
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getComponentInfo Exception %s", pException.what());
    }
    
    return lComponentInfo;
}

ComponentInfo DataManager::getComponentInfo(string pComponentName, int pCategoryID/* = 0*/)
{
    assert(_dbFile.length() > 0);
    ComponentInfo lComponentInfo;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            
            lConditions.insert(make_pair("ImageName", pComponentName.c_str()));
            if (pCategoryID > 0) {
                ostringstream lOs;
                lOs << pCategoryID;
                lConditions.insert(make_pair("CategoryID", lOs.str()));
                lOs.str("");
            }
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "Component");
            if (lRecords->next()) {
                lComponentInfo = this->parseComponent(lRecords);
                
                vector<string> lFields;
                lFields.push_back("*");
                map<string, string> lConditions;
                ostringstream lOs;
                lOs << lComponentInfo.componentID;
                
                lConditions.insert(make_pair("ComponentID", lOs.str()));
                lOs.str("");
                Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "ComponentTexture");
                vector<ComponentTexture> lComponentTextures;
                while (lRecords->next()) {
                    ComponentTexture lTexture = this->parseComponentTexture(lRecords);
                    lComponentTextures.push_back(lTexture);
                }
                lComponentInfo.textures = lComponentTextures;
                delete lRecords;
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getComponentInfo Exception %s", pException.what());
    }
    
    return lComponentInfo;
}

vector<ComponentInfo> DataManager::getComponentInfos(int pCategoryID)
{
    assert(_dbFile.length() > 0);
    vector<ComponentInfo> lComponentInfos;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            //vector<string> lFields;
            //lFields.push_back("*");
            //map<string, string> lConditions;
            ostringstream lOs;
            lOs << pCategoryID;
            
            //lConditions.insert(make_pair("CategoryID", lOs.str()));
            string lSqlstring = "SELECT * FROM Component WHERE CategoryID=" + lOs.str() + " ORDER BY idx ASC";
            lOs.str("");
            Records *lRecords = Database::sharedDatabase()->query(lSqlstring);
            while (lRecords->next()) {
                ComponentInfo lItem = this->parseComponent(lRecords);
                
                vector<string> lFields;
                lFields.push_back("*");
                map<string, string> lConditions;
                ostringstream lOs;
                lOs << lItem.componentID;
                
                lConditions.insert(make_pair("ComponentID", lOs.str()));
                lOs.str("");
                Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "ComponentTexture");
                vector<ComponentTexture> lComponentTextures;
                while (lRecords->next()) {
                    ComponentTexture lTexture = this->parseComponentTexture(lRecords);
                    lComponentTextures.push_back(lTexture);
                }
                lItem.textures = lComponentTextures;
                delete lRecords;
                lComponentInfos.push_back(lItem);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getComponentInfos Exception %s", pException.what());
    }
    
    return lComponentInfos;
}

vector<ComponentInfo> DataManager::getAllComponentInfos()
{
    assert(_dbFile.length() > 0);
    vector<ComponentInfo> lComponentInfos;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            string lSqlstring = "SELECT * FROM Component ORDER BY idx ASC";
            Records *lRecords = Database::sharedDatabase()->query(lSqlstring);
            while (lRecords->next()) {
                ComponentInfo lItem = this->parseComponent(lRecords);
                
                vector<string> lFields;
                lFields.push_back("*");
                map<string, string> lConditions;
                ostringstream lOs;
                lOs << lItem.componentID;
                string lSqlstring = "SELECT * FROM ComponentTexture WHERE ComponentID=" + lOs.str() + " ORDER BY idx ASC";
                lOs.str("");
                
                Records *lRecords = Database::sharedDatabase()->query(lSqlstring);
                vector<ComponentTexture> lComponentTextures;
                while (lRecords->next()) {
                    ComponentTexture lTexture = this->parseComponentTexture(lRecords);
                    lComponentTextures.push_back(lTexture);
                }
                lItem.textures = lComponentTextures;
                delete lRecords;
                lComponentInfos.push_back(lItem);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getAllComponentInfos Exception %s", pException.what());
    }
    
    return lComponentInfos;
}

vector<ComponentInfo>DataManager::getAllDefaultDress()
{
    assert(_dbFile.length() > 0);
    vector<ComponentInfo> lComponentInfos;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "DefaultDress");
            while (lRecords->next()) {
                int lComponentID = lRecords->intForField("ComponentID");
                
                ComponentInfo lComponentInfo = this->getComponentInfo(lComponentID);
                lComponentInfos.push_back(lComponentInfo);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getAllDefaultDress Exception %s", pException.what());
    }
    
    return lComponentInfos;
}

vector<ComponentInfo>DataManager::getDefaultDresses(int pCategoryID)
{
    assert(_dbFile.length() > 0);
    vector<ComponentInfo> lComponentInfos;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            
            ostringstream lOs;
            lOs << pCategoryID;
            lConditions.insert(make_pair("CategoryID", lOs.str()));
            lOs.str("");
            
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "DefaultDress");
            while (lRecords->next()) {
                int lComponentID = lRecords->intForField("ComponentID");
                
                ComponentInfo lComponentInfo = this->getComponentInfo(lComponentID);
                lComponentInfos.push_back(lComponentInfo);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getDefaultDress Exception %s", pException.what());
    }
    
    return lComponentInfos;
}

ComponentInfo DataManager::getDefaultDress(int pID)
{
    assert(_dbFile.length() > 0);
    ComponentInfo lComponentInfo;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            
            ostringstream lOs;
            lOs << pID;
            lConditions.insert(make_pair("ID", lOs.str()));
            lOs.str("");
            
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "DefaultDress");
            if (lRecords->next()) {
                int lComponentID = lRecords->intForField("ComponentID");
                
                lComponentInfo = this->getComponentInfo(lComponentID);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getDefaultDress Exception %s", pException.what());
    }
    
    return lComponentInfo;
}

string DataManager::getLanguage(string pDescription, string pType)
{
    assert(_dbFile.length() > 0);
    string lLanguage(pDescription);
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("ID");
            map<string, string> lConditions;
            lConditions.insert(make_pair("Description", pDescription));
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "LangrageDescription");
            if (lRecords->next()) {
                int lDescriptionID = lRecords->intForField("ID");
                
                vector<string> lFields;
                lFields.push_back("*");
                map<string, string> lConditions;
                ostringstream lOs;
                lOs << lDescriptionID;
                lConditions.insert(make_pair("DescriptionID", lOs.str()));
                lOs.str("");
                lConditions.insert(make_pair("TypeID", pType));
                Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "Language");
                
                if (lRecords->next()) {
                    lLanguage = lRecords->textForField("Comment");
                }
                else{
                    lConditions.erase("TypeID");
                    lConditions.insert(make_pair("TypeID", "en"));
                    Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "Language");
                    if (lRecords->next()) {
                        lLanguage = lRecords->textForField("Comment");
                    }
                    delete lRecords;
                }
                
                delete lRecords;
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getLanguage Exception %s", pException.what());
    }
    
    return lLanguage;
}

vector<Category> DataManager::getCategoryByTag( string tag )
{
	assert(_dbFile.length() > 0);
	vector<Category> categories;
	try {
		string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
		if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            string lSqlstring = "SELECT * FROM Category WHERE Tag=" + tag + " ORDER BY idx ASC";
			Records *lRecords = Database::sharedDatabase()->query(lSqlstring);
			while (lRecords->next()) {
				Category lItem = this->parseCategory(lRecords);
				categories.push_back(lItem);
			}
			delete lRecords;

			Database::sharedDatabase()->close();
		}
		else{
			CCLOG("Data base open failed!");
		}
	} catch (exception pException) {
		CCLOG("DataManager::getAllCategory Exception %s", pException.what());
	}

	return categories;
}

inline IAPBean DataManager::parseIAP(Records *pRecords)
{
    IAPBean lIAPBean;
    try {
        lIAPBean.id = pRecords->intForField("ID");
        lIAPBean.key = pRecords->textForField("IAPKey");
        lIAPBean.buyNumber = pRecords->intForField("BuyNumber");
        
    } catch (exception pException) {
        CCLOG("DataManager::parseCategory Exception %s", pException.what());
    }
    
    return lIAPBean;
}

vector<IAPBean> DataManager::getAllIAPs(){
    assert(_dbFile.length() > 0);
    vector<IAPBean> lAllIAPBeans;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "IAP");
            while (lRecords->next()) {
                IAPBean lItem = this->parseIAP(lRecords);
                lAllIAPBeans.push_back(lItem);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getAllCategory Exception %s", pException.what());
    }
    
    return lAllIAPBeans;
}

IAPBean DataManager::getIAP(int pIAPID)
{
    assert(_dbFile.length() > 0);
    
    IAPBean lIAPBean;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            ostringstream lOs;
            lOs << pIAPID;
            
            lConditions.insert(make_pair("ID", lOs.str()));
            lOs.str("");
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "IAP");
            if (lRecords->next()) {
                lIAPBean = this->parseIAP(lRecords);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getIAP Exception %s", pException.what());
    }
    
    return lIAPBean;
}

IAPBean DataManager::getIAP(string pIAPKey)
{
    assert(_dbFile.length() > 0);
    
    IAPBean lIAPBean;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            vector<string> lFields;
            lFields.push_back("*");
            map<string, string> lConditions;
            lConditions.insert(make_pair("IAPKey", pIAPKey));
            
            Records *lRecords = Database::sharedDatabase()->query(lFields, lConditions, "IAP");
            if (lRecords->next()) {
                lIAPBean = this->parseIAP(lRecords);
            }
            delete lRecords;
            
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::getIAP Exception %s", pException.what());
    }
    
    return lIAPBean;
}

bool DataManager::updateIAP(int pIAPID, int pBuyNumber){
    assert(_dbFile.length() > 0);
    
    bool lRes = false;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            map<string, string> lFieldAndValues;
            ostringstream lOs;
            lOs << pBuyNumber;
            lFieldAndValues.insert(make_pair("BuyNumber", lOs.str()));
            lOs.str("");
            lRes = Database::sharedDatabase()->update(pIAPID, lFieldAndValues, "IAP");
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::updateIAP Exception %s", pException.what());
    }
    
    return lRes;
}

bool DataManager::updateIAP(string pIAPKey, int pBuyNumber){
    assert(_dbFile.length() > 0);
    
    bool lRes = false;
    try {
        string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
        if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
            map<string, string> lFieldAndValues;
            ostringstream lOs;
            lOs << pBuyNumber;
            lFieldAndValues.insert(make_pair("BuyNumber", lOs.str()));
            lOs.str("");
            map<string, string> lConditions;
            lConditions.insert(make_pair("IAPKey", pIAPKey));
            lRes = Database::sharedDatabase()->update(lConditions, lFieldAndValues, "IAP");
            Database::sharedDatabase()->close();
        }
        else{
            CCLOG("Data base open failed!");
        }
    } catch (exception pException) {
        CCLOG("DataManager::updateIAP Exception %s", pException.what());
    }
    
    return lRes;
}



bool DataManager::executeSql( string sql )
{
    CCLOG("sql %s", sql.c_str());
	assert(_dbFile.length() > 0);

	bool lRes = false;
	try {
		string lDatabasePath = DatabaseHelper::sharedDatabaseHelper()->databasePath(_dbFile);
		if (Database::sharedDatabase()->open(lDatabasePath.c_str())) {
			
			lRes = Database::sharedDatabase()->update(sql);
			Database::sharedDatabase()->close();
		}
		else{
			CCLOG("Data base open failed!");
		}
	} catch (exception pException) {
		CCLOG("DataManager::update Exception %s", pException.what());
	}

	return lRes;
}
