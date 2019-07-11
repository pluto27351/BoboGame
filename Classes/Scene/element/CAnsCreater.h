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
	int answer[3] = {0,0,0}; //帶．母．子
public:
	void queCreater(int uni, int queNo, int number);
	void Input_que(cocos2d::Node &Q, int number);
	void Input_ans(cocos2d::Node &Q, int number);

    void queCreater(int uni, int queNo, int number,int c,int b);
    void Input_que(cocos2d::Node &Q, int number,int c,int b);
    void Input_ans(int number,int c,int b);
    
	char *Numerator(const char *c, const char *number);

	bool CheckAnswer(Vec3);

	cocos2d::Node * Set_CAnsCreater(const char *numerator, const char *denominator, const char *front); //生成分數
	cocos2d::Node * CAnsCreaterOperation(int n);

};
