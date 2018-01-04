#pragma once
#include "gameNode.h"
#include "progressBar.h"
#include "miniMap.h"

class player;
class gameController;

class gameInterface : public gameNode
{
private:
	RECT				_rcStat1;
	RECT				_rcStat2[SELECTUNIT_MAX];
	RECT				_rcFace;

	RECT				_rcIconWeapon[3];
	image*				_imgIconWeapon[3];
	UINT				_imgIconFrameX[3];





	progressBar*		_progressBar;
	miniMap*			_miniMap;
	gameController*		_gameController;

	player*				_player[PLAYER_NUM];			//플레이어정보, sceneBattle 에서 받는다.


private:
	void initVariables(void);


	void actionMouseMiniMap(void);
	void updateIconWeapon(void);
	
	void renderSelectInfo(void);
	void renderIconWeapon(void);



public:
	gameInterface();
	~gameInterface();


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);



public:
	inline void setLinkAdressGameController(gameController* gc) { _gameController = gc; }
	inline void setLinkAdressPlayers(player* player, PLAYER playerNum) { _player[playerNum] = player; }

};

