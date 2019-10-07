#include "CLevelCreate.h"
#include<stdlib.h>
#define DG_WIDTH 426.0f
#define LEVELTIME 30 //level distance
#define DISTANCE 10 //board distance
#define OBSTACLE_SPEED 12
#define START_NUM OB_NUM //7
#define TEACH_NUM 12 //teach Obstacle number

USING_NS_CC;

CLevelCreate::~CLevelCreate() {
    removeAllChildren();
    
    for (int i = 0; i<OB_NUM; i++,num++) {
        delete _DownGroundCollision[i];
    }
}

CLevelCreate::CLevelCreate(b2World* _b2W, float PlayerPosX) {
    _fPlayerPosX = PlayerPosX;
	srand(time(NULL));
	sprintf(level, "Level_%d", 0);
	sprintf(name, "%d", 0);
    if(UserDefault::getInstance()->getBoolForKey("TEACH_FLAG") == 0){ // 0:no
        num = -(START_NUM + TEACH_NUM);
    }
    else{
        num = -START_NUM;
        TeachFlag = 2;
    }
	for (int i = 0; i<OB_NUM; i++,num++) {
		_DownGroundCollision[i] = new CObstacle(_b2W, CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getChildByName(name));
        if(i==0)
            _DownGroundCollision[i]->SetPos(0, 200);
        else
            _DownGroundCollision[i]->SetPos(_DownGroundCollision[i-1]->Getpos().x + _DownGroundCollision[i-1]->_fWidth/2 + _DownGroundCollision[i]->_fWidth/2, 200);
		this->addChild(_DownGroundCollision[i], num);
	}
}
void CLevelCreate::dostep(float dt) {
	for (int i = 0; i < OB_NUM; i++) {
        if(_DownGroundCollision[i]->teach == true){
            if(TeachCreateFlag[0] == true){
				if (_DownGroundCollision[i]->Getpos().x <= _fPlayerPosX+300) {
					TeachFlag = 1;
					_DownGroundCollision[i]->teach = false;
					TeachCreateFlag[0] = false;
				}
            }
            else if(TeachCreateFlag[1] == true){
                if(_DownGroundCollision[i]->Getpos().x <= _fPlayerPosX+600){
                    TeachFlag = 0;
                    _DownGroundCollision[i]->teach = false;
                    TeachCreateFlag[1] = false;
                }
            }
            else if(TeachCreateFlag[2] == true){
                if(_DownGroundCollision[i]->Getpos().x <= _fPlayerPosX+700){
                    TeachFlag = 0;
                    TeachCreateFlag[2] = false;
                }
            }
            else{
                if(_DownGroundCollision[i]->Getpos().x <= _fPlayerPosX+550){
                    TeachFlag = 1;
                    _DownGroundCollision[i]->teach = false;
                }
            }
        }
		if (_DownGroundCollision[i]->Getpos().x < -(_DownGroundCollision[i]->_fWidth / 2)) {
			SetObstacle(i);
		}
        if (_DownGroundCollision[i]->Getpos().x < _fPlayerPosX && _DownGroundCollision[i]->start) {
            _DownGroundCollision[i]->start = false;
            f_tDistance += _DownGroundCollision[i]->_fWidth / DG_WIDTH;
        }
		_DownGroundCollision[i]->Move(-OBSTACLE_SPEED, 0);
	}
}
void CLevelCreate::SetObstacle(int i) {
    //教學
    if(num < 0){
        if(num == -TEACH_NUM){
            sprintf(level, "Level_%d", 1);
            sprintf(name, "%d", 13);
            _DownGroundCollision[i]->teach = true;
            TeachCreateFlag[0] = true;
        }
        else if(num == -TEACH_NUM+4){
            sprintf(level, "Level_%d", 2);
            sprintf(name, "%d", 0);
            _DownGroundCollision[i]->teach = true;
            TeachCreateFlag[1] = true;
        }
        else if(num == -TEACH_NUM+8){
            sprintf(kind, "up");
            sprintf(level, "Level_%d", 3);
            sprintf(name, "%d", 0);
            _DownGroundCollision[i]->teach = true;
            TeachCreateFlag[2] = true;
        }
        else if(num > -TEACH_NUM+4 && num < -TEACH_NUM+8){
            sprintf(kind, "up");
            sprintf(level, "Level_%d", 0);
            sprintf(name, "%d", 0);
        }
        else{
            sprintf(kind, "down");
            sprintf(level, "Level_%d", 0);
            sprintf(name, "%d", 0);
        }
        _DownGroundCollision[i]->ChangeObstacle(CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getChildByName(name));
    }
	else { //非教學
        if(num == 0)BoardFlag = true;
		if (num % LEVELTIME == 0 && _iLevel < 3) { //提升level
			_iLevel++;
			_iLevelFrequency == 5;
        }
		int n;
        if (DieFlag) //有會死掉的物件
            sprintf(level, "Level_%d", 0);
        else {
            n = rand() % _iLevelFrequency; //如果n=1
            if (num % 5 == 0 && _iLevelFrequency > 3) _iLevelFrequency--;
            if (n == 1)n = (rand() % _iLevel) + 1;
            else n = 0;
            sprintf(level, "Level_%d", n);
        }
        if (UpFlag) {
            n = rand() % 3;
            if (n)
                sprintf(kind, "up");
            else {
                sprintf(kind, "down");
                sprintf(level, "Level_%d", 0);
            }
        }
        if ((Distance+1) % DISTANCE == 0 || !Distance) {
            sprintf(level, "Level_%d", 0);
            BoardFlag = true;
        }
        n = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getTag();
        sprintf(name, "%d", n);
        _DownGroundCollision[i]->ChangeObstacle(CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getChildByName(name));
        _DownGroundCollision[i]->start = true;
        if((Distance+2) % DISTANCE == 0){
            while((_DownGroundCollision[i]->_fWidth/DG_WIDTH)==2){
                CCLOG("change");
                n = rand() % _iLevelFrequency; //如果n=1
                if (num % 5 == 0 && _iLevelFrequency > 3) _iLevelFrequency--;
                if (n == 1)n = (rand() % _iLevel) + 1;
                else n = 0;
                sprintf(level, "Level_%d", n);
                if (UpFlag) {
                    n = rand() % 3;
                    if (n)
                        sprintf(kind, "up");
                    else {
                        sprintf(kind, "down");
                        sprintf(level, "Level_%d", 0);
                    }
                }
                n = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getTag();
                sprintf(name, "%d", n);
                _DownGroundCollision[i]->ChangeObstacle(CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getChildByName(name));
            }
        }
        Distance += _DownGroundCollision[i]->_fWidth / DG_WIDTH;
	}
    if(UpFlag == true && strcmp(kind, "up")==0 && _DownGroundCollision[i]->light!=NULL)_DownGroundCollision[i]->light->setVisible(false);
    if(BoardFlag == true){
        BoardFlag = false;
        Node *board = (cocos2d::Node*)CSLoader::createNode("Obstacle.csb")->getChildByName("board");
        this->_DownGroundCollision[i]->_Obstacle->addChild(board);
        Text * t = (cocos2d::ui::Text *)board->getChildByName("text");
        char d[6];
        sprintf(d, "%d", Distance/DISTANCE);
        t->setString(d);
    }
    UpFlag = _DownGroundCollision[i]->UpFlag;
    DieFlag = _DownGroundCollision[i]->DieFlag;
    if (i == 0)
        _DownGroundCollision[i]->SetPos(_DownGroundCollision[OB_NUM - 1]->Getpos().x + _DownGroundCollision[OB_NUM - 1]->_fWidth / 2 + _DownGroundCollision[i]->_fWidth / 2, 200);
    else
        _DownGroundCollision[i]->SetPos(_DownGroundCollision[i - 1]->Getpos().x + _DownGroundCollision[i - 1]->_fWidth / 2 + _DownGroundCollision[i]->_fWidth / 2, 200);
    _DownGroundCollision[i]->setLocalZOrder(num);
    num++;
}
