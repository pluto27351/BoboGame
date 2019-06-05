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
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/scene101.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/scene101bg.plist");

	//標題按鈕
	auto title = rootNode->getChildByName("Title");
	_bTitle.setButtonInfo( "w_bg.png", "w_bg.png",*this,title->getPosition() ,1);
	_bTitle.setScale(title->getScaleX(), title->getScaleY());
	_bTitle.setRotate(title->getRotation());
	rootNode->removeChild(title);

	char name[20] = "";

	//擺動的草
	for (int i = 0; i < 2; i++) {
		sprintf(name, "Grass_%02d", i+1);
		_grass[i] = rootNode->getChildByName(name);
		_grassAction[i] = (ActionTimeline *)CSLoader::createTimeline("Ani/Grass.csb");
		_grass[i]->runAction(_grassAction[i]);
	}

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


	return true;
}


void HomeScene::ChangeScene() 
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/scene101.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/scene101bg.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures(); 

	auto scene = MenuScene::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
}


bool  HomeScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	_bTitle.touchesBegin(touchLoc);
	//if (rPR.containsPoint(touchLoc)){
	//	SimpleAudioEngine::getInstance()->playEffect("./Audio/button.WAV", false);
	//	ChageAni(_PR, _PY, _PG, _PB, Color3B(180, 53, 44));
	//}
	

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
			_grassAction[0]->gotoFrameAndPlay(0, 30, false);
			_grassAction[1]->gotoFrameAndPlay(0, 30, false);
			_grassAction[0]->setLastFrameCallFunc([=]()
			{
				ChangeScene();
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

	//轉場景
	//if (_btnPlay->isUsed()) {
	//	//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	//	bkmusic->stopBackgroundMusic();

	//	CCScene *scene = CCScene::create();
	//	auto *layer = GamePlay::createScene(Mode, PColor, PColor2,_STable);
	//	scene->addChild(layer);
	//	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
	//}
	
	
}
