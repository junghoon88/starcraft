#include "stdafx.h"
#include "MBGManager.h"


MBGManager::MBGManager()
{
}


MBGManager::~MBGManager()
{
}

HRESULT MBGManager::init(wstring strImgName)
{
	_imgBG = IMAGEMANAGER->findImage(strImgName);
	if (!_imgBG)
		return E_FAIL;

	_hdcImg = _imgBG->getMemDC();

	hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 255));
	hBrush = CreateSolidBrush(RGB(255, 0, 255));

	return S_OK;
}
void MBGManager::release(void)
{
	if (!_imgBG)
		return;

	DeleteObject(hPen);
	DeleteObject(hBrush);

	SAFE_DELETE(_imgBG);
}
void MBGManager::update(void) 
{
	if (!_imgBG)
		return;

	for (int i = 0; i < _vExplosion.size(); i++)
	{
		tagExplosion* ex = &_vExplosion[i];
		if (ex->isExplosioned) continue;

		if (ex->explosionTime <= 0) 
			ex->explosionTime = 1;

		if (ex->explosionTimeCnt * 10 % ex->explosionTime == 0)
		{
			ex->explosionTimeCnt = 0;
			PlayExplosion(ex);				//Æø¹ß½ÇÇà
			ex->explosionCnt++; 
			if (ex->explosionCnt >= ex->explosionCntMax)
			{
				ex->isExplosioned = true;	//Æø¹ß ¿Ï·á
			}
			else
			{
				ex->pt.x += cosf(Deg2Rad(ex->angleDeg)) * ex->speed;
				ex->pt.y += -sinf(Deg2Rad(ex->angleDeg)) * ex->speed;
				ex->width *= (float)ex->explosionDamping / 100;
				ex->height *= (float)ex->explosionDamping / 100;
			}
		}
		ex->explosionTimeCnt++;			// ÇÑÆ½´ç 10ms
	}

	for (_viExplosion = _vExplosion.begin(); _viExplosion != _vExplosion.end();)
	{
		if ((*_viExplosion).isExplosioned)
		{
			_viExplosion = _vExplosion.erase(_viExplosion);
		}
		else ++_viExplosion;
	}
}
void MBGManager::render(void) 
{
	if (!_imgBG)
		return;

	_imgBG->render(getMemDC(), -MAINCAMERA->getCameraX(), -MAINCAMERA->getCameraY());

	oldPen	 = (HPEN)SelectObject(_hdcImg, hPen);
	oldBrush = (HBRUSH)SelectObject(_hdcImg, hBrush);

	for (int i = 0; i < _vRCTrace.size(); i++)
	{
		switch (_vRCTrace[i].type)
		{
		case EXPOLISION_TYPE_ELLIPSE:		//¿ø
			Ellipse(_hdcImg, _vRCTrace[i].rc.left, _vRCTrace[i].rc.top, _vRCTrace[i].rc.right, _vRCTrace[i].rc.bottom);
			break;
		case EXPOLISION_TYPE_RECTANGLE:		//»ç°¢Çü
			Rectangle(_hdcImg, _vRCTrace[i].rc.left, _vRCTrace[i].rc.top, _vRCTrace[i].rc.right, _vRCTrace[i].rc.bottom);
			break;
		}
		
	}

	SelectObject(_hdcImg, hPen);
	SelectObject(_hdcImg, hBrush);
}

void MBGManager::PlayExplosion(tagExplosion* ex)
{
	tagTrace trace;
	trace.type = ex->type;
	trace.rc = RectMakeCenter(ex->pt.x, ex->pt.y, ex->width, ex->height);
	_vRCTrace.push_back(trace);
}

void MBGManager::setExplosion(tagExplosion ex)
{
	_vExplosion.push_back(ex);
}


bool MBGManager::getisExplosion(void)
{
	if (_vExplosion.size() > 0) 
		return false;

	return true;
}
