#pragma once
#include "gameNode.h"

//게임 내 모든 플레이어 공통으로 사용함

struct tagProduction
{
	UINT				costMinerals;	//소모 미네랄
	UINT				costGas;		//소모 가스
	FLOAT				control;		//인구수
	FLOAT				buildTime;		//빌드시간
};


class zergProductionInfo
{
private:
	static tagProduction _zuProduction[UNITNUM_ZERG_MAX];
	static tagProduction _zbProduction[BUILDINGNUM_ZERG_MAX];

public:
	zergProductionInfo(bool initInfo);
	zergProductionInfo();
	~zergProductionInfo();


public:
	tagProduction getZUProductionInfo(UNITNUM_ZERG num) { return _zuProduction[num]; }
	tagProduction getZBProductionInfo(BUILDINGNUM_ZERG num) { return _zbProduction[num]; }


};

