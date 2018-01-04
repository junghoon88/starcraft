#pragma once
#include "Building.h"
class zbLair : public Building
{
private:
	vector<zuLarva*>	_vLarva;

	FLOAT				_larvaResponeTime;

private:
	void initBaseStatus(void);
	void initBattleStatus(POINT ptTile);

	void larvaValidCheck(void);
	void responeLarva(void);
	void createLarva(POINT pt);

	//상속받은 가상함수
	void updateBattleStatus(void);
	void updatePosition(void);
	void updateImageFrame(void);
	void updateProcessing(void);
	void updateCommandSet(void);

	void procCommands(void);

public:
	zbLair(PLAYER playerNum);
	~zbLair();

	HRESULT init(POINT ptTile);
	void release(void);
	void update(void);
	void render(int imgOffsetX = 0, int imgOffsetY = 0);



public:
	inline vector<zuLarva*> getLarvas(void) { larvaValidCheck();	return _vLarva; }
	inline void setLarvas(vector<zuLarva*> larvas) { _vLarva = larvas; }
	inline FLOAT getLarvaResponeTime(void) { return _larvaResponeTime; }
	inline void setLarvaResponeTime(FLOAT time) { _larvaResponeTime = time; }

};

