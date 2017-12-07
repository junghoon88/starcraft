#pragma once
#define PI 3.141592654f
#define PI2 PI * 2

#define PI8 float(PI / 8.0f)
#define PI16 float(PI / 16.0f)
#define PI32 float(PI / 32.0f)
#define PI64 float(PI / 64.0f)
#define PI128 float(PI / 128.0f)

#define FLOAT_TO_INT(f1) static_cast<int>(f1)
#define FLOAT_EPSILON 0.001f	//�Ǽ��� ���� ���� ���� (�׸�����)


namespace IOTA_UTIL
{
	//�Ÿ� �������� �Լ�
	float getDistance(float startX, float startY, float endX, float endY);

	//���� �������� �Լ�
	float getAngle(float x1, float y1, float x2, float y2);

	float getAngle2(float x1, float y1, float x2, float y2);

	float Rad2Deg(float rad);
	float Deg2Rad(float deg);



	//���ڿ� ��ȯ �Լ�
	wchar_t* convert_wc(char *str_param);
	wchar_t* convert_wc(string str_param);
	char* convert_mb(wstring wstr);
	char* convert_mb(wchar_t* wstr);

}