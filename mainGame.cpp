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

	//UnitŬ���� ���� static������ �ʱ�ȭ�ϱ� ����

	_gameStart = FALSE;
}


mainGame::~mainGame()
{
}


//�ʱ�ȭ
HRESULT mainGame::init(void)
{
	gameNode::init(true);

	initScene();

	return S_OK;
}

void mainGame::initScene(void)
{
	gameNode* node = NULL;
	
	node = SCENEMANAGER->addScene(L"�ʱ�ȭ��", new sceneInit);  //���� ���ҽ� �ʱ�ȭ
	node = SCENEMANAGER->addScene(L"���þ�", new sceneSelect);
	node = SCENEMANAGER->addScene(L"������", new sceneMaptool);				//����
	node = SCENEMANAGER->addScene(L"������", new sceneBattle);				//����


	SCENEMANAGER->changeScene(L"�ʱ�ȭ��");

}



//�޸� ����
void mainGame::release(void)
{
	SCENEMANAGER->release();
	
	gameNode::release();
}

//�������(Ÿ�̸�)
void mainGame::update(void)
{
	gameNode::update();

	checkWindowSize();
	controlFPS();
	//playBGM();




	MAINCAMERA->update();

	SCENEMANAGER->update();
}

//�׷��ִ� �Լ�
void mainGame::render(void)	
{
	//��� ��ȭ�� �� �� �ʿ�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================
	
	SCENEMANAGER->render();



	TIMEMANAGER->render(getMemDC());
	MAINCAMERA->render(getMemDC());
	
	//========================================================================
	//����ۿ� �ִ°� HDC�� �׷��ִ� ����
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

		if (_gameStart == FALSE && SCENEMANAGER->isCurScene(L"������"))
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

