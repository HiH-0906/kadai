#include "Bullet.h"
#include <ImageMng.h>


Bullet::Bullet()
{
	init();
}

Bullet::Bullet(Vector2Dbl pos)
{
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
	if (_pos.y > -_size.y&&
		_pos.y - _size.y < 0)
	{
		_alive = false;
	}
	_pos.y = _pos.y + 5 * std::sin(_rad);
	_pos.x = _pos.x + 5 * std::cos(_rad);
}


Bullet::~Bullet()
{
}

void Bullet::init()
{
	AnimVector data;
	data.reserve(1);
	data.emplace_back(IMAGE_ID("’e")[0],1);
	SetAnim(STATE::NORMAL, data);
	data.reserve(1);
	data.emplace_back(IMAGE_ID("’e")[0],0);
	SetAnim(STATE::DEATH, data);
}
