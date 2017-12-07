#pragma once
#include "gameNode.h"

//�ݹ��Լ� �Լ�������
typedef void(*CALLBACK_FUNCTION)(void);

//<Functional>
//�� ���̺귯��	std::Function
//				std::move
//				std::bind
//�Ϲ� �������, ������� ���� �����ϰ� ��
//����) �ǿܷ� ����� ����

//�ݹ��Լ��� �������Ѻ��ÿ� 

enum BUTTONDIRECTION
{
	BUTTONDIRECTION_NULL,
	BUTTONDIRECTION_UP,
	BUTTONDIRECTION_DOWN
};



class button : public gameNode
{
private:
	BUTTONDIRECTION _direction;		//��ư �̳�

	const TCHAR* _imageName;			//��ư �̹��� �̸�
	image* _image;					//��ư �̹���
	RECT _rc;
	COLORREF _color;
	float _x, _y;

	TCHAR _strText[1024];
	FONTVERSION _fontNum;
	

	POINT _btnDownFramePoint;
	POINT _btnUpFramePoint;

	void* _obj;
	CALLBACK_FUNCTION _callbackFunction;
	CALLBACK_FUNCTION_PARAMETER _callbackFunctionParameter;

public:
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

	void release(void);
	void update(void);
	void render(void);
	button();
	~button();

public:
	void setText(const TCHAR* text);
	void setRect(int x,int y);

public:
	inline RECT getRect(void) { return _rc; }
	inline void setFontNum(FONTVERSION fontNum) { _fontNum = fontNum; }
	inline void setColor(COLORREF color) { _color = color; }

	
};

