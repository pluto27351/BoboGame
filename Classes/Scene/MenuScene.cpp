#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "TeachScene.h"
#include "GameScene.h"
#include "BoardScene.h"
#include "SimpleAudioEngine.h"
#include "element/Data.h"

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
    
    //記錄數據開始
    // CCUserDefault::sharedUserDefault()->setBoolForKey("HAS_UNITDATA",0);
    //
    if(!CCUserDefault::sharedUserDefault()->getBoolForKey("HAS_UNITDATA")){
        //CCLOG("%s",CCUserDefault::sharedUserDefault()->getXMLFilePath().c_str());
        CCUserDefault::sharedUserDefault()->setBoolForKey("HAS_UNITDATA",1);
        for(int i=0;i<5;i++){
            sprintf(name, "U%d_FINISH",i+1);
            CCUserDefault::sharedUserDefault()->setIntegerForKey(name, 0);  //0
            for(int j=0;j<12;j++){
                int maxNO = UNIT[i][j][0];
                sprintf(name, "U%d_Q%d_FINISH",i+1,j+1);
                CCUserDefault::sharedUserDefault()->setIntegerForKey(name, 0);  //0
                for(int k=0 ;k < maxNO ;k++){
                    int n = UNIT[i][j][k+1];
                    sprintf(name, "U%d_Q%d_N%d",i+1,j+1,n);
                    CCUserDefault::sharedUserDefault()->setBoolForKey(name,false);  //false
                }
            }
        }
        
        CCUserDefault::sharedUserDefault()->setIntegerForKey("STAR", 0);  //0
        CCUserDefault::sharedUserDefault()->flush();
    }
    
    
    //章節按鈕
    for (int i = 0; i < 5; i++) {
        sprintf(name, "title_%d", i + 1);
        auto btn = rootNode->getChildByName(name);
        sprintf(name, "menu_btn_ch%d.png", i + 1);
        _chapBtn[i].setButtonInfo(name,name,*this, btn->getPosition(),1);
        _chapBtn[i].setScale(btn->getScaleX(), btn->getScaleY());
        _chapBtn[i].setRotate(btn->getRotation());
        rootNode->removeChild(btn);
        
        sprintf(name, "line_%d", i + 1);
        _chapLoad[i] = (LoadingBar *)rootNode->getChildByName(name)->getChildByName("inner");
        int max = 0,now = 0;
        for(int j=0 ;j<12 ;j++){
            sprintf(name, "U%d_Q%d_FINISH",i+1,j+1);
            int n = CCUserDefault::sharedUserDefault()->getIntegerForKey(name);
            max += UNIT[i][j][0];
            now += (n > UNIT[i][j][0] ? UNIT[i][j][0]:n);
        }
        float percent =(float)now/max *100;
        _chapLoad[i]->setPercent(percent);
        CCLOG("u%d:%f percent",i+1,percent);
        
        sprintf(name, "pic_%d", i + 1);
        btn = rootNode->getChildByName(name);
        if(percent >= 100) sprintf(name, "menu_ch%d_1.png", i + 1);
        else    sprintf(name, "menu_ch%d_0.png", i + 1);
        _chapPic[i] = (Sprite*)Sprite::createWithSpriteFrameName(name);
        _chapPic[i]->setPosition(btn->getPosition());
        _chapPic[i]->setScale(btn->getScaleX(), btn->getScaleY());
        addChild(_chapPic[i]);
        rootNode->removeChild(btn);
        
    }
    
    _scoreText = (Text *)rootNode->getChildByName("n_star");
    char ss[20] = "";
    sprintf(ss, "%d", CCUserDefault::sharedUserDefault()->getIntegerForKey("STAR"));
    CCLOG("game = %d", CCUserDefault::sharedUserDefault()->getIntegerForKey("STAR"));
    _scoreText->setString(ss);
    
    //遊戲按鈕
    auto btn = rootNode->getChildByName("title_g");
    _gameBtn.setButtonInfo("menu_game_on.png","menu_game_on.png","menu_game_lock.png", *this, btn->getPosition(), 1);
    _gameBtn.setScale(btn->getScaleX(), btn->getScaleY());
    _gameBtn.setRotate(btn->getRotation());
    //if(CCUserDefault::sharedUserDefault()->getIntegerForKey("STAR") <= 5) _gameBtn.setEnabled(false);
    rootNode->removeChild(btn);
    
    //排行按鈕
    btn = rootNode->getChildByName("title_b");
    _boardBtn.setButtonInfo("menu_btn_b.png","menu_btn_b.png", *this, btn->getPosition(), 1);
    _boardBtn.setScale(btn->getScaleX(), btn->getScaleY());
    _boardBtn.setRotate(btn->getRotation());
    rootNode->removeChild(btn);
    
    //觸控
    _listener1 = EventListenerTouchOneByOne::create();    //創建一個一對一的事件聆聽器
    _listener1->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);        //加入觸碰開始事件
    _listener1->onTouchMoved = CC_CALLBACK_2(MenuScene::onTouchMoved, this);        //加入觸碰移動事件
    _listener1->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);        //加入觸碰離開事件
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener1, this);    //加入剛創建的事件聆聽器
    
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
    int k;
    switch (changescene)
    {
        case TeachScene:
            scene = TeachScene::createScene(chap);
            break;
        case GameScene:
            k = CCUserDefault::sharedUserDefault()->getIntegerForKey("STAR")-5;
            CCUserDefault::sharedUserDefault()->setIntegerForKey("STAR", k);
            CCLOG("game = %d",k);
            CCUserDefault::sharedUserDefault()->flush();
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

