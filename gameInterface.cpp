#include "stdafx.h"
#include "gameInterface.h"

#include "gameController.h"
#include "player.h"

gameInterface::gameInterface()
	: _progressBar(NULL), _gameController(NULL)
{
	_imgIconWeapon[0] = NULL;
	_imgIconWeapon[1] = NULL;
	_imgIconWeapon[2] = NULL;
	_imgIconFrameX[0] = 0;
	_imgIconFrameX[1] = 0;
	_imgIconFrameX[2] = 0;
}


gameInterface::~gameInterface()
{
}

HRESULT gameInterface::init(void)
{
	initVariables();


	_progressBar = new progressBar;
	_progressBar->init(L"Mutating");
	_progressBar->setPointLT(263, 427);

	return S_OK;
}



void gameInterface::release(void)
{
	SAFE_RELEASEDELETE(_progressBar);
}

void gameInterface::update(void) 
{
	updateFace();
	updateIconWeapon();

	updateSelectInfo();
}

void gameInterface::render(void) 
{
	//선택된 유닛, 건물의 정보를 보여준다.
	renderSelectInfo();


}



void gameInterface::initVariables(void)
{
	_rcStat1 = RectMake(153, 374, 89, 96);

	for (int i = 0; i < SELECTUNIT_MAX; i++)
	{
		int posx = 168 + (i / 2) * 36;
		int posy = 396 + (i % 2) * 37;

		_rcStat2[i] = RectMake(posx, posy, 33, 34);
	}

	_rcFace = RectMake(417, 415, 50, 55);

	for (int i = 0; i < 3; i++)
	{
		_rcIconWeapon[i] = RectMake(242 + i * 39, 439, 36, 36);
	}
}

void gameInterface::updateFace(void)
{
	if (PtInRect(&_rcFace, _ptMouse) == FALSE)
		return;

	tagSelectInfo selectInfo = _gameController->getSelectInfo();

	if (selectInfo.isSelected && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		bool valid = false;

		int index = 0;
		int topUnit = UNITNUM_ZERG_NONE;

		for (int i = 0; i < SELECTUNIT_MAX; i++)
		{
			if (selectInfo.object[i] == NULL) continue;

			if (selectInfo.object[i]->getValid())
			{
				valid = true;
			}

			//유닛중에 제일 높은애를 찾는다.
			if (topUnit < selectInfo.object[i]->getUnitnumZerg())
			{
				topUnit = selectInfo.object[i]->getUnitnumZerg();
				index = i;
			}
		}

		if (valid)
		{
			POINT pt = selectInfo.object[index]->getBattleStatus().pt.toPoint();
			MAINCAMERA->setCameraX(pt.x - WINSIZEX / 2);
			MAINCAMERA->setCameraY(pt.y - WINSIZEY / 2);
		}
	}
}

void gameInterface::updateIconWeapon(void)
{
	tagSelectInfo selectInfo = _gameController->getSelectInfo();

	if (selectInfo.num == 1)
	{
		if (selectInfo.object[0]->getIsBuilding())
		{
			switch (selectInfo.object[0]->getBuildingNumZerg())
			{
			case BUILDINGNUM_ZERG_SUNKENCOLONY:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-atkSunken");
				_imgIconFrameX[0] = 0;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case BUILDINGNUM_ZERG_SPORECOLONY:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-atkSpore");
				_imgIconFrameX[0] = 0;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
				break;

			default:
				_imgIconWeapon[0] = NULL;
				_imgIconFrameX[0] = 0;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;
			}

		}
		else
		{
			zergUpgrade* zUpgrade = _player[selectInfo.object[0]->getPlayerNum()]->getZergUpgrade();

			switch (selectInfo.object[0]->getUnitnumZerg())
			{
			//GROUND
			case UNITNUM_ZERG_LARVA:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depGround");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_ZERGEGG:
				_imgIconWeapon[0] = NULL;
				_imgIconFrameX[0] = 0;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_DRONE:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depGround");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level;
				_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkDrone");
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_ZERGLING:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depGround");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level;
				_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkZergling");
				_imgIconFrameX[1] = zUpgrade->getUpgrade()[UPGRADE_ZERG_MELEEATTACKS].level;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_HYDRALISK:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depGround");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level;
				_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkHydralisk");
				_imgIconFrameX[1] = zUpgrade->getUpgrade()[UPGRADE_ZERG_MISSILEATTACKS].level;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_LURKER:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depGround");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level;
				if (selectInfo.object[0]->getBaseStatus().GWable)
				{
					_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkLurker");
					_imgIconFrameX[1] = zUpgrade->getUpgrade()[UPGRADE_ZERG_MISSILEATTACKS].level;
				}
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_LURKEREGG:
				_imgIconWeapon[0] = NULL;
				_imgIconFrameX[0] = 0;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_ULTRALISK:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depGround");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level + (UINT)zUpgrade->getEvolution()[EVOLUTION_ZERG_CHITINOUS_PLATING].complete * 2;
				_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkUltra");
				_imgIconFrameX[1] = zUpgrade->getUpgrade()[UPGRADE_ZERG_MELEEATTACKS].level;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_BROODLING:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depGround");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level;
				_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkBroodring");
				_imgIconFrameX[1] = zUpgrade->getUpgrade()[UPGRADE_ZERG_MELEEATTACKS].level;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_DEFILER:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depGround");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_INFESTEDTERRAN:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depGround");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_CARAPACE].level;
				_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkInfest");
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;


			//AIR
			case UNITNUM_ZERG_OVERLORD:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depFlying");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERCARAPACE].level;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_MUTALISK:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depFlying");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERCARAPACE].level;
				_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkMutalisk");
				_imgIconFrameX[1] = zUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERATTACKS].level;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_SCOURGE:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depFlying");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERCARAPACE].level;
				_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkScourge");
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_QUEEN:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depFlying");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERCARAPACE].level;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_COCOON:
				_imgIconWeapon[0] = NULL;
				_imgIconFrameX[0] = 0;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;

			case UNITNUM_ZERG_GUADIAN:
			case UNITNUM_ZERG_DEVOURER:
				_imgIconWeapon[0] = IMAGEMANAGER->findImage(L"iconWeapon-depFlying");
				_imgIconFrameX[0] = zUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERCARAPACE].level;
				_imgIconWeapon[1] = IMAGEMANAGER->findImage(L"iconWeapon-atkGuadian");
				_imgIconFrameX[1] = zUpgrade->getUpgrade()[UPGRADE_ZERG_FLYERATTACKS].level;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;


			default:
				_imgIconWeapon[0] = NULL;
				_imgIconFrameX[0] = 0;
				_imgIconWeapon[1] = NULL;
				_imgIconFrameX[1] = 0;
				_imgIconWeapon[2] = NULL;
				_imgIconFrameX[2] = 0;
			break;
			}
		}
	}
	else
	{
		_imgIconWeapon[0] = NULL;
		_imgIconFrameX[0] = 0;
		_imgIconWeapon[1] = NULL;
		_imgIconFrameX[1] = 0;
		_imgIconWeapon[2] = NULL;
		_imgIconFrameX[2] = 0;
	}
}

void gameInterface::updateSelectInfo(void)
{
	tagSelectInfo selectInfo = _gameController->getSelectInfo();
	
	if (selectInfo.isSelected == FALSE)
		return;

	if (selectInfo.num == 1)
		return;

	for (int i = 0; i < SELECTUNIT_MAX; i++)
	{
		if (PtInRect(&_rcStat2[i], _ptMouse) == FALSE) continue;

		if (selectInfo.object[i])
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				if (KEYMANAGER->isStayKeyDown(VK_SHIFT))
				{
					_gameController->deleteSelectInfo(i);
				}
				else if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
				{
					_gameController->filterSelectInfo(i);
				}
				else
				{
					_gameController->onlySelecInfo(i);
				}
			}
		}
		break;
	}
}



void gameInterface::renderSelectInfo(void)
{
	tagSelectInfo selectInfo = _gameController->getSelectInfo();

	if (selectInfo.num == 0)
	{
		return;
	}
	else if (selectInfo.num == 1)
	{
		tagBaseStatus baseStatus = selectInfo.object[0]->getBaseStatus();
		tagBattleStatus battleStatus = selectInfo.object[0]->getBattleStatus();
		tagProcessing processing = selectInfo.object[0]->getProcessing();

		//유닛 이름
		RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(248, 389, 140, 16), baseStatus.name, TEXTCOLOR_UNITNAME);


		//디텍터
		if (baseStatus.detector)
		{
			RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(295, 406, 50, 16), L"Detector", TEXTCOLOR_DETECTOR);
		}

		//Kills
		switch (selectInfo.object[0]->getUnitnumZerg())
		{
			case UNITNUM_ZERG_DRONE:
			case UNITNUM_ZERG_ZERGLING:
			case UNITNUM_ZERG_HYDRALISK:
			case UNITNUM_ZERG_LURKER:
			case UNITNUM_ZERG_ULTRALISK:
			case UNITNUM_ZERG_BROODLING:
			case UNITNUM_ZERG_MUTALISK:
			case UNITNUM_ZERG_QUEEN:
			case UNITNUM_ZERG_GUADIAN:
			case UNITNUM_ZERG_DEVOURER:
			{
				TCHAR strKill[100];
				_stprintf(strKill, L"Kills: %d", selectInfo.object[0]->getBattleStatus().kills);
				RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(274, 415, 80, 18), strKill, TEXTCOLOR_UNITNAME);
			}
			break;
		}

		//Stat1
		RENDERMANAGER->insertImg(ZORDER_INTERFACE2, baseStatus.imgStat1, _rcStat1.left, _rcStat1.top);

		//Face
		RENDERMANAGER->insertImg(ZORDER_INTERFACE2, baseStatus.imgFace, _rcFace.left, _rcFace.top);

		renderIconWeapon();


		if ((INT)battleStatus.maxHP > 0)
		{
			//HP
			TCHAR strHP[100];
			_stprintf(strHP, L"%d / %d", (INT)battleStatus.curHP, (INT)battleStatus.maxHP);
			RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(153, 453, 89, 12), strHP, TEXTCOLOR_UNITHP);
		}

		if (baseStatus.useMP)
		{
			//MP
			TCHAR strMP[100];
			_stprintf(strMP, L"%d / %d", (INT)battleStatus.curMP, (INT)battleStatus.maxMP);
			RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(153, 470, 89, 12), strMP, TEXTCOLOR_UNITMP);
		}

		//진행작업표시
		switch (processing.type)
		{
		case PROCESSING_MUTATING:
			_progressBar->setPointLT(263, 427);
			_progressBar->setGauge(processing.curTime, processing.maxTime);
			_progressBar->ZRender(ZORDER_INTERFACE2);
			RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(292, 410, 48, 16), L"Mutating", TEXTCOLOR_UNITNAME);
			break;
		case PROCESSING_MORPHING:
			_progressBar->setPointLT(282, 427);
			_progressBar->setGauge(processing.curTime, processing.maxTime);
			_progressBar->ZRender(ZORDER_INTERFACE2);
			RENDERMANAGER->insertImgFrame(ZORDER_INTERFACE2, processing.img, 242, 410, 0, 0);
			RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(309, 410, 50, 16), L"Morphing", TEXTCOLOR_UNITNAME);
			break;
		case PROCESSING_EVOLVING:
			_progressBar->setPointLT(282, 427);
			_progressBar->setGauge(processing.curTime, processing.maxTime);
			_progressBar->ZRender(ZORDER_INTERFACE2);
			RENDERMANAGER->insertImgFrame(ZORDER_INTERFACE2, processing.img, 242, 410, 0, 0);
			RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(309, 410, 50, 16), L"Evolving", TEXTCOLOR_UNITNAME);
			break;
		}

		//자원량
		if (selectInfo.object[0]->getIsNrMineral())
		{
			TCHAR strMineral[100];
			_stprintf(strMineral, L"Minerals: %d", selectInfo.object[0]->getAmountMineral());
			RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(273, 430, 120, 16), strMineral, TEXTCOLOR_UNITNAME);
		}
		else if (selectInfo.object[0]->getIsNrGas())
		{
			TCHAR strGas[100];
			_stprintf(strGas, L"Vespene Gas: %d", selectInfo.object[0]->getAmountGas());
			RENDERMANAGER->insertTextCenter(ZORDER_INTERFACE2, RectMake(273, 430, 120, 16), strGas, TEXTCOLOR_UNITNAME);
		}
	}
	else
	{
		bool valid = false;
		
		int index = 0;
		int topUnit = UNITNUM_ZERG_NONE;

		//Stat2
		for (int i = 0; i < SELECTUNIT_MAX; i++)
		{
			if (selectInfo.object[i] == NULL) continue;

			if (selectInfo.object[i]->getValid())
			{
				valid = true;
			}

			//유닛중에 제일 높은애를 찾는다.
			if (topUnit < selectInfo.object[i]->getUnitnumZerg())
			{
				topUnit = selectInfo.object[i]->getUnitnumZerg();
				index = i;
			}

			RENDERMANAGER->insertImg(ZORDER_INTERFACE2, selectInfo.object[i]->getBaseStatus().imgStat2, _rcStat2[i].left, _rcStat2[i].top);
		}

		//Face
		if (valid)
		{
			RENDERMANAGER->insertImg(ZORDER_INTERFACE2, selectInfo.object[index]->getBaseStatus().imgFace, _rcFace.left, _rcFace.top);
		}
	}
}

void gameInterface::renderIconWeapon(void)
{
	for (int i = 0; i < 3; i++)
	{
		if (_imgIconWeapon[i] == NULL) continue;

		RENDERMANAGER->insertImgFrame(ZORDER_INTERFACE2, _imgIconWeapon[i], _rcIconWeapon[i].left, _rcIconWeapon[i].top, _imgIconFrameX[i], 0);
	}

}
