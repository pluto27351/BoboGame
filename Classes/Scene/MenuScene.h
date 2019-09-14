#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "element/CButton.h"

#include "firebase/app.h"
#include "firebase/database.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace ui;
using namespace CocosDenshion;

class MenuScene : public cocos2d::Layer
{
private:
	Node *rootNode;
	CButton _chapBtn[5],_gameBtn,_boardBtn;
	Text *_scoreText;
    LoadingBar *_chapLoad[5],*_lightbar[5];
    Sprite * _chapPic[5];
    
	int _iscale;
    bool _bchangeScene = false;
    int _sceneNum,_uni;
    float _totalTime;
	void doStep(float);
public:
	~MenuScene();
	bool init();
	void ChangeScene(int,int chap = 0);
    void ShineLightBar();
	static cocos2d::Scene* createScene();

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

	// implement the "static create()" method manually
	CREATE_FUNC(MenuScene);
};

