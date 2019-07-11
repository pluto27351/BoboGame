#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "MenuScene.h"

#define PTM_RATIO 32.0f
#define BOX2D_DEBUG 1

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
	
	//B2World
	_b2World = nullptr;
	b2Vec2 Gravity = b2Vec2(0.0f, -98);	//重力方向
	bool AllowSleep = true;					//允許睡著
	_b2World = new b2World(Gravity);		//創建世界
	_b2World->SetAllowSleeping(AllowSleep);	//設定物件允許睡著

    midground[0] = (cocos2d::Sprite *)rootNode->getChildByName("mg_0");
    midground[1] = (cocos2d::Sprite *)rootNode->getChildByName("mg_1");
    
	CreatePlayer();// 放入玩家
    CreateLevel();
    
    _b2World->SetContactListener(&_contactListener);
	if (BOX2D_DEBUG) {
		//DebugDrawInit
		_DebugDraw = nullptr;
		_DebugDraw = new GLESDebugDraw(PTM_RATIO);
		//設定DebugDraw
		_b2World->SetDebugDraw(_DebugDraw);
		//選擇繪製型別
		uint32 flags = 0;
		flags += GLESDebugDraw::e_shapeBit;						//繪製形狀
		flags += GLESDebugDraw::e_pairBit;
		flags += GLESDebugDraw::e_jointBit;
		flags += GLESDebugDraw::e_centerOfMassBit;
		flags += GLESDebugDraw::e_aabbBit;
		//設定繪製類型
		_DebugDraw->SetFlags(flags);
	}

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
    _fSlipTime+=dt;
	int velocityIterations = 8; // 速度迭代次數
	int positionIterations = 1; // 位置迭代次數，迭代次數一般設定為8~10 越高越真實但效率越差
	_b2World->Step(dt, velocityIterations, positionIterations);
    _Player->dostep();
    for (b2Body* body = _b2World->GetBodyList(); body; body = body->GetNext()){
        if (body->GetUserData() != NULL) {
            Sprite *ballData = (Sprite*)body->GetUserData();
            ballData->setPosition(body->GetPosition().x*PTM_RATIO,body->GetPosition().y*PTM_RATIO);
            ballData->setRotation(-1 *CC_RADIANS_TO_DEGREES(body->GetAngle()));
        }
    }
    if(midground[0]->getPosition().x < (-1575.52f))
        midground[0]->setPosition(midground[1]->getPosition().x+2599.52f, 768);
    midground[0]->setPosition(midground[0]->getPosition().x -3,768);
    if(midground[1]->getPosition().x < (-1575.52f))
        midground[1]->setPosition(midground[0]->getPosition().x+2599.52f, 768);
    midground[1]->setPosition(midground[1]->getPosition().x -3,768);
    _Level->dostep(dt);
    if(_contactListener.RunFlag == true && _fSlipTime > 1.0f)
        _Player->RunAct();
}

void GameScene::CreatePlayer() {
	// 放入玩家
	_Player = new CPlayer(_b2World);
	this->addChild(_Player, 2);
    _contactListener.setCollisionTargetPlayer(*(_Player->_body));
    _Player->RunAct();
}
void GameScene::CreateLevel(){
    _Level = new CLevelCreate(_b2World,1);
    this->addChild(_Level,2);
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
    if (touchLoc.x < rect.getMaxX()/2 && _fSlipTime > 1.0f) {
        if(_contactListener.JumpFlag == false){
            _fSlipTime = 0;
            _Player->SlipAct();
        }
        else
            _Player->AttackAct();
    }
    if (touchLoc.x > rect.getMaxX()/2 && _contactListener.JumpFlag == false) {
        _Player->JumpAct();
        _contactListener.JumpFlag = true;
        _contactListener.RunFlag = false;
    }
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

CContactListener::CContactListener(){}
void CContactListener::setCollisionTargetPlayer(cocos2d::Sprite &targetSprite){
    _Playersprite = &targetSprite;
}
void CContactListener::BeginContact(b2Contact* contact){
    b2Body* BodyA = contact->GetFixtureA()->GetBody();
    b2Body* BodyB = contact->GetFixtureB()->GetBody();
//    if(BodyA->GetFixtureList()->GetDensity() == -10000.0f){
//        if(BodyB->GetUserData() == _Playersprite)
//            CCLog("GameOver\n");
//    }
//    if(BodyB->GetFixtureList()->GetDensity() == -10000.0f){
//        if(BodyA->GetUserData() == _Playersprite)
//            CCLog("GameOver\n");
//    }
    if(BodyA->GetUserData() == _Playersprite){
        if(BodyB->GetFixtureList()->GetDensity() == 0.0f){
            if(BodyA->GetLinearVelocityFromWorldPoint(BodyB->GetPosition()).y<0)
                JumpFlag = false;
            RunFlag = true;
        }
    }
    if(BodyB->GetUserData() == _Playersprite){
        if(BodyA->GetFixtureList()->GetDensity() == 0.0f){
            if(BodyB->GetLinearVelocityFromWorldPoint(BodyA->GetPosition()).y<0)
                JumpFlag = false;
            RunFlag =true;
        }
    }
}
void CContactListener::EndContact(b2Contact* contact){
    b2Body* BodyA = contact->GetFixtureA()->GetBody();
    b2Body* BodyB = contact->GetFixtureB()->GetBody();
    }

void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();
	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	_b2World->DrawDebugData();
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}
