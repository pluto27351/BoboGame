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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/game_menu.plist");

	char name[20] = "";

	//章節按鈕
	for (int i = 0; i < 5; i++) {
		sprintf(name, "title_%d", i + 1);
		auto btn = rootNode->getChildByName(name);
        sprintf(name, "menu_btn_ch%d.png", i + 1);
		_chapBtn[i].setButtonInfo(name,name,*this, btn->getPosition(),1);
		_chapBtn[i].setScale(btn->getScaleX(), btn->getScaleY());
		_chapBtn[i].setRotate(btn->getRotation());
		rootNode->removeChild(btn);
	}

	//遊戲按鈕
	auto btn = rootNode->getChildByName("title_g");
	_gameBtn.setButtonInfo("menu_btn_g.png", "menu_btn_g.png", *this, btn->getPosition(), 1);
	_gameBtn.setScale(btn->getScaleX(), btn->getScaleY());
	_gameBtn.setRotate(btn->getRotation());
	rootNode->removeChild(btn);

	//排行按鈕
	btn = rootNode->getChildByName("title_b");
	_boardBtn.setButtonInfo("menu_btn_b.png","menu_btn_b.png", *this, btn->getPosition(), 1);
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
    if(_bchangeScene)ChangeScene(_sceneNum,_uni);
}

void MenuScene::ChangeScene(int changescene,int chap)
{
    this->unscheduleAllCallbacks();
    this->removeAllChildren();
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/game_menu.plist");
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
            _bchangeScene = true;
            _sceneNum = TeachScene;
            _uni = i+1;
			//ChangeScene(TeachScene,i+1);
			return;
		}
	}

	if(_gameBtn.touchesEnded(touchLoc)) {
        _bchangeScene = true;
        _sceneNum = GameScene;
        _uni = 0;
		//ChangeScene(GameScene);
		return;
	}
	if(_boardBtn.touchesEnded(touchLoc)) {
        _bchangeScene = true;
        _sceneNum = BoardScene;
        _uni = 0;
		//ChangeScene(BoardScene);
		return;
	}

}

