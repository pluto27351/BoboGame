#include "CNumberPannel.h"

USING_NS_CC;

Vec3 CNumberPannel::getBoxAns(){
    return(Vec3(_answerNumber[0],_answerNumber[1],_answerNumber[2]));
}

void CNumberPannel::setNumberInfo(const cocos2d::Point locPt, int level){
    char name[20] = "";
    _triggerBtn.setButtonInfo("s_menuOn.png", "s_menuDown.png", *this, locPt - Vec2(140,0), level);
    _triggerBtn.setScale(1.705);
    for(int i = 0; i < 3; i++){
        sprintf(name, "bb_no%02d.png", i + 1);
        _number[i].setButtonInfo(name, name, *this, locPt + Vec2(140 * i, 0), level);
    }
    _bShowNumber = false;
    _bMoveNumber = false;
    _answerNumber[0] = _answerNumber[1] = _answerNumber[2] = 0;
    setNumberVisual(_bShowNumber);
}

void CNumberPannel::setAnswerInfo(Node *root){
    char name[20] = "";
    
    for(int i=0;i<3;i++){
        sprintf(name, "F_%02d",i);
        auto btn = root->getChildByName(name);
        Vec2 rootPos = root->getPosition();
        Vec2 pos = btn->getPosition();
        
        float sx =btn->getScaleX();
        float sy =btn->getScaleY();
        _answerArea[i] = (Sprite *)Sprite::createWithSpriteFrameName("w_bg.png");
        _answerArea[i]->setPosition(rootPos + pos);
        _answerArea[i]->setScaleX(sx);
        _answerArea[i]->setScaleY(sy);
        auto size =_answerArea[i]->getContentSize();
        size.width *= sx;
        size.height *= sy;
        _answerAreaRect[i].size = size;
        _answerAreaRect[i].origin.x = rootPos.x + pos.x - size.width * 0.5f;
        _answerAreaRect[i].origin.y = rootPos.y + pos.y - size.height * 0.5f;
        
        root->removeChild(btn);
        addChild(_answerArea[i],1);
        
    }
    _answerBg = _answerArea[0]->getDisplayFrame();
}

void CNumberPannel::setNumberVisual(bool s){
    for(int i = 0; i < 3 ; i++) _number[i].setVisible(s);
}

void CNumberPannel::setTouchedPic(int nowNumber,Point pos){
    _nowNumber = nowNumber;
    
    char name[20] = "";
    sprintf(name, "bb_no%02d.png",_nowNumber);
    _touchedPic = (Sprite *)Sprite::createWithSpriteFrameName(name);
    _touchedPic->setPosition(pos);
    addChild(_touchedPic,1);
    _bMoveNumber = true;
}

bool CNumberPannel::touchesBegin(cocos2d::Point inPos){
    if(_triggerBtn.touchesBegin(inPos))return true;
    
    if(_bShowNumber){
        for(int i=0;i<3;i++){
            if(_number[i].touchesBegin(inPos)){
                if(!_bMoveNumber) setTouchedPic(i+1,inPos);
                return true;
            }
        }
    }
    
    //答案區
    for(int i=0;i<3;i++){
        if(_answerAreaRect[i].containsPoint(inPos)){
            if(_answerNumber[i] != 0 && !_bMoveNumber){
                setTouchedPic(_answerNumber[i],inPos);
                _answerArea[i]->setDisplayFrame(_answerBg);
                _answerNumber[i] = 0;
                return true;
            }
        }
    }
    
    
    return false;
}

bool CNumberPannel::touchesMoved(cocos2d::Point inPos){
    if(_bMoveNumber){
        _touchedPic->setPosition(inPos);
        return true;
    }
    
    if(_triggerBtn.touchesMoved(inPos))return true;
    for(int i=0;i<3;i++){
        if(_number[i].touchesMoved(inPos))return true;
    }
    
    return false;
}

bool CNumberPannel::touchesEnded(cocos2d::Point inPos){
    if(_bMoveNumber){
        for(int i =0;i<3;i++){
            if(_answerAreaRect[i].containsPoint(inPos)){
                _answerNumber[i] = _nowNumber;
                _answerArea[i]->setDisplayFrame(_touchedPic->getDisplayFrame());
            }
        }
        _bMoveNumber =false;
        removeChild(_touchedPic);
    }
    
    if(_triggerBtn.touchesEnded(inPos)){
        _bShowNumber = !_bShowNumber;
        setNumberVisual(_bShowNumber);
        return true;
    }
    
    for(int i=0;i<3;i++){
        if(_number[i].touchesEnded(inPos))return true;
    }
    
    return false;
}
