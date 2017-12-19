#include "stdafx.h"
#include "button.h"


button::button()
	: _image(NULL)
{
	_stprintf(_strText, L"");

	_fontNum = FONTVERSION_STARCRAFT;

	_color = RGB(0, 0, 0);
}


button::~button()
{

}

HRESULT button::init(const TCHAR* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	_callbackFunctionParameter = NULL;

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	_disable = false;
	_onlyUp = false;
	_onlyDown = false;


	return S_OK;
}

HRESULT button::init(const TCHAR* imageName, int x, int y,
	POINT btnDownFramePoint, POINT btnUpFramePoint,
	void* cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	_disable = false;
	_onlyUp = false;
	_onlyDown = false;


	return S_OK;

}

HRESULT button::init(const TCHAR* imageName, const TCHAR* text, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, CALLBACK_FUNCTION cbFunction)
{
	_obj = NULL;
	_callbackFunction = static_cast<CALLBACK_FUNCTION>(cbFunction);
	_callbackFunctionParameter = NULL;

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	setText(text);

	_disable = false;
	_onlyUp = false;
	_onlyDown = false;


	return S_OK;
}

HRESULT button::init(const TCHAR* imageName, const TCHAR* text, int x, int y, POINT btnDownFramePoint, POINT btnUpFramePoint, void * cbFunction, void * obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_x = x;
	_y = y;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;

	_image = IMAGEMANAGER->findImage(imageName);

	_rc = RectMakeCenter(x, y, _image->getFrameWidth(), _image->getFrameHeight());

	setText(text);

	_disable = false;
	_onlyUp = false;
	_onlyDown = false;


	return S_OK;
}

HRESULT button::init(const TCHAR* imageName, RECT rc, POINT btnUpFramePoint, POINT btnDownFramePoint, POINT btnDisableFramePoint, void* cbFunction, void* obj)
{
	_obj = obj;
	_callbackFunction = NULL;
	_callbackFunctionParameter = static_cast<CALLBACK_FUNCTION_PARAMETER>(cbFunction);

	_direction = BUTTONDIRECTION_NULL;

	_btnUpFramePoint = btnUpFramePoint;
	_btnDownFramePoint = btnDownFramePoint;
	_btnDisableFramePoint = btnDisableFramePoint;

	_image = IMAGEMANAGER->findImage(imageName);

	_rc = rc;

	setText(L"");

	_disable = false;
	_onlyUp = false;
	_onlyDown = false;


	return S_OK;
}

void button::release(void)
{
}

void button::update(void)
{
	if (_disable)
	{
		_direction = BUTTONDIRECTION_NULL;
		return;
	}


	if (PtInRect(&_rc, _ptMouse))
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_direction = BUTTONDIRECTION_DOWN;
			
		}
		else if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON) && _direction == BUTTONDIRECTION_DOWN)
		{
			_direction = BUTTONDIRECTION_UP;

			if (_callbackFunction != NULL)
			{
				_callbackFunction();
			}
			else if (_callbackFunctionParameter != NULL && _obj != NULL)
			{
				_callbackFunctionParameter(_obj);
			}
		}
	}
	else _direction = BUTTONDIRECTION_NULL;
	
}

void button::render(void) 
{
	renderImage();
	renderText();

}

void button::setText(const TCHAR* text)
{
	if (text == NULL) return;

	_tcscpy(_strText, text);
}

void button::setRect(int x, int y)
{
	_rc = RectMake(x, y, _image->getFrameWidth(), _image->getFrameHeight());
}

void button::renderImage(void)
{
	if (_image == NULL)
	{
		return;
	}

	if (_disable)
	{
		//Disable 상태일때
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnDisableFramePoint.x, _btnDisableFramePoint.y);
	}
	else if (_onlyUp)
	{
		//Up 이미지만 보여줄때
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnUpFramePoint.x, _btnUpFramePoint.y);
	}
	else if (_onlyDown)
	{
		//Down 이미지만 보여줄때
		_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnDownFramePoint.x, _btnDownFramePoint.y);
	}
	else
	{
		switch (_direction)
		{
		case BUTTONDIRECTION_NULL: case BUTTONDIRECTION_UP:
			_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnUpFramePoint.x, _btnUpFramePoint.y);
			break;
		case BUTTONDIRECTION_DOWN:
			_image->frameRender(getMemDC(), _rc.left, _rc.top, _btnDownFramePoint.x, _btnDownFramePoint.y);
			break;
		}
	}
}
void button::renderText(void)
{
	//버튼 글자가 있을경우
	if (_tcslen(_strText) == 0)
	{
		return;
	}

	COLORREF oldcolor = GetTextColor(getMemDC());
	SetTextColor(getMemDC(), _color);
	SetBkMode(getMemDC(), TRANSPARENT);
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), _gFont[_fontNum]);
	DrawText(getMemDC(), _strText, _tcslen(_strText), &_rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	SetTextColor(getMemDC(), oldcolor);
}
