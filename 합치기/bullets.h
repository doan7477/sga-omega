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

class grenade : public gameNode
{
private:
	tagBullet _bullet;
	vector<tagBullet> _vGrenade;
	vector<tagBullet>::iterator _viGrenade;

	const char* _imageName;
	float _gravity;
	int _bulletMax;

	float _poisionX;
	float _poisionY;

public:
	HRESULT init(const char* imageName, int bulletMax);
	void release(void);
	void update(void);
	void render(float x, float y);

	void fire(float x, float y, float angle, float speed);

	void move(void);

	void removeBullet(int arrNum);

	void poision(void);

	image* getImage() { return _bullet.bulletImage; }
	float getX() { return _bullet.x; }
	float getY() { return _bullet.y; }

	vector<tagBullet> getVGrenade(void) { return _vGrenade; }
	vector<tagBullet>::iterator getVIGrenade(void) { return _viGrenade; }

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