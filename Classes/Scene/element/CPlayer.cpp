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
    _Player->setScale(0.8, 0.8);
    this->addChild(_Player);
    _PlayerAni = (ActionTimeline *)CSLoader::createTimeline("Ani/Player.csb");
    _Player->runAction(_PlayerAni);
}
CPlayer::CPlayer(Color3B color, Color3B color2)
{
}

//void CPlayer::start() {
//	_PlayerAni->gotoFrameAndPlay(0, 24, true);
//}

//跑步動作
void CPlayer::RunAct() {
    _Player->setPosition(pt);
    Sprite *_body = (cocos2d::Sprite *)_Player->getChildByName("Jump");
    _body->setVisible(false);
    _body = (cocos2d::Sprite *)_Player->getChildByName("Slip");
    _body->setVisible(false);
    _body = (cocos2d::Sprite *)_Player->getChildByName("Attack");
    _body->setVisible(false);
    _body = (cocos2d::Sprite *)_Player->getChildByName("Tension");
    _body->setVisible(false);
    _body = (cocos2d::Sprite *)_Player->getChildByName("Run");
    _body->setVisible(true);
    _PlayerAni->gotoFrameAndPlay(0, 30, true);
}
void CPlayer::JumpAct(){
    if(JumpTime == 0 && ActFlag == true){
        Sprite *_body = (cocos2d::Sprite *)_Player->getChildByName("Run");
        _body->setVisible(false);
        _body = (cocos2d::Sprite *)_Player->getChildByName("Jump");
        _body->setVisible(true);
        jumpAction = cocos2d::JumpTo::create(1.0f, pt, 300, 1);
        Sequence *sequence;
        CallFunc *callback = CallFunc::create(this, callfunc_selector(CPlayer::ActionEnd));
        _PlayerAni->gotoFrameAndPlay(0, 24, false);
        sequence = Sequence::create(jumpAction, callback, NULL);
        _Player->runAction(sequence);
        ActFlag = false;
        JumpTime = 1;
    }
}
void CPlayer::SlipAct(){
    if(ActFlag == true){
        Sprite *_body = (cocos2d::Sprite *)_Player->getChildByName("Run");
        _body->setVisible(false);
        _body = (cocos2d::Sprite *)_Player->getChildByName("Slip");
        _body->setVisible(true);
        _PlayerAni->gotoFrameAndPlay(0, 5, true);
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
    Sprite *_body = (cocos2d::Sprite *)_Player->getChildByName("Run");
    _body->setVisible(false);
    _body = (cocos2d::Sprite *)_Player->getChildByName("Jump");
    _body->setVisible(false);
    _body = (cocos2d::Sprite *)_Player->getChildByName("Attack");
    _body->setVisible(true);
    _PlayerAni->gotoFrameAndPlay(0, 5, false);
    MoveTo *AttackAction = cocos2d::MoveTo::create(0.3f, Vec2(pt));
    Sequence *sequence;
    CallFunc *callback = CallFunc::create(this, callfunc_selector(CPlayer::ActionEnd));
    sequence = Sequence::create(AttackAction, callback, NULL);
    _Player->runAction(sequence);
    JumpTime = 2;
}
void CPlayer::TensionAct(){
    Sprite *_body = (cocos2d::Sprite *)_Player->getChildByName("Run");
    _body->setVisible(false);
    _body = (cocos2d::Sprite *)_Player->getChildByName("Tension");
    _body->setVisible(true);
    _PlayerAni->gotoFrameAndPlay(0, 24, true);
}

//避免多重觸碰
void CPlayer::ActionEnd() {
	ActFlag = true;
    JumpTime = 0;
    RunAct();
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



