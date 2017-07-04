#include "stdafx.h"
#include "loadingScene.h"


loadingScene::loadingScene()
{
}


loadingScene::~loadingScene()
{

}

HRESULT loadingScene::init()
{
	_loading = new loading;
	_loading->init();

	this->loadingImage();



	return S_OK;
}

void loadingScene::release()
{
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	_loading->update();

	if (_loading->loadingDone())
	{
		//로딩이 끝난후 플레이어와 카메라 좌표
		char temp[128];
		vector<string> vStr;
		vStr.push_back(itoa(200, temp, 10));
		vStr.push_back(itoa(600, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(0, temp, 10));
		vStr.push_back(itoa(1, temp, 10));
		vStr.push_back(itoa(0, temp, 10));


		TXTDATA->txtSave("PlayerPosition.txt", vStr);

		SCENEMANAGER->changeScene("맵1");
	}
}

void loadingScene::render()
{
	_loading->render();
}


void loadingScene::loadingImage()
{
	//맵 이미지 로드
	_loading->loadImage("배경1", "image/background/background1.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("배경2", "image/background/background2.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("맵1-1", "image/background/map 1-1.bmp", 1500, 1410, true, RGB(255, 0, 255));
	_loading->loadImage("맵1-1픽셀", "image/background/map1-1_pixel.bmp", 1500, 1410, true, RGB(255, 0, 255));
	_loading->loadImage("맵1-2", "image/background/map 1-2.bmp", 2959, 734, true, RGB(255, 0, 255));
	_loading->loadImage("맵1-2픽셀", "image/background/map1-2_pixel.bmp", 2959, 734, true, RGB(255, 0, 255));
	_loading->loadImage("맵1-3", "image/background/map 1-3.bmp", 1956, 734, true, RGB(255, 0, 255));
	_loading->loadImage("맵1-3픽셀", "image/background/map1-3_pixel.bmp", 1956, 734, true, RGB(255, 0, 255));
	_loading->loadImage("맵1-boss", "image/background/map 1-boss.bmp", 1947, 734, true, RGB(255, 0, 255));
	_loading->loadImage("맵1-boss픽셀", "image/background/map1-boss_pixel.bmp", 1947, 734, true, RGB(255, 0, 255));

	//플레이어 이미지 로드
	_loading->loadFrameImage("정지", "image/봉기남/idle.bmp", 450, 222, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("달리기", "image/봉기남/run.bmp", 900, 222, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("브레이크", "image/봉기남/brake.bmp", 588, 235, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("턴", "image/봉기남/turn.bmp", 207, 228, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("점프", "image/봉기남/jump.bmp", 207, 222, 3, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("폴", "image/봉기남/fall.bmp", 375, 240, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("앉기", "image/봉기남/crouch.bmp", 216, 168, 4, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("일어서기", "image/봉기남/rise.bmp", 120, 210, 2, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("구르기", "image/봉기남/roll.bmp", 768, 204, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격1", "image/봉기남/attack1.bmp", 567, 216, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격2", "image/봉기남/attack2.bmp", 609, 222, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격3", "image/봉기남/attack3.bmp", 1155, 222, 11, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("점프공격", "image/봉기남/jumpAttack1.bmp", 483, 216, 7, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("평지활", "image/봉기남/bow.bmp", 486, 270, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("점프활", "image/봉기남/jumpBow.bmp", 486, 270, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("앉기활", "image/봉기남/crouchBow.bmp", 486, 210, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("사다리진입", "image/봉기남/ladderEnter.bmp", 450, 222, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("사다리떠남", "image/봉기남/ladderLeave.bmp", 360, 228, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("사다리내려가기", "image/봉기남/ladderDown.bmp", 189, 111, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("사다리올라가기", "image/봉기남/ladderUp.bmp", 306, 114, 6, 1, true, RGB(255, 0, 255));

	//플레이어 이펙트
	_loading->loadFrameImage("공격1이펙트오른쪽", "image/봉기남/attack1right.bmp", 1218, 90, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격1이펙트왼쪽", "image/봉기남/attack1left.bmp", 1218, 90, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격2이펙트오른쪽", "image/봉기남/attack2right.bmp", 1176, 114, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격2이펙트왼쪽", "image/봉기남/attack2left.bmp", 1176, 114, 7, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격3이펙트오른쪽", "image/봉기남/attack3right.bmp", 2592, 144, 9, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("공격3이펙트왼쪽", "image/봉기남/attack3left.bmp", 2592, 144, 9, 1, true, RGB(255, 0, 255));
	

	//아이템 및 상점 이미지 로드


	//적 이미지 로드
	_loading->loadFrameImage("폭탄병스탠딩", "image/김기준/Idle.bmp", 54, 138, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("폭탄병폭탄투척", "image/김기준/IdleBombThrow.bmp", 837, 156, 9, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("폭탄병히트", "image/김기준/IdleHit.bmp", 57, 156, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("방패병스탠딩", "image/김기준/IdleShieldStand.bmp", 24, 44, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("방패병무빙", "image/김기준/IdleShieldWalk.bmp", 120, 46, 5, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("방패병칼투척", "image/김기준/IdleShieldThrow.bmp", 216, 48, 8, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("방패병히트", "image/김기준/IdleShieldHit.bmp", 23, 52, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("단도병점핑", "image/김기준/IdleJump.bmp", 16, 46, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("단도병추락", "image/김기준/IdleFall.bmp", 108, 56, 6, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("단도병칼투척", "image/김기준/IdleKnifeThrow.bmp", 260, 48, 10, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("단도병히트", "image/김기준/IdleHit.bmp", 23, 52, 1, 2, true, RGB(255, 0, 255));

	_loading->loadFrameImage("보스머리", "image/김기준/BossHeadStand.bmp", 480, 108, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보스몸통1", "image/김기준/BossBody1.bmp", 276, 75, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보스몸통2", "image/김기준/BossBody2.bmp", 252, 57, 4, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보스공격1", "image/김기준/BossHeadAttack.bmp", 1890, 135, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보스공격2", "image/김기준/BossHeadVenom.bmp", 1092, 102, 14, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보스공격3", "image/김기준/BossHeadVenomBomb.bmp", 624, 102, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보스공격모션끝", "image/김기준/BossHeadStand.bmp", 480, 108, 8, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("보스사망", "image/김기준/BossHeadDead.bmp", 1287, 102, 11, 1, true, RGB(255, 0, 255));
	_loading->loadImage("보스꼬리", "image/김기준/BossTail.bmp", 63, 66, true, RGB(255, 0, 255));
	_loading->loadImage("폭탄", "image/김기준/Bomb.bmp", 33, 42, true, RGB(255, 0, 255));
	_loading->loadFrameImage("칼", "image/김기준/Knife.bmp", 30, 33, 1, 2, true, RGB(255, 0, 255));

	//총알 관련 이미지 로드
	_loading->loadFrameImage("화살", "image/봉기남/arrow.bmp", 66, 18, 1, 2, true, RGB(255, 0, 255));
	_loading->loadFrameImage("화살터지는이펙트", "image/봉기남/arrowRemoveEffect.bmp", 350, 64, 6, 1, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{

}
