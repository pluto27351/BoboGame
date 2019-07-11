#include "BoardScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

BoardScene::~BoardScene() {
	this->removeAllChildren();
	//AnimationCache::destroyInstance();
}

Scene* BoardScene::createScene()
{
	auto scene = Scene::create();

	auto layer = BoardScene::create();

	scene->addChild(layer);

	return scene;
}

bool BoardScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode("BoardScene.csb");

	addChild(rootNode);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/game_board.plist");

	char name[20] = "";

	//排行按鈕
	auto btn = rootNode->getChildByName("HomeBtn");
	_homeBtn.setButtonInfo("board_backbtn.png","board_backbtn.png",*this, btn->getPosition(), 1);
	_homeBtn.setScale(btn->getScaleX(), btn->getScaleY());
	rootNode->removeChild(btn);

	
	//觸控
	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(BoardScene::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(BoardScene::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(BoardScene::onTouchEnded, this);		//加入觸碰離開事件

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器

	// 將 doStep 函式掛入 schedule list 中，每一個 frame 就都會被呼叫到
	this->schedule(CC_SCHEDULE_SELECTOR(BoardScene::doStep));
	return true;

}


void BoardScene::doStep(float dt)
{
	
}

void BoardScene::ChangeScene()
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/game_board.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();

	auto scene = MenuScene::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
}


bool BoardScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();

	_homeBtn.touchesBegin(touchLoc);



	return true;
}

void  BoardScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();
	_homeBtn.touchesMoved(touchLoc);

}

void  BoardScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();

	if (_homeBtn.touchesEnded(touchLoc)) {
		ChangeScene();
	}
}

