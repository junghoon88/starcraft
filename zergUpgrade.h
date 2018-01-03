#pragma once

//게임 내 플레이어별로 따로 사용 함

struct tagUpgradeCost
{
	UINT	level;
	UINT	mineral;
	UINT	gas;
	FLOAT	duration;
};

struct tagUpgrade
{
	TCHAR					name[128];		//이름
	UINT					level;			//레벨
	UINT					maxLevel;		//맥스레벨

	BOOL					isProcessing;	//진행중
	BOOL					complete;		//완료

	vector<tagUpgradeCost>	vCost;			//레벨별 업그레이드 비용
};

struct tagEvolution
{
	TCHAR			name[128];		//이름
	BOOL			isProcessing;	//진행중
	BOOL			complete;		//완료
								
	tagUpgradeCost	cost;			//업그레이드 비용
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
	inline tagEvolution* getEvolution(void) { return _evolution; }

};

