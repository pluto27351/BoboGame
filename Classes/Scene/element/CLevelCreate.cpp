#include "CLevelCreate.h"
#define DG_WIDTH 425.0f

USING_NS_CC;

CLevelCreate::~CLevelCreate() {}
CLevelCreate::CLevelCreate(b2World* _b2W, int L) {
	//¹Ï¤ù
	char level[9];
	char name[4];
	sprintf(level, "Level_%d", L);
	int num = rand() % 2;
	sprintf(name, "%d", num);
	for (int i = 0; i<1; i++) {
		_DownGroundCollision[i] = new CObstacle(_b2W, CSLoader::createNode("Obstacle.csb")->getChildByName("Level_2")->getChildByName("1"),Point(210 + 425 * i, 235));
        //_DownGroundCollision[i] = new CObstacle(_b2W, CSLoader::createNode("Obstacle.csb")->getChildByName("Level_0")->getChildByName("0"),Point(210 + 425 * i, 235));
		this->addChild(_DownGroundCollision[i]);
	}
}
void CLevelCreate::dostep() {
	for (int i = 0; i<6; i++) {
		if (_DownGroundCollision[i]->Getpos().x < -DG_WIDTH) {
			if (i == 0) {
				_DownGroundCollision[i]->Setpos(_DownGroundCollision[i]->Getpos().x + DG_WIDTH, 0);
			}
			else {
				_DownGroundCollision[i]->Setpos(_DownGroundCollision[i]->Getpos().x + DG_WIDTH, 0);
			}
		}
		_DownGroundCollision[i]->Setpos(_DownGroundCollision[i]->Getpos().x - 20, 0);
	}
}
