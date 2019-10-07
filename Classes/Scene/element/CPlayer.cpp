#include "CPlayer.h"
#define PTM_RATIO 32.0f

USING_NS_CC;

// on "init" you need to initialize your instance
CPlayer::~CPlayer(){}
CPlayer::CPlayer(b2World* _b2W, Vec2 pos)
{
    //圖片
    pt = pos;
    _Player = CSLoader::createNode("Ani/Player.csb");
    _Player->setPosition(pt);
	this->addChild(_Player, 1);
    _PlayerAni = (ActionTimeline *)CSLoader::createTimeline("Ani/Player.csb");
    _Player->runAction(_PlayerAni);
	_body = (cocos2d::Sprite *)_Player->getChildByName("bo");
    //box2d
    _b2World = _b2W;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = _body;
    PlayerBody = _b2World->CreateBody(&bodyDef);
    CreateCollision();
    _PlayerAni->gotoFrameAndPlay(0, 30, true);
    _PlayerAni->setTimeSpeed(1.2f);
}
void CPlayer::dostep(){
    CreateCollision();
    _Player->setPosition(pt.x + PlayerBody->GetPosition().x*PTM_RATIO, pt.y + PlayerBody->GetPosition().y*PTM_RATIO);
}
void CPlayer::CreateCollision(){
    if(PlayerBody->GetFixtureList()!=NULL)
        PlayerBody->DestroyFixture(PlayerBody->GetFixtureList());
    Point loc = pt + _body->getPosition();
    Size ts = _body->getContentSize();
    b2PolygonShape rectShape;
    float angle = _body->getRotation();
    float scaleX = _body->getScaleX();    // §Ù•≠™∫Ωu¨qπœ•‹∞≤≥]≥£•u¶≥πÔ X ∂b©Ò§j
    float scaleY = _body->getScaleY();    // §Ù•≠™∫Ωu¨qπœ•‹∞≤≥]≥£•u¶≥πÔ X ∂b©Ò§j
    
    Point lep[4], wep[4];
    lep[0].x = (ts.width-80) / 2.0f;  lep[0].y = (ts.height) / 2.0f;
    lep[1].x = -(ts.width-80) / 2.0f; lep[1].y = (ts.height) / 2.0f;
    lep[2].x = -(ts.width-80) / 2.0f; lep[2].y = -(ts.height) / 2.0f;
    lep[3].x = (ts.width-80) / 2.0f;  lep[3].y = -(ts.height) / 2.0f;
    
    cocos2d::Mat4 modelMatrix, rotMatrix;
    modelMatrix.m[0] = scaleX;  // •˝≥]©w X ∂b™∫¡Y©Ò
    modelMatrix.m[5] = scaleY;  // •˝≥]©w Y ∂b™∫¡Y©Ò
    cocos2d::Mat4::createRotationZ(angle * M_PI / 180.0f, &rotMatrix);
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
    fixtureDef.density = 0.1f;
    fixtureDef.friction = 0.0f;
    PlayerBody->CreateFixture(&fixtureDef);
    PlayerBody->SetFixedRotation(1);
}
//動作
void CPlayer::RunAct() {
    if(_PlayerAni->getCurrentFrame()>30){
        _PlayerAni->gotoFrameAndPlay(0, 30, true);
        _PlayerAni->setTimeSpeed(1.2f);
        PlayerBody->SetLinearVelocity(b2Vec2(0,0));
    }
}
void CPlayer::JumpAct(){
    if(_PlayerAni->getCurrentFrame()<=30){
        _PlayerAni->gotoFrameAndPlay(31, 55, false);
        _PlayerAni->setTimeSpeed(1.0f);
        PlayerBody->SetLinearVelocity(b2Vec2(0,58));
    }
}
void CPlayer::SlipAct(){
    _PlayerAni->gotoFrameAndPlay(56, 64, true);
    _PlayerAni->setTimeSpeed(1.0f);
}
void CPlayer::AttackAct(){
    _PlayerAni->gotoFrameAndPlay(65, 75, true);
    _PlayerAni->setTimeSpeed(1.0f);
    PlayerBody->SetLinearVelocity(b2Vec2(0,-35));
}
void CPlayer::TensionAct(){
    _PlayerAni->gotoFrameAndPlay(76, 100, true);
    _PlayerAni->setTimeSpeed(1.0f);
}
void CPlayer::AniPause(){
    _PlayerAni->pause();
}
void CPlayer::AniResume(){
    _PlayerAni->resume();
}
Point CPlayer::GetPos(){
    return(_Player->getPosition());
}
