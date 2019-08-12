#include "CLevelCreate.h"
#include<stdlib.h>

USING_NS_CC;

CLevelCreate::~CLevelCreate() {}
CLevelCreate::CLevelCreate(b2World* _b2W, int L) {
	srand(time(NULL));
	sprintf(level, "Level_%d", 0);
	sprintf(name, "%d", 0);
	for (int i = 0; i<OB_NUM; i++) {
		_DownGroundCollision[i] = new CObstacle(_b2W, CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getChildByName(name));
        if(i==0)
            _DownGroundCollision[i]->SetPos(0, 200);
        else
            _DownGroundCollision[i]->SetPos(_DownGroundCollision[i-1]->Getpos().x + _DownGroundCollision[i-1]->_fWidth/2 + _DownGroundCollision[i]->_fWidth/2, 200);
		this->addChild(_DownGroundCollision[i], 1);
	}
}
void CLevelCreate::dostep(float dt) {
    Leveltime+=dt;
	for (int i = 0; i < OB_NUM; i++) {
        if(_DownGroundCollision[i]->teach == true){
            if(TeachCreateFlag[1] == true){
               if(_DownGroundCollision[i]->Getpos().x <= 700 ){
                   TeachFlag = 1;
                   _DownGroundCollision[i]->teach = false;
                   TeachCreateFlag[1] = false;
               }
            }
            else if(TeachCreateFlag[0] == true){
                if(_DownGroundCollision[i]->Getpos().x <= 1000){
                    TeachFlag = 0;
                    _DownGroundCollision[i]->teach = false;
                    TeachCreateFlag[0] = false;
                }
            }
            else if(TeachCreateFlag[2] == true){
                if(_DownGroundCollision[i]->Getpos().x <= 1100){
                    TeachFlag = 0;
                    TeachCreateFlag[2] = false;
                }
            }
            else{
                if(_DownGroundCollision[i]->Getpos().x <= 920){
                    TeachFlag = 1;
                    _DownGroundCollision[i]->teach = false;
                }
            }
        }
		if (_DownGroundCollision[i]->Getpos().x < -(_DownGroundCollision[i]->_fWidth / 2)) {
			SetObstacle(i);
			if (i == 0)
				_DownGroundCollision[i]->SetPos(_DownGroundCollision[OB_NUM - 1]->Getpos().x + _DownGroundCollision[OB_NUM - 1]->_fWidth / 2 + _DownGroundCollision[i]->_fWidth / 2, 200);
			else
				_DownGroundCollision[i]->SetPos(_DownGroundCollision[i - 1]->Getpos().x + _DownGroundCollision[i - 1]->_fWidth / 2 + _DownGroundCollision[i]->_fWidth / 2, 200);
		}
		_DownGroundCollision[i]->Move(-10, 0);
	}
}
void CLevelCreate::SetObstacle(int i) {
    //教學
    if(num < 12){
        if(num == 3){
            sprintf(level, "Level_%d", 1);
            sprintf(name, "%d", 13);
            TeachCreateFlag[1] = true;
            _DownGroundCollision[i]->teach = true;
        }
        else if(num == 7){
            sprintf(level, "Level_%d", 2);
            sprintf(name, "%d", 0);
            TeachCreateFlag[0] = true;
            _DownGroundCollision[i]->teach = true;
        }
        else if(num == 11){
            sprintf(kind, "up");
            sprintf(level, "Level_%d", 3);
            sprintf(name, "%d", 0);
            TeachCreateFlag[2] = true;
            _DownGroundCollision[i]->teach = true;
        }
        else if(num > 7 && num < 11){
            sprintf(kind, "up");
            sprintf(level, "Level_%d", 0);
            sprintf(name, "%d", 0);
        }
        else{
            sprintf(kind, "down");
            sprintf(level, "Level_%d", 0);
            sprintf(name, "%d", 0);
        }
    }
    else{ //非教學
        //三分之一的機率
        int n;
        if(UpFlag){
            n = rand() % 2;
            if (n)
                sprintf(kind, "down");
            else
                sprintf(kind, "up");
        }
        if(DieFlag)
            sprintf(level, "Level_%d", 0);
        else{
            n = rand() % 4;
            //if (n != 1)n = 0;
            sprintf(level, "Level_%d", n);
        }
        n = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getTag();
        sprintf(name, "%d", n);
    }
    _DownGroundCollision[i]->ChangeObstacle(CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getChildByName(name));
    UpFlag = _DownGroundCollision[i]->UpFlag;
    DieFlag = _DownGroundCollision[i]->DieFlag;
    CCLOG("%d",num%OB_NUM);
    num++;
}
