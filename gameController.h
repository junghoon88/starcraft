#pragma once
#include "gameNode.h"

#include "Unit.h"
#include "Building.h"
#include "gameMap.h"

#include "hotkeys.h"
#include "miniMap.h"
#include "button.h"


//전방선언
class player;

#define SELECTUNIT_MAX	12

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
	BUILDSTATE_PLACEABLE,	//건물 설치할 수 있음
	BUILDSTATE_OVERLAP,		//건물 설치불가(겹침)
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
	BOOL				_findLocation;					//건물 위치 정할때
	POINT				_buildingSize;					//건물 크기
	BUILDSTATE			_buildingPlaceable[OBJECTSIZE_MAX_X][OBJECTSIZE_MAX_Y];				//건물 배치 가능여부(타일별로)
	BOOL				_buildable;						//건물 지을수 있는지

	//마우스 관련
	POINT				_cursorPt;						//카메라 위치 적용된 마우스 위치
	POINT				_cursorTile;					//카메라 위치 적용된 마우스 위치의 타일 번호



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

	gameMap*			_gameMap;

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
	//현재 선택한 정보를 다음 오브젝트로 변경해주는 함수 (예:드론->해처리)
	void changeSelectInfoToNextObect(gameObject* object);
	//라바를 선택하는 함수(해처리, 레어, 하이브 3개 다 써야되서 void* 로 함.)
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

