#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"

#define PTM_RATIO 32.0f
#define BOX2D_DEBUG 1
#define SLIP_TIME 0.7f
#define MG_SPEED 2

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

GameScene::~GameScene() {

    
}

void GameScene::ChangeScene()
{
    this->unscheduleAllCallbacks();
    this->removeAllChildren();
    
    if(_Player != NULL)delete _Player;
    if(_Level != NULL)delete _Level;
    if(_b2World != NULL)delete _b2World;
    
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    CCDirector::sharedDirector()->replaceScene(MenuScene::createScene());
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

    Sprite *bg = (cocos2d::Sprite *)rootNode->getChildByName("bg");
    bg->setGlobalZOrder(-2);
    
    //playername
    PlayerName = (cocos2d::ui::TextField*)rootNode->getChildByName("PlayerName");
    PlayerName->setMaxLengthEnabled(true);
    PlayerName->addEventListener(CC_CALLBACK_2(GameScene::textFieldEvent, this));
    //score
    distance = (cocos2d::ui::Text *)rootNode->getChildByName("distance");
	//中景
    midground[0] = (cocos2d::Sprite *)rootNode->getChildByName("mg_0");
    midground[1] = (cocos2d::Sprite *)rootNode->getChildByName("mg_1");
    midground[0]->setGlobalZOrder(-2);
    midground[1]->setGlobalZOrder(-2);
    //教學提示
    _Teach = CSLoader::createNode("Ani/TeachAni.csb");
    this->addChild(_Teach, 2);
    TeachAni = (ActionTimeline *)CSLoader::createTimeline("Ani/TeachAni.csb");
    _Teach->runAction(TeachAni);
    TeachAni->setTimeSpeed(0.1f);
    _Teach->setVisible(false);
	_Teach->getChildByName("prompt")->setGlobalZOrder(6);
    
	CreatePlayer();// 放入玩家
	CreateGround();// 地板碰撞
    CreateLevel();// 關卡生成
    
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
	_fGmaeTime += dt;
    if(PlayFlag == false){
        if (_fGmaeTime >= 4.5){
            PlayFlag = true;
        }
    }
	Play(dt);
}
void GameScene::Play(float dt) {
    //教學
    if(_Level->TeachFlag < 2){
        if(_Level->TeachFlag == 0){
            if(TeachAni->getCurrentFrame() > 3)
                TeachAni->gotoFrameAndPlay(0,3,true);
            _Teach->setPosition(1536,768);
        }
        else{
            if(TeachAni->getCurrentFrame() <= 3)
                TeachAni->gotoFrameAndPlay(4,7,true);
            _Teach->setPosition(512,768);
        }
        _Teach->setVisible(true);
        _Player->AniPause();
    }
    else{
        //Box2D
        int velocityIterations = 8; // 速度迭代次數
        int positionIterations = 1; // 位置迭代次數，迭代次數一般設定為8~10 越高越真實但效率越差
        _b2World->Step(dt, velocityIterations, positionIterations);
        //草叢移動
        if (midground[0]->getPosition().x < (-1575.52f))
            midground[0]->setPosition(midground[1]->getPosition().x + 2599.52f, 768);
        midground[0]->setPosition(midground[0]->getPosition().x - MG_SPEED, 768);
        if (midground[1]->getPosition().x < (-1575.52f))
            midground[1]->setPosition(midground[0]->getPosition().x + 2599.52f, 768);
        midground[1]->setPosition(midground[1]->getPosition().x - MG_SPEED, 768);
        //角色
        _fSlipTime += dt;
        _Player->dostep();
        if (_contactListener.AttackFlag == true && AttackFlag == true && _Player->_Player->getPosition().y >= 770){
            _contactListener.Breaksprite->setVisible(false);
            _contactListener.BreakBody->GetFixtureList()->SetSensor(true);
        }
        if (_contactListener.RunFlag == true && _fSlipTime > SLIP_TIME){
            _Player->RunAct();
            AttackFlag = false;
            _contactListener.AttackFlag = false;
        }
        if (_Player->PlayerBody->GetLinearVelocity().y < -8){
            _contactListener.RunFlag = false;
        }
        //關卡
        _Level->dostep(dt);
        char d[30];
        float _fd = _Level->f_tDistance/10;
        sprintf(d, "%6.1f m", _fd);
        distance->setString(d);
        if (_contactListener.gameover == true) {
            //ChangeScene();
        }
    }
}
void GameScene::CreatePlayer() {
	// 放入玩家
	_Player = new CPlayer(_b2World, Vec2(450,600));
	this->addChild(_Player, 2);
    _contactListener.setCollisionTargetPlayer(*(_Player->_body));
    _Player->RunAct();
}
void GameScene::CreateGround() {
	Sprite * _body = (cocos2d::Sprite *)rootNode->getChildByName("ground");
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.userData = _body;
	b2Body *Body;
	Body = _b2World->CreateBody(&bodyDef);
	Point loc = _body->getPosition();
	Size ts = _body->getContentSize();
	b2PolygonShape rectShape;
	float scaleX = _body->getScaleX();    // §Ù•≠™∫Ωu¨qπœ•‹∞≤≥]≥£•u¶≥πÔ X ∂b©Ò§j
	float scaleY = _body->getScaleY();    // §Ù•≠™∫Ωu¨qπœ•‹∞≤≥]≥£•u¶≥πÔ X ∂b©Ò§j

	Point lep[4], wep[4];
	lep[0].x = (ts.width - 80) / 2.0f;  lep[0].y = (ts.height) / 2.0f;
	lep[1].x = -(ts.width - 80) / 2.0f; lep[1].y = (ts.height) / 2.0f;
	lep[2].x = -(ts.width - 80) / 2.0f; lep[2].y = -(ts.height) / 2.0f;
	lep[3].x = (ts.width - 80) / 2.0f;  lep[3].y = -(ts.height) / 2.0f;

	cocos2d::Mat4 modelMatrix, rotMatrix;
	modelMatrix.m[0] = scaleX;  // •˝≥]©w X ∂b™∫¡Y©Ò
	modelMatrix.m[5] = scaleY;  // •˝≥]©w Y ∂b™∫¡Y©Ò
	cocos2d::Mat4::createRotationZ(0 * M_PI / 180.0f, &rotMatrix);
	modelMatrix.multiply(rotMatrix);
	modelMatrix.m[3] = /*PntLoc.x + */loc.x; //≥]©w Translation°A¶€§v™∫•[§W§˜øÀ™∫
	modelMatrix.m[7] = /*PntLoc.y + */loc.y; //≥]©w Translation°A¶€§v™∫•[§W§˜øÀ™∫
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
	fixtureDef.restitution = 0.0f;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;
	Body->CreateFixture(&fixtureDef);
}
void GameScene::CreateLevel(){
    _Level = new CLevelCreate(_b2World);
    this->addChild(_Level,2);
}

bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
    Rect rect = Director::getInstance()->getOpenGLView()->getVisibleRect();
	if (PlayFlag == true) {
        switch(_Level->TeachFlag){
            case 0:
                if (touchLoc.x > rect.getMaxX() / 2 && _contactListener.RunFlag == true) {
                    _Teach->setVisible(false);
                    _Level->TeachFlag = 3;
                    _Player->AniResume();
                    _Player->JumpAct();
                    _contactListener.RunFlag = false;
                }
                break;
            case 1:
                if(touchLoc.x < rect.getMaxX() / 2 ){
                    _Teach->setVisible(false);
                    _Player->AniResume();
                    if (_contactListener.RunFlag == true && _fSlipTime > SLIP_TIME) {
                        _Level->TeachFlag = 3;
                        _fSlipTime = 0;
                        _Player->SlipAct();
                    }
                    else{
                        _Player->AttackAct();
                        _Level->TeachFlag = 2;
                        AttackFlag = true;
                        
                        //教學結束
                        UserDefault::getInstance()->setBoolForKey("TEACH_FLAG", 1);
                        UserDefault::getInstance()->flush();
                    }
                }
                break;
            case 2:
                if (touchLoc.x < rect.getMaxX() / 2 && _fSlipTime > SLIP_TIME) {
                    if (_contactListener.RunFlag == true) {
                        _fSlipTime = 0;
                        _Player->SlipAct();
                    }
                    else{                                                  
                        _Player->AttackAct();
                        AttackFlag = true;
                    }
                }
                else if (touchLoc.x > rect.getMaxX() / 2 && _contactListener.RunFlag == true) {
                    _Player->JumpAct();
                    _contactListener.RunFlag = false;
                }
                break;
        }
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

void GameScene::textFieldEvent(Ref*pSender, cocos2d::ui::TextField::EventType type){
    switch(type){
        case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME: //輸入
            PlayerName = dynamic_cast<cocos2d::ui::TextField*>(pSender);
            break;
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME: //結束
            PlayerName = dynamic_cast<cocos2d::ui::TextField*>(pSender);
            PlayerName->setColor(Color3B(70,70,87));
            break;
        case cocos2d::ui::TextField::EventType::INSERT_TEXT: //增加
            PlayerName = dynamic_cast<cocos2d::ui::TextField*>(pSender);
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD: //減少
            PlayerName = dynamic_cast<cocos2d::ui::TextField*>(pSender);
            break;
    }
}
void GameScene::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    Director* director = Director::getInstance();
    GL::enableVertexAttribs(cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION);
    director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    _b2World->DrawDebugData();
    director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

CContactListener::CContactListener(){}
void CContactListener::setCollisionTargetPlayer(cocos2d::Sprite &targetSprite){
    _Playersprite = &targetSprite;
}
void CContactListener::BeginContact(b2Contact* contact){
    b2Body* BodyA = contact->GetFixtureA()->GetBody();
    b2Body* BodyB = contact->GetFixtureB()->GetBody();
    if(BodyA->GetUserData() == _Playersprite){
        if (BodyB->GetFixtureList()->GetDensity() == 5000.0f) {
            gameover = true;
        }
        else if(BodyB->GetFixtureList()->GetDensity() == 0.0f){
            if(BodyA->GetLinearVelocity().y <= 0)
                RunFlag = true;
        }
        else if(BodyB->GetFixtureList()->GetDensity() == 10000.0f){
            AttackFlag = true;
            if(BodyB->GetFixtureList()->IsSensor() == true)
                Breaksprite = (Sprite*)BodyB->GetUserData();
            BreakBody = BodyB;
        }
    }
}
void CContactListener::EndContact(b2Contact* contact){
    b2Body* BodyA = contact->GetFixtureA()->GetBody();
    b2Body* BodyB = contact->GetFixtureB()->GetBody();
}
