#include "CButton.h"

USING_NS_CC;

void CButton::setButtonInfo(const char *normalImg, const char *touchedImg, Layer &parent, const cocos2d::Point locPt, int level)
{
    _normalPic = (Sprite *)Sprite::createWithSpriteFrameName(normalImg);
    _touchedPic = (Sprite *)Sprite::createWithSpriteFrameName(touchedImg);
    _BtnLoc = locPt;
    _normalPic->setPosition(_BtnLoc);
    _touchedPic->setPosition(_BtnLoc);
    _touchedPic->setVisible(false);
    _touchedPic->setScale(1.15f);
    parent.addChild(_normalPic, level);
    parent.addChild(_touchedPic, level);
    
    // ���o�j�p
    _BtnSize = _normalPic->getContentSize();
    // �]�w�P�_�ϰ�
    _BtnRect.size = _BtnSize;
    _BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
    _BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
    _bTouched = false;
    _ftouchedScale = 1.15f;
    _bVisible = _bEnabled = true;
}

void CButton::setButtonInfo(const char *normalImg, const char *touchedImg, const char *enabledImg, Layer &parent, const cocos2d::Point locPt, int level)
{
    _normalPic = (Sprite *)Sprite::createWithSpriteFrameName(normalImg);
    _touchedPic = (Sprite *)Sprite::createWithSpriteFrameName(touchedImg);
    _enabledPic =(Sprite *)Sprite::createWithSpriteFrameName(enabledImg);
    _BtnLoc = locPt;
    _normalPic->setPosition(_BtnLoc);
    _touchedPic->setPosition(_BtnLoc);
    _enabledPic->setPosition(_BtnLoc);
    _touchedPic->setVisible(false);
    _enabledPic->setVisible(false);
    _touchedPic->setScale(1.15f);
    parent.addChild(_normalPic, level);
    parent.addChild(_touchedPic, level);
    parent.addChild(_enabledPic, level);
    // ���o�j�p
    _BtnSize = _normalPic->getContentSize();
    // �]�w�P�_�ϰ�
    _BtnRect.size = _BtnSize;
    _BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
    _BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
    _bTouched = false;
    _ftouchedScale = 1.15f;
    _bVisible = _bEnabled = true;
}

bool CButton::touchesBegin(cocos2d::Point inPos)
{
    if (_BtnRect.containsPoint(inPos) && _bVisible && _bEnabled)
    {
        _bTouched = true;
        _normalPic->setVisible(false);
        _touchedPic->setVisible(true);
        return(true); // �����b�W��
    }
    return(false);
}

bool CButton::touchesMoved(cocos2d::Point inPos)
{
    if (_bTouched) { // �u���Q�����ɭԤ~�B�z
        if (!_BtnRect.containsPoint(inPos)) { // ����Y��m���}���s
            _bTouched = false;
            _normalPic->setVisible(true);
            _touchedPic->setVisible(false);
            return(false);
        }
        else return(true);
    }
    return(false); // �ƫ�A������s�W�N�Q����
}

bool CButton::touchesEnded(cocos2d::Point inPos)
{
    if (_bTouched)
    {
        _bTouched = false;
        _normalPic->setVisible(true);
        _touchedPic->setVisible(false);
        if (_BtnRect.containsPoint(inPos)) return(true);  // ����Y��m���s�ɡA�٦b�ӫ��s�W
    }
    return false;
}

void CButton::setTouched()
{
    _bTouched = true;
    _normalPic->setVisible(false);
    _touchedPic->setVisible(true);
}

void CButton::setVisible(bool bVisible)
{
    _bVisible = bVisible;
    if (!_bVisible) {
        _normalPic->setVisible(false);
        if(_enabledPic != NULL)_enabledPic->setVisible(false);
    }
    else {
        _normalPic->setVisible(true);
        if(_enabledPic != NULL)_enabledPic->setVisible(true);
    }
}


void CButton::setEnabled(bool bEnable)
{
    _bEnabled = bEnable;
    if(_enabledPic != NULL){
        if (_bEnabled) {
            _enabledPic->setVisible(false);
            _normalPic->setVisible(true);
        }
        else{
            _enabledPic->setVisible(true);
            _normalPic->setVisible(false);
        }
    }else{
        if (_bEnabled) _normalPic->setColor(Color3B(255, 255, 255));
        else _normalPic->setColor(Color3B(50, 50, 50));
    }
    
}


void CButton::setPosition(Vec2 locPt) {
    _BtnLoc = locPt;
    _normalPic->setPosition(_BtnLoc);
    _touchedPic->setPosition(_BtnLoc);
    if(_enabledPic != NULL)_enabledPic->setPosition(_BtnLoc);
    
    _BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
    _BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
}

void CButton::setScale(float fscale)
{
    _BtnSize = _normalPic->getContentSize()*fscale;
    
    _BtnRect.size = _BtnSize;
    _BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
    _BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
    
    _normalPic->setScale(fscale);
    _touchedPic->setScale(fscale*_ftouchedScale);
    if(_enabledPic != NULL)_enabledPic->setScale(fscale);
}

void CButton::setScale(float fscaleX,float fscaleY)
{
    _BtnSize = _normalPic->getContentSize();
    _BtnSize.width *= fscaleX;
    _BtnSize.height *= fscaleY;
    
    _BtnRect.size = _BtnSize;
    _BtnRect.origin.x = _BtnLoc.x - _BtnSize.width*0.5f;
    _BtnRect.origin.y = _BtnLoc.y - _BtnSize.height*0.5f;
    
    _normalPic->setScaleX(fscaleX);
    _normalPic->setScaleY(fscaleY);
    _touchedPic->setScaleX(fscaleX*_ftouchedScale);
    _touchedPic->setScaleY(fscaleY*_ftouchedScale);
    if(_enabledPic != NULL){
        _enabledPic->setScaleX(fscaleX);
        _enabledPic->setScaleY(fscaleY);
    }
}


void CButton::setRotate(float rot) {
    _normalPic ->setRotation(rot);
    _touchedPic->setRotation(rot);
    if(_enabledPic != NULL) _enabledPic->setRotation(rot);
}
