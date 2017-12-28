#include "stdafx.h"
#include "mainGame.h"

#include "sceneInit.h"
#include "sceneSelect.h"
#include "sceneMaptool.h"
#include "sceneBattle.h"



mainGame::mainGame()
{
	_stop = false;
	_winsize = { WINSIZEX, WINSIZEY };
	_FPS = 60.0f;

	//Unit클래스 내에 static변수를 초기화하기 위해

	_gameStart = FALSE;
}


mainGame::~mainGame()
{
}


//초기화
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	initScene();

	return S_OK;
}

void mainGame::initScene(void)
{
	gameNode* node = NULL;
	
	node = SCENEMANAGER->addScene(L"초기화씬", new sceneInit);  //게임 리소스 초기화
	node = SCENEMANAGER->addScene(L"선택씬", new sceneSelect);
	node = SCENEMANAGER->addScene(L"맵툴씬", new sceneMaptool);				//맵툴
	node = SCENEMANAGER->addScene(L"전투씬", new sceneBattle);				//맵툴


	SCENEMANAGER->changeScene(L"초기화씬");

}



//메모리 해제
void mainGame::release(void)
{
	SCENEMANAGER->release();
	
	gameNode::release();
}

//연산관련(타이머)
void mainGame::update(void)
{
	gameNode::update();

	checkWindowSize();
	controlFPS();
	//playBGM();




	MAINCAMERA->update();

	SCENEMANAGER->update();
}

//그려주는 함수
void mainGame::render(void)	
{
	//흰색 도화지 한 장 필요
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================
	
	SCENEMANAGER->render();



	TIMEMANAGER->render(getMemDC());
	MAINCAMERA->render(getMemDC());
	
	//========================================================================
	//백버퍼에 있는걸 HDC로 그려주는 역할
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void mainGame::getChar(WPARAM wParam)
{
	SCENEMANAGER->getChar(wParam);

}

void mainGame::checkScene(void)
{
	if (SCENEMANAGER->willChangeScene() == TRUE)
	{
		SCENEMANAGER->changeScene();

		MAINCAMERA->setCameraPos(0, 0);

		if (_gameStart == FALSE && SCENEMANAGER->isCurScene(L"전투씬"))
		{
			_gameStart = TRUE;
		}
	}
}

void mainGame::setWindowResize(POINT size)
{
	if (_winsize.x == size.x && _winsize.y == size.y)
		return;

	_stop = true; 
	_winsize = size;
}

void mainGame::checkWindowSize(void)
{

}

void mainGame::controlFPS(void)
{
}

