#include "Bullet.h"
#include <ImageMng.h>
#include <SceneMng.h>


Bullet::Bullet()
{
	init();
}

Bullet::Bullet(UNIT_ID unitID,Vector2Dbl pos)
{
	_unitID = unitID;
	_pos = pos;
	_size = { 8,3 };
	_rad = 270.0 * (PI / 180.0);
	_zOrder = 10;
	init();
}

void Bullet::Update(void)
{
	if (DestroyProc())
	{
		return;
	}
	if (_pos.y < -_size.x ||
		_pos.y - _size.x > lpSceneMng.GameScreenSize.y)
	{
		SetAlive(false);
		state(STATE::DEATH);
	}
	_pos.y = _pos.y + 5 * std::sin(_rad);
	_pos.x = _pos.x + 5 * std::cos(_rad);
}


Bullet::~Bullet()
{
}

bool Bullet::init()
{
	AnimVector data;
	data.reserve(1);
	data.emplace_back(IMAGE_ID("�e")[0],1);
	SetAnim(STATE::NORMAL, data);
	data.reserve(1);
	data.emplace_back(-1,0);
	SetAnim(STATE::DEATH, data);
	return true;
}
