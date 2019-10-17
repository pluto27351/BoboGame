#include "CLevelCreate.h"
#include<stdlib.h>
#define LEVELTIME 70 //level distance
#define LEVELFREQUENCY 20 //level distance
#define DISTANCE 10 //board distance
#define OBSTACLE_SPEED 12
#define START_NUM OB_NUM
#define TEACH_NUM 12 //teach Obstacle number

USING_NS_CC;

CLevelCreate::~CLevelCreate() {
    removeAllChildren();
    for (int i = 0; i<OB_NUM; i++,_iNum++) {
        delete _DownGroundCollision[i];
    }
}
CLevelCreate::CLevelCreate(b2World* _b2W, float PlayerPosX) {
    srand(time(NULL));
    _fPlayerPosX = PlayerPosX;
    if(!(UserDefault::getInstance()->getBoolForKey("TEACH_FLAG")))_iNum = -(START_NUM + TEACH_NUM); //有沒有教學
    else{ _iNum = -START_NUM;Teach = 2; }
	for (int i = 0; i<OB_NUM; i++,_iNum++) {
		_DownGroundCollision[i] = new CObstacle(_b2W, CSLoader::createNode("Obstacle.csb")->getChildByName(_cKind)->getChildByName(_cLevel)->getChildByName(_cName));
        if(i==0)
            _DownGroundCollision[i]->SetPos(0, 200);
        else
            _DownGroundCollision[i]->SetPos(_DownGroundCollision[i-1]->Getpos().x + _DownGroundCollision[i-1]->GetWidth()/2 + _DownGroundCollision[i]->GetWidth()/2, 200);
		this->addChild(_DownGroundCollision[i], _iNum);
	}
}
void CLevelCreate::dostep(float dt) {
	for (int i = 0; i < OB_NUM; i++) {
        if(_DownGroundCollision[i]->TeachFlag){
            if(_bTeachCreateFlag[0]){
				if (_DownGroundCollision[i]->Getpos().x <= _fPlayerPosX+300) {
					Teach = 1;
					_DownGroundCollision[i]->TeachFlag = false;
					_bTeachCreateFlag[0] = false;
				}
            }
            else if(_bTeachCreateFlag[1]){
                if(_DownGroundCollision[i]->Getpos().x <= _fPlayerPosX+550){
                    Teach = 0;
                    _DownGroundCollision[i]->TeachFlag = false;
                    _bTeachCreateFlag[1] = false;
                }
            }
            else if(_bTeachCreateFlag[2]){
                if(_DownGroundCollision[i]->Getpos().x <= _fPlayerPosX+700){
                    Teach = 0;
                    _bTeachCreateFlag[2] = false;
                }
            }
            else{
                if(_DownGroundCollision[i]->Getpos().x <= _fPlayerPosX+500){
                    Teach = 1;
                    _DownGroundCollision[i]->TeachFlag = false;
                }
            }
        }
		if (_DownGroundCollision[i]->Getpos().x < -(_DownGroundCollision[i]->GetWidth() / 2)) {
			SetObstacle(i);
		}
        if (_DownGroundCollision[i]->Getpos().x < _fPlayerPosX && _DownGroundCollision[i]->start) {
            _DownGroundCollision[i]->start = false;
            Score += _DownGroundCollision[i]->GetWidth() / DG_WIDTH;
        }
		_DownGroundCollision[i]->MoveX(-OBSTACLE_SPEED, dt);
	}
}
void CLevelCreate::SetObstacle(int i) {
    //teach
    if(_iNum < 0){
        if(_iNum == -TEACH_NUM){
            sprintf(_cLevel, "Level_%d", 1);
            sprintf(_cName, "%d", 13);
            _DownGroundCollision[i]->TeachFlag = true;
            _bTeachCreateFlag[0] = true;
        }
        else if(_iNum == -TEACH_NUM+4){
            sprintf(_cLevel, "Level_%d", 2);
            sprintf(_cName, "%d", 0);
            _DownGroundCollision[i]->TeachFlag = true;
            _bTeachCreateFlag[1] = true;
        }
        else if(_iNum == -TEACH_NUM+8){
            sprintf(_cKind, "up");
            sprintf(_cLevel, "Level_%d", 3);
            sprintf(_cName, "%d", 0);
            _DownGroundCollision[i]->TeachFlag = true;
            _bTeachCreateFlag[2] = true;
        }
        else if(_iNum > -TEACH_NUM+4 && _iNum < -TEACH_NUM+8){
            sprintf(_cKind, "up");
            sprintf(_cLevel, "Level_%d", 0);
            sprintf(_cName, "%d", 0);
        }
        else{
            sprintf(_cKind, "down");
            sprintf(_cLevel, "Level_%d", 0);
            sprintf(_cName, "%d", 0);
        }
        _DownGroundCollision[i]->ChangeObstacle(CSLoader::createNode("Obstacle.csb")->getChildByName(_cKind)->getChildByName(_cLevel)->getChildByName(_cName));
    }
	else { //Play
        //Level
		if (_iNum % LEVELTIME == 0 && _iLevel < 3) {
			_iLevel++;
			_iLevelFrequency = 5;
        }
        if (_iNum % LEVELFREQUENCY == 0 && _iLevelFrequency > 3) _iLevelFrequency--;
        int n;
        if(_bUpFlag){ //如果前一個是上方地形，要決定下一個接上方還下方
            if(_bNextdown){ //現在這一個要變下方
                _bSafeFlag = true;
                _bNextdown = false;
                sprintf(_cKind, "down");
            }
            else{
                sprintf(_cKind, "up");
                n = rand() % 3; //有2/3的機率繼續是上方物件
                if(!n) { //上方地形結尾
                    _bNextdown = true;
                    _bSafeFlag = true;
                }
            }
        }
        if (_bDieFlag){ //如果前一個有死亡物件
            _bSafeFlag = true;
            if(_bAttackFlag){sprintf(_cKind, "down");_bNextdown = false;} //如果前一個有攻擊物件
        }
        if (!_iNum || (_iDistance+1) % DISTANCE == 0){ //出路牌 － 剛開始，前一個距離差１就出牌子
            _bSafeFlag = true;
            _bBoardFlag = true;
        }
        if(_bSafeFlag){ //一定要出安全地形的時候
            n = 0;
            _bSafeFlag = false;
        }
        else if(_iNoDieNum>=_iLevelFrequency)n = (rand() % _iLevel) + 1; //一定要出非安全地形的時候
        else{ //按機率隨機出
            n = rand() % _iLevelFrequency;
            if (n == 1)
                n = (rand() % _iLevel) + 1;
            else n = 0;
        }
        if(!n) _iNoDieNum++;
        else _iNoDieNum = 0; //算目前連續出幾個安全地形
        sprintf(_cLevel, "Level_%d", n); //獲得障礙物Level
        if(_bNextdown)n = 1;
        else n = rand() % CSLoader::createNode("Obstacle.csb")->getChildByName(_cKind)->getChildByName(_cLevel)->getTag();
        sprintf(_cName, "%d", n);
        CCLOG("%s %s %s",_cKind,_cLevel,_cName);
        _DownGroundCollision[i]->ChangeObstacle(CSLoader::createNode("Obstacle.csb")->getChildByName(_cKind)->getChildByName(_cLevel)->getChildByName(_cName));
        _DownGroundCollision[i]->start = true;
        _iDistance += (_DownGroundCollision[i]->GetWidth() / DG_WIDTH); //距離 = 兩個地板算1
        //出路牌
        if(_bBoardFlag == true){
            _bBoardFlag = false;
            Node *board = (cocos2d::Node*)CSLoader::createNode("Obstacle.csb")->getChildByName("board");
            this->_DownGroundCollision[i]->GetNode()->addChild(board);
            Text * t = (cocos2d::ui::Text *)board->getChildByName("text");
            char d[6];
            sprintf(d, "%d", _iDistance/DISTANCE);
            t->setString(d);
        }
        _bUpFlag = _DownGroundCollision[i]->UpFlag;
        _bDieFlag = _DownGroundCollision[i]->DieFlag;
        _bAttackFlag = _DownGroundCollision[i]->AttackFlag;
	}
    //Position
    if (i == 0)
        _DownGroundCollision[i]->SetPos(_DownGroundCollision[OB_NUM - 1]->Getpos().x + _DownGroundCollision[OB_NUM - 1]->GetWidth() / 2 + _DownGroundCollision[i]->GetWidth() / 2, 200);
    else
        _DownGroundCollision[i]->SetPos(_DownGroundCollision[i - 1]->Getpos().x + _DownGroundCollision[i - 1]->GetWidth() / 2 + _DownGroundCollision[i]->GetWidth() / 2, 200);
    _DownGroundCollision[i]->setLocalZOrder(_iNum);
    _iNum++;
}
