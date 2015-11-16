#include "Machtimer.h"
#include <time.h>

void Machtimer::initialize() {
}

void Machtimer::init() {
	t0 = currentTimeInMS();
}

void Machtimer::start() {
	t0 = currentTimeInMS();
}

long Machtimer::elapsed() {
	return currentTimeInMS()- t0;
}

long Machtimer::elapsedSec() {
	return elapsed() * 10000;
}
long Machtimer::elapsedMS() {

	return elapsed();
}

long Machtimer::currentTimeInMS() {

	struct cocos2d::cc_timeval now;

	cocos2d::CCTime::gettimeofdayCocos2d(&now, NULL);    
	return (now.tv_sec * 1000 + now.tv_usec /1000.0)/10;
}