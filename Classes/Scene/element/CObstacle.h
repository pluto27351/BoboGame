#pragma once

#include "cocos2d.h"
//#include "ui/CocosGUI.h"
//#include "ui/UIWidget.h"
//#include "SimpleAudioEngine.h"
//#include "cocostudio/CocoStudio.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

//using namespace cocostudio::timeline;
using namespace ui;
//using namespace CocosDenshion;

class CObstacle : public cocos2d::Node
{
private:
    Sprite * _body;
    int num = 0;
	bool BoSpeed = true;
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
    bool UpFlag = false;
    bool DieFlag = false;
    
    void ChangeObstacle(Node* _ob);
    void CreateObstacle();
    void CreateCollision();
    void SetPos(float x, float y);
    void Move(float x, float y);
	Point Getpos();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CObstacle);
};
