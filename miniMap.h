#pragma once
#include "gameNode.h"
#include "tileNode.h"

class gameMap;
class gameController;
class player;

class miniMap : public gameNode
{
private:
	image*		_imgBackground;	//�̴ϸ��� ���� ��׶���
	image*		_img;			//�ܺο��� ������Ʈ�� ����
	image*		_imgTemp;		//������Ʈ �Ǳ� �������� ���� �����͸� ��Ƴ��� ��ҿ� �������Ѵ�.
	RECT		_rcMiniMap;
	RECT		_rcMiniMapCamera;


	gameController*		_gameController;
	player*				_player[PLAYER_NUM];			//�÷��̾�����, sceneBattle ���� �޴´�.
	gameMap*			_gameMap;

	BOOL		_updated;

private:
	void updateCamera(void);

public:
	miniMap();
	~miniMap();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	//thread ���� �غ���
	void updateMiniMap(void);

public:
	inline void setLinkAdressGameController(gameController* gc) { _gameController = gc; }
	inline void setLinkAdressPlayers(player* player, PLAYER playerNum) { _player[playerNum] = player; }
	inline void setLinkAdressGameMap(gameMap* map) { _gameMap = map; }

};

