#include "stdafx.h"
#include "bullets.h"

//잡몹 공격 - 폭탄던지기
grenade::grenade(){}

grenade::~grenade(){}

HRESULT grenade::init(const char* imageName, int bulletMax)
{
	_imageName = imageName;
	_bulletMax = bulletMax;

	_gravity = 0.04f;

	return S_OK;
}

void grenade::release(void)
{
}

void grenade::update(void)
{
	move();
}

void grenade::render(float x, float y)
{
	for (_viGrenade = _vGrenade.begin(); _viGrenade != _vGrenade.end(); ++_viGrenade)
	{
		_viGrenade->bulletImage->render(getMemDC(), _viGrenade->rc.left - x, _viGrenade->rc.top - y);
	}
}


void grenade::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vGrenade.size()) return;

	tagBullet grenade;
	ZeroMemory(&grenade, sizeof(tagBullet));
	grenade.bulletImage = IMAGEMANAGER->findImage(_imageName);
	grenade.speed = speed;
	grenade.angle = angle;
	grenade.radius = grenade.bulletImage->getWidth() / 2;
	grenade.x = grenade.fireX = x;
	grenade.y = grenade.fireY = y;
	grenade.rc = RectMakeCenter(grenade.x, grenade.y, grenade.bulletImage->getWidth(), grenade.bulletImage->getHeight());
	_gravity = 0;

	_vGrenade.push_back(grenade);
}


void grenade::move(void)
{
	for (_viGrenade = _vGrenade.begin(); _viGrenade != _vGrenade.end();)
	{
		_gravity += 0.080f;
		_viGrenade->x += cosf(_viGrenade->angle) * _viGrenade->speed;
		_viGrenade->y += -sinf(_viGrenade->angle) * _viGrenade->speed + _gravity;

		_viGrenade->rc = RectMakeCenter(_viGrenade->x, _viGrenade->y, _viGrenade->bulletImage->getWidth(), _viGrenade->bulletImage->getHeight());

		++_viGrenade;
	}
}


void grenade::removeBullet(int arrNum)
{
	_vGrenade.erase(_vGrenade.begin() + arrNum);
}

//독인데... 일단보류
void grenade::poision(void)
{
	RECT poision;
	poision = RectMakeCenter(_poisionX, _poisionY, 30, 30);
}

//잡몹 공격 - 단도던지기
knife::knife(){}

knife::~knife(){}

HRESULT knife::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void knife::release(void)
{
}

void knife::update(void)
{
	move();
}

void knife::render(void)
{
	for (_viKnife = _vKnife.begin(); _viKnife != _vKnife.end(); ++_viKnife)
	{
		//_vibossGrenade->bulletImage->render(getMemDC(), _vibossGrenade->rc.left, _vibossGrenade->rc.top);
	}
}


void knife::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vKnife.size()) return;

	tagBullet knife;
	ZeroMemory(&knife, sizeof(tagBullet));
	knife.bulletImage = IMAGEMANAGER->findImage(_imageName);
	knife.speed = speed;
	knife.radius = knife.bulletImage->getWidth() / 2;
	knife.x = knife.fireX = x;
	knife.y = knife.fireY = y;
	knife.rc = RectMakeCenter(knife.x, knife.y, knife.bulletImage->getWidth(), knife.bulletImage->getHeight());

	_vKnife.push_back(knife);
}


void knife::move(void)
{
	for (_viKnife = _vKnife.begin(); _viKnife != _vKnife.end();)
	{
		_viKnife->x += _viKnife->speed;

		_viKnife->rc = RectMakeCenter(_viKnife->x, _viKnife->y, _viKnife->bulletImage->getWidth(), _viKnife->bulletImage->getHeight());

		if (_range < getDistance(_viKnife->fireX, _viKnife->fireY, _viKnife->x, _viKnife->y))
		{
			_viKnife = _vKnife.erase(_viKnife);
		}
		else ++_viKnife;
	}
}

//보스공격 - 수류탄
bossgrenade::bossgrenade(){}

bossgrenade::~bossgrenade(){}

HRESULT bossgrenade::init(const char* imageName, int bulletMax, float range)
{
	_imageName = imageName;
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bossgrenade::release(void)
{
}

void bossgrenade::update(void)
{
	move();
}

void bossgrenade::render(void)
{
	for (_vibossGrenade = _vbossGrenade.begin(); _vibossGrenade != _vbossGrenade.end(); ++_vibossGrenade)
	{
		//_vibossGrenade->bulletImage->render(getMemDC(), _vibossGrenade->rc.left, _vibossGrenade->rc.top);
	}
}


void bossgrenade::fire(float x, float y, float angle, float speed)
{
	if (_bulletMax < _vbossGrenade.size()) return;

	tagBullet bossgrenade;
	ZeroMemory(&bossgrenade, sizeof(tagBullet));
	bossgrenade.bulletImage = IMAGEMANAGER->findImage(_imageName);
	bossgrenade.speed = speed; 
	bossgrenade.radius = bossgrenade.bulletImage->getWidth() / 2;
	bossgrenade.x = bossgrenade.fireX = x;
	bossgrenade.y = bossgrenade.fireY = y;
	bossgrenade.rc = RectMakeCenter(bossgrenade.x, bossgrenade.y, bossgrenade.bulletImage->getWidth(), bossgrenade.bulletImage->getHeight());

	_vbossGrenade.push_back(bossgrenade);
}


void bossgrenade::move(void)
{
	for (_vibossGrenade = _vbossGrenade.begin(); _vibossGrenade != _vbossGrenade.end();)
	{
		_vibossGrenade->x -= cosf((PI * 3) / 4) * _vibossGrenade->speed;
		_vibossGrenade->y += sinf((PI * 3) / 4) * _vibossGrenade->speed;

		_vibossGrenade->rc = RectMakeCenter(_vibossGrenade->x, _vibossGrenade->y, _vibossGrenade->bulletImage->getWidth(), _vibossGrenade->bulletImage->getHeight());
		
		++_vibossGrenade;
	}
}