//
//  Polygon.h
//  Burgers
//
//  Created by tanshoumei on 13-7-12.
//
//

#ifndef __Burgers__Polygon__
#define __Burgers__Polygon__

#include <iostream>
#include <math.h>
#import <vector>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

//向量
static CCPoint vectMake(int x, int y)
{
	return ccp(x, y);
}

//向量点乘
static float vectDot(CCPoint v1, CCPoint v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

//向量减法
static CCPoint vectSub(CCPoint v1, CCPoint v2)
{
	return vectMake(v1.x - v2.x, v1.y - v2.y);
}

//向量加法
static inline CCPoint vectAdd(CCPoint v1, CCPoint v2)
{
	return vectMake(v1.x + v2.x, v1.y + v2.y);
}

//向量长度
static inline float vectLength(CCPoint v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}
//向量的垂直向量
static inline CCPoint vectPerp(CCPoint v)
{
	return vectMake(-(v.y), v.x);
}

//多边形定义
class Polygon{
public:
	Polygon();
	Polygon(vector<CCPoint> vecs);
    //返回多边形点的数目
	int getVecNum();
    //获取指定位置的顶点坐标
	CCPoint getVectAt(int i);
    //于尾部添加一个顶点
	void addVec(CCPoint vec);
    //打印当前所有的顶点坐标
    void print()
    {
        for(vector<CCPoint>::iterator it=vectors.begin(); it!=vectors.end();++it)
        {
            CCLOG("%d %d",(*it).x,(*it).y);
        }
    }
    void draw();
private:
	vector<CCPoint> vectors;
};


#endif /* defined(__Burgers__Polygon__) */