#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "element/CButton.h"
#include "element/CPlayer.h"
#include "element/CLevelCreate.h"

#include "Box2D/Box2D.h"
#include "element/GLES-Render.h"

#include "firebase/app.h"
#include "firebase/database.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace ui;
using namespace CocosDenshion;

class CContactListener : public b2ContactListener
{
public:
	bool gameover = false;
    bool RunFlag = true;
    bool AttackFlag = false;
    cocos2d::Sprite * _Playersprite;
    CContactListener();

    virtual void BeginContact(b2Contact* contact);
    virtual void EndContact(b2Contact* contact);
    void setCollisionTargetPlayer(cocos2d::Sprite &targetSprite);
};

class GameScene : public cocos2d::Layer
{
private:
    CContactListener _contactListener;
    CPlayer *_Player;
    CLevelCreate *_Level;
    CButton _NameBtn;
	Node *_rootNode;
    Sprite *_MidGround[2];
    Sprite* _Namelight;
    Text *_Score;
    Node *_Teach;
    ActionTimeline* _TeachAni;
    ActionTimeline* _NameAni;
    ui::TextField* _InputName;
    float _fSlipTime = 1;
	float _fGmaeTime = 0;
    bool _bPlayFlag = true;
    char _cPlayerName[25];
    
    firebase::App* app;
    firebase::database::Database *database;
    firebase::database::DatabaseReference dbref;
    firebase::Future<firebase::database::DataSnapshot> data;
    
	// b2World
	b2World* _b2World;
	GLESDebugDraw* _DebugDraw;
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags);

	void doStep(float);
	void Play(float); //遊戲開始
    void CreatePlayer();
    void CreateGround();
    void CreateLevel();
public:
	~GameScene();
	bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	void ChangeScene();

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件
    
    //textfield
    void textFieldEvent(Ref*pSender, cocos2d::ui::TextField::EventType type);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

