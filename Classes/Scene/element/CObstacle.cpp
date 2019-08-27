 #include "CObstacle.h"
#define PTM_RATIO 32.0f
#define DG_WIDTH 426.0f
#define INSECT_SPEED 5.0f;
#define BO_SPEED 2.0f;

USING_NS_CC;

// on "init" you need to initialize your instance
CObstacle::~CObstacle(){}
CObstacle::CObstacle(b2World* _b2W, Node* _ob) {
	_b2World = _b2W;
    _Obstacle = _ob;
    CreateObstacle();
}
void CObstacle::ChangeObstacle(Node* _ob){
    //初始
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/Img/game_element.plist");
	for (int i = 0; i < num; i++) {
        _b2World->DestroyBody(ObstacleBody[i]);
    }
	removeChild(_Obstacle);
	std::vector <b2Body*>().swap(ObstacleBody);
    num = 0;
    UpFlag = false;
    DieFlag = false;
    _Obstacle = _ob;
    CreateObstacle();
}
void CObstacle::CreateObstacle(){
    char sprite[10];
    _Obstacle->setPosition(0,0);
    _Obstacle->setVisible(true);
    this->addChild(_Obstacle, 1);

    _body = (cocos2d::Sprite *)_Obstacle->getChildByName("Sprite_0");
    _fWidth = DG_WIDTH * _Obstacle->getTag();
    for (int i = 1; _body != NULL; i++) {
        _body->setGlobalZOrder(1);
        if (_body->getTag() != 0) {
            num++;
            CreateCollision();
        }
        if(i == 2){
            if(_body->getChildByTag(1)!=NULL)
                _body->getChildByTag(1)->setGlobalZOrder(-1);
        }
        sprintf(sprite, "Sprite_%d", i);
        _body = (cocos2d::Sprite *)_Obstacle->getChildByName(sprite);
    }

	//裝飾
    if(rand()%5 == 0){
        Sprite *img = Sprite::createWithSpriteFrameName("d_img.png");
        this->_Obstacle->addChild(img,2);
		img->setGlobalZOrder(2);
    }
    if(rand()%8 == 0){
        Sprite *img;
        int n = rand()%2;
        switch(n){
            case 0:
                img = Sprite::createWithSpriteFrameName("decoration_flower.png");
                break;
            case 1:
                img = Sprite::createWithSpriteFrameName("decoration_leaf.png");
                break;
        }
        if(UpFlag == true){
            switch(n%2){
                case 0:
                    img->setPosition((rand() % 375) - 187,220);
                    break;
                case 1:
                    img->setPosition((rand() % 375) - 187,610);
                    break;
            }
        }
        else  img->setPosition((rand() % 375) - 187,220);
        this->_Obstacle->addChild(img,2);
		img->setGlobalZOrder(2);
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
    float scaleX = _body->getScaleX();    // §Ù•≠™∫Ωu¨qπœ•‹∞≤≥]≥£•u¶≥πÔ X ∂b©Ò§j
    float scaleY = _body->getScaleY();    // §Ù•≠™∫Ωu¨qπœ•‹∞≤≥]≥£•u¶≥πÔ X ∂b©Ò§j
    
    Point lep[4], wep[4];
    lep[0].x = (ts.width) / 2.0f;  lep[0].y = (ts.height) / 2.0f;
    lep[1].x = -(ts.width) / 2.0f; lep[1].y = (ts.height) / 2.0f;
    lep[2].x = -(ts.width) / 2.0f; lep[2].y = -(ts.height) / 2.0f;
    lep[3].x = (ts.width) / 2.0f;  lep[3].y = -(ts.height) / 2.0f;
    
    cocos2d::Mat4 modelMatrix, rotMatrix;
    modelMatrix.m[0] = scaleX;  // •˝≥]©w X ∂b™∫¡Y©Ò
    modelMatrix.m[5] = scaleY;  // •˝≥]©w Y ∂b™∫¡Y©Ò
    cocos2d::Mat4::createRotationZ(0 * M_PI / 180.0f, &rotMatrix);
    modelMatrix.multiply(rotMatrix);
    modelMatrix.m[3] = loc.x; //≥]©w Translation°A¶€§v™∫•[§W§˜øÀ™∫
    modelMatrix.m[7] = loc.y; //≥]©w Translation°A¶€§v™∫•[§W§˜øÀ™∫
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
    fixtureDef.friction = 0.0f;
    if(_body->getTag() == 1) //normal up
        UpFlag = true;
    else if(_body->getTag() == 2) //attack
        fixtureDef.density = 10000.0f;
	else if (_body->getTag() == 4 || _body->getTag() == 7) { //die
        fixtureDef.density = 5000.0f;
		_body->setGlobalZOrder(3);
		fixtureDef.isSensor = true;
		DieFlag = true;
	}
	else if (_body->getTag() == 5) { //rock
		_body->setGlobalZOrder(0);
		fixtureDef.isSensor = true;
		fixtureDef.density = 10000.0f;
	}
	else if (_body->getTag() == 6) { //bo
		_body->setGlobalZOrder(0);
        fixtureDef.density = 5000.0f;
		fixtureDef.isSensor = true;
		DieFlag = true;
	}
	_Cbody->CreateFixture(&fixtureDef);
	ObstacleBody.push_back(_Cbody);
}
void CObstacle::Move(float x, float y) {
	_Obstacle->setPosition(_Obstacle->getPosition().x + x, _Obstacle->getPosition().y + y);
	for (int i = 0; i < num; i++) {
        Sprite *Data = (Sprite*)ObstacleBody[i]->GetUserData();
        float fx = _Obstacle->getPosition().x;
        float fy = _Obstacle->getPosition().y;
        ObstacleBody[i]->SetTransform(b2Vec2(fx / PTM_RATIO, fy / PTM_RATIO), 0);
		if (Data->getTag() == 6) {
			fy = Data->getPosition().y;
			if (BoSpeed) {
				if (Data->getPosition().y <= 310) {
					fy += BO_SPEED;
				}
				else { BoSpeed = !BoSpeed; }
			}
			else {
				if (Data->getPosition().y >= 0) {
					fy -= BO_SPEED;
				}
				else { BoSpeed = !BoSpeed; }
			}
			Data->setPosition(Data->getPosition().x, fy);
			ObstacleBody[i]->SetTransform(b2Vec2(fx / PTM_RATIO, ObstacleBody[i]->GetPosition().y + fy / PTM_RATIO), 0);
		}
		else if (Data->getTag() == 7) {
			fx = Data->getPosition().x - INSECT_SPEED;
			Data->setPosition(fx, Data->getPosition().y);
			ObstacleBody[i]->SetTransform(b2Vec2(ObstacleBody[i]->GetPosition().x + fx / PTM_RATIO, fy / PTM_RATIO), 0);
		}
	}
}
void CObstacle::SetPos(float x, float y) {
	_Obstacle->setPosition(x, y);
	for (int i = 0; i<num; i++) {
		Sprite *Data = (Sprite*)ObstacleBody[i]->GetUserData();
		float fx = _Obstacle->getPosition().x;
		float fy = _Obstacle->getPosition().y;
		ObstacleBody[i]->SetTransform(b2Vec2(fx / PTM_RATIO, fy / PTM_RATIO), 0);
	}
}
Point CObstacle::Getpos() {
	Point pos;
	pos.x = _Obstacle->getPosition().x;
	pos.y = _Obstacle->getPosition().y;
	return (pos);
}
