#ifndef CNumberPannel_h
#define CNumberPannel_h

#include "cocos2d.h"
#include "CButton.h"

USING_NS_CC;
class CNumberPannel:public Layer
{
private:
    CButton _triggerBtn,_number[9];
    Sprite *_touchedPic,*_answerArea[3];
    SpriteFrame *_answerBg;
    Rect _answerAreaRect[3];
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
    void setTouchedPic(int,Point);
    bool touchesBegin(cocos2d::Point);
    bool touchesMoved(cocos2d::Point);
    bool touchesEnded(cocos2d::Point);
    
    CREATE_FUNC(CNumberPannel);
};

#endif /* CNumberPannel_h */
