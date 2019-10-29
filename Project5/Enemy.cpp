#include "Enemy.h"
#include <ImageMng.h>


void Enemy::Init()
{
	// ｴﾈﾐｰｱﾆﾒｰｼｮﾝﾃﾞｰﾀ作成
	AnimVector data;
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[10 + 10 * static_cast<int>(_type)], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[11 + 10 * static_cast<int>(_type)], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("敵爆発")[0], 10);
	data.emplace_back(IMAGE_ID("敵爆発")[1], 15);
	data.emplace_back(IMAGE_ID("敵爆発")[2], 20);
	data.emplace_back(IMAGE_ID("敵爆発")[3], 25);
	data.emplace_back(IMAGE_ID("敵爆発")[4], 30);
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
	// 引数でもらった値による初期化
	_type = std::get<static_cast<int>(ENEMY_STATE::TYPE)>(state);
	_pos = std::move(std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(state));
	_size = std::move(std::get<static_cast<int>(ENEMY_STATE::SIZE)>(state));
	Init();
}

void Enemy::Update(void)
{
	if (DestroyProc())
	{
		return;
	}
	moveCtl.Update();
	//if (rand() % 300 == 0)
	//{
	//	SetAlive(false);
	//}
}


Enemy::~Enemy()
{
}
