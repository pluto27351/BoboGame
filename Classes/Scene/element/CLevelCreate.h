#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "CObstacle.h"

#define OB_NUM 8

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

class CLevelCreate : public cocos2d::Node
{
private:
	CObstacle *_DownGroundCollision[OB_NUM];
	b2World* _b2World;
    bool _bUpFlag = false;
    bool _bDieFlag = false;
    bool _bAttackFlag = false;
    bool _bBoardFlag = false;
    bool _bTeachCreateFlag[3] = { false }; //0:slip 1:jump 2:attack
    bool _bNextdown = false;
    bool _bSafeFlag = false;
    float _fPlayerPosX = 0.0f;
	int _iLevel = 0;
	int _iLevelFrequency = 6;
    int _iNoDieNum = 0;
    int _iNum = 0;
    int _iDistance = 0;
    char _cKind[5] = "down"; //down or up
    char _cLevel[8] = "Level_0";
	char _cName[3] = "0";
    
public:
	CLevelCreate();
	CLevelCreate(b2World* _b2W, float PlayerPosX);
	~CLevelCreate();

    int Teach = 3; //0:right 1:left 2:normal 3:no
    float Score = 0.0f;

	void SetObstacle(int i);
	void dostep(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(CLevelCreate);
};
