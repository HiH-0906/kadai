#include <DxLib.h>
#include <ImageMng.h>
#include "Player.h"


void Player::Init(void)
{
	AnimVector data;
	data.reserve(5);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[2], 0);
	SetAnim(STATE::EX, data);
	data.emplace_back(IMAGE_ID("PL爆発")[0], 10);
	data.emplace_back(IMAGE_ID("PL爆発")[1], 15);
	data.emplace_back(IMAGE_ID("PL爆発")[2], 20);
	data.emplace_back(IMAGE_ID("PL爆発")[3], 25);
	data.emplace_back(-1, 40);
	SetAnim(STATE::DEATH, data);


	state(STATE::NORMAL);
}

Player::Player()
{
	Init();
}

Player::Player(Vector2 pos, Vector2 size)
{
	_pos = pos;
	_size = size;

	Init();
}

void Player::Update(void)
{
	// 状態ﾁｪｯｸ
	if (DestroyProc())
	{
		// 死んでるならreturn
		return;
	}
	// ﾗﾑﾀﾞ式で移動制御　引数で方向管理することによって処理を1つしか書かなくてよい
	auto move = [](const int keyID,int& pNum,const int speed) {
		if(CheckHitKey(keyID))
		{
			pNum += speed;
		}
	};
	// 上
	move(KEY_INPUT_UP,    _pos.y, -2);
	// 下
	move(KEY_INPUT_DOWN,  _pos.y, +2);
	// 左
	move(KEY_INPUT_LEFT,  _pos.x, -2);
	// 右
	move(KEY_INPUT_RIGHT, _pos.x, +2);
}


Player::~Player()
{
}
