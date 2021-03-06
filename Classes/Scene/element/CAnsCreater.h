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
    char chiness[11][8] = {{"二"},{"三"},{"四"},{"五"},{"六"},{"七"},{"八"},{"九"},{"十"},{"十一"},{"十二"}};
    int _answer[3] = {0,0,0};
    Color3B _textColor3B = Color3B(0,0,0);
    Color4B _textColor4B = Color4B(0,0,0,255);
public:

    //答案生成
    CAnsCreater(int uni, int queNo, int number);
    CAnsCreater(int uni, int queNo, int number,int c,int b=-1);  //第4章變量題．第5章全
    CAnsCreater(int number,int q);               //第3張線段題
    void Input_ans(cocos2d::Node &Q, int number);
    
    //題目生成
    CAnsCreater() {};
    void queCreater(int uni, int queNo, int number);
    void queCreater(int uni, int queNo, int number,int c,int b=-1); //第4章變量題．第5章全
    void queLineCreater(int number,int q);  //第3張線段題
    void Input_que(cocos2d::Node &Q, int number);
    
    char *Numerator(const char *c, const char *number);
    
    bool CheckAnswer(Vec3);
    int getA(){return _answer[1];}
    
    cocos2d::Node * Set_CAnsCreater(const char *numerator, const char *denominator, const char *front);
    cocos2d::Node * CAnsCreaterOperation(int n);
};

