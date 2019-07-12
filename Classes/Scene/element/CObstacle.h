#pragma once

#include "cocos2d.h"
//#include "ui/CocosGUI.h"
//#include "ui/UIWidget.h"
//#include "SimpleAudioEngine.h"
//#include "cocostudio/CocoStudio.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

//using namespace cocostudio::timeline;
//using namespace ui;
//using namespace CocosDenshion;

class CObstacle : public cocos2d::Node
{
private:
    Node* _Obstacle;
    Sprite * _body;
    int num = 0;
    
    //b2world
    b2World* _b2World;
    std::vector<b2Body*> ObstacleBody;
public:
    CObstacle();
	CObstacle(b2World* _b2W, Node* _ob);
    ~CObstacle();
    
    float _fWidth = 0;
    
    void ChangeObstacle(Node* _ob);
    void CreateCollision();
	void Setpos(float x, float y);
    void MoveBy(float x, float y);
	Point Getpos();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CObstacle);
};
