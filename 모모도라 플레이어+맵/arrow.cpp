#include "stdafx.h"
#include "arrow.h"


arrow::arrow()
{
}


arrow::~arrow()
{
}

HRESULT arrow::init(const char* imgName)
{
	_imgName = imgName;
	
	EFFECTMANAGER->addEffect("화살터지는이펙트", "화살터지는이펙트", IMAGEMANAGER->findImage("화살터지는이펙트")->getWidth(), IMAGEMANAGER->findImage("화살터지는이펙트")->getHeight(),
		IMAGEMANAGER->findImage("화살터지는이펙트")->getFrameWidth(), IMAGEMANAGER->findImage("화살터지는이펙트")->getFrameHeight(), 3, 0.1f, 10);

	return S_OK;
}

void arrow::release()
{
	_vArrow.clear();
}

void arrow::update()
{
	move();
}

void arrow::render(float x, float y)
{
	iterArrow iter = _vArrow.begin();

	for (; iter != _vArrow.end(); ++iter)
	{
		if (iter->isRight) iter->img->setFrameY(0);
		if (!iter->isRight) iter->img->setFrameY(1);
		iter->img->frameRender(getMemDC(), iter->rc.left - x, iter->rc.top - y);
	}
}

void arrow::move()											
{
	for (int i = 0;i < _vArrow.size();)
	{
		_vArrow.begin()[i].x += cosf(_vArrow.begin()[i].angle) * _vArrow.begin()[i].speed * 1.5f;
		_vArrow.begin()[i].y += -sinf(_vArrow.begin()[i].angle) * _vArrow.begin()[i].speed * 1.5f;

		_vArrow.begin()[i].rc = RectMakeCenter(_vArrow.begin()[i].x, _vArrow.begin()[i].y, _vArrow.begin()[i].img->getWidth(), _vArrow.begin()[i].img->getHeight());

		if (_vArrow.begin()[i].isRight)
		{
			if (PIXELMANAGER->isPixelCollisionRightX(_vArrow.begin()[i].img, _vArrow.begin()[i].x, _vArrow.begin()[i].y, IMAGEMANAGER->findImage("맵1-1픽셀")))
			{
				EFFECTMANAGER->play("화살터지는이펙트", _vArrow.begin()[i].x, _vArrow.begin()[i].y);
				removeArrow(i);
			}
		}
		else if (!_vArrow.begin()[i].isRight)
		{
			if (PIXELMANAGER->isPixelCollisionLeftX(_vArrow.begin()[i].img, _vArrow.begin()[i].x, _vArrow.begin()[i].y, IMAGEMANAGER->findImage("맵1-1픽셀")))
			{
				EFFECTMANAGER->play("화살터지는이펙트", _vArrow.begin()[i].x, _vArrow.begin()[i].y);
				removeArrow(i);
			}
		}

		++i;
	}
}

void arrow::fire(float x, float y, float speed, float angle, bool isRight)
{
	tagArrow arrow;
	ZeroMemory(&arrow, sizeof(arrow));

	arrow.img = IMAGEMANAGER->findImage(_imgName);
	arrow.speed = speed;
	arrow.angle = angle;
	arrow.radius = arrow.img->getWidth() / 2;
	arrow.isRight = isRight;
	arrow.x = x;
	arrow.y = y;
	arrow.rc = RectMake(arrow.x, arrow.y, arrow.radius * 2, arrow.radius * 2);

	_vArrow.push_back(arrow);
}

void arrow::removeArrow(int arrNum)
{
	_vArrow.erase(_vArrow.begin() + arrNum);
}