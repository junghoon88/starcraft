#pragma once
#include "gameNode.h"
#include "tileNode.h"

class gameMap;
class player;

class fog : public gameNode
{
private:
	image*		_imgFog;
	tagFog		_fogs[TILEX][TILEY];	//타일별로 적용할 fog

	vector<RECT> _vObjectViewRect;	//오브젝트가 가지고 있는 시야 렉트
	vector<RECT> _vObjectDetectRect;	//오브젝트가 가지고 있는 시야 렉트

	

	BYTE		_alpha;


	gameMap*	_gameMap;
	player*		_myPlayer;

private:
	void addSightArea(POINT pt, FLOAT sight, BOOL detect);


public:
	fog();
	~fog();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	inline void setLinkAdressMyPlayer(player* player) { _myPlayer = player; }
	inline void setLinkAdressGameMap(gameMap* map) { _gameMap = map; }

	typedef tagFog(*pFogs)[TILEY];


	inline pFogs getFogs(void) { return _fogs; }


};

