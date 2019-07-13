#pragma once

#include "cocos2d.h"
#include "CButton.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

class CNumberPannel:public Layer
{
private:
    CButton _triggerBtn,_number[12];
    Sprite *_touchedPic,*_answerArea[3],*_numberbg;
    SpriteFrame *_answerBg;
    Rect _answerAreaRect[3];
    Vec2 _ansAreaSize;
    bool _bShowNumber;
    bool _bMoveNumber;
    int _nowNumber;
    int _answerNumber[3];
public:
    CNumberPannel(){};
    void setNumberInfo(const cocos2d::Point,int);
    void setAnswerInfo(Node *);
    void setNumberVisual(bool);
    Vec3 getBoxAns();
    void clear();
    void setTouchedPic(int,Point);
    bool touchesBegin(cocos2d::Point);
    bool touchesMoved(cocos2d::Point);
    bool touchesEnded(cocos2d::Point);
    
    CREATE_FUNC(CNumberPannel);
};

/* CNumberPannel_h */
