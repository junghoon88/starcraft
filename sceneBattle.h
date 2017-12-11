#pragma once
#include "gameNode.h"
#include "player.h"
#include "gameMap.h"

class sceneBattle : public gameNode
{
private:
	player*		_player[PLAYER_NUM];

	PLAYER		_selectPlayerNum;		//선택된 플레이어만 interface render 를 한다.

public:
	sceneBattle();
	~sceneBattle();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);


};

