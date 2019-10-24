#include <DxLib.h>
#include <ImageMng.h>
#include "Player.h"
#include <KeyState.h>


void Player::Init(void)
{
	// ﾌﾟﾚｲﾔｰｱﾆﾒｰｼｮﾝｾｯﾄ
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
	data.emplace_back(-1, 40);							// ﾜﾝｼｮｯﾄﾉｱﾆﾒｰｼｮﾝにしたいので-1
	SetAnim(STATE::DEATH, data);

	// ﾕﾆｰｸﾎﾟｲﾝﾀ 中身は後 c++14以降
	_input = std::make_unique<KeyState>();
	//// 上が使えなかった場合 覚えておこう
	//_input.reset(new KeyState());

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

	// ｷｰ関係ｱｯﾌﾟﾃﾞｰﾄ呼び出し
	(*_input).Update();

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
