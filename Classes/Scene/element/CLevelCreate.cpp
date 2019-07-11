#include "CLevelCreate.h"

USING_NS_CC;

CLevelCreate::~CLevelCreate() {}
CLevelCreate::CLevelCreate(b2World* _b2W, int L) {
	//¹Ï¤ù
	char level[9];
	char name[4];
	for (int i = 0; i<7; i++) {
        int num = rand() % 3;
        sprintf(level, "Level_%d", 0);
        num = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName(level)->getTag();
        sprintf(name, "%d", num);
		_DownGroundCollision[i] = new CObstacle(_b2W, CSLoader::createNode("Obstacle.csb")->getChildByName(level)->getChildByName(name));
        if(i==0)
            _DownGroundCollision[i]->Setpos(210, 0);
        else
            _DownGroundCollision[i]->MoveBy(_DownGroundCollision[i-1]->Getpos().x - _DownGroundCollision[i]->Getpos().x + _DownGroundCollision[i-1]->_fWidth/2 +_DownGroundCollision[i]->_fWidth/2, 0);
		this->addChild(_DownGroundCollision[i]);
	}
}
void CLevelCreate::dostep() {
	for (int i = 0; i<7; i++) {
        if (_DownGroundCollision[i]->Getpos().x < -(_DownGroundCollision[i]->_fWidth)/2) {
            if (i == 0) {
                _DownGroundCollision[i]->MoveBy(_DownGroundCollision[5]->Getpos().x - _DownGroundCollision[i]->Getpos().x + _DownGroundCollision[5]->_fWidth/2 +_DownGroundCollision[i]->_fWidth/2, 0);
            }
            else {
                _DownGroundCollision[i]->MoveBy(_DownGroundCollision[i-1]->Getpos().x - _DownGroundCollision[i]->Getpos().x + _DownGroundCollision[i-1]->_fWidth/2 +_DownGroundCollision[i]->_fWidth/2, 0);
            }
        }
		_DownGroundCollision[i]->MoveBy(-10, 0);
	}
}
