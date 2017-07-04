#include "stdafx.h"
#include "Boss.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

HRESULT Boss::init(const char* imageName, POINT position)
{
	_player = new player;
	_player->init();

	_boss.HeadimgName = "�����Ӹ�";
	_boss.Headimg = IMAGEMANAGER->findImage(_boss.HeadimgName);
	_boss.Body1imgName = "��������1";
	_boss.Body1img = IMAGEMANAGER->findImage(_boss.Body1imgName);
	_boss.Body2imgName = "��������2";
	_boss.Body2img = IMAGEMANAGER->findImage(_boss.Body2imgName);
	_boss.TailimgName = "��������";
	_boss.Tailimg = IMAGEMANAGER->findImage(_boss.TailimgName);

	_boss.headx = position.x;
	_boss.heady = position.y;

	_boss.body1x[0] = _boss.headx;
	_boss.body1y[0] = _boss.heady + 85;
	_boss.body1x[1] = _boss.headx + 14;
	_boss.body1y[1] = _boss.heady + 137;
	_boss.body1x[2] = _boss.headx + 45;
	_boss.body1y[2] = _boss.heady + 167;

	_boss.body2x[0] = _boss.headx + 95;
	_boss.body2y[0] = _boss.heady + 185;
	_boss.body2x[1] = _boss.headx + 153;
	_boss.body2y[1] = _boss.heady + 193;
	_boss.body2x[2] = _boss.headx + 199;
	_boss.body2y[2] = _boss.heady + 186;
	_boss.body2x[3] = _boss.headx + 248;
	_boss.body2y[3] = _boss.heady + 193;

	_boss.tailx = _boss.headx + 293;
	_boss.taily = _boss.heady + 173;

	_boss.fps = 0;
	_boss.speed = 1.0f;
	_boss.jumpPower = 5.0f;
	_boss.gravity = 0.1;

	//�Ӹ�
	_boss.headrc = RectMakeCenter(_boss.headx, _boss.heady, _boss.Headimg->getFrameWidth(), _boss.Headimg->getFrameHeight());
	//����1	
	for (int i = 0; i < 3; i++)
	{
		_boss.body1rc[i] = RectMakeCenter(_boss.body1x[i], _boss.body1y[i], _boss.Body1img->getFrameWidth(), _boss.Body1img->getFrameHeight());
	}
	//����2
	for (int i = 0; i < 4; i++)
	{
		_boss.body2rc[i] = RectMakeCenter(_boss.body2x[i], _boss.body2y[i], _boss.Body2img->getFrameWidth(), _boss.Body2img->getFrameHeight());
	}
	//����
	_boss.tailrc = RectMakeCenter(_boss.tailx, _boss.taily, _boss.Tailimg->getWidth(), _boss.Tailimg->getHeight());

	_boss.state = BOSSSTATE_STAND;
	_boss.attack = false;
	_boss.currentHP = 1000.0f;
	_boss.maxHP = 1000.0f;

	_fireCount = 0;

	_rndAttack = RND->getInt(3);

	return S_OK;
}

void Boss::release(void)
{

}

void Boss::update(void)
{
	_player->update();

	_boss.fps++;
	_fireCount++;

	move();

	if (_boss.state == BOSSSTATE_STAND)
	{
		imageSet("�����Ӹ�");
	}
	if (_boss.state == BOSSSTATE_ATTACK1_END || _boss.state == BOSSSTATE_ATTACK2_END || _boss.state == BOSSSTATE_ATTACK3_END)
	{
		imageSet("�������ݸ�ǳ�");
	}
	if (_fireCount % 180 == 0)
	{
		if (_boss.state == BOSSSTATE_STAND && _rndAttack == 0)
		{
			_boss.state = BOSSSTATE_ATTACK1;
			imageSet("��������1");
		}
		if (_boss.state == BOSSSTATE_STAND && _rndAttack == 1)
		{
			_boss.state = BOSSSTATE_ATTACK2;
			imageSet("��������2");
		}
		if (_boss.state == BOSSSTATE_STAND && _rndAttack == 2)
		{
			_boss.state = BOSSSTATE_ATTACK3;
			imageSet("��������3");
		}
		//_fireCount = 0;
	}

	//������ǥ�Ѹ���
	//�Ӹ�
	_boss.headrc = RectMakeCenter(_boss.headx, _boss.heady, _boss.Headimg->getFrameWidth(), _boss.Headimg->getFrameHeight());
	//����1	
	for (int i = 0; i < 3; i++)
	{
		_boss.body1rc[i] = RectMakeCenter(_boss.body1x[i], _boss.body1y[i], _boss.Body1img->getFrameWidth(), _boss.Body1img->getFrameHeight());
	}
	//����2
	for (int i = 0; i < 4; i++)
	{
		_boss.body2rc[i] = RectMakeCenter(_boss.body2x[i], _boss.body2y[i], _boss.Body2img->getFrameWidth(), _boss.Body2img->getFrameHeight());
	}
	//����
	_boss.tailrc = RectMakeCenter(_boss.tailx, _boss.taily, _boss.Tailimg->getWidth(), _boss.Tailimg->getHeight());
}

void Boss::render(float x, float y)
{
	char str[123];
	char str1[123];
	sprintf(str, "%d", _rndAttack);
	sprintf(str1, "%d", _boss.fps);
	TextOut(getMemDC(), 50, 50, str, strlen(str));
	TextOut(getMemDC(), 200, 50, str1, strlen(str1));
	if (_boss.state == BOSSSTATE_STAND) TextOut(getMemDC(), 10, 50, "���", strlen("���"));
	if (_boss.state == BOSSSTATE_ATTACK1) TextOut(getMemDC(), 10, 50,"����1",strlen("����1"));
	if (_boss.state == BOSSSTATE_ATTACK2) TextOut(getMemDC(), 10, 50, "����2", strlen("����2"));
	if (_boss.state == BOSSSTATE_ATTACK3) TextOut(getMemDC(), 10, 50, "����3", strlen("����3"));

	_boss.Body2img->frameRender(getMemDC(), _boss.body2rc[3].left - x, _boss.body2rc[3].top - y);
	_boss.Body2img->frameRender(getMemDC(), _boss.body2rc[2].left - x, _boss.body2rc[2].top - y);
	_boss.Body2img->frameRender(getMemDC(), _boss.body2rc[1].left - x, _boss.body2rc[1].top - y);
	_boss.Body2img->frameRender(getMemDC(), _boss.body2rc[0].left - x, _boss.body2rc[0].top - y);

	_boss.Tailimg->render(getMemDC(), _boss.tailrc.left - x, _boss.tailrc.top - y);

	_boss.Body1img->frameRender(getMemDC(), _boss.body1rc[2].left - x, _boss.body1rc[2].top - y);
	_boss.Body1img->frameRender(getMemDC(), _boss.body1rc[1].left - x, _boss.body1rc[1].top - y);
	_boss.Body1img->frameRender(getMemDC(), _boss.body1rc[0].left - x, _boss.body1rc[0].top - y);

	_boss.Headimg->frameRender(getMemDC(), _boss.headrc.left - x, _boss.headrc.top - y);

	//��� ������ ����
	if (_boss.state == BOSSSTATE_STAND)
	{
		//�̺κ��� �� �ȵ�?
		if (_boss.fps % 5 == 0)	_boss.Headimg->setFrameX(_boss.Headimg->getFrameX() + 1);
	}

	if (_boss.HeadimgName == "��������1")
	{
		if (_boss.fps % 5 == 0) _boss.Headimg->setFrameX(_boss.Headimg->getFrameX() + 1);
	}
	if (_boss.HeadimgName == "��������2")
	{
		if (_boss.fps % 5 == 0) _boss.Headimg->setFrameX(_boss.Headimg->getFrameX() + 1);
	}
	if (_boss.HeadimgName == "��������3")
	{
		if (_boss.fps % 5 == 0) _boss.Headimg->setFrameX(_boss.Headimg->getFrameX() + 1);
	}

	if (_boss.HeadimgName == "�������ݸ�ǳ�")
	{
		if (_boss.fps % 10 == 0) _boss.Headimg->setFrameX(_boss.Headimg->getFrameX() + 1);
	}
	if ((_boss.Body1imgName == "��������1"))
	{
		if (_boss.fps % 10 == 0) _boss.Body1img->setFrameX(_boss.Body1img->getFrameX() + 1);
	}
	if ((_boss.Body2imgName == "��������2"))
	{
		if (_boss.fps % 10 == 0) _boss.Body2img->setFrameX(_boss.Body2img->getFrameX() + 1);
	}

	switch (_boss.state)
	{
	case BOSSSTATE_LEFT_MOVE: case BOSSSTATE_RIGHT_MOVE: case BOSSSTATE_STAND:
		//if (_boss.Headimg->getFrameX() >= _boss.Headimg->getMaxFrameX()) _boss.Headimg->setFrameX(0);
	break;
	//���ݰ��� ������,���¼���
	case BOSSSTATE_ATTACK1:
		if (_boss.Headimg->getFrameX() >= _boss.Headimg->getMaxFrameX())
		{
			_boss.state = BOSSSTATE_ATTACK1_END;
			_boss.Headimg->setFrameX(0);
			_rndAttack = RND->getInt(3);
		}
	break;
	case BOSSSTATE_ATTACK2:
		if (_boss.Headimg->getFrameX() >= _boss.Headimg->getMaxFrameX())
		{
			_boss.state = BOSSSTATE_ATTACK2_END;
			_boss.Headimg->setFrameX(0);
			_rndAttack = RND->getInt(3);
		}
	break;
	case BOSSSTATE_ATTACK3:
		if (_boss.Headimg->getFrameX() >= _boss.Headimg->getMaxFrameX())
		{
			_boss.state = BOSSSTATE_ATTACK3_END;
			_boss.Headimg->setFrameX(0);
			_rndAttack = RND->getInt(3);
		}
	break;
	//������ ���
	case BOSSSTATE_ATTACK1_END:case BOSSSTATE_ATTACK2_END: case BOSSSTATE_ATTACK3_END:
		if (_fireCount % 300 == 0)
		{
			_boss.Headimg->setFrameX(0);
			_fireCount = 0;
			_boss.state = BOSSSTATE_STAND;
		}
	break;
	}

	if (_boss.Headimg->getFrameX() >= _boss.Headimg->getMaxFrameX()) _boss.Headimg->setFrameX(0);
	if (_boss.Body2img->getFrameX() >= _boss.Body2img->getMaxFrameX()) _boss.Body2img->setFrameX(0);
	if (_boss.Body1img->getFrameX() >= _boss.Body1img->getMaxFrameX()) _boss.Body1img->setFrameX(0);
}

void Boss::move(void)
{
	switch (_boss.state)
	{
	//������
	case BOSSSTATE_LEFT_MOVE: //case BOSSSTATE_SHOWUP:
		_boss.headx -= 0.1f;
		_boss.body1x[0] -= 0.1f;
		_boss.body1x[1] -= 0.1f;
		_boss.body1x[2] -= 0.1f;
		_boss.body2x[0] -= 0.1f;
		_boss.body2x[1] -= 0.1f;
		_boss.body2x[2] -= 0.1f;
		_boss.body2x[3] -= 0.1f;
		_boss.tailx -= 0.1f;
	break;

	case BOSSSTATE_RIGHT_MOVE:
		_boss.headx += 0.1f;
		_boss.body1x[0] += 0.1f;
		_boss.body1x[1] += 0.1f;
		_boss.body1x[2] += 0.1f;
		_boss.body2x[0] += 0.1f;
		_boss.body2x[1] += 0.1f;
		_boss.body2x[2] += 0.1f;
		_boss.body2x[3] += 0.1f;
		_boss.tailx += 0.1f;
	break;

	//�����Ҷ�
	//Į����
	case BOSSSTATE_ATTACK1:
		_boss.headx -= 1;
		_boss.heady += 2;

		_boss.body1x[0] -= 0.75;
		_boss.body1y[0] += 1.5;

		_boss.body1x[1] -= 0.5;
		_boss.body1y[1] += 1;

		_boss.body1x[2] -= 0.25;
		_boss.body1y[2] += 0.5;
	break;
	//����°���
	case BOSSSTATE_ATTACK2:
		_boss.headx -= 0.4;
		_boss.heady += 2;

		_boss.body1x[0] -= 0.3;
		_boss.body1y[0] += 1.5;

		_boss.body1x[1] -= 0.2;
		_boss.body1y[1] += 1;

		_boss.body1x[2] -= 0.1;
		_boss.body1y[2] += 0.5;
	break;
	//����ź�ε� ���� �����Ӿ���
	case BOSSSTATE_ATTACK3:
	break;

	//���ݸ�� ��������
	case BOSSSTATE_ATTACK1_END:
		_boss.headx += 1;
		_boss.heady -= 2;

		_boss.body1x[0] += 0.75;
		_boss.body1y[0] -= 1.5;

		_boss.body1x[1] += 0.5;
		_boss.body1y[1] -= 1;

		_boss.body1x[2] += 0.25;
		_boss.body1y[2] -= 0.5;
	break;
	case BOSSSTATE_ATTACK2_END:
		_boss.headx += 0.4;
		_boss.heady -= 2;

		_boss.body1x[0] += 0.3;
		_boss.body1y[0] -= 1.5;

		_boss.body1x[1] += 0.2;
		_boss.body1y[1] -= 1;

		_boss.body1x[2] += 0.1;
		_boss.body1y[2] -= 0.5;
	break;
	case BOSSSTATE_ATTACK3_END:
	break;
	}
}

void Boss::imageSet(char* imgName)
{
	_boss.HeadimgName = imgName;
	_boss.Headimg = IMAGEMANAGER->findImage(imgName);
}

bool Boss::bulletCountFire(void)
{
	//���� ������ �ѹ����� �޾ƿͼ� �װ�(���)�̶�� ����������
	//Į��
	if (_boss.state == BOSSSTATE_ATTACK1)
	{
		if (_boss.Headimg->getFrameX() == 6) return true;
	}
	//�����
	if (_boss.state == BOSSSTATE_ATTACK2)
	{
		if (_boss.Headimg->getFrameX() == 3) return true;
	}
	//����ź���
	if (_boss.state == BOSSSTATE_ATTACK3)
	{
		if (_boss.Headimg->getFrameX() == 3) return true;
	}
	return false;
}
