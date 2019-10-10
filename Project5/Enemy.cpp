#include "Enemy.h"
#include <ImageMng.h>


void Enemy::Init()
{
	AnimVector data;
	data.emplace_back(IMAGE_ID("·¬×")[10], 30);
	data.emplace_back(IMAGE_ID("·¬×")[11], 60);
	SetAnim("NORMAL", data);

	data.emplace_back(IMAGE_ID("“G”š”­")[0], 10);
	data.emplace_back(IMAGE_ID("“G”š”­")[1], 15);
	data.emplace_back(IMAGE_ID("“G”š”­")[2], 20);
	data.emplace_back(IMAGE_ID("“G”š”­")[3], 25);
	data.emplace_back(IMAGE_ID("“G”š”­")[4], 30);
	data.emplace_back(-1, 35);
	SetAnim("BLAST", data);

	animKey("NORMAL");
}

Enemy::Enemy()
{
	Init();
}

Enemy::Enemy(EnemyState &enemyState)
{
	_type = std::get<static_cast<int>(ENEMY_STATE::TYPE)>(enemyState);
	_pos = std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(enemyState);
	_size = std::get<static_cast<int>(ENEMY_STATE::SIZE)>(enemyState);
}


Enemy::~Enemy()
{
}
