//
//  ShowDialog.cpp
//  BBQParty
//
//  Created by liuwei on 14-9-3.
//
//

#include "ShowDialog.h"


ShowDialog::ShowDialog(){
    _delegate = 0;
    currentTag = -1;
}

void ShowDialog::showDilog(string title, string content, void *arg, int type, int tag, AlertViewDelegate *pDelegate, CCNode* pNode) {
    if (_delegate) {
        _delegate = 0;
    }
    _delegate = pDelegate;
    currentTag = tag;
    
    MyDialog* dialog = MyDialog::create(CCSizeMake(600, 330), arg, type);
    dialog->setCallback(this);
    if (title.length() > 0) {
        dialog->setTitleText(title.c_str());
    }
    dialog->setContentText(content.c_str());
    pNode->addChild(dialog, 9999);
}


void ShowDialog::onNegativeClick(void *arg){
    if (_delegate) {
        _delegate->onAlertViewClickatIndex(currentTag, 0);
    }
    currentTag = -1;
    _delegate = 0;
}

void ShowDialog::onPositiveClick(void *arg) {
    if (_delegate) {
        _delegate->onAlertViewClickatIndex(currentTag, 1);
    }
    currentTag = -1;
    _delegate = 0;
}