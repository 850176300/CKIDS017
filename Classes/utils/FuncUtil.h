//
//  FuncUtil.h
//  Burgers
//
//  Created by tanshoumei on 13-6-26.
//
//

#ifndef Burgers_FuncUtil_h
#define Burgers_FuncUtil_h

#include "cocos2d.h"
#include <sstream>
using namespace std;
using namespace cocos2d;
namespace FuncHelper {
    
    template <class T>
    inline string toString( const T src )
    {
        std::ostringstream os;
        os<<src;
        return os.str();
    }
    
}

#endif
