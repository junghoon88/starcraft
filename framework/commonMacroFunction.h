#include "stdafx.h"

inline POINT PointMake(int x, int y)
{
	POINT pt = { x, y };

	return pt;
}



//선
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

inline void LineMakeAngle(HDC hdc, int x1, int y1, float length, float angle)
{
	MoveToEx(hdc, x1, y1, NULL);
	int x2 = (int)(x1 + length * cosf(angle));
	int y2 = (int)(y1 + length * (-sinf(angle)));
	LineTo(hdc, x2, y2);
}


inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

inline void RectMove(RECT& rc, int moveX, int moveY)
{
	rc.left += moveX;
	rc.right += moveX;
	rc.top += moveY;
	rc.bottom += moveY;
}

//좌표로 부터 가로, 세로가 만들어지는 사각형
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//중점좌표로 부터 가로 세로 크기 형태로 사각형
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//좌표로 부터 가로, 세로가 만들어지는 동그라미
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//중점좌표로 부터 가로 세로 크기 형태로 동그라미
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}