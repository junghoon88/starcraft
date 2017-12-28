#pragma once
#include "gameNode.h"
#include "player.h"
#include "gameMap.h"
#include "gameObjectPool.h"

#include "zergProductionInfo.h"


class sceneBattle : public gameNode
{
private:
	//������
	gameMap*		_gameMap;

	//���ӿ�����ƮǮ
	//gameObjectPool* _gameObjectPool;


	//�÷��̾�
	player*			_player[PLAYER_NUM];

	//�����������̽�
	//gameInterface*	_gameInterface[PLAYER_NUM];

	//������Ʈ�ѷ�
	//gameController*	_gameController;



	PLAYER			_selectPlayerNum;		//���õ� �÷��̾ interface render �� �Ѵ�.


	FLOAT			_playTime;

	zergProductionInfo* _zergProductionInfo;


public:
	sceneBattle();
	~sceneBattle();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void getChar(WPARAM wParam);


	
};

