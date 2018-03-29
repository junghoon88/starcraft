#include "stdafx.h"
#include "bullets.h"


bullets::bullets(BULLETNUM bulletNum)
	: _master(NULL), _enemy(NULL)
{
	_valid = true;

	_bulletNum = bulletNum;
	_img = NULL;

	switch (_bulletNum)
	{
	case BULLETNUM_MUTALISK:
		_dmgType = DAMAGETYPE_NORMAL;
		_speed = 10.0f;
		_img = IMAGEMANAGER->findImage(L"ZU-mutalisk-Bullet");
		_zorder = ZORDER_GAMEOBJECTAIR;
		break;
	case BULLETNUM_GUADIAN:
		_dmgType = DAMAGETYPE_NORMAL;
		_speed = 10.0f;
		_img = IMAGEMANAGER->findImage(L"ZU-guadian-Bullet");
		_zorder = ZORDER_GAMEOBJECTAIR;
		break;
	case BULLETNUM_DEVOURER:
		_dmgType = DAMAGETYPE_EXPLOSIVE;
		_speed = 10.0f;
		_img = IMAGEMANAGER->findImage(L"ZU-devourer-Bullet");
		_zorder = ZORDER_GAMEOBJECTAIR;
		break;
	}

	_imgFrame = { 0, 0 };
	_imgFrameTime = 0.0f;

	if(_img == NULL)	_valid = false;
}


bullets::~bullets()
{
}

HRESULT bullets::init(gameObject* master, gameObject* enemy)
{
	_master = master;
	_enemy = enemy;


	if (enemy->getBaseStatus().isAir)
	{
		_damage = master->getBattleStatus().curAWdamage;
	}
	else
	{
		_damage = master->getBattleStatus().curGWdamage;
	}

	_startPt = master->getBattleStatus().pt.toPoint();
	_endPt = enemy->getBattleStatus().pt.toPoint();

	_angle = getAngle(_startPt.x, _startPt.y, _endPt.x, _endPt.y);

	_pt.set((float)_startPt.x, (float)_startPt.y);

	if (_img)
	{
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
	}
	else
	{
		_rc = RectMakeCenter(_pt.x, _pt.y, 32, 32);
	}


	return S_OK;
}

void bullets::release(void)
{
}

void bullets::update(void) 
{
	if (!_valid)
		return;

	bool last = false;
	float dist = getDistance(_pt.x, _pt.y, _endPt.x, _endPt.y);
	float length = _speed;// *TIMEMANAGER->getElapsedTime();

	if (length >= dist)
	{
		length = dist;
		last = true;
	}

	_pt.x += length * cosf(_angle);
	_pt.y += length * (-sinf(_angle));

	if (_img)
	{
		_rc = RectMakeCenter(_pt.x, _pt.y, _img->getFrameWidth(), _img->getFrameHeight());
	}
	else
	{
		_rc = RectMakeCenter(_pt.x, _pt.y, 32, 32);
	}


	if (last)
	{
		_valid = false;

		_enemy->hitDamage(_master, _damage, _dmgType);

		MYPOINT ptOffset = _pt;
		//ptOffset.move(-MAINCAMERA->getCameraX(), -MAINCAMERA->getCameraY());


		//ÀÌÆåÆ® Ãß°¡
		switch (_bulletNum)
		{
		case BULLETNUM_MUTALISK:
			EFFECTMANAGER->play(L"ZU-mutalisk-BulletEffect", ptOffset.x, ptOffset.y);
			break;
		case BULLETNUM_GUADIAN:
			EFFECTMANAGER->play(L"ZU-guadian-BulletEffect", ptOffset.x, ptOffset.y);
			break;
		case BULLETNUM_DEVOURER:
			break;
		}
	}


	if (_img)
	{
		float tick = TIMEMANAGER->getElapsedTime();

		_imgFrameTime += tick;
		if (_imgFrameTime >= (1.0f / 30))
		{
			_imgFrameTime -= (1.0f / 30);

			_imgFrame.x++;
			if (_imgFrame.x > _img->getMaxFrameX())
			{
				_imgFrame.x = 0;
			}

			_imgFrame.y++;
			if (_imgFrame.y > _img->getMaxFrameY())
			{
				_imgFrame.y = 0;
			}
		}
	}
}

void bullets::render(void) 
{
	if (!_valid)
		return;

	if (_img)
	{
		MYPOINT ptOffset = _pt;
		ptOffset.move(-MAINCAMERA->getCameraX(), -MAINCAMERA->getCameraY());
		RENDERMANAGER->insertImgFrame(_zorder, _img, ptOffset.x, ptOffset.y, _imgFrame.x, _imgFrame.y);
	}
	else
	{
		RENDERMANAGER->insertRectangle(_zorder, _rc, PENVERSION_BLUE2);
	}
}

