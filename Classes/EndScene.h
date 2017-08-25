#pragma once

#include "cocos2d.h"
#include <iostream>
#include "SimpleAudioEngine.h"
#include "GlobalParameters.h"

USING_NS_CC;
using namespace CocosDenshion;
using namespace std;

class End:public Scene
{
public:
	static Scene* creatScene();
	virtual bool init();
	CREATE_FUNC(End);

	void menuRetryCallBack(Ref* pSender);
	void menuExitCallBack(Ref* pSender);

private:

};
