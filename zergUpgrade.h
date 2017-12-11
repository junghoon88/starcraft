#pragma once

//���� �� �÷��̾�� ���� ��� ��

struct tagUpgradeCost
{
	UINT	level;
	UINT	mineral;
	UINT	gas;
	FLOAT	duration;
};

struct tagUpgrade
{
	TCHAR					name[128];	//�̸�
	UINT					level;		//����
	UINT					maxLevel;	//�ƽ�����
										
	vector<tagUpgradeCost>	vCost;		//������ ���׷��̵� ���
};

struct tagEvolution
{
	TCHAR			name[128];	//�̸�
	BOOL			complete;	//��ȭ�Ϸ� ����
								
	tagUpgradeCost	cost;		//���׷��̵� ���
};

class zergUpgrade
{
private:
	tagUpgrade		_upgrade[UPGRADE_ZERG_MAX];
	tagEvolution	_evolution[EVOLUTION_ZERG_MAX];

public:
	zergUpgrade();
	~zergUpgrade();

public:
	inline tagUpgrade* getUpgrade(void) { return _upgrade; }
	inline tagEvolution* getEvolution(void) { return _evolution; }

};

