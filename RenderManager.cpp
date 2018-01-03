#include "stdafx.h"
#include "RenderManager.h"


RenderManager::RenderManager()
{
}


RenderManager::~RenderManager()
{
}

HRESULT RenderManager::init()
{

	return S_OK;
}
void RenderManager::release()
{
	for (int i = 0; i < ZORDER_MAX; i++)
	{
		_vRenderList[i].clear();
	}
}

void RenderManager::insertRectangle(ZORDER zorder, RECT rc, PENVERSION penVersion)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_RECT;
	info.rcShow = rc;
	info.penVersion = penVersion;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertLineRectangle(ZORDER zorder, RECT rc, PENVERSION penVersion)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_LINERECT;
	info.rcShow = rc;
	info.penVersion = penVersion;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertEllipse(ZORDER zorder, RECT rc, PENVERSION penVersion)
{
	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_ELLIPSE;
	info.rcShow = rc;
	info.penVersion = penVersion;

	_vRenderList[zorder].push_back(info);
}

void RenderManager::insertText(ZORDER zorder, RECT rc, TCHAR* text, COLORREF color)
{
	tagTextRenderInfo info;
	ZeroMemory(&info, sizeof(tagTextRenderInfo));

	info.renderType = RENDER_TYPE_TEXT;
	info.rcShow = rc;
	_tcscpy(info.strText, text);
	info.colorText = color;

	_vTextRenderList[zorder].push_back(info);
}

void RenderManager::insertTextCenter(ZORDER zorder, RECT rc, TCHAR* text, COLORREF color)
{
	tagTextRenderInfo info;
	ZeroMemory(&info, sizeof(tagTextRenderInfo));

	info.renderType = RENDER_TYPE_TEXTCENTER;
	info.rcShow = rc;
	_tcscpy(info.strText, text);
	info.colorText = color;

	_vTextRenderList[zorder].push_back(info);
}

//void RenderManager::insertTextCenter(ZORDER zorder, RECT rc, TCHAR* text, COLORREF color)
//{
//	tagRenderInfo info;
//	ZeroMemory(&info, sizeof(tagRenderInfo));
//
//	info.renderType = RENDER_TYPE_TEXTCENTER;
//	info.rcShow = rc;
//	info.strText = text;
//	info.colorText = color;
//
//	_vRenderList[zorder].push_back(info);
//}


//입력함수
void RenderManager::insertImg(ZORDER zorder, image* img, int destX, int destY)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_NORMAL;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.rcShow = RectMake(destX, destY, img->getWidth(), img->getHeight());

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImg(ZORDER zorder, image* img, int destX, int destY, int sourWidth, int sourHeight)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_RESIZE;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.sourWidth = sourWidth;
	info.sourHeight = sourHeight;
	info.rcShow = RectMake(destX, destY, sourWidth, sourHeight);

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgCT(ZORDER zorder, image* img, int cx, int cy)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	int destX = cx - (img->getWidth()  * 0.5f);
	int destY = cy - (img->getHeight() * 0.5f);

	info.renderType = RENDER_TYPE_IMAGE_RESIZE;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.rcShow = RectMake(destX, destY, img->getWidth(), img->getHeight());

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgFrame(ZORDER zorder, image* img, int destX, int destY, int currentFrameX, int currentFrameY)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_FRAME;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.curFrameX = currentFrameX;
	info.curFrameY = currentFrameY;
	info.rcShow = RectMake(destX, destY, img->getFrameWidth(), img->getFrameHeight());

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgFrameCC(ZORDER zorder, image* img, int cx, int cy, int currentFrameX, int currentFrameY)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	int destX = cx - (img->getFrameWidth()  * 0.5f);
	int destY = cy - (img->getFrameHeight() * 0.5f);

	info.renderType = RENDER_TYPE_IMAGE_FRAME;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.curFrameX = currentFrameX;
	info.curFrameY = currentFrameY;
	info.rcShow = RectMake(destX, destY, img->getFrameWidth(), img->getFrameHeight());

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgLoop(ZORDER zorder, image* img, const LPRECT drawArea, int offsetX, int offsetY)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_LOOP;
	info.img = img;
	info.drawArea = drawArea;
	info.offsetX = offsetX;
	info.offsetY = offsetY;
	info.rcShow = RectMake(0, 0, img->getWidth(), img->getHeight());

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgAlpha(ZORDER zorder, image* img, int destX, int destY, BYTE alpha)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ALPHA;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.alpha = alpha;
	info.rcShow = RectMake(destX, destY, img->getWidth(), img->getHeight());

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgAlpha(ZORDER zorder, image* img, int destX, int destY, int sourWidth, int sourHeight, BYTE alpha)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ALPHA_RESIZE;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.sourWidth = sourWidth;
	info.sourHeight = sourHeight;
	info.alpha = alpha;
	info.rcShow = RectMake(destX, destY, sourWidth, sourHeight);

	_vRenderList[zorder].push_back(info);

}
void RenderManager::insertImgAlphaFrame(ZORDER zorder, image* img, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ALPHA_FRAME;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.curFrameX = currentFrameX;
	info.curFrameY = currentFrameY;
	info.alpha = alpha;
	info.rcShow = RectMake(destX, destY, img->getFrameWidth(), img->getFrameHeight());

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgAni(ZORDER zorder, image* img, int destX, int destY, animation* ani)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ANIMATION;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.ani = ani;
	info.rcShow = RectMake(destX, destY, img->getWidth(), img->getHeight());

	_vRenderList[zorder].push_back(info);
}
//~입력함수

//rcShow 입력함수
void RenderManager::insertImg(ZORDER zorder, image* img, int destX, int destY, RECT rcShow)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_NORMAL;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.rcShow = rcShow;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImg(ZORDER zorder, image* img, int destX, int destY, int sourWidth, int sourHeight, RECT rcShow)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_RESIZE;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.sourWidth = sourWidth;
	info.sourHeight = sourHeight;
	info.rcShow = rcShow;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgFrame(ZORDER zorder, image* img, int destX, int destY, int currentFrameX, int currentFrameY, RECT rcShow)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_FRAME;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.curFrameX = currentFrameX;
	info.curFrameY = currentFrameY;
	info.rcShow = rcShow;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgLoop(ZORDER zorder, image* img, const LPRECT drawArea, int offsetX, int offsetY, RECT rcShow)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_LOOP;
	info.img = img;
	info.drawArea = drawArea;
	info.offsetX = offsetX;
	info.offsetY = offsetY;
	info.rcShow = rcShow;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgAlpha(ZORDER zorder, image* img, int destX, int destY, BYTE alpha, RECT rcShow)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ALPHA;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.alpha = alpha;
	info.rcShow = rcShow;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgAlpha(ZORDER zorder, image* img, int destX, int destY, int sourWidth, int sourHeight, BYTE alpha, RECT rcShow)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ALPHA_RESIZE;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.sourWidth = sourWidth;
	info.sourHeight = sourHeight;
	info.alpha = alpha;
	info.rcShow = rcShow;

	_vRenderList[zorder].push_back(info);

}
void RenderManager::insertImgAlphaFrame(ZORDER zorder, image* img, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha, RECT rcShow)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ALPHA_FRAME;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.curFrameX = currentFrameX;
	info.curFrameY = currentFrameY;
	info.alpha = alpha;
	info.rcShow = rcShow;

	_vRenderList[zorder].push_back(info);
}
void RenderManager::insertImgAni(ZORDER zorder, image* img, int destX, int destY, animation* ani, RECT rcShow)
{
	if (img == NULL)
		return;

	tagRenderInfo info;
	ZeroMemory(&info, sizeof(tagRenderInfo));

	info.renderType = RENDER_TYPE_IMAGE_ANIMATION;
	info.img = img;
	info.destX = destX;
	info.destY = destY;
	info.ani = ani;
	info.rcShow = rcShow;

	_vRenderList[zorder].push_back(info);
}
//~rcShow 입력함수

int RenderManager::funcCompare(const void* first, const void* second)
{
	tagRenderInfo* info1 = (tagRenderInfo*)first;
	tagRenderInfo* info2 = (tagRenderInfo*)second;

	if (info1->rcShow.bottom > info2->rcShow.bottom)
	{
		return 1;
	}
	else if (info1->rcShow.bottom < info2->rcShow.bottom)
	{
		return -1;
	}
	else
	{
		if (info1->rcShow.top > info2->rcShow.top)
		{
			return 1;
		}
		else if (info1->rcShow.top < info2->rcShow.top)
		{
			return -1;
		}

		return 0;
	}
}
void RenderManager::sort(void)
{
	if (_vRenderList[ZORDER_GAMEOBJECT].size() >= 2)
	{
		qsort((tagRenderInfo*)&_vRenderList[ZORDER_GAMEOBJECT][0], _vRenderList[ZORDER_GAMEOBJECT].size(), sizeof(tagRenderInfo), &funcCompare);
	}

	if (_vRenderList[ZORDER_GAMEOBJECTAIR].size() >= 2)
	{
		qsort((tagRenderInfo*)&_vRenderList[ZORDER_GAMEOBJECTAIR][0], _vRenderList[ZORDER_GAMEOBJECTAIR].size(), sizeof(tagRenderInfo), &funcCompare);
	}
}


void RenderManager::render(HDC hdc)
{
	HFONT oldFont = (HFONT)SelectObject(hdc, _gFont[FONTVERSION_STARCRAFT]);

	HPEN oldPen = NULL;


	for (int i = 0; i < ZORDER_MAX; i++)
	{
		for (int j = 0; j < _vRenderList[i].size(); j++)
		{
			tagRenderInfo info = _vRenderList[i][j];
			
			switch (info.renderType)
			{
			case RENDER_TYPE_RECT:
				oldPen = (HPEN)SelectObject(hdc, _gPen[info.penVersion]);
				RectangleMake(hdc, info.rcShow);
				SelectObject(hdc, oldPen);
				break;
			case RENDER_TYPE_LINERECT:
				oldPen = (HPEN)SelectObject(hdc, _gPen[info.penVersion]);
				LineToRect(hdc, info.rcShow);
				SelectObject(hdc, oldPen);
				break;
			case RENDER_TYPE_ELLIPSE:
			{		
				image* _backBuffer2 = IMAGEMANAGER->addImage(L"backBuffer2", WINSIZEX, WINSIZEY);
				HDC hDCtemp = _backBuffer2->getMemDC();
				PatBlt(hDCtemp, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);

				oldPen = (HPEN)SelectObject(hDCtemp, _gPen[info.penVersion]);
				EllipseMake(hDCtemp, info.rcShow);
				SelectObject(hDCtemp, oldPen);

				GdiTransparentBlt(hdc,
					info.rcShow.left,
					info.rcShow.top,
					(info.rcShow.right - info.rcShow.left),
					(info.rcShow.bottom - info.rcShow.top),

					hDCtemp,			
					info.rcShow.left,
					info.rcShow.top,
					(info.rcShow.right - info.rcShow.left),
					(info.rcShow.bottom - info.rcShow.top),
					RGB(255, 255, 255));
			}
				break;
			//case RENDER_TYPE_TEXTCENTER:
			//	{
			//		COLORREF oldColor = GetTextColor(hdc);
			//		SetTextColor(hdc, info.colorText);
			//		DrawText(hdc, info.strText, _tcslen(info.strText), &info.rcShow, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			//		SetTextColor(hdc, oldColor);
			//	}
			//	break;
			case RENDER_TYPE_IMAGE_NORMAL:
				if(info.img)	info.img->render(hdc, info.destX, info.destY);
				break;
			case RENDER_TYPE_IMAGE_RESIZE:
				if (info.img)	info.img->render(hdc, info.destX, info.destY, 0, 0, info.sourWidth, info.sourHeight);
				break;
			case RENDER_TYPE_IMAGE_FRAME:
				if (info.img)	info.img->frameRender(hdc, info.destX, info.destY, info.curFrameX, info.curFrameY);
				break;
			case RENDER_TYPE_IMAGE_LOOP:
				if (info.img)	info.img->loopRender(hdc, info.drawArea, info.offsetX, info.offsetY);
				break;
			case RENDER_TYPE_IMAGE_ALPHA:
				if (info.img)	info.img->alphaRender(hdc, info.destX, info.destY, info.alpha);
				break;
			case RENDER_TYPE_IMAGE_ALPHA_RESIZE:
				if (info.img)	info.img->alphaRender(hdc, info.destX, info.destY, 0, 0, info.sourWidth, info.sourHeight, info.alpha);
				break;
			case RENDER_TYPE_IMAGE_ALPHA_FRAME:
				if (info.img)	info.img->alphaFrameRender(hdc, info.destX, info.destY, info.alpha);
				break;
			case RENDER_TYPE_IMAGE_ANIMATION:
				if (info.img)	info.img->aniRender(hdc, info.destX, info.destY, info.ani);
				break;
			}
		}
		_vRenderList[i].clear();

		for (int j = 0; j < _vTextRenderList[i].size(); j++)
		{
			tagTextRenderInfo info = _vTextRenderList[i][j];

			switch (info.renderType)
			{
				case RENDER_TYPE_TEXT:
				{
					COLORREF oldColor = GetTextColor(hdc);
					SetTextColor(hdc, info.colorText);
					DrawText(hdc, info.strText, _tcslen(info.strText), &info.rcShow, DT_VCENTER | DT_SINGLELINE);
					SetTextColor(hdc, oldColor);
				}
				break;

				case RENDER_TYPE_TEXTCENTER:
				{
					COLORREF oldColor = GetTextColor(hdc);
					SetTextColor(hdc, info.colorText);
					DrawText(hdc, info.strText, _tcslen(info.strText), &info.rcShow, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					SetTextColor(hdc, oldColor);
				}
				break;
			}

		}
		_vTextRenderList[i].clear();
	}

	SelectObject(hdc, oldFont);
	DeleteObject(oldFont);

}
