#include "CObstacle.h"
#define PTM_RATIO 32.0f

USING_NS_CC;

// on "init" you need to initialize your instance
CObstacle::~CObstacle()
{
}
CObstacle::CObstacle(b2World* _b2W, int L)
{
    //圖片
    Point Pt;
    Pt = Vec2(250, 0);
    //_Obstacle = CSLoader::createNode("Obstacle.csb");
    char level[9];
    char name[4];
    sprintf(level, "Level_%d", L);
    int num = rand()%2;
    sprintf(name, "%d", num);
    _Obstacle = CSLoader::createNode("Obstacle.csb")->getChildByName(level)->getChildByName(name);
    _Obstacle->setPosition(Pt);
    this->addChild(_Obstacle);
    _body = (cocos2d::Sprite *)_Obstacle;
    
    //box2d
    _b2World = _b2W;
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.userData = NULL;
    Obstacleody = _b2World->CreateBody(&bodyDef);
    CreateCollision();
}
void CObstacle::CreateCollision(){
    if(Obstacleody->GetFixtureList()!=NULL)
        Obstacleody->DestroyFixture(Obstacleody->GetFixtureList());
    Point loc = _Obstacle->getPosition();
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
    fixtureDef.restitution = 0.5f;
    fixtureDef.density = 0.1f;
    fixtureDef.friction = 0.15f;
    Obstacleody->CreateFixture(&fixtureDef);
}
