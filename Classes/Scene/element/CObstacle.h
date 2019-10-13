#pragma once

#include "cocos2d.h"
//#include "ui/CocosGUI.h"
//#include "ui/UIWidget.h"
//#include "SimpleAudioEngine.h"
//#include "cocostudio/CocoStudio.h"
#include "Box2D/Box2D.h"
#define BO_SPEED 9.0f;

USING_NS_CC;

//using namespace cocostudio::timeline;
using namespace ui;
//using namespace CocosDenshion;

class CObstacle : public cocos2d::Node
{
private:
    Sprite * _body;
    Sprite* light;
    int num = 0;
	int BoSpeed = 0;
    float f_BoSpeed = BO_SPEED;
    //b2world
    b2World* _b2World;
    std::vector<b2Body*> ObstacleBody;
public:
    CObstacle();
	CObstacle(b2World* _b2W, Node* _ob);
    ~CObstacle();
    
    Node* _Obstacle;
    float _fWidth = 0;
	bool teach = false;
    bool start = false;
    bool UpFlag = false;
    bool DieFlag = false;
    bool AttackFlag = false;
    
    void ChangeObstacle(Node* _ob);
    void CreateObstacle();
    void CreateCollision();
    void LightVisible(bool v);
    void SetPos(float x, float y);
    void Move(float x, float y);
	Point Getpos();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CObstacle);
};
