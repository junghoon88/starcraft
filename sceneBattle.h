#pragma once
#include "gameNode.h"
#include "player.h"
#include "gameMap.h"

#include "gameInterface.h"
#include "gameController.h"

class sceneBattle : public gameNode
{
private:
	//������
	gameMap*		_gameMap;

	//�÷��̾�
	player*			_player[PLAYER_NUM];

	//�����������̽�
	//gameInterface*	_gameInterface[PLAYER_NUM];

	//������Ʈ�ѷ�
	gameController*	_gameController;


	PLAYER			_selectPlayerNum;		//���õ� �÷��̾ interface render �� �Ѵ�.


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

