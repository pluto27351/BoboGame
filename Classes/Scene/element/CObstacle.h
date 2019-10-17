#pragma once

#include "cocos2d.h"
//#include "ui/CocosGUI.h"
//#include "ui/UIWidget.h"
//#include "SimpleAudioEngine.h"
//#include "cocostudio/CocoStudio.h"
#include "Box2D/Box2D.h"
#define PTM_RATIO 32.0f
#define PTM_RATIO_DIV(n) n/PTM_RATIO
#define DG_WIDTH 426.0f
USING_NS_CC;

//using namespace cocostudio::timeline;
using namespace ui;
//using namespace CocosDenshion;

class CObstacle : public cocos2d::Node
{
private:
    Sprite * _body;
    Node* _Obstacle;
    bool _bPit = false;
    float _fWidth = 0;
    float _fBigboTime = 0;
    int _iNum = 0;
    //b2world
    b2World* _b2World;
    std::vector<b2Body*> ObstacleBody;
public:
    CObstacle();
	CObstacle(b2World* _b2W, Node* _ob);
    ~CObstacle();
    
	bool TeachFlag = false;
    bool start = false;
    bool UpFlag = false;
    bool DieFlag = false;
    bool AttackFlag = false;
    
    void ChangeObstacle(Node* _ob);
    void CreateObstacle();
    void CreateCollision();
    void SetPos(float x, float y);
    void MoveX(float x, float time);
	Point Getpos();
    Node *GetNode();
    float GetWidth();
    
    // implement the "static create()" method manually
    CREATE_FUNC(CObstacle);
};
