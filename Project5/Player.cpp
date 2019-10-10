#include <ImageMng.h>
#include "Player.h"


void Player::Init(void)
{
	AnimVector data;
	data.reserve(5);
	data.emplace_back(IMAGE_ID("·¬×")[0], 30);
	data.emplace_back(IMAGE_ID("·¬×")[1], 60);
	SetAnim("NORMAL", data);

	data.reserve(1);
	data.emplace_back(IMAGE_ID("·¬×")[2], 0);
	SetAnim("EX", data);
	data.emplace_back(IMAGE_ID("PL”š”­")[0], 20);
	data.emplace_back(IMAGE_ID("PL”š”­")[1], 25);
	data.emplace_back(IMAGE_ID("PL”š”­")[2], 30);
	data.emplace_back(IMAGE_ID("PL”š”­")[3], 35);
	data.emplace_back(-1, 40);
	SetAnim("BLAST", data);

	animKey("NORMAL");
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


Player::~Player()
{
}
