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
				17,						//������
				0,						//���� ����
				0,						//���� ����(������ ���ڰ� ������ ���)
				0,						//���� ����
				400,					//���� ����(��Ʈ ũ��)
				false,					//bool ���� ����
				false,					//bool ���� ����
				false,					//bool ���� ��Ҽ�(������Ű�� ����)
				HANGUL_CHARSET,			//���� ����
				OUT_DEFAULT_PRECIS,		//��� ��Ȯ��
				CLIP_DEFAULT_PRECIS,	//Ŭ���� ��Ȯ��
				DEFAULT_QUALITY,		//����� ����Ƽ
				FF_DONTCARE,			//�ڰ�
				TEXT("�ü�"));			//��Ʈ
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
			case PENVERSION_BLACK:
				_gPen[i] = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				break;
			case PENVERSION_BLUE:
				_gPen[i] = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
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


