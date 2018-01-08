#pragma once
#include "gameNode.h"
#include "tileNode.h"

class gameMap;
class gameController;
class player;

class miniMap : public gameNode
{
private:
	image*		_imgBackground;	//미니맵의 제일 백그라운드
	image*		_img;			//외부에서 업데이트를 받음
	image*		_imgTemp;		//업데이트 되기 전까지는 이전 데이터를 담아놓고 평소에 랜더링한다.
	RECT		_rcMiniMap;
	RECT		_rcMiniMapCamera;


	gameController*		_gameController;
	player*				_player[PLAYER_NUM];			//플레이어정보, sceneBattle 에서 받는다.
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

	//thread 에서 해보자
	void updateMiniMap(void);

public:
	inline void setLinkAdressGameController(gameController* gc) { _gameController = gc; }
	inline void setLinkAdressPlayers(player* player, PLAYER playerNum) { _player[playerNum] = player; }
	inline void setLinkAdressGameMap(gameMap* map) { _gameMap = map; }

};

