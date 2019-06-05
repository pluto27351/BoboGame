#pragma once

#include <Vector>
#include "cocos2d.h"
#include "CButton.h"
#include "CSwitch.h"

using namespace std;
using namespace cocos2d;

enum tool { blackpen,eraser };


class CDrawPanel : public Ref
{
protected:
	int kk;
	// for hand drawing
	RenderTexture *_pWhiteBoard;
	Sprite* _pPenBrush;
	Sprite* _pEraserBrush;

	Vector <Sprite*> _penBrushList;
	Vector <Sprite*> _eraserBrushList;

	Color3B _lineColor;

	static CDrawPanel* _pHandDrawing;
	CButton _clearAllBtn;
	CSwitch _toolBtn[2];
	int _toolMode;
	void SetPen(Color3B color = Color3B(0, 0, 0));
	void SwitchButton(int btn);
public:
	static CDrawPanel *create();		// 建立物件的實體
	static CDrawPanel *getInstance();	// 取得 CDrawPanel 的實體
	void   initDrawingPanel(Node &rootNode, cocos2d::Layer &parent);	// 設定初始內容

	void setLineColor(Color3B color);
	void drawing(Point &pt);

	void clearWhiteBoard();	// 清除所有繪製在畫面上的線條
	//int  getMode();	// 取得目前的狀態
	void changeToBlackPen();

	bool touchesBegin(Point inPt);
	bool touchesMoved(Point inPt, Point inPrePt);
	bool touchesEnded(Point inPt);
	void doStep(float dt);
	CDrawPanel();

};
