#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "element/CButton.h"


USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace ui;
using namespace CocosDenshion;

class HomeScene : public cocos2d::Layer
{
private:
	int _iTitleTouchTime = 0;
    Sprite *_forntBg;
	CButton _bTitle,_bTree,_bStar;
	Node *_grass,*_star,*_tree;
	ActionTimeline *_grassAction,*_starAction,*_treeAction;
    
    bool _bchangeScene = false,_bstarTouched,_btreeTouched;
    void doStep(float);
public:
	~HomeScene();
	static cocos2d::Scene* createScene();

	bool init();
	void ChangeScene();

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

	// implement the "static create()" method manually
	CREATE_FUNC(HomeScene);
};

