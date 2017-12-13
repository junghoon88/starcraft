#pragma once
#include "gameNode.h"

//���� �� ��� �÷��̾� �������� �����

struct tagProduction
{
	UINT				costMinerals;	//�Ҹ� �̳׶�
	UINT				costGas;		//�Ҹ� ����
	FLOAT				control;		//�α���
	FLOAT				buildTime;		//����ð�
	TCHAR				hotKey;			//����Ű
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

