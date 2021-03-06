#include "CPlayer.h"
#define PTM_RATIO 32.0f
USING_NS_CC;

// on "init" you need to initialize your instance
CPlayer::~CPlayer(){
    SimpleAudioEngine::getInstance()->unloadEffect("game_run.mp3");
    SimpleAudioEngine::getInstance()->unloadEffect("game_jump.mp3");
    SimpleAudioEngine::getInstance()->unloadEffect("game_slip.mp3");
}
CPlayer::CPlayer(b2World* _b2W, Vec2 pos)
{
    // 預先載入音效檔
    SimpleAudioEngine::getInstance()->preloadEffect("game_run.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("game_jump.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("game_slip.mp3");
    _MusicRun = SimpleAudioEngine::getInstance()->playEffect("game_run.mp3",1);
    //圖片
    _pt = pos;
    _Player = CSLoader::createNode("Ani/Player.csb");
    _Player->setPosition(_pt);
	this->addChild(_Player, 1);
    _PlayerAni = (ActionTimeline *)CSLoader::createTimeline("Ani/Player.csb");
    _Player->runAction(_PlayerAni);
	_PlayerSprite = (cocos2d::Sprite *)_Player->getChildByName("bo");
    //box2d
    _b2World = _b2W;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.userData = _PlayerSprite;
    _PlayerBody = _b2World->CreateBody(&bodyDef);
    _PlayerBody->SetSleepingAllowed(false);
    _PlayerAni->gotoFrameAndPlay(0, 30, true);
    _PlayerAni->setTimeSpeed(1.2f);
    CreateCollision();
}
void CPlayer::dostep(){
    if(_PlayerAni->getCurrentFrame()>30)CreateCollision(); //跑步時不換碰撞
    _Player->setPosition(_pt.x, _pt.y + _PlayerBody->GetPosition().y*PTM_RATIO);
    _PlayerBody->SetTransform(b2Vec2(0, _PlayerBody->GetPosition().y), 0); //固定player的x座標
    //CCLOG("%f , %f",_PlayerBody->GetPosition().x, _Player->getPosition().x);
}
void CPlayer::CreateCollision(){
    if(_PlayerBody->GetFixtureList()!=NULL)
        _PlayerBody->DestroyFixture(_PlayerBody->GetFixtureList());
    Point loc = _pt + _PlayerSprite->getPosition();
    Size ts = _PlayerSprite->getContentSize();
    b2PolygonShape rectShape;
    float angle = _PlayerSprite->getRotation();
    float scaleX = _PlayerSprite->getScaleX();
    float scaleY = _PlayerSprite->getScaleY();
    Point lep[4], wep[4];
    if(_bAttack){
        lep[0].x = (ts.width) / 2.0f;  lep[0].y = (ts.height-50) / 2.0f;
        lep[1].x = -(ts.width) / 2.0f; lep[1].y = (ts.height-50) / 2.0f;
        lep[2].x = -(ts.width) / 2.0f; lep[2].y = -(ts.height-50) / 2.0f;
        lep[3].x = (ts.width) / 2.0f;  lep[3].y = -(ts.height-50) / 2.0f;}
    else{
        lep[0].x = (ts.width-80) / 2.0f;  lep[0].y = (ts.height) / 2.0f;
        lep[1].x = -(ts.width-80) / 2.0f; lep[1].y = (ts.height) / 2.0f;
        lep[2].x = -(ts.width-80) / 2.0f; lep[2].y = -(ts.height) / 2.0f;
        lep[3].x = (ts.width-80) / 2.0f;  lep[3].y = -(ts.height) / 2.0f;
    }
    cocos2d::Mat4 modelMatrix, rotMatrix;
    modelMatrix.m[0] = scaleX;
    modelMatrix.m[5] = scaleY;
    cocos2d::Mat4::createRotationZ(angle * M_PI / 180.0f, &rotMatrix);
    modelMatrix.multiply(rotMatrix);
    modelMatrix.m[3] = /*PntLoc.x + */loc.x;
    modelMatrix.m[7] = /*PntLoc.y + */loc.y;
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
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    _PlayerBody->CreateFixture(&fixtureDef);
    _PlayerBody->SetFixedRotation(1);
}
//動作
void CPlayer::RunAct() {
    if(_PlayerAni->getCurrentFrame()>30){
        _bAttack = false;
        SimpleAudioEngine::getInstance()->resumeEffect(_MusicRun);
        _PlayerAni->gotoFrameAndPlay(0, 30, true);
        _PlayerAni->setTimeSpeed(1.2f);
        CreateCollision();
    }
}
void CPlayer::JumpAct(){
    if(_PlayerAni->getCurrentFrame()<=30){
        _bAttack = false;
        SimpleAudioEngine::getInstance()->pauseEffect(_MusicRun);
        SimpleAudioEngine::getInstance()->playEffect("game_jump.mp3",0,1,0,0.3f); //音量0.3倍
        _PlayerAni->gotoFrameAndPlay(31, 55, false);
        _PlayerAni->setTimeSpeed(1.0f);
        _PlayerBody->SetLinearVelocity(b2Vec2(0,60));
    }
}
void CPlayer::SlipAct(){
    _bAttack = false;
    SimpleAudioEngine::getInstance()->pauseEffect(_MusicRun);
    SimpleAudioEngine::getInstance()->playEffect("game_slip.mp3",0);
    _PlayerAni->gotoFrameAndPlay(56, 64, true);
    _PlayerAni->setTimeSpeed(1.0f);
}
void CPlayer::AttackAct(){
    _bAttack = true;
    SimpleAudioEngine::getInstance()->pauseEffect(_MusicRun);
    _PlayerAni->gotoFrameAndPlay(65, 75, true);
    _PlayerAni->setTimeSpeed(1.0f);
    _PlayerBody->SetLinearVelocity(b2Vec2(0,-50));
}
void CPlayer::TensionAct(){
    _bAttack = false;
    _PlayerAni->gotoFrameAndPlay(76, 100, true);
    _PlayerAni->setTimeSpeed(1.0f);
}
void CPlayer::AniPause(){
    SimpleAudioEngine::getInstance()->pauseEffect(_MusicRun);
    _PlayerAni->pause();
}
void CPlayer::AniResume(){
    SimpleAudioEngine::getInstance()->resumeEffect(_MusicRun);
    _PlayerAni->resume();
}
Point CPlayer::GetPos(){
    return _Player->getPosition();
}
Sprite *CPlayer::GetSprite(){
    return _PlayerSprite;
}
b2Body *CPlayer::GetBody(){
    return _PlayerBody;
}
