#pragma once
#include "gameNode.h"
#include "progressBar.h"


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




	gameController*		_gameController;
	player*				_player[PLAYER_NUM];			//�÷��̾�����, sceneBattle ���� �޴´�.


private:
	void initVariables(void);

	void updateFace(void);
	void updateIconWeapon(void);
	void updateSelectInfo(void);
	
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

