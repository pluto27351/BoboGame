#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "CObstacle.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;
using namespace CocosDenshion;

class CLevelCreate : public cocos2d::Node
{
private:
	CObstacle *_DownGroundCollision[6];
	float time = 0;
	b2World* _b2World;
public:
	CLevelCreate();
	CLevelCreate(b2World* _b2W, int level);
	~CLevelCreate();
	void dostep();

	// implement the "static create()" method manually
	CREATE_FUNC(CLevelCreate);
};
