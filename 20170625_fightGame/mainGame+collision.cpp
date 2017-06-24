#include "stdafx.h"
#include "mainGame.h"

//��ü�����ڵ������ �����鼭
//�ϳ��� ��������� ������ CPP������ �Ŵ��� �� �ְ� �Ǿ��µ�
//�������α׷��� ���� ������ �ڵ差�� ���� ���ϱ�
//��������� ���� �Ŀ� �Լ��� ������������
//�ڵ带 ���� ���ϰ� ¥�� �� ����������
//

//1�� ���
void mainGame::collision()
{
	//�ٷ� ������ �������ְ� �Ǹ� �ٸ� ��ü���� ���μ����� ���ư��� ���� ���
	//���� ���� ���� �������� �� ������ ����
	//���� �ٷ� ������ ������ ���ֱ⺸�ٴ� �ε� �̻��� ��ü���� ������
	//�޽����� �ְ� �ε� �̻��� ��ü���� ����� �ϴ°� ����


	for (int i = 0; i < _ship->getThaadMissile()->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_ship->getThaadMissile()->getVBullet()[i].rc,
				&_em->getVMinion()[j]->getRect()))
			{
				_ship->getThaadMissile()->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}