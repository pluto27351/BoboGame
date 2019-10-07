#include "TeachScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "element/Data.h"

USING_NS_CC;
#define SCREEN_POS Vec2(1365.5,768)
#define QUE_POS Vec2(SCREEN_POS.x + 26,1180)
using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

TeachScene::~TeachScene() {
//    _handDrawing->release();
//    delete _numberArea;
//    delete _question;
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
    _curQue = -1;
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
    _answerBtn.setButtonInfo("teach_btn_giveup.png", "teach_btn_giveup.png","tb_giveup_no.png", *this, target->getPosition(), INTERFACE_LEVEL);
    _answerBtn.setScale(target->getScaleX(), target->getScaleY());
    _answerBtn.setRotate(target->getRotation());
    _answerBtn.setEnabled(false);
    rootNode->removeChild(target);
    
    //放棄按鈕
    target = rootNode->getChildByName("nextque");
    _giveupBtn.setButtonInfo("teach_btn_answer.png", "teach_btn_answer.png", *this, target->getPosition(), INTERFACE_LEVEL);
    _giveupBtn.setScale(target->getScaleX(), target->getScaleY());
    _giveupBtn.setRotate(target->getRotation());
    rootNode->removeChild(target);
    
    //數字區
    _numberArea = new CNumberPannel;
    target = rootNode->getChildByName("number");
    _triggerBtn.setButtonInfo("teach_btn_number.png", "teach_btn_number.png", *this, target->getPosition(), INTERFACE_LEVEL);
    _numberArea->setNumberInfo(target->getPosition(), INTERFACE_LEVEL);
    
    target = rootNode->getChildByName("answer_area");
    _numberArea->setAnswerInfo(target);
    this->addChild(_numberArea, INTERFACE_LEVEL);
    
    
    //手繪版
    _handDrawing = CDrawPanel::create();
    _handDrawing->initDrawingPanel(*rootNode, *this);
    _handDrawing->retain();
    
    target = rootNode->getChildByName("right");
    _right = (Sprite *)Sprite::createWithSpriteFrameName("teacc_effect_right.png");
    _right->setPosition(target->getPosition());
    _right->setVisible(false);
    this->addChild(_right,10);
    rootNode->removeChild(target);
    
    _wrongAct = (Node *)rootNode->getChildByName("wrong");
    _wrongAct->setVisible(false);
    this->addChild(_wrongAct,10);
    _wrongActTime = (ActionTimeline *)CSLoader::createTimeline("Ani/wrong.csb");
    _wrongAct->runAction(_wrongActTime);
    _checkAns = -1;
    
    //觸控
    _listener1 = EventListenerTouchOneByOne::create();    //創建一個一對一的事件聆聽器
    _listener1->onTouchBegan = CC_CALLBACK_2(TeachScene::onTouchBegan, this);        //加入觸碰開始事件
    _listener1->onTouchMoved = CC_CALLBACK_2(TeachScene::onTouchMoved, this);        //加入觸碰移動事件
    _listener1->onTouchEnded = CC_CALLBACK_2(TeachScene::onTouchEnded, this);        //加入觸碰離開事件
    _listener1->onTouchCancelled = CC_CALLBACK_2(TeachScene::onTouchEnded, this);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);    //加入剛創建的事件聆聽器
    
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
    
    _handDrawing->release();
    delete _numberArea;
    delete _question;
    
    SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("Img/game_teach.plist");
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    Director::getInstance()->replaceScene(MenuScene::createScene());

}

void TeachScene::NextQuestion(float a) {
    _checkAns = -1;
    _right->setVisible(false);
    _wrongAct->setVisible(false);
    
    _curQue++;
    resetQue();
    _handDrawing->clearWhiteBoard();
    _numberArea->clear();
    _answerBtn.setEnabled(false);
    _bNumberOpened =false;
}

bool TeachScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
    Point touchLoc = pTouch->getLocation();
    if (_giveupBtn.touchesBegin(touchLoc) && _checkAns != 0)return true;  //答對時需按下題鍵
    if (_homeBtn.touchesBegin(touchLoc) && _checkAns != 0)return true;
    
    if(_checkAns != -1)return false;  //確認答案後 功能暫時關閉
    
    if(_triggerBtn.touchesBegin(touchLoc))return true;
    if (_answerBtn.touchesBegin(touchLoc))return true;
    if (_numberArea->touchesBegin(touchLoc))return true;
    else if(_bNumberOpened){
        _numberArea->setNumberVisual(false);
        _bNumberOpened = false;
        _handDrawing->changeToBlackPen();
    }
    
    _handDrawing->touchesBegin(touchLoc);
    
    
    return true;
}

void  TeachScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
    Point touchLoc = pTouch->getLocation();
    Point preTouchLoc = pTouch->getPreviousLocation();
    
    if(_triggerBtn.touchesMoved(touchLoc))return;
    if (_homeBtn.touchesMoved(touchLoc))return;
    if (_answerBtn.touchesMoved(touchLoc))return;
    if (_giveupBtn.touchesMoved(touchLoc))return;
    if (_numberArea->touchesMoved(touchLoc))return;
    
    if(_checkAns == -1)_handDrawing->touchesMoved(touchLoc, preTouchLoc);
    
}

void  TeachScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件
{
    Point touchLoc = pTouch->getLocation();
    
    if (_numberArea->touchesEnded(touchLoc)){
        if(_numberArea->hasAnyAns())_answerBtn.setEnabled(true);
        else _answerBtn.setEnabled(false);
        return;
    }
    
    if (_answerBtn.touchesEnded(touchLoc)) {
        _numberArea->setNumberVisual(false);
        _bNumberOpened = false;
        if (_question->CheckAnswer(_numberArea->getBoxAns())) {
            _right->setVisible(true);
            _checkAns = 1;
            char name[20] = "";
            sprintf(name, "U%d_Q%d_N%d",_curUnit,_curQue,_curNum);
            UserDefault::getInstance()->setBoolForKey(name, true);
            sprintf(name, "U%d_Q%d_FINISH",_curUnit,_curQue);
            int k = UserDefault::getInstance()->getIntegerForKey(name)+1;
            UserDefault::getInstance()->setIntegerForKey(name, k);
            if(k >= UNIT[_curUnit-1][_curQue-1][0]){
                sprintf(name, "U%d_FINISH",_curUnit);
                int k = UserDefault::getInstance()->getIntegerForKey(name)+1;
                UserDefault::getInstance()->setIntegerForKey(name, k);
            }
            k = UserDefault::getInstance()->getIntegerForKey("STAR")+1;
            UserDefault::getInstance()->setIntegerForKey("STAR", k);
            UserDefault::getInstance()->flush();
        }
        else {
            _wrongAct->setVisible(true);
            _wrongActTime->gotoFrameAndPlay(0, 80, false);
            _checkAns =0;
            _wrongActTime->setLastFrameCallFunc([=]()
            {
                _checkAns = -1;
                _wrongAct->setVisible(false);
            });
            
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
    
    if(_triggerBtn.touchesEnded(touchLoc)){
        _bNumberOpened = !_bNumberOpened;
        _numberArea->setNumberVisual(_bNumberOpened);
        return;
    }
    
    if(_checkAns == -1)_handDrawing->touchesEnded(touchLoc);
}

void TeachScene::resetQue()
{
    //重設題目
    if(_question != NULL) {this->removeChild(_question);  delete _question;}
    
    srand(time(NULL));
    char name[20] = "";
    sprintf(name, "U%d_FINISH",_curUnit);
    
    if(UserDefault::getInstance()->getIntegerForKey(name) >= 12){
        _curQue = rand()%12+1;
        switchdata = UNIT[_curUnit - 1][_curQue - 1];
        int cNum;
        do{
            int num = (rand() % switchdata[0]) + 1;
            cNum = switchdata[num];
        }while(cNum == _curNum);
        _curNum =  cNum;
        
    }
    else{
        int d =0;
        do{
            _curQue = rand()%12+1;
            sprintf(name, "U%d_Q%d_FINISH",_curUnit,_curQue);
            d = UserDefault::getInstance()->getIntegerForKey(name) - UNIT[_curUnit-1][_curQue-1][0];
            CCLOG("剩餘 %d 題",-d);
        }while (d >= 0);
        switchdata = UNIT[_curUnit - 1][_curQue - 1];
        int cNum;
        do{
            int num = (rand() % switchdata[0]) + 1;
            cNum = switchdata[num];
            sprintf(name, "U%d_Q%d_N%d",_curUnit,_curQue,cNum);
        }while(UserDefault::getInstance()->getBoolForKey(name) ||( d != -1 && cNum == _curNum));
        _curNum =  cNum;
    }
    
    int queCate = UNIT_QUE[_curUnit - 1][_curQue - 1];
    int cate = queCate%100;
    int cate_data = queCate/100-1;
    switch (cate) {
        case 1:                                 //一般題
            setQue(cate);
            break;
        case 2:                                 //變量題 chap4-7~12
            setQue_quantity();
            break;
        case 3:                                 //比例題 chap5-3.4.6
            setQue_picline();
            break;
        case 4:                                 //倍數題 chap5-其他題
            setQue_multiple();
            break;
        case 5:                                 //線段題 chap3-6
            setQue_line();
            break;
        case 11:                                //分子題1 chap2-3.5.8.11
            setQue(cate);
            break;
        case 12:                                //分子題2 chap3-7~12
            setQue(cate);
            break;
    }
    
    
}

void TeachScene::setQue(int k) {
    //設定題目
    _question = new CAnsCreater(_curUnit, _curQue, _curNum);
    
    _question->queCreater(_curUnit, _curQue, _curNum);
    _question->setPosition(QUE_POS);
    this->addChild(_question);
    
}


void TeachScene::setQue_picline() {  //chap5-3.4.6
    int k = 0;
    int _c = 0,_b = 0;  // _c = 2~6  , _b = 1~5
    _c = rand() % 5+2;
    do {
        _b = rand() % 5 + 1;
    } while (_b >= _curNum);
    
    //設定題目
    _question = new CAnsCreater(_curUnit, _curQue, _curNum, _c, _b);
    _question->queCreater(_curUnit, _curQue, _curNum, _c, _b);
    _question->setPosition(QUE_POS);
    this->addChild(_question);
    
}

void TeachScene::setQue_multiple() {  //chap5其餘題
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
    int q = rand() %  (2*_curNum);
    //設定題目
    _question = new CAnsCreater(_curNum,q);
    _question->queCreater(_curUnit, _curQue, _curNum);
    _question->queLineCreater(_curNum,q);
    _question->setPosition(QUE_POS);
    this->addChild(_question);
    
}

void TeachScene::setQue_quantity() {  //chap4-7~12
    int limit[9] = {2,3,4,5,6,8,9,10,12};
    int c;
    do{
        int k = rand() % 9;
        c = limit[k];
    }while(c%_curNum != 0 ||  c == _c) ;
    _c = c;
    
    //設定題目
    _question = new CAnsCreater(_curUnit, _curQue, _curNum);
    _question->queCreater(_curUnit, _curQue, _curNum, _c);
    _question->setPosition(QUE_POS);
    this->addChild(_question);
    
    
}
