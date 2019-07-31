#include "CLevelCreate.h"
#include<stdlib.h>

USING_NS_CC;

CLevelCreate::~CLevelCreate() {}
CLevelCreate::CLevelCreate(b2World* _b2W, int L) {
	srand(time(NULL));
	for (int i = 0; i<OB_NUM; i++) {
		_DownGroundCollision[i] = new CObstacle(_b2W, CSLoader::createNode("Obstacle.csb")->getChildByName("down")->getChildByName("Level_1")->getChildByName("2"));
        if(i==0)
            _DownGroundCollision[i]->SetPos(0, 200);
        else
            _DownGroundCollision[i]->SetPos(_DownGroundCollision[i-1]->Getpos().x + _DownGroundCollision[i-1]->_fWidth/2 + _DownGroundCollision[i]->_fWidth/2, 200);
		this->addChild(_DownGroundCollision[i], 1);
	}
}
void CLevelCreate::dostep(float dt) {
	Leveltime+=dt;
	for (int i = 0; i<OB_NUM; i++) {
        if (_DownGroundCollision[i]->Getpos().x < -(_DownGroundCollision[i]->_fWidth/2)) {
			_DownGroundCollision[i]->ChangeObstacle(CSLoader::createNode("Obstacle.csb")->getChildByName("down")->getChildByName(level)->getChildByName(name));
            if (i == 0) 
                _DownGroundCollision[i]->SetPos(_DownGroundCollision[OB_NUM-1]->Getpos().x + _DownGroundCollision[OB_NUM-1]->_fWidth/2 + _DownGroundCollision[i]->_fWidth/2, 200);
            else 
                _DownGroundCollision[i]->SetPos(_DownGroundCollision[i-1]->Getpos().x + _DownGroundCollision[i-1]->_fWidth/2 + _DownGroundCollision[i]->_fWidth/2, 200);
		}
		//_DownGroundCollision[i]->Move(-10, 0);
	}
//    if (Leveltime < 10){
        int num = rand() % 4;
        if (num != 1)num = 0;
        sprintf(level, "Level_%d", 1);
        num = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName("down")->getChildByName(level)->getTag();
        sprintf(name, "%d", 2);
//    }
//    else if (Leveltime < 20) {
//        int num = rand() % 6;
//        if (num != 1 && num != 2)num = 0;
//        sprintf(level, "Level_%d", num);
//        num = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName("down")->getChildByName(level)->getTag();
//        sprintf(name, "%d", num);
//    }
//    else {
//        int num = rand() % 6;
//        if (num != 1 && num != 2)num = 0;
//        sprintf(level, "Level_%d", num);
//        num = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName("down")->getChildByName(level)->getTag();
//        sprintf(name, "%d", num);
//    }
}
