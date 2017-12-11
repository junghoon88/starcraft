#pragma once
#include "gameNode.h"
#include "player.h"
#include "gameMap.h"

class sceneBattle : public gameNode
{
private:
	player*		_player[PLAYER_NUM];

	PLAYER		_selectPlayerNum;		//���õ� �÷��̾ interface render �� �Ѵ�.

public:
	sceneBattle();
	~sceneBattle();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);


};

