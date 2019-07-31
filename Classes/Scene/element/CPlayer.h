#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"

#include "Box2D/Box2D.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

class CPlayer : public cocos2d::Node
{
private:
    Point pt;
	Node* _Player;
	ActionTimeline* _PlayerAni;
    float time = 0;
    
    //b2world
    b2Body *PlayerBody;
    b2World* _b2World;
    
    bool ActFlag = true;
public:
    CPlayer();
	CPlayer(b2World* _b2W, Vec2 pos);
	~CPlayer();

    Sprite * _body;
    
    void CreateCollision();
    void dostep();
    void RunAct();
    void JumpAct();
    void SlipAct();
    void AttackAct();
    void TensionAct();
    
    //void ActionEnd();

	// implement the "static create()" method manually
	CREATE_FUNC(CPlayer);
};
