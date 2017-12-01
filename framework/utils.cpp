#include "stdafx.h"
#include "utils.h"


namespace IOTA_UTIL
{
	//거리 가져오는 함수
	float getDistance(float startX, float startY, float endX, float endY)
	{
		float x = endX - startX;
		float y = endY - startY;

		return sqrtf(x * x + y * y);
	}

	//각도 가져오는 함수
	float getAngle(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = PI2 - angle;
			if (angle >= PI2) angle -= PI2;
		}

		return angle;
	}

	//-PI~PI
	float getAngle2(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		float distance = sqrtf(x * x + y * y);

		float angle = acosf(x / distance);

		if (y2 > y1)
		{
			angle = PI2 - angle;
			if (angle >= PI) angle -= PI2;
		}

		return angle;
	}


	float Rad2Deg(float rad)
	{
		return (rad * 180 / PI);
	}
	float Deg2Rad(float deg)
	{
		return (deg * PI / 180);
	}


	wchar_t* convert_wc(char *str_param)
	{
		size_t convertedChars = 0;
		size_t str_param_len = strlen(str_param) + 1;

		wchar_t *wc = new wchar_t[str_param_len];
		setlocale(LC_ALL, "");
		mbstowcs_s(&convertedChars, wc, str_param_len, str_param, _TRUNCATE);

		return wc;
	}

	wchar_t* convert_wc(string str_param)
	{
		size_t convertedChars = 0;
		size_t str_param_len = strlen(str_param.c_str()) + 1;

		wchar_t *wc = new wchar_t[str_param_len];
		setlocale(LC_ALL, "");
		mbstowcs_s(&convertedChars, wc, str_param_len, str_param.c_str(), _TRUNCATE);

		return wc;
	}


	char* convert_mb(wstring wstr)
	{
		size_t convertedChars = 0;
		size_t wstr_len = (wcslen(wstr.c_str()) * 2) + 1;

		char *mb = new char[wstr_len];
		setlocale(LC_ALL, "");
		wcstombs_s(&convertedChars, mb, wstr_len, wstr.c_str(), wstr_len);

		return mb;
	}

	char* convert_mb(wchar_t* wstr)
	{
		size_t convertedChars = 0;
		size_t wstr_len = (wcslen(wstr) * 2) + 1;

		char *mb = new char[wstr_len];
		setlocale(LC_ALL, "");
		wcstombs_s(&convertedChars, mb, wstr_len, wstr, wstr_len);

		return mb;
	}
}