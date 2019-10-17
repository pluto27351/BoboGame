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
    Point _pt;
	ActionTimeline* _PlayerAni;
    Sprite * _PlayerSprite;
    b2Body *_PlayerBody;
    Node* _Player;
    //b2world
    b2World* _b2World;
public:
    CPlayer();
	CPlayer(b2World* _b2W, Vec2 pos);
	~CPlayer();
    
    void CreateCollision();
    void dostep();
    void RunAct();
    void JumpAct();
    void SlipAct();
    void AttackAct();
    void TensionAct();
    void AniPause();
    void AniResume();
    Point GetPos();
    Sprite *GetSprite();
    b2Body *GetBody();
    
    //void ActionEnd();

	// implement the "static create()" method manually
	CREATE_FUNC(CPlayer);
};
