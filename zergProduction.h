#pragma once
#include "gameNode.h"

//게임 내 모든 플레이어 공통으로 사용함

struct tagProduction
{
	UINT				costMinerals;	//소모 미네랄
	UINT				costGas;		//소모 가스
	FLOAT				control;		//인구수
	FLOAT				buildTime;		//빌드시간
	TCHAR				hotKey;			//단축키
};


class zergProduction
{
private:
	static tagProduction _zuProduction[UNITNUM_ZERG_MAX];
	static tagProduction _zbProduction[BUILDINGNUM_ZERG_MAX];

public:
	zergProduction(bool initInfo);
	zergProduction();
	~zergProduction();


public:
	tagProduction getZUProduction(UNITNUM_ZERG num);


};

