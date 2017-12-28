#pragma once
#include "gameNode.h"

//콜백함수 함수포인터
typedef void(*CALLBACK_FUNCTION)(void);

//<Functional>
//이 라이브러리	std::Function
//				std::move
//				std::bind
//일반 멤버변수, 멤버변수 참조 가능하게 됨
//함정) 의외로 쉬운게 함정

//콜백함수를 변형시켜보시요 

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};



class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;		//버튼 이넘

	const TCHAR* _imageName;			//버튼 이미지 이름
	image* _image;					//버튼 이미지
	RECT _rc;
	COLORREF _color;
	float _x, _y;

	TCHAR _strText[1024];
	FONTVERSION _fontNum;
	
	BOOL	_disable;		//버튼 비활성화
	BOOL	_onlyUp;		//버튼 이미지를 하나만 나오게 할때
	BOOL	_onlyDown;		//버튼 이미지를 하나만 나오게 할때

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;
	POINT _btnDisableFramePoint;

	void* _obj;
	CALLBACK_FUNCTION _callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
	button();
	~button();

	HRESULT init(const TCHAR* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);
	HRESULT init(const TCHAR* imageName, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		void* cbFunction, void* obj);

	HRESULT init(const TCHAR* imageName, const TCHAR* text, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		CALLBACK_FUNCTION cbFunction);
	HRESULT init(const TCHAR* imageName, const TCHAR* text, int x, int y,
		POINT btnDownFramePoint, POINT btnUpFramePoint,
		void* cbFunction, void* obj);

	HRESULT init(const TCHAR* imageName, RECT rc, POINT btnUpFramePoint, POINT btnDownFramePoint, POINT btnDisableFramePoint, void* cbFunction, void* obj);

	void release(void);
	void update(void);
	void render(void);
	void ZRender(ZORDER zorder);

private:
	void renderImage(void);
	void renderText(void);
	void renderImage(ZORDER zorder);
	void renderText(ZORDER zorder);



public:
	void setText(const TCHAR* text);
	void setRect(int x,int y);

public:
	inline RECT getRect(void) { return _rc; }
	inline void setFontNum(FONTVERSION fontNum) { _fontNum = fontNum; }
	inline void setColor(COLORREF color) { _color = color; }
	inline void setImage(const TCHAR* strKey) { _image = IMAGEMANAGER->findImage(strKey); }
	inline void setDisable(BOOL disable) { _disable = disable; }
	inline void setOnlyUp(BOOL onlyUp) { _onlyUp = onlyUp; }
	inline void setOnlyDown(BOOL onlyDown) { _onlyDown = onlyDown; }
	
};

