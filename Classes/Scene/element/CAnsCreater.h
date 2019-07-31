#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

using namespace cocostudio::timeline;
using namespace ui;

class CAnsCreater : public cocos2d::Node
{
private:
    char chiness[11][8] = {{"Ä¨"},{"Äµ"},{"Æ¾"},{"Äì"},{"Äú"},{"Ä¤"},{"Ä¬"},{"Ä¦"},{"Ä²"},{"Ä²Ä¡"},{"Ä²Ä¨"}};
    int answer[3] = {0,0,0};
    Color3B _textColor3B = Color3B(0,0,0);
    Color4B _textColor4B = Color4B(0,0,0,255);
public:
    void queCreater(int uni, int queNo, int number);
    void Input_que(cocos2d::Node &Q, int number);
    void Input_ans(cocos2d::Node &Q, int number);
    void Input_ans2(cocos2d::Node &Q, int number); //í²Õëá¿ÜÉÄ¨ÝýÆî
    
    void queCreater(int uni, int queNo, int number,int c,int b);
    void Input_que(cocos2d::Node &Q, int number,int c,int b);
    void Input_ans(int number,int c,int b);
    
    char *Numerator(const char *c, const char *number);
    
    bool CheckAnswer(Vec3);
    
    cocos2d::Node * Set_CAnsCreater(const char *numerator, const char *denominator, const char *front);
    cocos2d::Node * CAnsCreaterOperation(int n);
};
