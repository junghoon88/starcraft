#include "stdafx.h"
#include "mainGame.h"

#include "sceneInit.h"
#include "sceneSelect.h"
#include "sceneMaptool.h"



mainGame::mainGame()
{
	_stop = false;
	_winsize = { WINSIZEX, WINSIZEY };
	_FPS = 60.0f;
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
	
	SCENEMANAGER->addScene(L"�ʱ�ȭ��", new sceneInit);  //���� ���ҽ� �ʱ�ȭ
	SCENEMANAGER->addScene(L"���þ�", new sceneSelect);
	SCENEMANAGER->addScene(L"������", new sceneMaptool);				//����


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

	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		//SCENEMANAGER->changeScene(L"���þ�");
	}

	SCENEMANAGER->update();
}

//�׷��ִ� �Լ�
void mainGame::render(void)	
{
	//��� ��ȭ�� �� �� �ʿ�
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//==============================================================
	
	SCENEMANAGER->render();


	RENDERMANAGER->render();

	TIMEMANAGER->render(getMemDC());
	
	//========================================================================
	//����ۿ� �ִ°� HDC�� �׷��ִ� ����
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

void mainGame::getChar(WPARAM wParam)
{
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

