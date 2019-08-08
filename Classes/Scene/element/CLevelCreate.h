#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "CObstacle.h"

#define OB_NUM 7

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

class CLevelCreate : public cocos2d::Node
{
private:
	CObstacle *_DownGroundCollision[OB_NUM];
	float Leveltime = 0;
	b2World* _b2World;
    int num = 0;
    bool UpFlag = false;
    bool DieFlag = false;

    char kind[5] = "down"; //down or up
	char level[9];
	char name[4];
public:
	CLevelCreate();
	CLevelCreate(b2World* _b2W, int level);
	~CLevelCreate();

    bool TeachCreateFlag[3] = {false}; //0:jump 1:slip 2:attack
    int TeachFlag = 3; //0:right 1:left 2:normal 3:no

	void SetObstacle(int i);
	void dostep(float dt);
	// implement the "static create()" method manually
	CREATE_FUNC(CLevelCreate);
};
