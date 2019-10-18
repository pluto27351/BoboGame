#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"

#define WIDTH 2731.0f
#define SCENEWIDTH (Director::getInstance()->getOpenGLView()->getFrameSize().width/Director::getInstance()->getOpenGLView()->getScaleX())
#define BOX2D_DEBUG 0
#define SLIP_TIME 0.7f
#define MG_SPEED 2

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

GameScene::~GameScene() {}
void GameScene::ChangeScene()
{
    this->unscheduleAllCallbacks();
    this->removeAllChildren();
    if(_Player != NULL)delete _Player;
    if(_Level != NULL)delete _Level;
    if(_b2World != NULL)delete _b2World;
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
    CCDirector::sharedDirector()->replaceScene(MenuScene::createScene());
    SimpleAudioEngine::getInstance()->unloadEffect("game_broken.mp3");
    SimpleAudioEngine::getInstance()->unloadEffect("game_bg");
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
    //firebase
    app = firebase::App::Create(::firebase::AppOptions());
    database = firebase::database::Database::GetInstance(app);
    dbref = database->GetReference();
    data = dbref.GetReference().GetValue();
    
	_rootNode = CSLoader::createNode("PlayScene.csb");
	addChild(_rootNode);
    //B2World
	_b2World = nullptr;
	b2Vec2 Gravity = b2Vec2(0.0f, -120);	//重力方向
	bool AllowSleep = true;					//允許睡著
	_b2World = new b2World(Gravity);		//創建世界
	_b2World->SetAllowSleeping(AllowSleep);	//設定物件允許睡著
    
    //GameOver Scene
    //playername
    _InputName  = (cocos2d::ui::TextField*)_rootNode->getChildByName("Gameover")->getChildByName("PlayerName")->getChildByName("Input");
    _InputName ->setMaxLengthEnabled(true);
    _InputName ->addEventListener(CC_CALLBACK_2(GameScene::textFieldEvent, this));
    _Namelight = (cocos2d::Sprite*)_rootNode->getChildByName("Gameover")->getChildByName("PlayerName")->getChildByName("name_light");
    _NameAni = (ActionTimeline *)CSLoader::createTimeline("PlayScene.csb");
    _NameAni->gotoFrameAndPlay(0, 30, true);
    _NameAni->setTimeSpeed(0.8f);
    _Namelight->runAction(_NameAni);
    sprintf(_cPlayerName, "Name");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Img/game_teach.plist");
    auto btn = _rootNode->getChildByName("Gameover")->getChildByName("PlayerName");
    _NameBtn.setButtonInfo("teach_btn_giveup.png","teach_btn_giveup.png",*this, btn->getPosition()+Point(449,-1),1);
    _NameBtn.setVisible(false);
    _NameBtn.setEnabled(false);
    //GameScene
    //Music
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game_bg.mp3"); // 預先載入音效檔
    SimpleAudioEngine::getInstance()->playBackgroundMusic("game_bg.mp3",1);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.02f);//音量0.02倍
    //score
    _Score = (cocos2d::ui::Text *)_rootNode->getChildByName("Game")->getChildByName("distance");
	//中景
    _MidGround[0] = (cocos2d::Sprite *)_rootNode->getChildByName("mg_0");
    _MidGround[1] = (cocos2d::Sprite *)_rootNode->getChildByName("mg_1");
    //教學提示
    _Teach = CSLoader::createNode("Ani/TeachAni.csb");
    this->addChild(_Teach, 2);
    _Teach->getChildByName("prompt_bg")->setScaleX(SCENEWIDTH/WIDTH); //提示範圍
    _TeachAni = (ActionTimeline *)CSLoader::createTimeline("Ani/TeachAni.csb");
    _Teach->runAction(_TeachAni);
    _TeachAni->setTimeSpeed(0.1f);
    _Teach->setVisible(false);
    _Teach->getChildByName("prompt")->setGlobalZOrder(2);
    
	CreatePlayer();// 放入玩家
	CreateGround();// 地板碰撞
    CreateLevel();// 關卡生成
    
    _b2World->SetContactListener(&_contactListener);
	if (BOX2D_DEBUG) {
        _rootNode->getChildByName("bg")->setVisible(false);
        _MidGround[0]->setVisible(false);
        _MidGround[1]->setVisible(false);
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
    if(_bPlayFlag == true) Play(dt);
    else if(_rootNode->getChildByName("Gameover")->isVisible() == false){
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
        _Player->AniPause();
        _Level->Teach = 3;
        _rootNode->getChildByName("Gameover")->setVisible(true);
        Text* Score = (cocos2d::ui::Text*)_rootNode->getChildByName("Gameover")->getChildByName("Score");
        Score->setString(_Score->getString());
        _NameBtn.setVisible(true);
        _NameBtn.setEnabled(true);
        //firebase
        data = dbref.GetReference().GetValue(); //獲取資料
    }
}
void GameScene::Play(float dt) {
    //教學
    if(_Level->Teach < 2){
        if(_Level->Teach == 0){
            if(_TeachAni->getCurrentFrame() > 3)
                _TeachAni->gotoFrameAndPlay(0,3,true);
            _Teach->setPosition((SCENEWIDTH*3/4 + (WIDTH-SCENEWIDTH)/2),768);
        }
        else{
            if(_TeachAni->getCurrentFrame() <= 3)
                _TeachAni->gotoFrameAndPlay(4,7,true);
            _Teach->setPosition(SCENEWIDTH/4 + (WIDTH-SCENEWIDTH)/2,768);
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
        if (_MidGround[0]->getPosition().x < (-1575.52f))
            _MidGround[0]->setPosition(_MidGround[1]->getPosition().x + 2954.0f, 768);
        _MidGround[0]->setPosition(_MidGround[0]->getPosition().x - MG_SPEED, 768);
        if (_MidGround[1]->getPosition().x < (-1575.52f))
            _MidGround[1]->setPosition(_MidGround[0]->getPosition().x + 2954.0f, 768);
        _MidGround[1]->setPosition(_MidGround[1]->getPosition().x - MG_SPEED, 768);
        //角色
        _fSlipTime += dt;
        _Player->dostep();
        if (_contactListener.RunFlag == true && _fSlipTime > SLIP_TIME){
            _Player->RunAct();
            _contactListener.AttackFlag = false;
        }
        if (_Player->GetBody()->GetLinearVelocity().y < -8){
            _contactListener.RunFlag = false;
        }
        //關卡
        _Level->dostep(dt);
        char d[30];
        float _fd = _Level->Score/10;
        sprintf(d, "%6.1f m", _fd);
        _Score->setString(d);
        if (_contactListener.gameover == true)_bPlayFlag = false;
    }
}
void GameScene::CreatePlayer() {
	// 放入玩家
    _Player = new CPlayer(_b2World, Vec2(SCENEWIDTH/4 + (WIDTH-SCENEWIDTH)/2,600));// 1/4scene
    Node * _body = (cocos2d::Node *)_rootNode->getChildByName("Game");
	_body->addChild(_Player, 2);
    _contactListener.setCollisionTargetPlayer(*(_Player->GetSprite()));
}
void GameScene::CreateGround() {
	Sprite * _body = (cocos2d::Sprite *)_rootNode->getChildByName("Game")->getChildByName("ground");
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
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.0f;
	Body->CreateFixture(&fixtureDef);
}
void GameScene::CreateLevel(){
    _Level = new CLevelCreate(_b2World, _Player->GetPos().x);
    Node * _body = (cocos2d::Node *)_rootNode->getChildByName("Game");
    _body->addChild(_Level,0);
}

bool GameScene::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)//觸碰開始事件
{
	Point touchLoc = pTouch->getLocation();
	if (_bPlayFlag == true) {
        switch(_Level->Teach){
            case 0:
                if (touchLoc.x > WIDTH/2 && _contactListener.RunFlag == true) {
                    _Teach->setVisible(false);
                    _Level->Teach = 3;
                    _Player->AniResume();
                    _Player->JumpAct();
                    _contactListener.RunFlag = false;
                }
                break;
            case 1:
                if(touchLoc.x < WIDTH/2 ){
                    _Teach->setVisible(false);
                    _Player->AniResume();
                    if (_contactListener.RunFlag == true && _fSlipTime > SLIP_TIME) {
                        _Level->Teach = 3;
                        _fSlipTime = 0;
                        _Player->SlipAct();
                    }
                    else{
                        _Player->AttackAct();
                        if(_Player->GetPos().y>=770)
                            _contactListener.AttackFlag = true;
                        _Level->Teach = 2;
                        //教學結束
                        UserDefault::getInstance()->setBoolForKey("TEACH_FLAG", 1);
                        UserDefault::getInstance()->flush();
                    }
                }
                break;
            case 2:
                if (touchLoc.x < WIDTH/2 && _fSlipTime > SLIP_TIME) {
                    if (_contactListener.RunFlag == true) {
                        _fSlipTime = 0;
                        _Player->SlipAct();
                    }
                    else{                                                  
                        _Player->AttackAct();
                        if(_Player->GetPos().y>=770)
                            _contactListener.AttackFlag = true;
                    }
                }
                else if (touchLoc.x > WIDTH/2 && _contactListener.RunFlag == true) {
                    _Player->JumpAct();
                    _contactListener.RunFlag = false;
                }
                break;
        }
    }
    _NameBtn.touchesBegin(touchLoc);
	return true;
}
void  GameScene::onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰移動事件
{
    Point touchLoc = pTouch->getLocation();
    _NameBtn.touchesMoved(touchLoc);
}
void  GameScene::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent) //觸碰結束事件 
{
    Point touchLoc = pTouch->getLocation();
    if(_NameBtn.touchesEnded(touchLoc)) {
        _NameBtn.setEnabled(false);
        CCLOG("2");
        if(data.status() != firebase::kFutureStatusPending){
            CCLOG("3");
            if(data.status() != firebase::kFutureStatusComplete){
                CCLOG("ERROR : GetValue() return an invalid result");
            }
            else if(data.error() != firebase::database::kErrorNone){
                CCLOG("ERRPR : GetValue return error %d : %s",data.error(),data.error_message());
            }
            else {
                // 主要區！！！
                const firebase::database::DataSnapshot *snapshot =  data.result();
                auto children = snapshot->children();
                for(int i=0;i<5;i++){
                    auto child_data = children[i].children();
                    auto c_name  = child_data[0].key_string().c_str();
                    auto c_score = child_data[0].value().int64_value();
                    int sc = (int)_Level->Score;  //_dis是距離  用int存->3.5用35存入!!!!!
                    if(sc >= c_score){   //比大小 存資料
                        for(int j=4;j >i;j--){                 //資料往下移
                            children[j].GetReference().RemoveValue();
                            child_data = children[j-1].children();
                            c_name  = child_data[0].key_string().c_str();
                            c_score = child_data[0].value().int64_value();
                            children[j].GetReference().Child(c_name).SetValue(c_score);
                        }
                        children[i].GetReference().RemoveValue();
                        children[i].GetReference().Child(_cPlayerName).SetValue(sc);  //new是使用者名字 sc是距離
                        i=100;                                  //跳離迴圈
                        data = dbref.GetReference().GetValue(); //獲取新連結(好像也可以不用)
                    }
                }
            }
        }
        ChangeScene();
        return;
    }
}

void GameScene::textFieldEvent(Ref*pSender, cocos2d::ui::TextField::EventType type){
    Node* PlayerNameImg = (cocos2d::Node*)_rootNode->getChildByName("Gameover")->getChildByName("PlayerName");
    switch(type){
        case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME: //輸入
            _InputName = dynamic_cast<cocos2d::ui::TextField*>(pSender);
            _InputName->setColor(Color3B(70,70,87));
            PlayerNameImg->setPosition(PlayerNameImg->getPosition().x,1000);
            _NameAni->gotoFrameAndPause(0);
            _NameBtn.setPosition(PlayerNameImg->getPosition() + Point(449,-1));
            break;
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME: //結束
            PlayerNameImg->setPosition(PlayerNameImg->getPosition().x,568);
            _NameBtn.setPosition(PlayerNameImg->getPosition() + Point(449,-1));
            break;
        case cocos2d::ui::TextField::EventType::INSERT_TEXT: //增加
            _InputName = dynamic_cast<cocos2d::ui::TextField*>(pSender);
            break;
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD: //減少
            _InputName = dynamic_cast<cocos2d::ui::TextField*>(pSender);
            break;
    }
    //名字能不能用
    sprintf(_cPlayerName, "%s", _InputName->getString().c_str());
    if(strcmp(_cPlayerName,"") == 0) sprintf(_cPlayerName, "Name");
    for(int i = 0; i < 25 && _cPlayerName[i] != NULL; i++){
        if(((int)_cPlayerName[i] >= 48 && (int)_cPlayerName[i] <= 57)
           || ((int)_cPlayerName[i] >= 65 && (int)_cPlayerName[i] <= 90)
           || ((int)_cPlayerName[i] >= 97 && (int)_cPlayerName[i] <= 122))_NameBtn.setEnabled(true); //數字.英文
        else{
            _NameBtn.setEnabled(false);
            i = 30;
        }
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
        else if(BodyB->GetFixtureList()->GetDensity() <= 1.0f){
            if(BodyA->GetLinearVelocity().y <= 0)
                RunFlag = true;
            else if(BodyB->GetFixtureList()->GetDensity() == 0.0f && BodyA->GetLinearVelocity().x != 0) //被上方地形推走
                BodyA->SetLinearVelocity(b2Vec2(0,0));
        }
        else if(BodyB->GetFixtureList()->GetDensity() == 10000.0f){
            if(AttackFlag == true){
                if(!BodyB->GetFixtureList()->IsSensor() || ((Sprite*)BodyB->GetUserData())->isVisible()){
                    ((Sprite*)BodyB->GetUserData())->setVisible(false);
                    BodyB->GetFixtureList()->SetSensor(true);
                    SimpleAudioEngine::getInstance()->preloadEffect("game_broken.mp3");
                    SimpleAudioEngine::getInstance()->playEffect("game_broken.mp3",0,1,0,0.1f);
                }
            }
            else if(BodyA->GetLinearVelocity().y <= 0)
                RunFlag = true;
        }
    }
}
void CContactListener::EndContact(b2Contact* contact){
    b2Body* BodyA = contact->GetFixtureA()->GetBody();
    b2Body* BodyB = contact->GetFixtureB()->GetBody();
}
