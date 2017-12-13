#pragma once
#include "gameNode.h"
#include "player.h"
#include "gameMap.h"

#include "gameInterface.h"
#include "gameController.h"

class sceneBattle : public gameNode
{
private:
	//맵정보
	gameMap*		_gameMap;

	//플레이어
	player*			_player[PLAYER_NUM];

	//게임인터페이스
	//gameInterface*	_gameInterface[PLAYER_NUM];

	//게임컨트롤러
	gameController*	_gameController;


	PLAYER			_selectPlayerNum;		//선택된 플레이어만 interface render 를 한다.


	FLOAT			_playTime;


public:
	sceneBattle();
	~sceneBattle();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);


};

