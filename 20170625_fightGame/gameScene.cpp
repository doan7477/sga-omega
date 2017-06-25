#include "stdafx.h"
#include "gameScene.h"


gameScene::gameScene()
{
}


gameScene::~gameScene()
{
}

HRESULT gameScene::init()
{
	vStr = TXTDATA->txtLoad("캐릭터선택.txt");
	_selectedChar = (atoi(vStr[0].c_str()));

	if (_selectedChar == 1)
	{
		_player = new naruto;
		_player->init();
	}
	if (_selectedChar == 2)
	{
		_player = new lee;
		_player->init();
	}
	if (_selectedChar == 3)
	{
		_player = new sasuke;
		_player->init();
	}
	if (_selectedChar == 4)
	{
		_player = new sakura;
		_player->init();
	}

	_dummy = new dummy;
	_dummy->init();

	return S_OK;
}

void gameScene::release()
{

}

void gameScene::update()
{
	SOUNDMANAGER->update();
	_player->update();
	_dummy->update();
	collision();
}

void gameScene::render()
{
	IMAGEMANAGER->findImage("픽셀라인")->render(getMemDC(), 0, 0);
	IMAGEMANAGER->render("백그라운드", getMemDC(), 0, 0);

	_player->render();
	_dummy->render();
}

void gameScene::collision()
{
	RECT temp;
	if (IntersectRect(&temp, &_player->getPlayerAttackRange(), &_dummy->getRect()))
	{
		if (_player->getPlayerStruct().playerState == PLAYERSTATE_LEFT_SOFT_PUNCH || _player->getPlayerStruct().playerState == PLAYERSTATE_LEFT_SOFT_KICK ||
			_player->getPlayerStruct().playerState == PLAYERSTATE_LEFT_HARD_PUNCH || _player->getPlayerStruct().playerState == PLAYERSTATE_LEFT_HARD_KICK)
		{
			if (_player->getPlayerStruct().x > _dummy->getCenter().x)
			{
				_dummy->setDummyState(DUMMYSTATE_LEFT_HIT);
				_dummy->setDummyAni(KEYANIMANAGER->findAnimation("더미왼쪽맞음"));
			}
		}
		if (_player->getPlayerStruct().playerState == PLAYERSTATE_RIGHT_SOFT_PUNCH || _player->getPlayerStruct().playerState == PLAYERSTATE_RIGHT_SOFT_KICK ||
			_player->getPlayerStruct().playerState == PLAYERSTATE_RIGHT_HARD_PUNCH || _player->getPlayerStruct().playerState == PLAYERSTATE_RIGHT_HARD_KICK)
		{
			if (_player->getPlayerStruct().x < _dummy->getCenter().x)
			{
				_dummy->setDummyState(DUMMYSTATE_LEFT_HIT);
				_dummy->setDummyAni(KEYANIMANAGER->findAnimation("더미왼쪽맞음"));
			}
		}
		_dummy->hitDamage(1.0f);
		_dummy->getAni()->start();
	}
	if (_selectedChar == 1)
	{
		for (int i = 0;i < _player->getKnife()->getVBullet().size();i++)
		{
			if (IntersectRect(&temp, &_player->getKnife()->getVBullet()[i].rc, &_dummy->getRect()))
			{
				_player->getKnife()->removeBullet(i);
				_dummy->hitDamage(5.0f);
				_dummy->setDummyState(DUMMYSTATE_LEFT_HIT);
				_dummy->setDummyAni(KEYANIMANAGER->findAnimation("더미왼쪽맞음"));
				_dummy->getAni()->start();
				break;
			}
		}
	}
}

void gameScene::dummyState()
{

}