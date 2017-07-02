#pragma once
#include "gameNode.h"
#include <vector>

struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float angle;
	float speed;
	float radius;
	float fireX, fireY;
	bool fire;
	int count;
};

class grenade
{
private:
	vector<tagBullet> _vGrenade;
	vector<tagBullet>::iterator _viGrenade;

	const char* _imageName;
	int _bulletMax;

public:
	HRESULT init(const char* imageName, int bulletMax);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);

	void move(void);

	grenade();
	~grenade();
};

class knife
{
private:
	vector<tagBullet> _vKnife;
	vector<tagBullet>::iterator _viKnife;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);

	void move(void);

	knife();
	~knife();
};

class bossgrenade
{
private:
	vector<tagBullet> _vbossGrenade;
	vector<tagBullet>::iterator _vibossGrenade;

	const char* _imageName;
	float _range;
	int _bulletMax;

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release(void);
	void update(void);
	void render(void);

	void fire(float x, float y, float angle, float speed);

	void move(void);

	bossgrenade();
	~bossgrenade();
};