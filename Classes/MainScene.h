#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class Main :public Scene{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Main);

	void menuEasyCallBack(Ref* pSender);
	void menuExitCallBack(Ref* pSender);
	void menuNormalCallBack(Ref* pSender);
	void menuHardCallBack(Ref* pSender);
private:
	SimpleAudioEngine* audio;
};


