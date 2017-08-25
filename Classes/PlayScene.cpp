#include "PlayScene.h"
#include "GlobalParameters.h"
#include "EndScene.h"
#include "MainScene.h"

Scene* Play::createScene(){
	return Play::create();
}

bool Play::init(){
	if (!Scene::init())
		return false;
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//music
	/*audio = SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("background1.mp3");
	audio->playBackgroundMusic("background1.mp3");*/

	//direction
	direction = random(0, 3);

	//add snake
	auto head = Sprite::create("head.png");
	auto body = Sprite::create("body.png");
	head->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	snake.push_back(head);
	tailPos = head->getPosition();
	this->addChild(snake[0]);

	//speed
	unitSize = head->getBoundingBox().size.width;
	speed = (1 * unitSize);

	maxWidthUnit = visibleSize.width / unitSize-2;
	maxHeightUnit = visibleSize.height / unitSize-2;
	minWidthUnit = 2;
	minHeightUnit = 2;

	//add food
	food = Sprite::create("body.png");
	food->setPosition(generateFood());
	this->addChild(food);

	//add border
	score = 0;
	
	//keyboard listener
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = [=](EventKeyboard::KeyCode code, Event* event){
		switch (code){
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		case EventKeyboard::KeyCode::KEY_W:
			if (direction != DOWN)
				direction = (UP);
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		case EventKeyboard::KeyCode::KEY_S:
			if (direction != UP)
				direction = (DOWN);
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			if (direction != RIGHT)
				direction = (LEFT);
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			if (direction != LEFT)
				direction = (RIGHT);
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);

	this->schedule(schedule_selector(Play::update), hard_level);

	return true;
}

void Play::update(float delta){
	//body move
	moveBody(delta);
	//head move
	moveHead(delta);

	if (isEating()){
		score++;
		expand();
		food->setPosition(generateFood());
	}
	else if (isHit()){
		pause();
		best_score = max(score, best_score);
		auto endScene = End::creatScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5f, endScene));
	}
}

Vec2 Play::generateFood(){
	Vec2 foodPos(random(2, maxWidthUnit)*unitSize, random(2, maxHeightUnit)*unitSize);
	while (isFoodOnSnake(foodPos)){
		foodPos.setPoint(random(0, maxWidthUnit)*unitSize, random(0, maxHeightUnit)*unitSize);
	}
	return foodPos;
}

void Play::moveBody(float delta){
	tailPos = snake.back()->getPosition();
	for (int i = (int)snake.size() - 1; i >= 1; i--){
		Vec2 lastpos = snake[i - 1]->getPosition();
		auto moveto = MoveTo::create(delta, snake[i - 1]->getPosition());
		//snake[i]->runAction(moveto);
		snake[i]->setPosition(snake[i - 1]->getPosition());
	}
}

void Play::moveHead(float delta){
	Vec2 pos = snake[0]->getPosition();
	MoveBy* move;
	switch (direction){
	case UP:
		move = MoveBy::create(delta, Vec2(0, speed));
		//snake[0]->runAction(move);
		snake[0]->setPosition(pos.x, pos.y + speed);
		break;
	case DOWN:
		move = MoveBy::create(delta, Vec2(0, -speed));
		//snake[0]->runAction(move);
		snake[0]->setPosition(pos.x, pos.y - speed);
		break;
	case LEFT:
		move = MoveBy::create(delta, Vec2(-speed, 0));
		//snake[0]->runAction(move);
		snake[0]->setPosition(pos.x - speed, pos.y);
		break;
	case RIGHT:
		move = MoveBy::create(delta, Vec2(speed, 0));
		//snake[0]->runAction(move);
		snake[0]->setPosition(pos.x + speed, pos.y);
		break;
	}
}

bool Play::isFoodOnSnake(Vec2 foodPos){
	for (int i = 0; i < (int)snake.size(); i++){
		if (foodPos == snake[i]->getPosition())
			return true;
	}
	return false;
}

bool Play::isEating(){
	return snake[0]->getPosition() == food->getPosition();
}

void Play::expand(){
	auto tail = Sprite::create("body.png");
	tail->setPosition(tailPos);
	snake.push_back(tail);
	this->addChild(snake.back());
}

bool Play::isHit(){
	Vec2 headPos = snake[0]->getPosition();
	if (headPos.x == (minWidthUnit - 1)*unitSize || headPos.x == (maxWidthUnit + 1)*unitSize ||
		headPos.y == (minHeightUnit - 1)*unitSize || headPos.y == (maxHeightUnit + 1)*unitSize){
		return true;
	}
	for (int i = 1; i < (int)snake.size(); i++){
		if (snake[0]->getPosition() == snake[i]->getPosition())
			return true;
	}
	return false;
}