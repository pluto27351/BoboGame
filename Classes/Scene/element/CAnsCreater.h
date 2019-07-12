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
	char chiness[11][8] = {{"�G"},{"�T"},{"�|"},{"��"},{"��"},{"�C"},{"�K"},{"�E"},{"�Q"},{"�Q�@"},{"�Q�G"}};
	int answer[3] = {0,0,0}; //�a�D���D�l
public:
	void queCreater(int uni, int queNo, int number);
	void Input_que(cocos2d::Node &Q, int number);
	void Input_ans(cocos2d::Node &Q, int number);

    void queCreater(int uni, int queNo, int number,int c,int b);
    void Input_que(cocos2d::Node &Q, int number,int c,int b);
    void Input_ans(int number,int c,int b);
    
	char *Numerator(const char *c, const char *number);

	bool CheckAnswer(Vec3);

	cocos2d::Node * Set_CAnsCreater(const char *numerator, const char *denominator, const char *front); //�ͦ�����
	cocos2d::Node * CAnsCreaterOperation(int n);

};
