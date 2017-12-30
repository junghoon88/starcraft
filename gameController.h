#pragma once
#include "gameNode.h"

#include "Unit.h"
#include "Building.h"
#include "gameMap.h"

#include "hotkeys.h"
#include "miniMap.h"
#include "button.h"


//���漱��
class player;

#define SELECTUNIT_MAX	12

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
	
	CURSORSTATE_BUILD_NORMAL,		// �ǹ�-�⺻
	CURSORSTATE_BUILD_HATCHERY,		// �ǹ�-��ó��
	CURSORSTATE_BUILD_EXTRACTOR,	// �ǹ�-����

};

struct tagSelectInfo
{
	BOOL			isSelected;

	UINT			num;
	gameObject*		object[SELECTUNIT_MAX];
};

struct tagUnitCommands
{
	COMMAND	curCommand;
	COMMAND	commands[COMMAND_MAX];
	image*	img[COMMAND_MAX];
};

struct tagCommandSet
{
	COMMAND	command;
	image*	img;
	RECT	rc;
	TCHAR	hotkey;
	button* button;
};

enum BUILDSTATE
{
	BUILDSTATE_NONE,		//
	BUILDSTATE_PLACEABLE,	//�ǹ� ��ġ�� �� ����
	BUILDSTATE_OVERLAP,		//�ǹ� ��ġ�Ұ�(��ħ)
};


class gameController : public gameNode
{
private:
	PLAYER				_playerNum;
	image*				_imgInterface;


	//���콺 Ŀ�� ����
	BOOL				_isInInterface;					//�������̽� ���� ���� �ִ���?
	CURSORSTATE			_cursorState;					//Ŀ�� ����
	image*				_imgCursor;						//Ŀ�� �̹���
	UINT				_frameCursor;					//Ŀ�� �̹��� ������
	FLOAT				_frameCursorTime;				//Ŀ�� �̹��� ������ ��� �ð�

	BOOL				_isClicked;						//Ŭ���ߴ���
	BOOL				_isDraging;						//�巡�� ��������
	POINT				_ptDragStart;					//�巡�� ���� ��ġ
	BOOL				_findTarget;					//Ÿ�� ������ �޴� ���϶�
	BOOL				_findLocation;					//�ǹ� ��ġ ���Ҷ�
	POINT				_buildingSize;					//�ǹ� ũ��
	BUILDSTATE			_buildingPlaceable[OBJECTSIZE_MAX_X][OBJECTSIZE_MAX_Y];				//�ǹ� ��ġ ���ɿ���(Ÿ�Ϻ���)
	BOOL				_buildable;						//�ǹ� ������ �ִ���

	//���콺 ����
	POINT				_cursorPt;						//ī�޶� ��ġ ����� ���콺 ��ġ
	POINT				_cursorTile;					//ī�޶� ��ġ ����� ���콺 ��ġ�� Ÿ�� ��ȣ



	//Ŀ�ǵ� ����
	COMMAND				_curCommand;					//���� ������Ʈ�ѷ����� ������ Ŀ�ǵ�
	//COMMAND				_oldCommand;					//ESC �� �ǵ��� �ð�� �����
	tagCommandSet		_commandSet[COMMAND_MAX];		//ȭ�� ������ ������ Ŀ�ǵ� 9��

	COMMAND				_unitCommandInfo;				//������ ������ ���� Ŀ�ǵ� ����

	COMMAND				_commandSetEsc[COMMAND_MAX];	//esc �� �ʿ��Ҷ� Ŀ�ǵ� ��Ʈ
	COMMAND				_commandSetBuild1[COMMAND_MAX];	//����1 Ŀ�ǵ� ��Ʈ
	COMMAND				_commandSetBuild2[COMMAND_MAX];	//����2 Ŀ�ǵ� ��Ʈ
	COMMAND				_commandSetUnit[COMMAND_MAX];	//������ �����ϰ� �ִ� Ŀ�ǵ� 9��

	
	tagSelectInfo		_selectInfo;	//���콺�� Ŭ���� ���� Ȥ�� �ǹ��� ����

	hotkeys*			_hotkeys;		//����Ű Ŭ����
	miniMap*			_miniMap;		//�̴ϸ� Ŭ����

	gameMap*			_gameMap;

private:
	player*			_myPlayer;
	player*			_player[PLAYER_NUM]; //�÷��̾�����, sceneBattle ���� �޴´�.

public:
	gameController();
	~gameController();

	HRESULT init(PLAYER playerNum, RACES races);
	void release(void);
	void update(void);
	void render(void);

private:
	void initCommandSet(void);

	void calcMouseRealPosition(void);
	BOOL actionHotkeys(void);
	void actionMouseMap(void);
	void actionMouseMiniMap(void);
	void actionMouseCommandSet(int num);
	void actionMouseImageFace(void);


	void setImageCursor(void);
	BOOL checkBuildable(void);



	void actionCommand(void);
	void setCommandSet(void);
	void matchingCommandHotkey(void);
	void matchingCommandImage(void);


	void renderInterface(void);
	void renderSelectInfo(void);
	void renderCommands(void);

	void renderBuildImage(void);
	void renderCursor(void);


	TEAM searchObject();
	TEAM clickObject();
	TEAM dragObjects(RECT rcDrag);

	gameObject* getTargetInfo(void);

	void clearSelectInfo(void);
	void clearSelectInfo(gameObject* object);
	void checkSelectInfo(void);
	void refreshSelectInfo(void);



public:
	//���� ������ ������ ���� ������Ʈ�� �������ִ� �Լ� (��:���->��ó��)
	void changeSelectInfoToNextObect(gameObject* object);
	//��ٸ� �����ϴ� �Լ�(��ó��, ����, ���̺� 3�� �� ��ߵǼ� void* �� ��.)
	void changeSelectInfoToLarva(void* hatchery, BUILDINGNUM_ZERG buildingNum); 



public:
	inline void setLinkAdressMyPlayer(player* player) { _myPlayer = player; };
	inline void setLinkAdressPlayers(player* player, PLAYER playerNum) { _player[playerNum] = player; }
	inline void setLinkAdressGameMap(gameMap* map) { _gameMap = map; }

	//button callback function
	inline static void cbCommandFunc0(void* obj) { gameController* gc = (gameController*)obj; gc->actionMouseCommandSet(0); }
	inline static void cbCommandFunc1(void* obj) { gameController* gc = (gameController*)obj; gc->actionMouseCommandSet(1); }
	inline static void cbCommandFunc2(void* obj) { gameController* gc = (gameController*)obj; gc->actionMouseCommandSet(2); }
	inline static void cbCommandFunc3(void* obj) { gameController* gc = (gameController*)obj; gc->actionMouseCommandSet(3); }
	inline static void cbCommandFunc4(void* obj) { gameController* gc = (gameController*)obj; gc->actionMouseCommandSet(4); }
	inline static void cbCommandFunc5(void* obj) { gameController* gc = (gameController*)obj; gc->actionMouseCommandSet(5); }
	inline static void cbCommandFunc6(void* obj) { gameController* gc = (gameController*)obj; gc->actionMouseCommandSet(6); }
	inline static void cbCommandFunc7(void* obj) { gameController* gc = (gameController*)obj; gc->actionMouseCommandSet(7); }
	inline static void cbCommandFunc8(void* obj) { gameController* gc = (gameController*)obj; gc->actionMouseCommandSet(8); }
};

