#include "CDrawPanel.h"
#include "Data.h"

#define BRUSH_SIZE 0.35f

CDrawPanel* CDrawPanel::_pHandDrawing = nullptr;

CDrawPanel *CDrawPanel::create()
{ // 建立物件的實體
	if (_pHandDrawing == nullptr) {
		_pHandDrawing = new (std::nothrow) CDrawPanel();
		if (_pHandDrawing) {
			_pHandDrawing->autorelease();
			return _pHandDrawing;
		}
		CC_SAFE_DELETE(_pHandDrawing);
		return nullptr;
	}
	else return _pHandDrawing;
}

CDrawPanel *CDrawPanel::getInstance()
{
	if (_pHandDrawing == nullptr) {
		_pHandDrawing = new (std::nothrow) CDrawPanel();
		if (_pHandDrawing) {
			_pHandDrawing->autorelease();
			return _pHandDrawing;
		}
		CC_SAFE_DELETE(_pHandDrawing);
		return nullptr;
	}
	return _pHandDrawing;
}


void  CDrawPanel::initDrawingPanel(Node &rootNode, cocos2d::Layer &parent)	// 設定初始內容
{
	Sprite *pBtn = (Sprite *)rootNode.getChildByName("Pen");
	Point pt = pBtn->getPosition();
	auto s = pBtn->getScale();
	_toolBtn[blackpen].setButtonInfo("pen_on.png", "pen_off.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[blackpen].setScale(s);
	rootNode.removeChildByName("Pen");

	pBtn = (Sprite *)rootNode.getChildByName("Eraser");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_toolBtn[eraser].setButtonInfo("eraser_on.png", "eraser_off.png", parent, pt, INTERFACE_LEVEL);
	_toolBtn[eraser].setScale(s);
	rootNode.removeChildByName("Eraser");

	// 設定清楚螢幕所有手繪圖型的按鈕
	pBtn = (Sprite *)rootNode.getChildByName("Clear");
	pt = pBtn->getPosition();
	s = pBtn->getScale();
	_clearAllBtn.setButtonInfo("clearall_nl.png", "clearall_off.png", parent, pt, INTERFACE_LEVEL);
	_clearAllBtn.setScale(s);
	rootNode.removeChildByName("Clear");

	_lineColor = Color3B(0, 0, 0);

	// 建立白板
	Size size = rootNode.getContentSize();
	_pWhiteBoard = RenderTexture::create(size.width, size.height, Texture2D::PixelFormat::RGBA8888);
	_pWhiteBoard->retain();
	_pWhiteBoard->setPosition(Vec2(size.width / 2, size.height / 2));
	parent.addChild(_pWhiteBoard, WHITEBOARD_LEVEL);

	_pPenBrush = (Sprite *)Sprite::createWithSpriteFrameName("brush.png");
	_pPenBrush->retain();
	_pPenBrush->setColor(_lineColor);

	_pEraserBrush = (Sprite *)Sprite::createWithSpriteFrameName("eraser_body.png");
	_pEraserBrush->retain();

	changeToBlackPen();
}

void CDrawPanel::doStep(float dt)
{

}


CDrawPanel::CDrawPanel()
{

}


void CDrawPanel::drawing(Point &pt)
{


}


void CDrawPanel::clearWhiteBoard()
{
	_pWhiteBoard->clear(0, 0, 0, 0);
}

void CDrawPanel::setLineColor(Color3B color)
{
	_lineColor = color;
}


bool CDrawPanel::touchesBegin(cocos2d::Point inPt)
{
	for (int i = 0; i < 5; i++) {
		if (_toolBtn[i].touchesBegin(inPt)) return(true);
	}

	if (_clearAllBtn.touchesBegin(inPt)) return(true);

	return(false);
}

bool CDrawPanel::touchesMoved(Point inPt, Point inPrePt)
{
	bool bBtnOn = false;

	if (_clearAllBtn.touchesMoved(inPt)) bBtnOn = true;
	else if(_toolBtn[blackpen].touchesMoved(inPt))bBtnOn = true;
	else if (_toolBtn[eraser].touchesMoved(inPt))bBtnOn = true;

	// 產生手繪線
	if (!bBtnOn) {
		_pWhiteBoard->begin();
		float distance = inPt.getDistance(inPrePt);
		if (distance > 1) {
			if (_toolMode == PEN_MODE) {
				for (int i = 0; i < distance; i++) {
					Sprite * sprite = Sprite::createWithSpriteFrameName("brush.png");;
					sprite->setColor(_lineColor);
					sprite->setScale(BRUSH_SIZE);
					_penBrushList.pushBack(sprite);
				}
				for (int i = 0; i < distance; i++) {
					float difx = inPrePt.x - inPt.x;
					float dify = inPrePt.y - inPt.y;
					float delta = (float)i / distance;
					_penBrushList.at(i)->setPosition(Point(inPt.x + (difx * delta), inPt.y + (dify * delta)));
					_penBrushList.at(i)->visit();
				}
			}
			else if (_toolMode == ERASER_MODE) {
				for (int i = 0; i < distance; i++) {
					Sprite * sprite = Sprite::createWithSpriteFrameName("eraser_body.png");
					sprite->setColor(Color3B(250, 250, 250));
					BlendFunc blendFunc = { GL_ZERO, GL_ONE_MINUS_SRC_ALPHA };
					sprite->setBlendFunc(blendFunc);
					_eraserBrushList.pushBack(sprite);
				}
				for (int i = 0; i < distance; i++) {
					float difx = inPrePt.x - inPt.x;
					float dify = inPrePt.y - inPt.y;
					float delta = (float)i / distance;
					_eraserBrushList.at(i)->setPosition(Point(inPt.x + (difx * delta), inPt.y + (dify * delta)));
					_eraserBrushList.at(i)->visit();
				}
			}
		}
		_pWhiteBoard->end();
		if (!_penBrushList.empty()) _penBrushList.clear();
		if (!_eraserBrushList.empty()) _eraserBrushList.clear();
	}
	return(true);
}

bool CDrawPanel::touchesEnded(cocos2d::Point inPt)
{
	if (_toolBtn[blackpen].touchesEnded(inPt)) {
		SetPen();
		SwitchButton(blackpen);
	}
	else if (_toolBtn[eraser].touchesEnded(inPt)) { // 按下的是 eraser button
		SwitchButton(eraser);
		_toolMode = ERASER_MODE;
	}


	else if (_clearAllBtn.touchesEnded(inPt)) { // 確認被按下
		// 清除螢幕上所有手繪的內容
		clearWhiteBoard();
		return(true);
	}
	return(false);
}

void CDrawPanel::changeToBlackPen() {
	SetPen();
	SwitchButton(blackpen);
}


void CDrawPanel::SetPen(Color3B color) {
	_toolMode = PEN_MODE;
	_lineColor = color;
	_pPenBrush->setColor(_lineColor);
	
}
void CDrawPanel::SwitchButton(int btn) {
	for (int i = 0; i < 2; i++)_toolBtn[i].setStatus(false);
	_toolBtn[btn].setStatus(true);
}
