#include <DxLib.h>
#include <ImageMng.h>
#include "Player.h"


void Player::Init(void)
{
	AnimVector data;
	data.reserve(5);
	data.emplace_back(IMAGE_ID("·¬×")[0], 30);
	data.emplace_back(IMAGE_ID("·¬×")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(IMAGE_ID("·¬×")[2], 0);
	SetAnim(STATE::EX, data);
	data.emplace_back(IMAGE_ID("PL”š”­")[0], 10);
	data.emplace_back(IMAGE_ID("PL”š”­")[1], 15);
	data.emplace_back(IMAGE_ID("PL”š”­")[2], 20);
	data.emplace_back(IMAGE_ID("PL”š”­")[3], 25);
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
	// ó‘ÔÁª¯¸
	if (DestroyProc())
	{
		// €‚ñ‚Å‚é‚È‚çreturn
		return;
	}
	// ×ÑÀŞ®‚ÅˆÚ“®§Œä@ˆø”‚Å•ûŒüŠÇ—‚·‚é‚±‚Æ‚É‚æ‚Á‚Äˆ—‚ğ1‚Â‚µ‚©‘‚©‚È‚­‚Ä‚æ‚¢
	auto move = [](const int keyID,int& pNum,const int speed) {
		if(CheckHitKey(keyID))
		{
			pNum += speed;
		}
	};
	// ã
	move(KEY_INPUT_UP,    _pos.y, -2);
	// ‰º
	move(KEY_INPUT_DOWN,  _pos.y, +2);
	// ¶
	move(KEY_INPUT_LEFT,  _pos.x, -2);
	// ‰E
	move(KEY_INPUT_RIGHT, _pos.x, +2);
}


Player::~Player()
{
}
