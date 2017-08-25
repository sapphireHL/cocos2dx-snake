#pragma once

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GlobalParameters.h"

USING_NS_CC;
using namespace CocosDenshion;

//const int UP = 0;
//const int DOWN = 1;
//const int LEFT = 2;
//const int RIGHT = 3;

class Play :public Scene{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(Play);

	void update(float) override;
	Vec2 generateFood();
	bool isFoodOnSnake(Vec2);
	void moveBody(float);
	void moveHead(float);
	bool isEating();
	void expand();
	bool isHit();

private:
	SimpleAudioEngine* audio;
	std::vector<Sprite*> snake;
	Sprite* food;
	Vec2 tailPos;

	int speed;
	int direction;

	int unitSize;
	int minWidthUnit;
	int maxWidthUnit;
	int maxHeightUnit;
	int minHeightUnit;

};


