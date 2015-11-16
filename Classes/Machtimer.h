//
//  Machtimer.h
//
//  Created by Huajie Wang on 06/01/2012.
//  Copyright (c) 2012 DotSoft Ltd. All rights reserved.
//


#ifndef _H_MACHTIMER_H_
#define _H_MACHTIMER_H_

#include "cocos2d.h"

class Machtimer :public cocos2d::CCObject{
private:
	long t0;
public:
	void init();
	void start();
	long elapsed();
	// return elapsed of time in Sec Unit: 
	long elapsedSec();
	// return elasped of time in MS
	long elapsedMS();
	static void initialize();
	static long currentTimeInMS();
};

#endif // _H_MACHTIMER_H_