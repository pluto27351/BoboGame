#pragma once

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "ui/UIWidget.h"
#include "SimpleAudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "element/CButton.h"
#include "element/CDrawPanel.h"
#include "element/CNumberPannel.h"
#include "element/CAnsCreater.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocostudio;
using namespace ui;
using namespace CocosDenshion;

class TeachScene : public cocos2d::Layer
{
private:
	int _chap, _chapNo,_chapNum;
    int _c,_b;
	Node *rootNode;
	Node *_right, *_wrong;
	CButton _homeBtn,_answerBtn,_giveupBtn;
	CDrawPanel *_handDrawing;
	CNumberPannel *_numberArea;
	CAnsCreater *_question;
	void doStep(float);
public:
	~TeachScene();
	bool init();
	void ChangeScene();
	void randomQuestion(int chap);
	void NextQuestion(float);
	static cocos2d::Scene* createScene(int unit);

	cocos2d::EventListenerTouchOneByOne *_listener1;
	bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
	void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
	void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件 

	// implement the "static create()" method manually
	CREATE_FUNC(TeachScene);
};

