//
//  ShowDialog.h
//  BBQParty
//
//  Created by liuwei on 14-9-3.
//
//

#ifndef __BBQParty__ShowDialog__
#define __BBQParty__ShowDialog__

#include <iostream>
#include "SingleTon.h"
#include "AlertViewDelegate.h"
#include "DialogCallback.h"
#include "cocos2d.h"
#include "MyDialog.h"
using namespace std;
USING_NS_CC;
class ShowDialog: public SingleTon<ShowDialog>, public DialogCallback
{
    friend class SingleTon<ShowDialog>;
private:
    AlertViewDelegate* _delegate;
    int currentTag;
public:
    ShowDialog();
    void showDilog(string title, string content,  void* arg, int type, int tag, AlertViewDelegate* pDelegate, CCNode* pNode);
    virtual void onNegativeClick(void*);
    virtual void onPositiveClick(void*);
};
#endif /* defined(__BBQParty__ShowDialog__) */
