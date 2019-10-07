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
    Sprite* board;
    int num = 0; //±Ð¾Ç¥Î
    int Distance = 0;
	int _iLevel = 0;
	int _iLevelFrequency = 5;
    bool UpFlag = false;
    bool DieFlag = false;
	bool TeachCreateFlag[3] = { false }; //0:slip 1:jump 2:attack
    bool BoardFlag = false;
    float _fPlayerPosX = 0.0f;

    char kind[5] = "down"; //down or up
	char level[9];
	char name[4];
public:
	CLevelCreate();
	CLevelCreate(b2World* _b2W, float PlayerPosX);
	~CLevelCreate();

    float f_tDistance = 0.0f;
    int TeachFlag = 3; //0:right 1:left 2:normal 3:no

	void SetObstacle(int i);
	void dostep(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(CLevelCreate);
};
