#include "TeachScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "element/Data.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

TeachScene::~TeachScene() {
	this->removeAllChildren();
	//AnimationCache::destroyInstance();
}

Scene* TeachScene::createScene(int unit)
{
	auto scene = Scene::create();

	auto layer = TeachScene::create();
	layer->randomQuestion(unit);

	scene->addChild(layer);

	return scene;
}

void TeachScene::randomQuestion(int chap) {
	rootNode = CSLoader::createNode("TeachScene.csb");

	_chap = chap;
	int n;
//    do {
//        n = random(1, 2);
//    } while (n == _chapNo);
//    _chapNo = n;

	do {
		n = random(2, 12);
	} while (n == _chapNum);
	_chapNum = n;

	int *k;
	k = new int;
	delete k;

	//設定題目
	CCLOG("new!");
	if (_question) {
		this->removeChild(_question);  delete _question;
	}

	_question = new CAnsCreater;
	auto target = rootNode->getChildByName("Question");
	//_question->queCreater(_chap, _chapNo, _chapNum);
    _chapNo++;
	_question->queCreater(_chap, _chapNo, _chapNum);
	_question->setPosition(target->getPosition());
	this->addChild(_question);
}

bool TeachScene::init()
{
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	rootNode = CSLoader::createNode("TeachScene.csb");

	addChild(rootNode);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/scene101.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/scene101bg.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/handdrawing.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/equalcontrol.plist");
	char name[20] = "";

	//返回按鈕
	auto target = rootNode->getChildByName("HomeBtn");
	_homeBtn.setButtonInfo("s_homeOn.png", "s_homeDown.png", *this, target->getPosition(), INTERFACE_LEVEL);
	_homeBtn.setScale(target->getScaleX(), target->getScaleY());
	_homeBtn.setRotate(target->getRotation());
	rootNode->removeChild(target);

	//回答按鈕
	target = rootNode->getChildByName("AnswerBtn");
	_answerBtn.setButtonInfo("b_playOn.png", "b_playDown.png", *this, target->getPosition(), INTERFACE_LEVEL);
	_answerBtn.setScale(target->getScaleX(), target->getScaleY());
	_answerBtn.setRotate(target->getRotation());
	rootNode->removeChild(target);

	//放棄按鈕
	target = rootNode->getChildByName("GiveupBtn");
	_giveupBtn.setButtonInfo("s_closeOn.png", "s_closeDown.png", *this, target->getPosition(), INTERFACE_LEVEL);
	_giveupBtn.setScale(target->getScaleX(), target->getScaleY());
	_giveupBtn.setRotate(target->getRotation());
	rootNode->removeChild(target);

	//數字區
	_numberArea = new CNumberPannel;
	target = rootNode->getChildByName("Number");
	_numberArea->setNumberInfo(target->getPosition(), INTERFACE_LEVEL);
	target = rootNode->getChildByName("Answer");
	_numberArea->setAnswerInfo(target);
	this->addChild(_numberArea, INTERFACE_LEVEL);

	//手繪版
	_handDrawing = CDrawPanel::create();
	_handDrawing->initDrawingPanel(*rootNode, *this);
	_handDrawing->retain();

	_right = rootNode->getChildByName("Right");
	_wrong = rootNode->getChildByName("Wrong");
	_right->setVisible(false);
	_wrong->setVisible(false);

	_chapNo = 0;
	_chapNum = 0;
	//觸控
	_listener1 = EventListenerTouchOneByOne::create();	//創建一個一對一的事件聆聽器
	_listener1->onTouchBegan = CC_CALLBACK_2(TeachScene::onTouchBegan, this);		//加入觸碰開始事件
	_listener1->onTouchMoved = CC_CALLBACK_2(TeachScene::onTouchMoved, this);		//加入觸碰移動事件
	_listener1->onTouchEnded = CC_CALLBACK_2(TeachScene::onTouchEnded, this);		//加入觸碰離開事件
	_listener1->onTouchCancelled = CC_CALLBACK_2(TeachScene::onTouchEnded, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);	//加入剛創建的事件聆聽器

	// 將 doStep 函式掛入 schedule list 中，每一個 frame 就都會被呼叫到
	this->schedule(CC_SCHEDULE_SELECTOR(TeachScene::doStep));
	return true;

}


void TeachScene::doStep(float dt)
{

}

void TeachScene::ChangeScene()
{
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/scene101.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/scene101bg.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/handdrawing.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/equalcontrol.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();

	auto scene = MenuScene::createScene();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
}

void TeachScene::NextQuestion(float a) {
	_right->setVisible(false);
	_wrong->setVisible(false);

	randomQuestion(_chap);
	_handDrawing->clearWhiteBoard();
}

bool TeachScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	if (_homeBtn.touchesBegin(touchLoc))return true;
	if (_answerBtn.touchesBegin(touchLoc))return true;
	if (_giveupBtn.touchesBegin(touchLoc))return true;
	if (_numberArea->touchesBegin(touchLoc))return true;
	_handDrawing->touchesBegin(touchLoc);
	return true;
}

void  TeachScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();
	Point preTouchLoc = pTouch->getPreviousLocation();

	if (_homeBtn.touchesMoved(touchLoc))return;
	if (_answerBtn.touchesMoved(touchLoc))return;
	if (_giveupBtn.touchesMoved(touchLoc))return;
	if (_numberArea->touchesMoved(touchLoc))return;

	_handDrawing->touchesMoved(touchLoc, preTouchLoc);
}

void  TeachScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();
	if (_numberArea->touchesEnded(touchLoc)) return;

	if (_answerBtn.touchesEnded(touchLoc)) {
		if (_question->CheckAnswer(_numberArea->getBoxAns())) {
			_right->setVisible(true);
			scheduleOnce(CC_SCHEDULE_SELECTOR(TeachScene::NextQuestion),1.5f);
		}
		else {
			_wrong->setVisible(true);
			scheduleOnce(CC_SCHEDULE_SELECTOR(TeachScene::NextQuestion), 1.5f);
		}
		return;
	}
	if (_giveupBtn.touchesEnded(touchLoc)) {
		NextQuestion(0);
		return;
	}

	if (_homeBtn.touchesEnded(touchLoc)) {
		ChangeScene();return; 
	}

	_handDrawing->touchesEnded(touchLoc);
}

