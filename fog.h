#pragma once
#include "gameNode.h"
#include "tileNode.h"

class gameMap;
class player;

class fog : public gameNode
{
private:
	image*		_imgFog;
	tagFog		_fogs[TILEX][TILEY];	//Ÿ�Ϻ��� ������ fog

	vector<RECT> _vObjectViewRect;	//������Ʈ�� ������ �ִ� �þ� ��Ʈ
	vector<RECT> _vObjectDetectRect;	//������Ʈ�� ������ �ִ� �þ� ��Ʈ

	

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

