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
	TCHAR					name[128];		//�̸�
	UINT					level;			//����
	UINT					maxLevel;		//�ƽ�����

	BOOL					isProcessing;	//������
	BOOL					complete;		//�Ϸ�

	vector<tagUpgradeCost>	vCost;			//������ ���׷��̵� ���
};

struct tagEvolution
{
	TCHAR			name[128];		//�̸�
	BOOL			isProcessing;	//������
	BOOL			complete;		//�Ϸ�
								
	tagUpgradeCost	cost;			//���׷��̵� ���
};

class zergUpgrade
{
private:
	tagUpgrade		_upgrade[UPGRADE_ZERG_MAX];
	tagEvolution	_evolution[EVOLUTION_ZERG_MAX];

public:
	zergUpgrade();
	~zergUpgrade();

	void upgradeComplete(UPGRADE_ZERG num);
	void evolutionComplete(EVOLUTION_ZERG num);

public:
	inline tagUpgrade* getUpgrade(void) { return _upgrade; }
	inline void setUpgradeIsProcessing(UPGRADE_ZERG num, bool processing) { _upgrade[num].isProcessing = processing; }

	inline tagEvolution* getEvolution(void) { return _evolution; }
	inline void setUpgradeIsProcessing(EVOLUTION_ZERG num, bool processing) { _evolution[num].isProcessing = processing; }

};

