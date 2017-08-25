#include "MainScene.h"
#include "PlayScene.h"
#include "HelloWorldScene.h"
#include "GlobalParameters.h"

using namespace CocosDenshion;

Scene* Main::createScene(){
	return Main::create();
}

bool Main::init(){
	if (!Scene::init()) {
		return false;
	}
	//window size
	auto windowSize = Director::getInstance()->getWinSize();	

	//music
	audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("background1.mp3");
	if (!audio->isBackgroundMusicPlaying()){
		audio->playBackgroundMusic("background1.mp3");
	}

	//add title
	TTFConfig config("fonts/Marker Felt.ttf", 100.0f, GlyphCollection::DYNAMIC, nullptr, false);
	auto label_title = Label::createWithTTF(config, "snake");
	//label_title->enableOutline(Color4B::BLUE, 5);
	label_title->setPosition(windowSize.width / 2, windowSize.height / 1.2);
	this->addChild(label_title);

	//add menu
	auto label_easy = Label::createWithTTF("easy", "fonts/Marker Felt.ttf", 60);
	auto label_normal = Label::createWithTTF("normal", "fonts/Marker Felt.ttf", 60);
	auto label_hard = Label::createWithTTF("hard", "fonts/Marker Felt.ttf", 60);
	auto label_exit = Label::createWithTTF("exit", "fonts/Marker Felt.ttf", 60);
	auto item_easy = MenuItemLabel::create(label_easy, CC_CALLBACK_1(Main::menuEasyCallBack, this));
	auto item_normal = MenuItemLabel::create(label_normal, CC_CALLBACK_1(Main::menuNormalCallBack, this));
	auto item_hard = MenuItemLabel::create(label_hard, CC_CALLBACK_1(Main::menuHardCallBack, this));
	auto item_exit = MenuItemLabel::create(label_exit, CC_CALLBACK_1(Main::menuExitCallBack, this));
	auto menu = Menu::create(item_easy, item_normal, item_hard, item_exit, nullptr);
	menu->setPosition(windowSize.width / 2, windowSize.height / 2);
	menu->alignItemsVerticallyWithPadding(20);
	this->addChild(menu);

	return true;
}

void Main::menuEasyCallBack(Ref* pSender){
	hard_level = 0.1f;
	//audio->stopBackgroundMusic(true);
	//audio->end();
	auto playScene = Play::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, playScene));
}

void Main::menuNormalCallBack(Ref* pSender){
	hard_level = 0.06f;
	//audio->stopBackgroundMusic(true);
	//audio->end();
	auto playScene = Play::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, playScene));
}

void Main::menuHardCallBack(Ref* pSender){
	hard_level = 0.03f;
	//audio->stopBackgroundMusic(true);
	//audio->end();
	auto playScene = Play::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, playScene));
}

void Main::menuExitCallBack(Ref* pSender){
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}