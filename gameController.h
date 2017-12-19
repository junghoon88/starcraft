#pragma once
#include "gameNode.h"

#include "Unit.h"
#include "Building.h"

#include "hotkeys.h"
#include "miniMap.h"
#include "button.h"

//전방선언
class player;

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
	
	CURSORSTATE_BUILD_NORMAL,		// 건물-기본
	CURSORSTATE_BUILD_HATCHERY,		// 건물-해처리
	CURSORSTATE_BUILD_EXTRACTOR,	// 건물-가스

};

enum TARGETTYPE
{
	TARGETTYPE_GROUND,
	TARGETTYPE_UNIT,
	TARGETTYPE_BUILDING,
};

struct tagSelectInfo
{
	BOOL			isSelected;

	BOOL			isMyTeam;		//내 유닛인지..ㅠㅠ

	BOOL			isBuilding;

	UINT			unitNum;
	Unit*			unit[12];
	Building*		building;
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


class gameController : public gameNode
{
private:
	PLAYER				_playerNum;
	image*				_imgInterface;


	//마우스 커서 관련
	BOOL				_isInInterface;					//인터페이스 영역 내에 있는지?
	CURSORSTATE			_cursorState;					//커서 상태
	image*				_imgCursor;						//커서 이미지
	UINT				_frameCursor;					//커서 이미지 프레임
	FLOAT				_frameCursorTime;				//커서 이미지 프레임 경과 시간

	BOOL				_isClicked;						//클릭했는지
	BOOL				_isDraging;						//드래그 상태인지
	POINT				_ptDragStart;					//드래그 시작 위치
	BOOL				_findTarget;					//타겟 정보를 받는 중일때
	BOOL				_findLocation;
	POINT				_buildingSize;


	//커맨드 관련
	COMMAND				_curCommand;					//현재 게임컨트롤러에서 선택한 커맨드
	//COMMAND				_oldCommand;					//ESC 로 되돌아 올경우 백업용
	tagCommandSet		_commandSet[COMMAND_MAX];		//화면 우측에 보여줄 커맨드 9개

	COMMAND				_unitCommandInfo;				//선택한 유닛의 현재 커맨드 상태

	COMMAND				_commandSetEsc[COMMAND_MAX];	//esc 만 필요할때 커맨드 세트
	COMMAND				_commandSetBuild1[COMMAND_MAX];	//빌드1 커맨드 세트
	COMMAND				_commandSetBuild2[COMMAND_MAX];	//빌드2 커맨드 세트
	COMMAND				_commandSetUnit[COMMAND_MAX];	//유닛이 보유하고 있는 커맨드 9개

	
	tagSelectInfo		_selectInfo;	//마우스로 클릭한 유닛 혹은 건물의 정보

	hotkeys*			_hotkeys;		//단축키 클래스
	miniMap*			_miniMap;		//미니맵 클래스


private:
	player*			_myPlayer;
	player*			_player[PLAYER_NUM]; //플레이어정보, sceneBattle 에서 받는다.

public:
	gameController();
	~gameController();

	HRESULT init(PLAYER playerNum, RACES races);
	void release(void);
	void update(void);
	void render(void);

private:
	void initCommandSet(void);

	BOOL actionHotkeys(void);
	void actionMouseMap(void);
	void actionMouseMiniMap(void);
	void actionMouseCommandSet(int num);
	void actionMouseImageFace(void);


	void setImageCursor(void);

	void actionCommand(void);
	void setCommandSet(void);
	void matchingCommandImage(void);

	void renderCursor(void);

	void renderInterface(void);
	void renderCommands(void);

	TEAM searchObject();
	TEAM clickObject();
	TEAM dragObjects(RECT rcDrag);

	void* getTargetInfo(TARGETTYPE &target, PLAYER &playerNum);



public:
	inline void setLinkAdressMyPlayer(player* player) { _myPlayer = player; };
	inline void setLinkAdressPlayers(player* player, PLAYER playerNum) { _player[playerNum] = player; }

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

