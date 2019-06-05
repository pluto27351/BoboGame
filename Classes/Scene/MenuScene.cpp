#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TeachScene.h"
#include "GameScene.h"
#include "BoardScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

enum SCENE{TeachScene,GameScene,BoardScene};

MenuScene::~MenuScene() {
	//for (int i = 0; i < 5; i++)delete _chapBtn[i];
	//delete _gameBtn;
	//delete _boardBtn;
	this->removeAllChildren();
	//AnimationCache::destroyInstance();
}

Scene* MenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = MenuScene::create();

	scene->addChild(layer);

	return scene;
}

bool MenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode("MenuScene.csb");
	addChild(rootNode);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/scene101.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/scene101bg.plist");

	char name[20] = "";

	//章節按鈕
	for (int i = 0; i < 5; i++) {
		sprintf(name, "Chap_%02d", i + 1);
		auto btn = rootNode->getChildByName(name);
		_chapBtn[i].setButtonInfo("w_bg.png", "w_bg.png",*this, btn->getPosition(),1);
		_chapBtn[i].setScale(btn->getScaleX(), btn->getScaleY());
		_chapBtn[i].setRotate(btn->getRotation());
		rootNode->removeChild(btn);
	}

	//遊戲按鈕
	auto btn = rootNode->getChildByName("Game");
	_gameBtn.setButtonInfo("w_bg.png", "w_bg.png", *this, btn->getPosition(), 1);
	_gameBtn.setScale(btn->getScaleX(), btn->getScaleY());
	_gameBtn.setRotate(btn->getRotation());
	rootNode->removeChild(btn);

	//排行按鈕
	btn = rootNode->getChildByName("Board");
	_boardBtn.setButtonInfo("w_bg.png", "w_bg.png", *this, btn->getPosition(), 1);
	_boardBtn.setScale(btn->getScaleX(), btn->getScaleY());
	_boardBtn.setRotate(btn->getRotation());
	rootNode->removeChild(btn);
	
	//觸控
	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(MenuScene::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);		//加入觸碰離開事件

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器

	// 將 doStep 函式掛入 schedule list 中，每一個 frame 就都會被呼叫到
	this->schedule(CC_SCHEDULE_SELECTOR(MenuScene::doStep));
	return true;

}


void MenuScene::doStep(float dt)
{
	
}

void MenuScene::ChangeScene(int changescene,int chap)
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/scene101.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/scene101bg.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();

	Scene *scene;
	switch (changescene)
	{
		case TeachScene:
			scene = TeachScene::createScene(chap);
			break;
		case GameScene:
			scene = GameScene::createScene();
			break;
		case BoardScene:
			scene = BoardScene::createScene();
			break;
	}
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
}


bool MenuScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();

	for (int i = 0; i < 5; i++) {
		_chapBtn[i].touchesBegin(touchLoc);
	}
	_gameBtn.touchesBegin(touchLoc);
	_boardBtn.touchesBegin(touchLoc);
	////跳躍與攻擊
	//if (touchLoc.y < 360  &&  START) {  
	//	if (touchLoc.x < 640 && _Player->BulletFlag == false) {
	//		_Player->RenderBullet();
	//		SimpleAudioEngine::getInstance()->playEffect("./Audio/bullet.WAV", false);
	//	}
	//	else if (touchLoc.x >= 640 && _Player->JumpFlag == false && _Player->JumpTime < 2) {
	//		_Player->JumpAct();
	//		SimpleAudioEngine::getInstance()->playEffect("./Audio/jump.WAV", false);
	//	}

	//}


	return true;
}

void  MenuScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();

	for (int i = 0; i < 5; i++) {
		_chapBtn[i].touchesMoved(touchLoc);
	}
	_gameBtn.touchesMoved(touchLoc);
	_boardBtn.touchesMoved(touchLoc);
}

void  MenuScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();

	for (int i = 0; i < 5; i++) {
		if (_chapBtn[i].touchesEnded(touchLoc)) {
			ChangeScene(TeachScene,i+1);
			return;
		}
	}

	if(_gameBtn.touchesEnded(touchLoc)) {
		ChangeScene(GameScene);
		return;
	}
	if(_boardBtn.touchesEnded(touchLoc)) {
		ChangeScene(BoardScene);
		return;
	}

}

