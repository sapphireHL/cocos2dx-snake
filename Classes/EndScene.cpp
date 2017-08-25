#include "EndScene.h"
#include "MainScene.h"

Scene* End::creatScene(){
	return End::create();
}

bool End::init(){
	if (!Scene::init())
		return false;

	Vec2 visibleSize = Director::getInstance()->getWinSize();

	auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 60);
	label->setPosition(visibleSize.x / 2, visibleSize.y / 2 + 120);
	this->addChild(label);

	auto label_score = Label::createWithTTF("Your score:"+to_string(score), "fonts/Marker Felt.ttf", 40);
	auto label_bestscore = Label::createWithTTF("Best score:" + to_string(best_score), "fonts/Marker Felt.ttf", 40);
	label_score->setPosition(visibleSize.x / 2, visibleSize.y / 2);
	label_bestscore->setPosition(visibleSize.x / 2, visibleSize.y / 2 - 60);
	this->addChild(label_score);
	this->addChild(label_bestscore);

	auto retryLabel = Label::createWithTTF("Retry", "fonts/Marker Felt.ttf", 60);
	auto retryItem = MenuItemLabel::create(retryLabel, CC_CALLBACK_1(End::menuRetryCallBack, this));
	auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 60);
	auto exitItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(End::menuExitCallBack, this));
	auto menu = Menu::create(retryItem, exitItem, nullptr);
	menu->setPosition(visibleSize.x / 2, visibleSize.y / 2 - 200);
	menu->alignItemsVerticallyWithPadding(20.0f);
	this->addChild(menu);

	return true;
}

void End::menuRetryCallBack(Ref* pSender){
	auto mainScene = Main::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, mainScene));
}

void End::menuExitCallBack(Ref* pSender){
	Director::getInstance()->end();
}