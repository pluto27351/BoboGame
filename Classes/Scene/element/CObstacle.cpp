#include "CObstacle.h"
#define PTM_RATIO 32.0f
#define DG_WIDTH 425.0f

USING_NS_CC;

// on "init" you need to initialize your instance
CObstacle::~CObstacle(){}
CObstacle::CObstacle(b2World* _b2W, Node* _ob) {
	_b2World = _b2W;
	char sprite[9];
	_Obstacle = _ob;
	_Obstacle->setPosition(-300,235);
	_Obstacle->setVisible(true);
	this->addChild(_Obstacle, 1);
    _fWidth = DG_WIDTH * _Obstacle->getTag();
	_body = (cocos2d::Sprite *)_Obstacle->getChildByName("Sprite_0");
	for (int i = 1; _body != NULL; i++) {
		sprintf(sprite, "Sprite_%d", i);
		_body = (cocos2d::Sprite *)_Obstacle->getChildByName(sprite);
        num++;
	}
    for (int i = 0; i<num; i++){
        sprintf(sprite, "Sprite_%d", i);
        _body = (cocos2d::Sprite *)_Obstacle->getChildByName(sprite);
        CreateCollision();
    }
}
void CObstacle::ChangeObstacle(Node* _ob){
	for (int i = 0; i < num; i++) {
		removeChild(_Obstacle);
		_b2World->DestroyBody(ObstacleBody[i]);
	}
	std::vector <b2Body*>().swap(ObstacleBody);
    num = 0;
    char sprite[9];
    _Obstacle = _ob;
    _Obstacle->setPosition(-300,235);
	_Obstacle->setVisible(true);
	this->addChild(_Obstacle, 1);
    _fWidth = DG_WIDTH * _Obstacle->getTag();
    _body = (cocos2d::Sprite *)_Obstacle->getChildByName("Sprite_0");
    for (int i = 1; _body != NULL; i++) {
        sprintf(sprite, "Sprite_%d", i);
        _body = (cocos2d::Sprite *)_Obstacle->getChildByName(sprite);
        num++;
    }
    for (int i = 0; i<num; i++){
        sprintf(sprite, "Sprite_%d", i);
        _body = (cocos2d::Sprite *)_Obstacle->getChildByName(sprite);
        CreateCollision();
    }
}
void CObstacle::CreateCollision(){
	b2Body * _Cbody;
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody;
    bodyDef.userData = _body;
    bodyDef.position.Set(_body->getPosition().x / PTM_RATIO, _body->getPosition().y / PTM_RATIO);;
	_Cbody = _b2World->CreateBody(&bodyDef);
    Point loc = _Obstacle->getPosition();
    Size ts = _body->getContentSize();
    b2PolygonShape rectShape;
    float scaleX = _body->getScaleX();    // §Ù•≠™∫Ωu¨qπœ•‹∞≤≥]≥£•u¶≥πÔ X ∂b©Ò§j
    float scaleY = _body->getScaleY();    // §Ù•≠™∫Ωu¨qπœ•‹∞≤≥]≥£•u¶≥πÔ X ∂b©Ò§j
    
    Point lep[4], wep[4];
    lep[0].x = (ts.width) / 2.0f;  lep[0].y = (ts.height-80) / 2.0f;
    lep[1].x = -(ts.width) / 2.0f; lep[1].y = (ts.height-80) / 2.0f;
    lep[2].x = -(ts.width) / 2.0f; lep[2].y = -(ts.height-80) / 2.0f;
    lep[3].x = (ts.width) / 2.0f;  lep[3].y = -(ts.height-80) / 2.0f;
    
    cocos2d::Mat4 modelMatrix, rotMatrix;
    modelMatrix.m[0] = scaleX;  // •˝≥]©w X ∂b™∫¡Y©Ò
    modelMatrix.m[5] = scaleY;  // •˝≥]©w Y ∂b™∫¡Y©Ò
    cocos2d::Mat4::createRotationZ(0 * M_PI / 180.0f, &rotMatrix);
    modelMatrix.multiply(rotMatrix);
    modelMatrix.m[3] = /*PntLoc.x + */loc.x; //≥]©w Translation°A¶€§v™∫•[§W§˜øÀ™∫
    modelMatrix.m[7] = /*PntLoc.y + */loc.y; //≥]©w Translation°A¶€§v™∫•[§W§˜øÀ™∫
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
	if (_body->getTag() == 1)
		fixtureDef.isSensor = true;
	_Cbody->CreateFixture(&fixtureDef);
	ObstacleBody.push_back(_Cbody);
}
void CObstacle::Setpos(float x, float y) {
    for (int i = 0; i<num; i++){
        ObstacleBody[i]->SetTransform(b2Vec2(x / PTM_RATIO, y / PTM_RATIO), 0);
    }
}
void CObstacle::MoveBy(float x, float y) {
    for (int i = 0; i<num; i++){
        ObstacleBody[i]->SetTransform(b2Vec2(ObstacleBody[i]->GetPosition().x + x / PTM_RATIO, ObstacleBody[i]->GetPosition().y + y / PTM_RATIO), 0);
    }
}
Point CObstacle::Getpos() {
	Point pos;
    pos.x = ObstacleBody[0]->GetPosition().x * PTM_RATIO;
    pos.y = ObstacleBody[0]->GetPosition().y * PTM_RATIO;
	return (pos);
}
