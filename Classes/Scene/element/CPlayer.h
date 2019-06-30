#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

class CPlayer : public cocos2d::Node
{
private:
	Point pt;
	Node *_Player;
	ActionTimeline *_PlayerAni;
    JumpTo *jumpAction;
    
    bool ActFlag = true;
	int JumpTime = 0;

public:
	Sprite *_body;
	CPlayer();
	CPlayer(Color3B, Color3B);
	~CPlayer();

	//bool ChangleCollision = false;
    void RunAct();
    void JumpAct();
    void SlipAct();
    void AttackAct();
    void TensionAct();
    void ActionEnd();

	Point GetPos();
	Size GetSize();
	Vec2 GetScale();
	// implement the "static create()" method manually
	CREATE_FUNC(CPlayer);
};