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
	rootNode = CSLoader::createNode("teachscene.csb");

	_chap = chap;

	//設定題目
	if (_question) {
		this->removeChild(_question);  delete _question;
	}

	_question = new CAnsCreater;
	auto target = rootNode->getChildByName("question");
    _chapNo++;
    
    if(_chapNo == 13) return;
    
    srand(time(NULL));
    auto objNum = UNIT_OBJ[_chap-1][_chapNo-1];
    int num = (rand() % PIECE[objNum][0]) + 1;
    _chapNum = PIECE[objNum][num];
    
    if(_chap == 5 && (_chapNo == 3||_chapNo == 4)){
        int k = 0;
        do {
            _c = rand()%6;
            _b= rand()%5;
            k = UNIT5[_chapNum-2][_c][_b];  //數字都從2開始 a.c.b
            _c+=2;_b+=2;
        }while (k == 0);
        
        _question->queCreater(_chap, _chapNo, _chapNum,_c,_b);
    }
    else{
        _question->queCreater(_chap, _chapNo, _chapNum);
    }
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

	rootNode = CSLoader::createNode("teachscene.csb");

	addChild(rootNode);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/game_start.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/game_teach.plist");
	char name[20] = "";

	//返回按鈕
	auto target = rootNode->getChildByName("home");
	_homeBtn.setButtonInfo("teach_btn_home.png", "teach_btn_home.png", *this, target->getPosition(), INTERFACE_LEVEL);
	_homeBtn.setScale(target->getScaleX(), target->getScaleY());
	_homeBtn.setRotate(target->getRotation());
	rootNode->removeChild(target);

	//回答按鈕
	target = rootNode->getChildByName("answer");
	_answerBtn.setButtonInfo("teach_btn_answer.png", "teach_btn_answer.png", *this, target->getPosition(), INTERFACE_LEVEL);
	_answerBtn.setScale(target->getScaleX(), target->getScaleY());
	_answerBtn.setRotate(target->getRotation());
	rootNode->removeChild(target);

	//放棄按鈕
	target = rootNode->getChildByName("giveup");
	_giveupBtn.setButtonInfo("teach_btn_giveup.png", "teach_btn_giveup.png", *this, target->getPosition(), INTERFACE_LEVEL);
	_giveupBtn.setScale(target->getScaleX(), target->getScaleY());
	_giveupBtn.setRotate(target->getRotation());
	rootNode->removeChild(target);

	//數字區
	_numberArea = new CNumberPannel;
	target = rootNode->getChildByName("number");
	_numberArea->setNumberInfo(target->getPosition(), INTERFACE_LEVEL);
	target = rootNode->getChildByName("answer_area");
	_numberArea->setAnswerInfo(target);
	this->addChild(_numberArea, INTERFACE_LEVEL);

	//手繪版
	_handDrawing = CDrawPanel::create();
	_handDrawing->initDrawingPanel(*rootNode, *this);
	_handDrawing->retain();

	_right = rootNode->getChildByName("right");
	_wrong = rootNode->getChildByName("wrong");
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
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/game_start.plist");
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/game_teach.plist");
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

