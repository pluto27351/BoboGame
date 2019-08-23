#include "HomeScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;


Scene* HomeScene::createScene()
{
	auto scene = Scene::create();

	auto layer = HomeScene::create();
	scene->addChild(layer);

	return scene;
}



HomeScene::~HomeScene() {
    this->removeAllChildren();
    
//    if (_grassAction[0] != nullptr)  _grassAction[0]->release();
//    if (_grassAction[1] != nullptr)  _grassAction[1]->release();
//    AnimationCache::destroyInstance();

}

bool HomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScene.csb");
	
	addChild(rootNode);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/game_start.plist");

	//標題按鈕
	auto title = rootNode->getChildByName("title");
	_bTitle.setButtonInfo( "s_title.png", "s_title.png",*this,title->getPosition() ,1);
	_bTitle.setScale(title->getScaleX(), title->getScaleY());
	_bTitle.setRotate(title->getRotation());
	rootNode->removeChild(title);

	char name[20] = "";

	//擺動的草
    sprintf(name, "grass");
    _grass = rootNode->getChildByName(name);
    _grassAction = (ActionTimeline *)CSLoader::createTimeline("Ani/s_grass.csb");
    _grass->runAction(_grassAction);

	////音效.音樂
	//SimpleAudioEngine::getInstance()->preloadEffect("./Audio/button.WAV");
	//auto bkmusic = (cocostudio::ComAudio *)rootNode->getChildByName("BG_Music")->getComponent("BG_Music");
	//bkmusic->playBackgroundMusic();


	//觸控
	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(HomeScene::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(HomeScene::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(HomeScene::onTouchEnded, this);		//加入觸碰離開事件

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器

    // 將 doStep 函式掛入 schedule list 中，每一個 frame 就都會被呼叫到
    this->schedule(CC_SCHEDULE_SELECTOR(HomeScene::doStep));
	return true;
}

void HomeScene::doStep(float dt)
{
    if(_bchangeScene)ChangeScene();
}

void HomeScene::ChangeScene() 
{
    this->unscheduleAllCallbacks();
    this->removeAllChildren();
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("img/game_start.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures(); 

	auto scene = MenuScene::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
}


bool  HomeScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	_bTitle.touchesBegin(touchLoc);
	return true;
}

void  HomeScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();
	_bTitle.touchesMoved(touchLoc);
}

void  HomeScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();
	if (_bTitle.touchesEnded(touchLoc)) {
		_iTitleTouchTime++;
		if (_iTitleTouchTime == 1) {
			_grassAction->gotoFrameAndPlay(0, 30, false);
			_grassAction->setLastFrameCallFunc([=]()
			{
                _bchangeScene = true;
                //ChangeScene();
			});
		}
		else {
			/*node321ani->gotoFrameAndPlay(0, 225, false);
			node321ani->setLastFrameCallFunc([=]()
			{
				ChangeScene();
				this->removeChild(node321);
			});*/
		}

	}
	
}
