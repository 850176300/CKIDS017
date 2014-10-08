//
//  ExtensionFunc.h
//  BBQParty
//
//  Created by liuwei on 14-8-11.
//
//

#ifndef BBQParty_ExtensionFunc_h
#define BBQParty_ExtensionFunc_h
#include <iostream>
#include <sstream>
#include "AlertViewDelegate.h"
using namespace std;



class ExtensionFunc{
public:
    ExtensionFunc();
    ~ExtensionFunc();
public:
    virtual string getMoregameUrl();
    void showAlerViewWithTagAndDelegate(int tag,string title, string message, string cancel, string confirm, AlertViewDelegate* pDelegate);
};

#endif
