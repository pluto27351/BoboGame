#include "CPlayer.h"
#define PTM_RATIO 32.0f

USING_NS_CC;

// on "init" you need to initialize your instance
CPlayer::~CPlayer(){}
CPlayer::CPlayer(b2World* _b2W)
{
    //圖片
    pt = Vec2(250, 600);
    _Player = CSLoader::createNode("Ani/Player.csb");
    _Player->setPosition(pt);
    this->addChild(_Player);
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
}
void CPlayer::dostep(){
    CreateCollision();
}
void CPlayer::CreateCollision(){
    if(PlayerBody->GetFixtureList()!=NULL)
        PlayerBody->DestroyFixture(PlayerBody->GetFixtureList());
    Point loc = _Player->getPosition();
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

//跑步動作
void CPlayer::RunAct() {
    if(_PlayerAni->getCurrentFrame()>30)
        _PlayerAni->gotoFrameAndPlay(0, 30, true);
}
void CPlayer::JumpAct(){
    if(_PlayerAni->getCurrentFrame()<30){
        _PlayerAni->gotoFrameAndPlay(31, 55, false);
        PlayerBody->ApplyForceToCenter(b2Vec2(0,13000), 0);
    }
}
void CPlayer::SlipAct(){
    _PlayerAni->gotoFrameAndPlay(56, 61, true);
    ActFlag = false;
}
void CPlayer::AttackAct(){
    _PlayerAni->gotoFrameAndPlay(62, 72, true);
    PlayerBody->ApplyForceToCenter(b2Vec2(0,-5000), 0);
}
void CPlayer::TensionAct(){
    _PlayerAni->gotoFrameAndPlay(73, 97, true);
}

//避免多重觸碰
//void CPlayer::ActionEnd() {
//    ActFlag = true;
//    JumpTime = 0;
//    RunAct();
//}

////停止動畫
//void CPlayer::actionControl(bool run) {
//	if (run) {
//		_Player->onEnter();
//	}
//	else {
//		_Player->onExit();
//	}
//	if (hasBullet) {
//		CBullet *b = _HeadBullet;
//		while (b != NULL) {
//			b->actionControl(run);
//			b = b->next;
//		}
//	}
//}
