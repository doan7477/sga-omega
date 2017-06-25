#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float speed;
	float fireX, fireY;
	bool fire;
	int _isLeft;
	int count;
	int _currentX;
};

class throwKnife : public gameNode
{
private:
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

	float _range;
	int _bulletMax;

public:
	HRESULT init(int bulletMax, int range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, int num);
	void move(void);
	void draw(void);

	void frameWork(void);
	void removeBullet(int arrNum);

	vector<tagBullet> getVBullet(void) { return _vBullet; }
	vector<tagBullet>::iterator getVIBullet(void) { return _viBullet; }

	throwKnife();
	~throwKnife();
};
