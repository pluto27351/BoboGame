#include "CPlayer.h"
//#include "cocostudio/CocoStudio.h"
//#include "ui/CocosGUI.h"
//#include "CBullet.h"

USING_NS_CC;

//using namespace cocostudio::timeline;
//using namespace ui;
//using namespace CocosDenshion;

// on "init" you need to initialize your instance
CPlayer::~CPlayer()
{
	
}
CPlayer::CPlayer()
{
    //圖片
    pt = Vec2(190, 245);
    _Player = CSLoader::createNode("Ani/Player.csb");
    _Player->setPosition(pt);
    _Player->setScale(0.8f);
    this->addChild(_Player);
    _PlayerAni = (ActionTimeline *)CSLoader::createTimeline("Ani/Player.csb");
    _Player->runAction(_PlayerAni);
	_body = (cocos2d::Sprite *)_Player->getChildByName("bo");
}
CPlayer::CPlayer(Color3B color, Color3B color2)
{
}

//void CPlayer::start() {
//	_PlayerAni->gotoFrameAndPlay(0, 24, true);
//}

//跑步動作
void CPlayer::RunAct() {
    _PlayerAni->gotoFrameAndPlay(0, 30, true);
}
void CPlayer::JumpAct(){
    if(JumpTime == 0 && ActFlag == true){
		jumpAction = cocos2d::JumpTo::create(1.0f, pt, 0, 1);
        Sequence *sequence;
        CallFunc *callback = CallFunc::create(this, callfunc_selector(CPlayer::ActionEnd));
        _PlayerAni->gotoFrameAndPlay(31, 55, false);
        sequence = Sequence::create(jumpAction, callback, NULL);
        _Player->runAction(sequence);
        ActFlag = false;
        JumpTime = 1;
    }
}
void CPlayer::SlipAct(){
    if(ActFlag == true){
        _PlayerAni->gotoFrameAndPlay(56, 61, true);
        MoveBy *slipAction = cocos2d::MoveBy::create(0.5f, Vec2(0, 0));
        Sequence *sequence;
        CallFunc *callback = CallFunc::create(this, callfunc_selector(CPlayer::ActionEnd));
        sequence = Sequence::create(slipAction, callback, NULL);
        _Player->runAction(sequence);
        ActFlag = false;
    }
    else if(JumpTime == 1)
        AttackAct();
}
void CPlayer::AttackAct(){
    _Player->stopActionByTag(jumpAction->getTag());
    _PlayerAni->gotoFrameAndPlay(62, 72, true);
    MoveTo *AttackAction = cocos2d::MoveTo::create(0.3f, Vec2(pt));
    Sequence *sequence;
    CallFunc *callback = CallFunc::create(this, callfunc_selector(CPlayer::ActionEnd));
    sequence = Sequence::create(AttackAction, callback, NULL);
    _Player->runAction(sequence);
    JumpTime = 2;
}
void CPlayer::TensionAct(){
    _PlayerAni->gotoFrameAndPlay(73, 97, true);
}

//避免多重觸碰
void CPlayer::ActionEnd() {
	ActFlag = true;
    JumpTime = 0;
    RunAct();
}

Point CPlayer::GetPos() {
	return(_Player->getPosition());
}
Size CPlayer::GetSize() {
	return(_body->getContentSize());
}
Vec2 CPlayer::GetScale() {
	return(Vec2(_body->getScaleX(), _body->getScaleY()));
}
//
//int CPlayer::jumpCollider(Point enemy) {
//	Rect colliderArea;
//	colliderArea = Rect(_Player->getPositionX() - 65, _Player->getPositionY() - 20,180, 120);
//	if (colliderArea.containsPoint(enemy)) return 2;  //失敗
//	else if (enemy.x < 140) return 1;  //成功
//	else return 0;									   //還有機會
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