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

}
CPlayer::CPlayer(Color3B color, Color3B color2)
{
	//圖片
	pt = Vec2(154.5, 350);
	_Player = CSLoader::createNode("Ani/Runner.csb");
	_Player->setPosition(pt);
	_Player->setScale(-0.88, 0.88);
	Sprite *_body = (cocos2d::Sprite *)_Player->getChildByName("body");
	Sprite *_mouth = (cocos2d::Sprite *)_Player->getChildByName("Normal")->getChildByName("mouth");
	_body->setColor(color);
	_mouth->setColor(color);

	this->addChild(_Player);

	_PlayerAni = (ActionTimeline *)CSLoader::createTimeline("Ani/Runner.csb");
	_Player->runAction(_PlayerAni);
	
}

//void CPlayer::start() {
//	_PlayerAni->gotoFrameAndPlay(0, 24, true);
//}



////跳躍動作
//void CPlayer::JumpAct() {
//	_Player->stopActionByTag(1);
//	JumpFlag = true;
//
//	Sequence *sequence;
//	JumpTo *jumpAction = cocos2d::JumpTo::create(0.6f, pt, 200, 1);
//	CallFunc *callback = CallFunc::create(this, callfunc_selector(CPlayer::JumpFlagChange));
//	if (JumpTime == 0) {
//		sequence = Sequence::create(jumpAction, callback, NULL);
//	}
//	else {
//		RotateBy *rotateto = RotateBy::create(0.6f, 360.0f);
//		Spawn *spawn = Spawn::createWithTwoActions(jumpAction, rotateto);
//		sequence = Sequence::create(spawn, callback, NULL);
//	}
//
//	sequence->setTag(1);
//	JumpTime += 1;
//
//	_Player->runAction(sequence);
//}

////避免多重觸碰
//void CPlayer::JumpFlagChange() {
//	//JumpFlag = false;
//	JumpTime = 0;
//}



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



