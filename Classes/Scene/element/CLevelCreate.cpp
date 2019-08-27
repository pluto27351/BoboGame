#include "CLevelCreate.h"
#include<stdlib.h>
#define DG_WIDTH 426.0f
#define LEVELTIME 30 //跑過幾個地升一次level
#define DISTANCE 10 //跑過幾個地升一次level
#define START_NUM 3
#define TEACH_NUM (16+START_NUM)

USING_NS_CC;

CLevelCreate::~CLevelCreate() {}
CLevelCreate::CLevelCreate(b2World* _b2W) {
	srand(time(NULL));
	sprintf(level, "Level_%d", 0);
	sprintf(name, "%d", 0);
    if(UserDefault::getInstance()->getBoolForKey("TEACH_FLAG") == 0){ // 0:no
        num = -TEACH_NUM;
    }
    else{
        num = -START_NUM-6;TeachFlag = 2;
    }
	for (int i = 0; i<OB_NUM; i++,num++) {
		_DownGroundCollision[i] = new CObstacle(_b2W, CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getChildByName(name));
        if(i==0)
            _DownGroundCollision[i]->SetPos(0, 200);
        else
            _DownGroundCollision[i]->SetPos(_DownGroundCollision[i-1]->Getpos().x + _DownGroundCollision[i-1]->_fWidth/2 + _DownGroundCollision[i]->_fWidth/2, 200);
		this->addChild(_DownGroundCollision[i], 0);
	}
}
void CLevelCreate::dostep(float dt) {
	for (int i = 0; i < OB_NUM; i++) {
        if(_DownGroundCollision[i]->teach == true){
            if(TeachCreateFlag[0] == true){
				if (_DownGroundCollision[i]->Getpos().x <= 700) {
					TeachFlag = 1;
					_DownGroundCollision[i]->teach = false;
					TeachCreateFlag[0] = false;
				}
            }
            else if(TeachCreateFlag[1] == true){
                if(_DownGroundCollision[i]->Getpos().x <= 1000){
                    TeachFlag = 0;
                    _DownGroundCollision[i]->teach = false;
                    TeachCreateFlag[1] = false;
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
		}
		_DownGroundCollision[i]->Move(-10, 0);
	}
}
void CLevelCreate::SetObstacle(int i) {
    //教學
    if(num < -START_NUM){
        CCLOG("%d",num);
        if(num == -TEACH_NUM+7){
            sprintf(level, "Level_%d", 1);
            sprintf(name, "%d", 13);
            TeachCreateFlag[0] = true;
            _DownGroundCollision[i]->teach = true;
        }
        else if(num == -TEACH_NUM+11){
            sprintf(level, "Level_%d", 2);
            sprintf(name, "%d", 0);
            TeachCreateFlag[1] = true;
            _DownGroundCollision[i]->teach = true;
        }
        else if(num == -TEACH_NUM+15){
            sprintf(kind, "up");
            sprintf(level, "Level_%d", 3);
            sprintf(name, "%d", 0);
            TeachCreateFlag[2] = true;
            _DownGroundCollision[i]->teach = true;
        }
        else if(num > -TEACH_NUM+11 && num < -TEACH_NUM+15){
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
    else if(num < 0){
        sprintf(kind, "down");
        sprintf(level, "Level_%d", 0);
        sprintf(name, "%d", 0);
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
		if (UpFlag) { //可以接上面地形
			n = rand() % 3;
			if (n)
				sprintf(kind, "up");
			else {
				sprintf(kind, "down");
				sprintf(level, "Level_%d", 0);
			}
		}
        if(_DownGroundCollision[i]->_fWidth / DG_WIDTH == 2){
            if (Distance % (DISTANCE+1) == 0) {
                sprintf(level, "Level_%d", 0);
                BoardFlag = true;
            }
        }
        else{
            if (Distance % DISTANCE == 0) {
                sprintf(level, "Level_%d", 0);
                BoardFlag = true;
            }
        }
		n = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getTag();
		sprintf(name, "%d", n);
        Distance += _DownGroundCollision[i]->_fWidth / DG_WIDTH;
	}
    _DownGroundCollision[i]->ChangeObstacle(CSLoader::createNode("Obstacle.csb")->getChildByName(kind)->getChildByName(level)->getChildByName(name));
    if(BoardFlag == true){
        BoardFlag = false;
        Node *board = (cocos2d::Node*)CSLoader::createNode("Obstacle.csb")->getChildByName("board");
        this->_DownGroundCollision[i]->_Obstacle->addChild(board);
        Text * t = (cocos2d::ui::Text *)board->getChildByName("text");
        //board->getChildByName("Sprite")->setGlobalZOrder(2);
        t->setGlobalZOrder(1);
        char d[6];
        sprintf(d, "%d", Distance/10);
        t->setString(d);
    }
    UpFlag = _DownGroundCollision[i]->UpFlag;
    DieFlag = _DownGroundCollision[i]->DieFlag;
    if (i == 0)
        _DownGroundCollision[i]->SetPos(_DownGroundCollision[OB_NUM - 1]->Getpos().x + _DownGroundCollision[OB_NUM - 1]->_fWidth / 2 + _DownGroundCollision[i]->_fWidth / 2, 200);
    else
        _DownGroundCollision[i]->SetPos(_DownGroundCollision[i - 1]->Getpos().x + _DownGroundCollision[i - 1]->_fWidth / 2 + _DownGroundCollision[i]->_fWidth / 2, 200);
    num++;
}
