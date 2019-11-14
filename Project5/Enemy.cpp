#include "Enemy.h"
#include <ImageMng.h>
#include "_DebugDispOut.h"


void Enemy::Init()
{
	// ´ÈĞ°±ÆÒ°¼®İÃŞ°Àì¬
	AnimVector data;
	data.emplace_back(IMAGE_ID("·¬×")[10 + 10 * static_cast<int>(_type)], 30);
	data.emplace_back(IMAGE_ID("·¬×")[11 + 10 * static_cast<int>(_type)], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("“G”š”­")[0], 10);
	data.emplace_back(IMAGE_ID("“G”š”­")[1], 15);
	data.emplace_back(IMAGE_ID("“G”š”­")[2], 20);
	data.emplace_back(IMAGE_ID("“G”š”­")[3], 25);
	data.emplace_back(IMAGE_ID("“G”š”­")[4], 30);
	data.emplace_back(-1, 35);
	SetAnim(STATE::DEATH, data);


	state(STATE::NORMAL);
}

Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(EnemyState &state)
{
	// ˆø”‚Å‚à‚ç‚Á‚½’l‚É‚æ‚é‰Šú‰»
	_type = std::get<static_cast<int>(ENEMY_STATE::TYPE)>(state);								// À²Ìß‚Ìİ’è
	_pos = std::move(std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(state));					// À•W‚Ìİ’è
	_size = std::move(std::get<static_cast<int>(ENEMY_STATE::SIZE)>(state));					// »²½Ş‚Ìİ’è
	_rad = std::move(std::get<static_cast<int>(ENEMY_STATE::RAD)>(state));
	_moveCtl.SetMoveState(std::get<static_cast<int>(ENEMY_STATE::AIM)>(state),true);			// s“®‚Ìİ’è
	Init();
}

void Enemy::Update(void)
{
	if (DestroyProc())
	{
		return;
	}
	_moveCtl.Update();
	//if (rand() % 300 == 0)
	//{
	//	SetAlive(false);
	//}
	_dbgSetAlpha(128);
	//_dbgDrawBox(_pos.x - (_size.x / 2), _pos.y - (_size.y / 2), _pos.x + (_size.x / 2), _pos.y + (_size.y / 2), 0xff00000, true);
	_dbgSetAlpha(255);
	//_dbgDrawBox(_pos.x - (_size.x / 4), _pos.y - (_size.y / 4), _pos.x + (_size.x / 4), _pos.y + (_size.y / 4), 0xffffff, false);
	//_dbgDrawCircle(_pos.x, _pos.y, 10, 0xffffff, true);
	_dbgDrawPixel(_pos.x, _pos.y, 0xffffff);
}


Enemy::~Enemy()
{
}
