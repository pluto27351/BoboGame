#include "CObstacle.h"
#define INSECT_SPEED 5.0f;
USING_NS_CC;

// on "init" you need to initialize your instance
CObstacle::~CObstacle(){
    for (int i = 0; i < _iNum; i++) {
        _b2World->DestroyBody(ObstacleBody[i]);
    }
    ObstacleBody.clear();
}
CObstacle::CObstacle(b2World* _b2W, Node* _ob) {
	_b2World = _b2W;
    _Obstacle = _ob;
    CreateObstacle();
}
void CObstacle::ChangeObstacle(Node* _ob){
    //初始
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Img/game_element.plist");
	for (int i = 0; i < _iNum; i++) {
        _b2World->DestroyBody(ObstacleBody[i]);
    }
	removeChild(_Obstacle);
	std::vector <b2Body*>().swap(ObstacleBody);
    _iNum = 0;
    _fWidth = 0;
    _fBigboTime = 0;
    UpFlag = false;
    DieFlag = false;
    AttackFlag = false;
    
    _Obstacle = _ob;
    CreateObstacle();
}
void CObstacle::CreateObstacle(){
    char sprite[9];
    _Obstacle->setPosition(0,0);
    _Obstacle->setVisible(true);
    this->addChild(_Obstacle, 1);
    _fWidth = DG_WIDTH * _Obstacle->getTag();
    _body = (cocos2d::Sprite *)_Obstacle->getChildByName("Sprite_0");
    for (int i = 1; _body != NULL; i++) {
        if (_body->getTag() != 0) {
            _iNum++;
            CreateCollision();
        }
        sprintf(sprite, "Sprite_%d", i);
        _body = (cocos2d::Sprite *)_Obstacle->getChildByName(sprite);
    }
	//裝飾
    if(!(rand()%5)){ //地板
        Sprite *img = Sprite::createWithSpriteFrameName("d_img.png");
        this->_Obstacle->addChild(img,2);
    }
    if(!(rand()%8)){ //花，葉子，草叢
        Sprite *img;
        switch(rand()%3){
            case 0:
                img = Sprite::createWithSpriteFrameName("decoration_flower.png");
                break;
            case 1:
                img = Sprite::createWithSpriteFrameName("decoration_leaf.png");
                break;
            case 2:
                img = Sprite::createWithSpriteFrameName("decoration_grass.png");
                img->setScale(0.8f);
                break;
        }
        img->setPosition(rand()%(300 * _Obstacle->getTag())-150,220);
        if(UpFlag && !(rand()%2))img->setPosition(rand()%(300 * _Obstacle->getTag())-150,610);
        this->_Obstacle->addChild(img,2);
    }
}
void CObstacle::CreateCollision(){
	b2Body * _Cbody;
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.userData = _body;
   _Cbody = _b2World->CreateBody(&bodyDef);
    Point loc = _body->getPosition() + _Obstacle->getPosition();
    Size ts = _body->getContentSize();
    b2PolygonShape rectShape;
    float scaleX = _body->getScaleX();
    float scaleY = _body->getScaleY();
    Point lep[4], wep[4];
    lep[0].x = (ts.width) / 2.0f;  lep[0].y = (ts.height) / 2.0f;
    lep[1].x = -(ts.width) / 2.0f; lep[1].y = (ts.height) / 2.0f;
    lep[2].x = -(ts.width) / 2.0f; lep[2].y = -(ts.height) / 2.0f;
    lep[3].x = (ts.width) / 2.0f;  lep[3].y = -(ts.height) / 2.0f;
    cocos2d::Mat4 modelMatrix, rotMatrix;
    modelMatrix.m[0] = scaleX;
    modelMatrix.m[5] = scaleY;
    cocos2d::Mat4::createRotationZ(0 * M_PI / 180.0f, &rotMatrix);
    modelMatrix.multiply(rotMatrix);
    modelMatrix.m[3] = loc.x;
    modelMatrix.m[7] = loc.y;
    for (size_t j = 0; j < 4; j++)
    {
        wep[j].x = lep[j].x * modelMatrix.m[0] + lep[j].y * modelMatrix.m[1] + modelMatrix.m[3];
        wep[j].y = lep[j].x * modelMatrix.m[4] + lep[j].y * modelMatrix.m[5] + modelMatrix.m[7];
    }
    b2Vec2 vecs[] = {
        b2Vec2(wep[0].x / PTM_RATIO, wep[0].y / PTM_RATIO),
        b2Vec2(wep[1].x / PTM_RATIO, wep[1].y / PTM_RATIO),
        b2Vec2(wep[2].x / PTM_RATIO, wep[2].y / PTM_RATIO),
        b2Vec2(wep[3].x / PTM_RATIO, wep[3].y / PTM_RATIO) };
    rectShape.Set(vecs, 4);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &rectShape;
    fixtureDef.restitution = 0.0f;
    fixtureDef.density = 5.0f;
    fixtureDef.friction = 0.0f;
    //障礙物類型
    if(_body->getTag() == 1){ //normal up
        fixtureDef.density = 0.0f;
        UpFlag = true;
    }
    else if(_body->getTag() == 2){ //attack
        fixtureDef.density = 10000.0f;
        UpFlag = true;
    }
	else if (_body->getTag() == 4 || _body->getTag() == 7) { //die
        fixtureDef.density = 5000.0f;
		fixtureDef.isSensor = true;
        _body->setLocalZOrder(1);
		DieFlag = true;
	}
	else if (_body->getTag() == 5) { //rock sensor
        fixtureDef.density = 10000.0f;
		fixtureDef.isSensor = true;
        AttackFlag = true;
	}
	else if (_body->getTag() == 6) { //BigBo
        fixtureDef.density = 5000.0f;
		fixtureDef.isSensor = true;
		DieFlag = true;
	}
	_Cbody->CreateFixture(&fixtureDef);
	ObstacleBody.push_back(_Cbody);
}
void CObstacle::MoveX(float x, float time) {
	_Obstacle->setPosition(_Obstacle->getPosition().x + x, _Obstacle->getPosition().y);
	for (int i = 0; i < _iNum; i++) {
        float fx = _Obstacle->getPosition().x;
        float fy = _Obstacle->getPosition().y;
        ObstacleBody[i]->SetTransform(b2Vec2(PTM_RATIO_DIV(fx), PTM_RATIO_DIV(fy)), 0);
        Sprite *Data = (Sprite*)ObstacleBody[i]->GetUserData();
		if (Data->getTag() == 6) { //BigBo
            _fBigboTime+=time;
			fy = abs(sin(_fBigboTime))*310;
			Data->setPosition(Data->getPosition().x, fy);
			ObstacleBody[i]->SetTransform(b2Vec2(PTM_RATIO_DIV(fx), ObstacleBody[i]->GetPosition().y+PTM_RATIO_DIV(fy)), 0);
		}
		else if (Data->getTag() == 7) { //Insect
			fx = Data->getPosition().x - INSECT_SPEED;
			Data->setPosition(fx, Data->getPosition().y);
            ObstacleBody[i]->SetTransform(b2Vec2(PTM_RATIO_DIV(fx)+ObstacleBody[i]->GetPosition().x,PTM_RATIO_DIV(fy)), 0);
		}
	}
}
void CObstacle::SetPos(float x, float y) {
	_Obstacle->setPosition(x, y);
	for (int i = 0; i<_iNum; i++) {
		Sprite *Data = (Sprite*)ObstacleBody[i]->GetUserData();
		ObstacleBody[i]->SetTransform(b2Vec2(PTM_RATIO_DIV(_Obstacle->getPosition().x), PTM_RATIO_DIV(_Obstacle->getPosition().y)), 0);
	}
}
Point CObstacle::Getpos() {
	return _Obstacle->getPosition();
}
Node *CObstacle::GetNode(){
    return _Obstacle;
}
float CObstacle::GetWidth(){
    return _fWidth;
}
