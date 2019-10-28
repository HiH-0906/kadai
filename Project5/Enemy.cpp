#include "Enemy.h"
#include <ImageMng.h>


void Enemy::Init()
{
	// ��а��Ұ����ް��쐬
	AnimVector data;
	data.emplace_back(IMAGE_ID("���")[10 + 10 * static_cast<int>(_type)], 30);
	data.emplace_back(IMAGE_ID("���")[11 + 10 * static_cast<int>(_type)], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("�G����")[0], 10);
	data.emplace_back(IMAGE_ID("�G����")[1], 15);
	data.emplace_back(IMAGE_ID("�G����")[2], 20);
	data.emplace_back(IMAGE_ID("�G����")[3], 25);
	data.emplace_back(IMAGE_ID("�G����")[4], 30);
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
	// �����ł�������l�ɂ�鏉����
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
	if (rand() % 300 == 0)
	{
		SetAlive(false);
	}
}


Enemy::~Enemy()
{
}