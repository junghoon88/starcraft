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
				15,						//������
				0,						//���� ����
				0,						//���� ����(������ ���ڰ� ������ ���)
				0,						//���� ����
				100,					//���� ����(��Ʈ ũ��)
				false,					//bool ���� ����
				false,					//bool ���� ����
				false,					//bool ���� ��Ҽ�(������Ű�� ����)
				HANGUL_CHARSET,			//���� ����
				OUT_DEFAULT_PRECIS,		//��� ��Ȯ��
				CLIP_DEFAULT_PRECIS,	//Ŭ���� ��Ȯ��
				DEFAULT_QUALITY,		//����� ����Ƽ
				FF_DONTCARE,			//�ڰ�
				TEXT("���� ���"));			//��Ʈ
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


