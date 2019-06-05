#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

GameScene::~GameScene() {
	/*while (hasEnemy) {
		CEnemy *e = _HeadEnemy;
		e->GoDie = true;		killEnemy();
	}*/

	
	// 釋放音效檔
	//SimpleAudioEngine::getInstance()->unloadEffect("./Audio/jump.WAV"); 

}

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode("PlayScene.csb");

	addChild(rootNode);

	// 預先載入音效檔	
	//SimpleAudioEngine::getInstance()->preloadEffect("./Audio/jump.WAV");
    
    // 放入玩家
    _Player = new CPlayer();
    this->addChild(_Player,2);
    _Player->RunAct();

	// 按鈕相關
	/*_btnGo = new C3Button(Vec2(1120,125), "b_playOn.png", "b_playDown.png", "b_playDown.png");
	this->addChild(_btnGo, 11);*/
	
	//觸控
	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);		//加入觸碰離開事件

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器

	// 將 doStep 函式掛入 schedule list 中，每一個 frame 就都會被呼叫到
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::doStep));
	return true;

}


void GameScene::doStep(float dt)
{
	
}

void GameScene::ChangeScene()
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/scene101.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/scene101bg.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();

	auto scene = MenuScene::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
}

bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
    Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
    if (touchLoc.x < rect.getMaxX()/2) {
        _Player->JumpAct();
    }
    if (touchLoc.x > rect.getMaxX()/2) {
        _Player->SlipAct();
    }
    
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

void  GameScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();


}

void  GameScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();


}

