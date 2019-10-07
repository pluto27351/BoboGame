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
    int _curUnit, _curQue,_curNum,_objNum;
    int _c,_b;
    Node *rootNode;
    Node *_right, *_wrong;
    CButton _homeBtn,_answerBtn,_giveupBtn,_triggerBtn;
    CDrawPanel *_handDrawing;
    CNumberPannel *_numberArea;
    CAnsCreater *_question;
    const int *switchdata;
    Node *_wrongAct;
    ActionTimeline *_wrongActTime;
    bool _bchangeScene;
    int _checkAns;
    bool _bNumberOpened = false;
    void doStep(float);
public:
    ~TeachScene();
    bool init();
    void ChangeScene();
    void initQue(int chap);
    void NextQuestion(float);
    
    void setQue(int k);
    void setQue_picline();
    void setQue_multiple();
    void setQue_line();
    void setQue_quantity();
    void resetQue();
    
    static cocos2d::Scene* createScene(int unit);
    
    cocos2d::EventListenerTouchOneByOne *_listener1;
    bool onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰開始事件
    void onTouchMoved(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰移動事件
    void onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent); //觸碰結束事件
    
    // implement the "static create()" method manually
    CREATE_FUNC(TeachScene);
};

