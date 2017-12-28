#pragma once
#include "gameNode.h"

//���� �� ��� �÷��̾� �������� �����

struct tagProduction
{
	UINT				costMinerals;	//�Ҹ� �̳׶�
	UINT				costGas;		//�Ҹ� ����
	FLOAT				control;		//�α���
	FLOAT				buildTime;		//����ð�
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

