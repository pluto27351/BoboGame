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
    bool AttackFlag = true;
    cocos2d::Sprite * _Playersprite;
    cocos2d::Sprite * Breaksprite;
    b2Body *BreakBody;
    CContactListener();
    //¸I¼²¶}©l
    virtual void BeginContact(b2Contact* contact);
    //¸I¼²µ²§ô
    virtual void EndContact(b2Contact* contact);
    void setCollisionTargetPlayer(cocos2d::Sprite &targetSprite);
};

class GameScene : public cocos2d::Layer
{
private:
	Node *rootNode;
    Sprite *midground[2];
    Node *_Teach;
    ActionTimeline* TeachAni;
	CPlayer *_Player;
    CLevelCreate *_Level;
    float _fSlipTime = 1;
	float _fGmaeTime = 0;
    bool AttackFlag = false;
    bool PlayFlag = false;
    
    CContactListener _contactListener;
	// b2World
	b2World* _b2World;
	GLESDebugDraw* _DebugDraw;
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags);

	void doStep(float);
	void Play(float); //遊戲開始
public:
	~GameScene();
	bool init();

	void CreatePlayer();
	void CreateGround();
    void CreateLevel();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();
	void ChangeScene();

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

