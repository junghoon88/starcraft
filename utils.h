#pragma once
#define PI 3.141592654f
#define PI2 PI * 2

#define PI8 float(PI / 8.0f)
#define PI16 float(PI / 16.0f)
#define PI32 float(PI / 32.0f)
#define PI64 float(PI / 64.0f)
#define PI128 float(PI / 128.0f)

#define FLOAT_TO_INT(f1) static_cast<int>(f1)
#define FLOAT_EPSILON 0.001f	//실수의 가장 작은 단위 (그리스어)


namespace IOTA_UTIL
{
	//거리 가져오는 함수
	float getDistance(float startX, float startY, float endX, float endY);

	//각도 가져오는 함수
	float getAngle(float x1, float y1, float x2, float y2);

	float getAngle2(float x1, float y1, float x2, float y2);

	float Rad2Deg(float rad);
	float Deg2Rad(float deg);



	//문자열 변환 함수
	wchar_t* convert_wc(char *str_param);
	wchar_t* convert_wc(string str_param);
	char* convert_mb(wstring wstr);
	char* convert_mb(wchar_t* wstr);

}