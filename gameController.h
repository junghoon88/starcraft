#pragma once
#include "gameNode.h"

#include "player.h"
#include "Unit.h"
#include "Building.h"

enum CURSORSTATE
{
	CURSORSTATE_IDLE,				// �⺻����
	CURSORSTATE_FOCUS_TO_ME,		// MOVE, ATTACK �� ���ػ���
	CURSORSTATE_FOCUS_TO_NEUTRAL,	// MOVE, ATTACK �� ���ػ���
	CURSORSTATE_FOCUS_TO_ENEMY,		// MOVE, ATTACK �� ���ػ���
	CURSORSTATE_ON_ME,				// ����, �ǹ� ���� �÷������� ����
	CURSORSTATE_ON_NEUTRAL,			// ����, �ǹ� ���� �÷������� ����
	CURSORSTATE_ON_ENEMY,			// ����, �ǹ� ���� �÷������� ����
	CURSORSTATE_DRAGING,			// �巡�� ����
	
	CURSORSTATE_MOVE_LF,			// ī�޶� ������ �� 
	CURSORSTATE_MOVE_LU,			// ī�޶� ������ �� 
	CURSORSTATE_MOVE_UP,			// ī�޶� ������ �� 
	CURSORSTATE_MOVE_RU,			// ī�޶� ������ �� 
	CURSORSTATE_MOVE_RG,			// ī�޶� ������ �� 
	CURSORSTATE_MOVE_RD,			// ī�޶� ������ �� 
	CURSORSTATE_MOVE_DN,			// ī�޶� ������ �� 
	CURSORSTATE_MOVE_LD,			// ī�޶� ������ �� 
	
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


	//���콺 Ŀ�� ����
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



	
	tagSelectInfo	_selectInfo;	//���콺�� Ŭ���� ���� Ȥ�� �ǹ��� ����


private:
	player*			_player[PLAYER_NUM]; //�÷��̾�����, sceneBattle ���� �޴´�.

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

