#include "CLevelCreate.h"
#include<stdlib.h>

USING_NS_CC;

CLevelCreate::~CLevelCreate() {}
CLevelCreate::CLevelCreate(b2World* _b2W, int L) {
	srand(NULL);
	for (int i = 0; i<7; i++) {
		_DownGroundCollision[i] = new CObstacle(_b2W, CSLoader::createNode("Obstacle.csb")->getChildByName("Level_0")->getChildByName("0"));
        if(i==0)
            _DownGroundCollision[i]->Setpos(210, 0);
        else
            _DownGroundCollision[i]->MoveBy(_DownGroundCollision[i-1]->Getpos().x - _DownGroundCollision[i]->Getpos().x + _DownGroundCollision[i-1]->_fWidth/2 +_DownGroundCollision[i]->_fWidth/2, 0);
		this->addChild(_DownGroundCollision[i], 1);
	}
}
void CLevelCreate::dostep(float dt) {
    time+=dt;
	for (int i = 0; i<7; i++) {
        if (_DownGroundCollision[i]->Getpos().x < -(_DownGroundCollision[i]->_fWidth)/2) {
			_DownGroundCollision[i]->ChangeObstacle(CSLoader::createNode("Obstacle.csb")->getChildByName(level)->getChildByName(name));
			_DownGroundCollision[i]->setVisible(false);
            if (i == 0) 
                _DownGroundCollision[i]->MoveBy(_DownGroundCollision[6]->Getpos().x - _DownGroundCollision[i]->Getpos().x + _DownGroundCollision[6]->_fWidth/2 +_DownGroundCollision[i]->_fWidth/2, 0);
            else 
                _DownGroundCollision[i]->MoveBy(_DownGroundCollision[i-1]->Getpos().x - _DownGroundCollision[i]->Getpos().x + _DownGroundCollision[i-1]->_fWidth/2 +_DownGroundCollision[i]->_fWidth/2, 0);
			_DownGroundCollision[i]->setVisible(true);
		}
		_DownGroundCollision[i]->MoveBy(-10, 0);
	}
	if (time < 10){
		int num = rand() % 4;
		if (num != 1)num = 0;
		sprintf(level, "Level_%d", num);
		num = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName(level)->getTag();
		sprintf(name, "%d", num);
	}
	else if (time < 20) {
		int num = rand() % 6;
		if (num != 1 && num != 2)num = 0;
		sprintf(level, "Level_%d", num);
		num = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName(level)->getTag();
		sprintf(name, "%d", num);
	}
	else {
		int num = rand() % 6;
		if (num != 1 && num != 2)num = 0;
		else if (num == 6)num = 2;
		sprintf(level, "Level_%d", num);
		num = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName(level)->getTag();
		sprintf(name, "%d", num);
	}
}
