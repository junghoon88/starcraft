#pragma once
//-------------------------------------------------------
//2017.09.20. jhkim
//Magenta Background Manager
//배경에 마젠타를 추가로 입력할 수 있도록 함 (포트리스에서 사용)
//-------------------------------------------------------

#include "gameNode.h"

enum EXPLOSION_TYPE
{
	EXPOLISION_TYPE_ELLIPSE,		//원
	EXPOLISION_TYPE_RECTANGLE,		//사각형


};

struct tagExplosion
{
	EXPLOSION_TYPE type;	// 폭발 종류
	POINT pt;				// 폭발 위치
	float width;			// 폭발 반경(가로)
	float height;			// 폭발 반경(세로)
	float angleDeg;			// 연쇄 폭발 방향(연발일때 사용)
	float speed;			// 연쇄 폭발 스피드(연발일때 사용)

	int explosionCnt;		// 폭발 회수
	int explosionCntMax;	// 최대 폭발 회수
	int explosionTime;		// 연쇄 폭발 시간(ms)
	int explosionTimeCnt;	// 연쇄 폭발 시간 내부 카운터
	int explosionDamping;	// 연쇄 폭발하면서 폭발 반경 줄어드는 정도 (%)
	bool isExplosioned;		// 폭발 했는지 
};

struct tagTrace
{
	EXPLOSION_TYPE type;
	RECT rc;
};

class MBGManager : public gameNode
{
private:
	image* _imgBG;			//백그라운드 이미지
	HDC _hdcImg;			//백그라운드 이미지 DC
	
	vector<tagExplosion> _vExplosion;
	vector<tagExplosion>::iterator _viExplosion;

	vector<tagTrace> _vRCTrace;	// 폭발하고 남은 잔해(마젠타 그릴 부분)
	vector<tagTrace>::iterator _viRCTrace;


	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

private:
	void PlayExplosion(tagExplosion* ex);

public:
	virtual HRESULT init(wstring strImgName);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	void setExplosion(tagExplosion ex);
	
	bool getisExplosion(void);


	MBGManager();
	~MBGManager();
};

