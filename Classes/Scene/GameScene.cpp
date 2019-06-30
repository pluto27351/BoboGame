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
	PntLoc = rootNode->getPosition();

	// 預先載入音效檔	
	//SimpleAudioEngine::getInstance()->preloadEffect("./Audio/jump.WAV");

	// 按鈕相關
	/*_btnGo = new C3Button(Vec2(1120,125), "b_playOn.png", "b_playDown.png", "b_playDown.png");
	this->addChild(_btnGo, 11);*/
	
	//B2World
	_b2World = nullptr;
	b2Vec2 Gravity = b2Vec2(0.0f, 0.0f);	//重力方向
	bool AllowSleep = true;					//允許睡著
	_b2World = new b2World(Gravity);		//創建世界
	_b2World->SetAllowSleeping(AllowSleep);	//設定物件允許睡著

	CreatePlayer();// 放入玩家

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
	int velocityIterations = 8; // 速度迭代次數
	int positionIterations = 1; // 位置迭代次數，迭代次數一般設定為8~10 越高越真實但效率越差
	_b2World->Step(dt, velocityIterations, positionIterations);
	PlayerCollision();
	for (b2Body* body = _b2World->GetBodyList(); body; body = body->GetNext()){
		if (body->GetUserData() != NULL) {
			Sprite *ballData = (Sprite*)body->GetUserData();
			ballData->setPosition(body->GetPosition().x*PTM_RATIO,body->GetPosition().y*PTM_RATIO);
			ballData->setRotation(-1 *CC_RADIANS_TO_DEGREES(body->GetAngle()));
		}
	}
}

void GameScene::CreatePlayer() {
	// 放入玩家
	_Player = new CPlayer();
	this->addChild(_Player, 2);
	_Player->RunAct();

	// box2D
	Point loc = _Player->GetPos();
	Size ts = _Player->GetSize();
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = _Player->_body;
	//bodyDef.position.Set(PntLoc.x + loc.x / PTM_RATIO, PntLoc.y + loc.y / PTM_RATIO);
	PlayerBody = _b2World->CreateBody(&bodyDef);

	b2PolygonShape rectShape;
	float scaleX = _Player->GetScale().x;	// 水平的線段圖示假設都只有對 X 軸放大
	float scaleY = _Player->GetScale().y;	// 水平的線段圖示假設都只有對 X 軸放大

	Point lep[4], wep[4];
	lep[0].x = (ts.width - 25) / 2.0f;  lep[0].y = (ts.height - 40) / 2.0f;
	lep[1].x = -(ts.width - 25) / 2.0f; lep[1].y = (ts.height - 40) / 2.0f;
	lep[2].x = -(ts.width - 25) / 2.0f; lep[2].y = -(ts.height - 40) / 2.0f;
	lep[3].x = (ts.width - 25) / 2.0f;  lep[3].y = -(ts.height - 40) / 2.0f;

	cocos2d::Mat4 modelMatrix, rotMatrix;
	modelMatrix.m[0] = scaleX;  // 先設定 X 軸的縮放
	modelMatrix.m[5] = scaleY;  // 先設定 Y 軸的縮放
	cocos2d::Mat4::createRotationZ(0 * M_PI / 180.0f, &rotMatrix);
	modelMatrix.multiply(rotMatrix);
	modelMatrix.m[3] = PntLoc.x + loc.x; //設定 Translation，自己的加上父親的
	modelMatrix.m[7] = PntLoc.y + loc.y; //設定 Translation，自己的加上父親的
	for (size_t j = 0; j < 4; j++)
	{
		wep[j].x = lep[j].x * modelMatrix.m[0] + lep[j].y * modelMatrix.m[1] + modelMatrix.m[3];
		wep[j].y = lep[j].x * modelMatrix.m[4] + lep[j].y * modelMatrix.m[5] + modelMatrix.m[7];
	}
	b2Vec2 vecs[] = {
		b2Vec2(wep[0].x / PTM_RATIO, wep[0].y / PTM_RATIO),
		b2Vec2(wep[1].x / PTM_RATIO, wep[1].y / PTM_RATIO),
		b2Vec2(wep[2].x / PTM_RATIO, wep[2].y / PTM_RATIO),
		b2Vec2(wep[3].x / PTM_RATIO, wep[3].y / PTM_RATIO) };

	rectShape.Set(vecs, 4);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &rectShape;
	fixtureDef.restitution = 0.5f;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.15f;
	PlayerBody->CreateFixture(&fixtureDef);
}
void GameScene::PlayerCollision()
{
	PlayerBody->DestroyFixture(PlayerBody->GetFixtureList());
	Point loc = _Player->GetPos();
	Size ts = _Player->GetSize();
	b2PolygonShape rectShape;
	float scaleX = _Player->GetScale().x;	// 水平的線段圖示假設都只有對 X 軸放大
	float scaleY = _Player->GetScale().y;	// 水平的線段圖示假設都只有對 X 軸放大
	

	Point lep[4], wep[4];
	lep[0].x = (ts.width - 25) / 2.0f;  lep[0].y = (ts.height - 40) / 2.0f;
	lep[1].x = -(ts.width - 25) / 2.0f; lep[1].y = (ts.height - 40) / 2.0f;
	lep[2].x = -(ts.width - 25) / 2.0f; lep[2].y = -(ts.height - 40) / 2.0f;
	lep[3].x = (ts.width - 25) / 2.0f;  lep[3].y = -(ts.height - 40) / 2.0f;

	cocos2d::Mat4 modelMatrix, rotMatrix;
	modelMatrix.m[0] = scaleX;  // 先設定 X 軸的縮放
	modelMatrix.m[5] = scaleY;  // 先設定 Y 軸的縮放
	cocos2d::Mat4::createRotationZ(0 * M_PI / 180.0f, &rotMatrix);
	modelMatrix.multiply(rotMatrix);
	modelMatrix.m[3] = PntLoc.x + loc.x; //設定 Translation，自己的加上父親的
	modelMatrix.m[7] = PntLoc.y + loc.y; //設定 Translation，自己的加上父親的
	for (size_t j = 0; j < 4; j++)
	{
		wep[j].x = lep[j].x * modelMatrix.m[0] + lep[j].y * modelMatrix.m[1] + modelMatrix.m[3];
		wep[j].y = lep[j].x * modelMatrix.m[4] + lep[j].y * modelMatrix.m[5] + modelMatrix.m[7];
	}
	b2Vec2 vecs[] = {
		b2Vec2(wep[0].x / PTM_RATIO, wep[0].y / PTM_RATIO),
		b2Vec2(wep[1].x / PTM_RATIO, wep[1].y / PTM_RATIO),
		b2Vec2(wep[2].x / PTM_RATIO, wep[2].y / PTM_RATIO),
		b2Vec2(wep[3].x / PTM_RATIO, wep[3].y / PTM_RATIO) };

	rectShape.Set(vecs, 4);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &rectShape;
	fixtureDef.restitution = 0.5f;
	fixtureDef.density = 0.1f;
	fixtureDef.friction = 0.15f;
	PlayerBody->CreateFixture(&fixtureDef);
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

void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	Director* director = Director::getInstance();

	GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	_b2World->DrawDebugData();
	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}