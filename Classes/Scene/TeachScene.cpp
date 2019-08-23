#include "TeachScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "element/Data.h"

USING_NS_CC;
#define QUE_POS Vec2(1050,1180)
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
	layer->initQue(unit);

	scene->addChild(layer);

	return scene;
}

void TeachScene::initQue(int chap) {
	rootNode = CSLoader::createNode("TeachScene.csb");

	_curUnit = chap;
    _curQue = 1;
    _curNum = -1;
    _question = NULL;
    
    resetQue();
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
        if(_bchangeScene)ChangeScene();
}

void TeachScene::ChangeScene()
{
    this->unscheduleAllCallbacks();
    this->removeAllChildren();
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/game_teach.plist");
	Director::getInstance()->getTextureCache()->removeUnusedTextures();

    Director::getInstance()->replaceScene(MenuScene::createScene());
//    auto scene = MenuScene::createScene();
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(1.5f, scene));
}

void TeachScene::NextQuestion(float a) {
	_right->setVisible(false);
	_wrong->setVisible(false);
    
    _curQue++;
	resetQue();
	_handDrawing->clearWhiteBoard();
    _numberArea->clear();
}

bool TeachScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	if (_homeBtn.touchesBegin(touchLoc))return true;
	if (_answerBtn.touchesBegin(touchLoc))return true;
	if (_giveupBtn.touchesBegin(touchLoc))return true;
	if (_numberArea->touchesBegin(touchLoc))return true;
    else _numberArea->setNumberVisual(false);
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
			scheduleOnce(CC_SCHEDULE_SELECTOR(TeachScene::NextQuestion),1.5f); //等待1.5秒再執行
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
        _bchangeScene = true;
        return;
	}

	_handDrawing->touchesEnded(touchLoc);
}

void TeachScene::resetQue()
{
    if(_curQue >= 13) return;
    
    //重設題目
    if(_question != NULL) {this->removeChild(_question);  delete _question;}
    
    _objNum = UNIT_OBJ[_curUnit - 1][_curQue - 1]; //圖片編號
    
    int queCate = UNIT_QUE[_curUnit - 1][_curQue - 1];
    int cate = queCate%100;
    int cate_data = queCate/100-1;
    switch (cate) {
        case 1:                                 //一般題
            switchdata = PIECE[_objNum];
            setQue(cate);
            break;
        case 2:                                 //變量題 chap4-7~12
            switchdata = PIECE_U4[_curQue-7];
            setQue_quantity();
            break;
        case 3:                                 //比例題 chap5-3.4.6
            switchdata = PIECE_U5[_curQue-1];
            setQue_picline();
            break;
        case 4:                                 //倍數題 chap5-其他題
            switchdata = PIECE_U5[_curQue-1];
            setQue_multiple();
            break;
        case 5:                                 //線段題 chap3-6
            switchdata = PIECE[0];
            setQue_line();
            break;
        case 11:                                //分子題1 chap2-3.5.8.11
            switchdata = PIECE_U2[cate_data];
            setQue(cate);
            break;
        case 12:                                //分子題2 chap3-7~12
            switchdata = PIECE_U3[cate_data];
            setQue(cate);
            break;
    }
    
    
}

void TeachScene::setQue(int k) {
    // 獲取題目分母資訊  隨幾取分母
   // if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
    //}
    
    //設定題目
    _question = new CAnsCreater(_curUnit, _curQue, _curNum);

    _question->queCreater(_curUnit, _curQue, _curNum);
    _question->setPosition(QUE_POS);
    this->addChild(_question);
    
}


void TeachScene::setQue_picline() {  //chap5-3.4.6
   // if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
   // }
    
    int k = 0;
    int _c = 0,_b = 0;
    do {
        _c = rand() % 6;
        _b = rand() % 5;
        k = UNIT5[_curNum - 2][_c][_b];  //_curNum = 2~6 , _c = 0~5  , _b = 0~4
        _c += 2; _b += 1;
    } while (k == 0);
    
    //設定題目
    _question = new CAnsCreater(_curUnit, _curQue, _curNum, _c, _b);
    _question->queCreater(_curUnit, _curQue, _curNum, _c, _b);
    _question->setPosition(QUE_POS);
    this->addChild(_question);
    
    
    
}

void TeachScene::setQue_multiple() {  //chap5其餘題
  //  if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
   // }
    int que_b = switchdata[11];
    int c = 0,ans_b = 0;
    int k = (2 * _curNum) / que_b;  //取上限 ２倍分母/分子 ＝ 倍數上限
    bool b;
    do {
        c = (rand() % k)+1; //隨機取倍數 <上限
        if(k == 2) {c = k; _c =-1;}
    } while ((c == 1 || c == _c));    //分母太小會沒有數字c出
    
    _c =c;
    ans_b = _c * que_b;
    
    
    //設定題目
    _question = new CAnsCreater(_curUnit, _curQue, _curNum, _c, que_b);
    _question->queCreater(_curUnit, _curQue, _curNum, _c, que_b);
    _question->setPosition(QUE_POS);
    this->addChild(_question);
    
}


void TeachScene::setQue_line(){
    // 獲取題目分母資訊  隨幾取分母
   // if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
   // }
    
//    int q[3]={-1};
//    do{
//        int qq[3];
//        qq[0] = rand() %  (2*_curNum);
//        qq[1] = rand() %  (2*_curNum);
//        qq[2] = rand() %  (2*_curNum);
//        q[0] = qq[0];
//        if(qq[1] < q[0]){
//            q[1]=q[0];q[0]=qq[1];
//        }
//        else {
//            q[1] = qq[1];
//        }
//
//        if(qq[2] < q[1]){
//            q[2]=q[1];
//            if(qq[2] < q[0]){
//                q[1]=q[0]; q[0]=qq[2];
//            }
//            else{
//                q[1]=qq[2];
//            }
//        }else{
//            q[2] = qq[2];
//        }
//    }while(q[0] == q[1] || q[0] == q[2] ||q[1] == q[2]);
//
//    CCLOG("a=%d , b=%d , c=%d",q[0],q[1],q[2]);
    
    int q = rand() %  (2*_curNum);
    //設定題目
    _question = new CAnsCreater(_curNum,q);
    _question->queCreater(_curUnit, _curQue, _curNum);
    _question->queLineCreater(_curNum,q);
    _question->setPosition(QUE_POS);
    this->addChild(_question);
    
    
    
}

void TeachScene::setQue_quantity() {  //chap4-7~12
   // if(_curNum == -1){
        srand(time(NULL));
        int num = (rand() % switchdata[0]) + 1;
        _curNum = switchdata[num];
   // }
    
    int c,r =UNIT4[_curQue-7][0];
    do{
        int k = (rand() % r) +1;
        c = UNIT4[_curQue-7][k];
    }while( c % _curNum != 0 || (_curNum <5  && c == _c) || (_curNum == 6 && (_curQue ==9 ||_curQue ==10|| _curQue == 12) && c == _c)) ;
    _c = c;
    
    
    //設定題目
    _question = new CAnsCreater(_curUnit, _curQue, _curNum);
    _question->queCreater(_curUnit, _curQue, _curNum, _c);
    _question->setPosition(QUE_POS);
    this->addChild(_question);
    
    
}
