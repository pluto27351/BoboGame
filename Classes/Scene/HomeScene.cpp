#include "HomeScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include "element/Data.h"


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
    char name[20] = "";
    //記錄初始化!
    UserDefault::getInstance()->setBoolForKey("TEACH_FLAG", 0);
    UserDefault::getInstance()->setBoolForKey("HAS_UNITDATA",0);
    if(!UserDefault::getInstance()->getBoolForKey("HAS_UNITDATA")){
        UserDefault::getInstance()->setBoolForKey("HAS_UNITDATA",1);
        for(int i=0;i<5;i++){
            sprintf(name, "U%d_FINISH",i+1);
            UserDefault::getInstance()->setIntegerForKey(name, 0);  //單元完成題數 max=12
            for(int j=0;j<12;j++){
                int maxNO = UNIT[i][j][0];
                sprintf(name, "U%d_Q%d_FINISH",i+1,j+1);
                UserDefault::getInstance()->setIntegerForKey(name, 0);  //題目完成分母數 max=UNIT[c][n][0]
                for(int k=0 ;k < maxNO ;k++){
                    int n = UNIT[i][j][k+1];
                    sprintf(name, "U%d_Q%d_N%d",i+1,j+1,n);
                    UserDefault::getInstance()->setBoolForKey(name,false);  //分母狀況
                }
            }
        }
        
        UserDefault::getInstance()->setIntegerForKey("STAR", 0);  //0
        UserDefault::getInstance()->flush();
    }
    
    UserDefault::getInstance()->flush();
    
	auto rootNode = CSLoader::createNode("MainScene.csb");
	
	addChild(rootNode);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/game_start.plist");

	//標題按鈕
	auto title = rootNode->getChildByName("title");
	_bTitle.setButtonInfo( "s_title.png", "s_title.png",*this,title->getPosition() ,0);
	_bTitle.setScale(title->getScaleX(), title->getScaleY());
	_bTitle.setRotate(title->getRotation());
	rootNode->removeChild(title);

	//擺動的草
    auto target = rootNode->getChildByName("grass");
    _grass = CSLoader::createNode("Ani/s_grass.csb");
    _grass->setPosition(target->getPosition());
    this->addChild(_grass,3);
    _grassAction = (ActionTimeline *)CSLoader::createTimeline("Ani/s_grass.csb");
    _grass->runAction(_grassAction);
     _grassAction->gotoFrameAndPlay(0, 0, false);
    rootNode->removeChild(target);
    
    target = rootNode->getChildByName("bg_f");
    _forntBg = (Sprite *)Sprite::createWithSpriteFrameName("startpage_front.png");
    _forntBg->setPosition(target->getPosition());
    this->addChild(_forntBg,5);
    rootNode->removeChild(target);
    
    
    //星星區
    _bstarTouched=false;
    target = rootNode->getChildByName("t_star");
    _bStar.setButtonInfo( "touchArea.png", "touchArea.png",*this,target->getPosition() ,0);
    _bStar.setScale(target->getScaleX(), title->getScaleY());
    _bStar.setRotate(target->getRotation());
    rootNode->removeChild(target);
    //掉落星星
    target = rootNode->getChildByName("star");
    _star = CSLoader::createNode("Ani/starfall.csb");
    _star->setPosition(target->getPosition());
    this->addChild(_star,10);
    _starAction = (ActionTimeline *)CSLoader::createTimeline("Ani/starfall.csb");
    _star->runAction(_starAction);
    _starAction->gotoFrameAndPlay(0, 0, false);
    rootNode->removeChild(target);
    

    //樹區
    _btreeTouched=false;
    target = rootNode->getChildByName("t_tree");
    _bTree.setButtonInfo( "touchArea.png", "touchArea.png",*this,target->getPosition() ,0);
    _bTree.setScale(target->getScaleX(), title->getScaleY());
    _bTree.setRotate(target->getRotation());
    rootNode->removeChild(target);
    //抖動的樹
    target = rootNode->getChildByName("tree");
    _tree = CSLoader::createNode("Ani/tree.csb");
    _tree->setPosition(target->getPosition());
    this->addChild(_tree,10);
    _treeAction = (ActionTimeline *)CSLoader::createTimeline("Ani/tree.csb");
    _tree->runAction(_treeAction);
    _treeAction->gotoFrameAndPlay(0, 0, false);
    rootNode->removeChild(target);
    
    


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

	auto scene = TransitionMoveInR::create(0.5f, MenuScene::createScene());
	CCDirector::sharedDirector()->replaceScene(scene);
}


bool  HomeScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	_bTitle.touchesBegin(touchLoc);
    _bStar.touchesBegin(touchLoc);
    _bTree.touchesBegin(touchLoc);
	return true;
}

void  HomeScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
	Point touchLoc = pTouch->getLocation();
	_bTitle.touchesMoved(touchLoc);
    _bStar.touchesMoved(touchLoc);
    _bTree.touchesMoved(touchLoc);
}

void  HomeScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
	Point touchLoc = pTouch->getLocation();
	if (_bTitle.touchesEnded(touchLoc)) {
		_iTitleTouchTime++;
		if (_iTitleTouchTime == 1) {
			_grassAction->gotoFrameAndPlay(0, 50, false);
			_grassAction->setLastFrameCallFunc([=]()
			{
                _bchangeScene = true;
			});
		}
	}
    
    if(_bStar.touchesMoved(touchLoc) && !_bstarTouched){
        _bstarTouched = true;
        _starAction->gotoFrameAndPlay(0, 70, false);
        _starAction->setLastFrameCallFunc([=]()
        {
            _bstarTouched = false;
            _starAction->gotoFrameAndPlay(0, 0, false);
        });
    }
    
    if(_bTree.touchesMoved(touchLoc) && !_btreeTouched){
        _btreeTouched = true;
        _treeAction->gotoFrameAndPlay(0, 32, false);
        _treeAction->setLastFrameCallFunc([=]()
        {
            _btreeTouched = false;
            _treeAction->gotoFrameAndPlay(0, 0, false);
        });
    }
	
}
