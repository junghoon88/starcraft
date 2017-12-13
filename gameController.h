#pragma once
#include "gameNode.h"

#include "player.h"
#include "Unit.h"
#include "Building.h"

enum CURSORSTATE
{
	CURSORSTATE_IDLE,				// 기본상태
	CURSORSTATE_FOCUS_TO_ME,		// MOVE, ATTACK 등 조준상태
	CURSORSTATE_FOCUS_TO_NEUTRAL,	// MOVE, ATTACK 등 조준상태
	CURSORSTATE_FOCUS_TO_ENEMY,		// MOVE, ATTACK 등 조준상태
	CURSORSTATE_ON_ME,				// 유닛, 건물 위에 올려놨을때 상태
	CURSORSTATE_ON_NEUTRAL,			// 유닛, 건물 위에 올려놨을때 상태
	CURSORSTATE_ON_ENEMY,			// 유닛, 건물 위에 올려놨을때 상태
	CURSORSTATE_DRAGING,			// 드래그 상태
	
	CURSORSTATE_MOVE_LF,			// 카메라 움직일 때 
	CURSORSTATE_MOVE_LU,			// 카메라 움직일 때 
	CURSORSTATE_MOVE_UP,			// 카메라 움직일 때 
	CURSORSTATE_MOVE_RU,			// 카메라 움직일 때 
	CURSORSTATE_MOVE_RG,			// 카메라 움직일 때 
	CURSORSTATE_MOVE_RD,			// 카메라 움직일 때 
	CURSORSTATE_MOVE_DN,			// 카메라 움직일 때 
	CURSORSTATE_MOVE_LD,			// 카메라 움직일 때 
	
};

struct tagSelectInfo
{
	BOOL			isSelected;

	BOOL			isBuilding;

	UINT			unitNum;
	Unit*			unit[12];
	Building*		building;
};

struct tagUnitCommands
{
	DWORD	curCommand;
	DWORD	commands[COMMAND_MAX];
	image*	img[COMMAND_MAX];
	RECT	rc[COMMAND_MAX];
};


class gameController : public gameNode
{
private:
	PLAYER			_playerNum;
	image*			_imgInterface;


	//마우스 커서 관련
	BOOL			_isInInterface;
	CURSORSTATE		_cursorState;
	DWORD			_command;
	tagUnitCommands	_unitCommandInfo;

	image*			_imgCursor;
	UINT			_frameCursor;
	FLOAT			_frameCursorTime;

	BOOL			_isClicked;
	BOOL			_isDraging;
	POINT			_ptDragStart;



	
	tagSelectInfo	_selectInfo;	//마우스로 클릭한 유닛 혹은 건물의 정보


private:
	player*			_player[PLAYER_NUM]; //플레이어정보, sceneBattle 에서 받는다.

public:
	gameController();
	~gameController();

	HRESULT init(PLAYER playerNum, RACES races);
	void release(void);
	void update(void);
	void render(void);

private:
	void initCommandRect(void);

	void actionMouseInterface(void);
	void actionMouseMap(void);
	BOOL actionHotkeys(void);

	void setImageCursor(void);
	void setCommandSet(void);

	void renderCursor(void);

	void renderInterface(void);
	void renderCommands(void);

	TEAM searchObject();
	TEAM clickObject();
	TEAM dragObjects(RECT rcDrag);

public:
	inline void setLinkAdressPlayers(player* player, PLAYER playerNum) { _player[playerNum] = player; }
};

