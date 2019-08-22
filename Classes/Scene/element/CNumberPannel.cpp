#include "CNumberPannel.h"

USING_NS_CC;

Vec3 CNumberPannel::getBoxAns(){
    int f,d,n; //帶．母．子
    if(_answerNumber[0] == -1) _answerNumber[0] = 0;
    if(_answerNumber[1] == -1) _answerNumber[1] = 0;
    if(_answerNumber[3] == -1) _answerNumber[3] = 0;
    
    if(_answerNumber[0] != -1 )f = _answerNumber[0];
    else f = 0;
    if(_answerNumber[2] != -1 )d = _answerNumber[1]*10 + _answerNumber[2];
    else d = _answerNumber[1];
    if(_answerNumber[4] != -1 )n = _answerNumber[3]*10 + _answerNumber[4];
    else n = _answerNumber[3];
    
//    for(int i=0;i<5;i++)CCLOG("%d = %d",i,_answerNumber[i]);
//
//    CCLOG("%d,%d,%d",f,d,n);
    return(Vec3(f,d,n));
}

void CNumberPannel::setNumberInfo(const cocos2d::Point locPt, int level){
    char name[20] = "";
    char nn[5] = "";
    _triggerBtn.setButtonInfo("teach_btn_number.png", "teach_btn_number.png", *this, locPt, level);
    Node *numbox = CSLoader::createNode("Ani/t_number.csb");
    for(int i = 0; i < 10; i++){
        sprintf(name, "teach_number_%d.png", i);
        sprintf(nn, "%d", i);
        auto pos = numbox->getChildByName(nn)->getPosition();
        _number[i].setButtonInfo(name, name, *this, locPt + pos+ Vec2(220,50), level);
    }
    _numberbg = (Sprite *)Sprite::createWithSpriteFrameName("teach_number_bg.png");
    _numberbg->setPosition(locPt + Vec2(220,50));
    addChild(_numberbg,0);
    
    _bShowNumber = false;
    _bMoveNumber = false;
    for(int i=0;i<5;i++)_answerNumber[i] = -1;
    
    setNumberVisual(_bShowNumber);
}

void CNumberPannel::clear(){
    _bShowNumber = false;
    setNumberVisual(_bShowNumber);
    _triggerBtn.setEnabled(true);
    
    for(int i=0; i<5; i++){
        _answerArea[i]->setDisplayFrame(_answerBg);
        _answerArea[i]->setScaleX(_ansAreaSize.x);
        _answerArea[i]->setScaleY(_ansAreaSize.y);
        _answerNumber[i] = -1;
        _answerArea[i]->setOpacity(0);
      //  CCLOG("init %d = %d", i,_answerNumber[i] );
    }
    
    _bShowNumber = false;
    _bMoveNumber = false;
}


void CNumberPannel::setAnswerInfo(Node *root){
    char name[20] = "";
    Vec2 rootPos = root->getPosition();
    
    for(int i=0;i<5;i++){
        if(i == 0)sprintf(name, "F_0%d",i+1);
        else if(i < 3)sprintf(name, "F_1%d",i);
        else sprintf(name, "F_2%d",i-2);
        
        auto btn = root->getChildByName(name);
        
        Vec2 pos = btn->getPosition();
        
        _ansAreaSize.x =btn->getScaleX();
        _ansAreaSize.y =btn->getScaleY();
        _answerArea[i] = (Sprite *)Sprite::createWithSpriteFrameName("ans_area.png");
        _answerArea[i]->setPosition(rootPos + pos);
        _answerArea[i]->setScaleX(_ansAreaSize.x);
        _answerArea[i]->setScaleY(_ansAreaSize.y);
        _answerArea[i]->setOpacity(0);
        
        root->removeChild(btn);
        addChild(_answerArea[i],1);
        
    }
    _answerBg = _answerArea[0]->getDisplayFrame();
    
    _ansX[0] = _answerArea[1]->getPositionX();
    _ansX[1] = _answerArea[2]->getPositionX();
    _ansX[2] = (_ansX[0] + _ansX[1])/2;
    
    for(int i=0;i<3;i++){
        sprintf(name, "area_%d",i);
        Node* area = root->getChildByName(name);
        Vec2 size = area->getContentSize();
        Point pos = area->getPosition();
        size.x *= area->getScaleX();
        _answerAreaRect[i].size = size;
        _answerAreaRect[i].origin = rootPos + pos - size * 0.5f;
        root->removeChildByName(name);
    }
}

void CNumberPannel::setNumberVisual(bool s){
    for(int i = 0; i < 10; i++) _number[i].setVisible(s);
    _numberbg->setVisible(s);
}

void CNumberPannel::setTouchedPic(int nowNumber,Point pos){
    _nowNumber = nowNumber;
    
    char name[20] = "";
    sprintf(name, "teach_number_%d.png",_nowNumber);
    _touchedPic = (Sprite *)Sprite::createWithSpriteFrameName(name);
    _touchedPic->setPosition(pos);
    _touchedPic->setScale(1.3f);
    addChild(_touchedPic,1);
    _bMoveNumber = true;
}

bool CNumberPannel::touchesBegin(cocos2d::Point inPos){
    if(_triggerBtn.touchesBegin(inPos))return true;
    
    if(_bShowNumber){
        for(int i=0;i<10;i++){
            if(_number[i].touchesBegin(inPos)){
                if(!_bMoveNumber) setTouchedPic(i,inPos);
                return true;
            }
        }
    }
    
    //答案區
    for(int i=0;i<3;i++){
        if(_answerAreaRect[i].containsPoint(inPos) && !_bMoveNumber){
            int target = i;
            if(i != 0){
                int k = i*2;
                if(_answerNumber[k-1] == -1) target = k;
                else {
                    if(inPos.x < _ansX[2])target = k-1;
                    else target = k;
                }
            }
            if(_answerNumber[target] != -1 ){
                setTouchedPic(_answerNumber[target],inPos);
                _answerArea[target]->setDisplayFrame(_answerBg);
                _answerArea[target]->setScaleX(_ansAreaSize.x);
                _answerArea[target]->setScaleY(_ansAreaSize.y);
                _answerArea[target]->setOpacity(0);
                _answerNumber[target] = -1;
                resortAns();
                return true;
            }
        }
    }
    
    
    return false;
}

bool CNumberPannel::touchesMoved(cocos2d::Point inPos){
    if(_bMoveNumber){
        _touchedPic->setPosition(inPos);
        int k = ansAreaHover(inPos);
         if(k != -1)_answerArea[k]->setOpacity(100);
        return true;
    }
    
    if(_triggerBtn.touchesMoved(inPos))return true;
    for(int i=0;i<10;i++){
        if(_number[i].touchesMoved(inPos))return true;
    }
    
    return false;
}

bool CNumberPannel::touchesEnded(cocos2d::Point inPos){
    if(_bMoveNumber){
        int k = ansAreaHover(inPos);
        if(k != -1){
             _answerNumber[k] = _nowNumber;
            _answerArea[k]->setDisplayFrame(_touchedPic->getDisplayFrame());
            _answerArea[k]->setOpacity(255);
            _answerArea[k]->setScale(1.3f);
        }
    
        _bMoveNumber =false;
        removeChild(_touchedPic);
    }
    
    if(_triggerBtn.touchesEnded(inPos)){
        _bShowNumber = !_bShowNumber;
        setNumberVisual(_bShowNumber);
        return true;
    }
    
    for(int i=0;i<10;i++){
        if(_number[i].touchesEnded(inPos))return true;
    }
    
    return false;
}

int CNumberPannel::ansAreaHover(Point inPos){
    resortAns();
    for(int i=0;i<5;i++){
        if(_answerNumber[i] == -1){
            _answerArea[i]->setOpacity(0);
            _answerArea[i]->setScale(1);
        }
        else {
            _answerArea[i]->setOpacity(255);
            _answerArea[i]->setScale(1.3f);
        }
    }
    
    for(int i=0;i<3;i++){
        if(_answerAreaRect[i].containsPoint(inPos)){
            int n = i*2;
            if(i == 0){ return 0; }
            else if(_answerNumber[n-1] == -1){
                if(_answerNumber[n] == -1) { return n; }
                else {
                    if(inPos.x < _ansX[2] - 20){
                        _answerArea[n]->setPositionX(_ansX[1]);
                        _answerArea[n-1]->setPositionX(_ansX[0]);
                        return n-1;
                    }else if(inPos.x > _ansX[2] + 20){
                        _answerArea[n]->setPositionX(_ansX[1]);
                        _answerArea[n-1]->setPositionX(_ansX[0]);
                        _answerNumber[n-1] = _answerNumber[n];
                        _answerArea[n-1]->setDisplayFrame(_answerArea[n]->getDisplayFrame());
                        _answerArea[n-1]->setOpacity(255);
                        _answerArea[n-1]->setScale(1.3f);
                        _answerNumber[n] = -1;
                        _answerArea[n]->setDisplayFrame(_answerBg);
                        _answerArea[n]->setScale(1);
                        return n;
                    }else {
                        _answerArea[n]->setPositionX(_ansX[2]);
                        return n;
                    }
                }
            }else {
                if(inPos.x < _ansX[2]){ return n-1; }
                else{ return n; }
            }
        }
    }
    return -1;
}

void CNumberPannel::resortAns(){
    for(int i=1;i<3;i++){
        int k = i*2;
        if(_answerNumber[k-1] != -1 && _answerNumber[k] == -1){
            _answerNumber[k] = _answerNumber[k-1];
            _answerArea[k]->setDisplayFrame(_answerArea[k-1]->getDisplayFrame());
            _answerArea[k]->setOpacity(255);
            _answerArea[k]->setScale(1.3f);
            _answerNumber[k-1] = -1;
            _answerArea[k-1]->setDisplayFrame(_answerBg);
            _answerArea[k-1]->setScale(1);
        }
        
        if(_answerNumber[k-1] == -1){
            _answerArea[k-1]->setPositionX(_ansX[2]);
            _answerArea[k]->setPositionX(_ansX[2]);
        }else{
            _answerArea[k-1]->setPositionX(_ansX[0]);
            _answerArea[k]->setPositionX(_ansX[1]);
        }
    }
}
