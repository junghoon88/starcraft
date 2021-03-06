#include "stdafx.h"
#include "globalTools.h"


globalTools::globalTools()
{
}


globalTools::~globalTools()
{
}

void globalTools::setFontAll(void)
{
	for (int i = 0; i < FONTVERSION_MAX; i++)
	{
		switch (i)
		{
		case FONTVERSION_STARCRAFT:
			_gFont[i] = CreateFont(
				15,						//문자폭
				0,						//문자 넓이
				0,						//문자 기울기(실제로 문자가 각도로 기움)
				0,						//문자 방향
				100,					//문자 굵기(폰트 크기)
				false,					//bool 문자 기울기
				false,					//bool 문자 밑줄
				false,					//bool 문자 취소선(나무위키에 많음)
				HANGUL_CHARSET,			//문자 셋팅
				OUT_DEFAULT_PRECIS,		//출력 정확도
				CLIP_DEFAULT_PRECIS,	//클리핑 정확도
				DEFAULT_QUALITY,		//출력의 퀄리티
				FF_DONTCARE,			//자간
				TEXT("맑은 고딕"));			//폰트
			break;
		}
	}
}
void globalTools::deleteFontAll(void)
{
	for (int i = 0; i < FONTVERSION_MAX; i++)
	{
		DeleteObject(_gFont[i]);
	}
}


void globalTools::setBrushAll(void)
{
	for (int i = 0; i < BRUSHVERSION_MAX; i++)
	{
		switch (i)
		{
			case BRUSHVERSION_WHITE:
				_gBrush[i] = CreateSolidBrush(RGB(255, 255, 255));
				break;
			case BRUSHVERSION_GRAY:
				_gBrush[i] = CreateSolidBrush(RGB(200, 200, 200));
				break;
			case BRUSHVERSION_BLACK:
				_gBrush[i] = CreateSolidBrush(RGB(0, 0, 0));
				break;

		}
	}
}
void globalTools::deleteBrushAll(void)
{
	for (int i = 0; i < BRUSHVERSION_MAX; i++)
	{
		DeleteObject(_gBrush[i]);
	}
}

void globalTools::setPenAll(void)
{
	for (int i = 0; i < PENVERSION_MAX; i++)
	{
		switch (i)
		{
		case PENVERSION_MOUSEDRAG:
			_gPen[i] = CreatePen(PS_SOLID, 2, RGB(16, 252, 24));
			break;
		case PENVERSION_UNITCLICK:
			_gPen[i] = CreatePen(PS_SOLID, 2, RGB(36, 152, 36));
			break;
		case PENVERSION_RESOURCECLICK:
			_gPen[i] = CreatePen(PS_SOLID, 2, RGB(174, 171, 53));
			break;
		case PENVERSION_SHOWGASRECT:
			_gPen[i] = CreatePen(PS_DOT, 1, RGB(36, 152, 36));
			break;
		case PENVERSION_BLACK:
			_gPen[i] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			break;
		case PENVERSION_BLUE1:
			_gPen[i] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			break;
		case PENVERSION_BLUE2:
			_gPen[i] = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
			break;
		case PENVERSION_MINIMAP:
			_gPen[i] = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
			break;
		}
	}
}

void globalTools::deletePenAll(void)
{
	for (int i = 0; i < PENVERSION_MAX; i++)
	{
		DeleteObject(_gPen[i]);
	}
}


