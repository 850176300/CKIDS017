//
//  ParentalGameAdapter.cpp
//  LibDoctor
//
//  Created by tanshoumei on 13-11-13.
//
//

#include "ParentalGateAdapter.h"
#include "AppController.h"
#import <Foundation/Foundation.h>
#include "cocos2d.h"
#include "ParentalGate.h"
USING_NS_CC;

#define ParentalGateTag 10003

@interface ParentalGateDelegator : NSObject<ParentalGateDelegate>
{
//    bool _isPassed;
}

@property(assign) bool isPassed;

+ (ParentalGateDelegator*)shared;
- (void)parentalGateDidPass:(ParentalGate *)parentGate;
- (void)parentalGateDidDismiss:(ParentalGate *)parentGate;
@end

static ParentalGateDelegator* _parentalGateDelegator = nil;

@implementation ParentalGateDelegator
+ ()shared
{
    if(!_parentalGateDelegator)
        _parentalGateDelegator = [[ParentalGateDelegator alloc] init];
    _parentalGateDelegator.isPassed = false;
    return _parentalGateDelegator;
}


- (id) init
{
    self = [super init];
    self.isPassed = false;
    return self;
}

- (void)parentalGateDidPass:(ParentalGate *)parentGate
{
    NSLog(@"parentalGateOk");
    self.isPassed = true;
    
    CCNotificationCenter::sharedNotificationCenter()->postNotification(NotifyParentalGateAnswerRight);
    NSLog(@"parentalGateOkend");
}

- (void)parentalGateDidDismiss:(ParentalGate *)parentGate
{

}

@end

void ParentalGateAdapter::showParentalGate()
{
    UIView* superViewOfParentGate = nil;
//    if(!DisclaimerAdapter::isDisclaimerPageShowing())
//    {
//        superViewOfParentGate = [[[AppController sharedAppController] viewController] view];
//    }
//    else
    superViewOfParentGate = [[AppController sharedAppController] window];
    
    UIView* view = [superViewOfParentGate viewWithTag:ParentalGateTag];
    if(view || !superViewOfParentGate)
        return;
    ParentalGate *page = [ParentalGate parentalGate];
    page.backgroundColor = [UIColor clearColor];
    page.opaque = NO;
    [page setDelegate: [ParentalGateDelegator shared]];
    [page showInView:superViewOfParentGate];
    [page setTag:ParentalGateTag];
}

void ParentalGateAdapter::bringParentalGateToFront()
{
    UIView* superViewOfParentGate = nil;
//    if(DisclaimerAdapter::isDisclaimerPageShowing())
//    {
//        superViewOfParentGate = [[AppController sharedAppController] window];
//        UIView* view = [superViewOfParentGate viewWithTag:ParentalGateTag];
//        if(view)
//            [superViewOfParentGate bringSubviewToFront:view];
//    }
}