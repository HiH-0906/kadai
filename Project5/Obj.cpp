#include <DxLib.h>
#include "Obj.h"
#include <SceneMng.h>
#include <ImageMng.h>


Obj::Obj()
{
	_alive = true;			// ¶
	_dead = false;			// €
	_animFrame = 0;
	_animCount = 0;
	_rad = 0;
	_speed = 1;
	_zOrder = 0;
}


Obj::~Obj()
{
}

bool Obj::state(const STATE state)
{
	// ·°‚ªg‚¦‚é‚©Áª¯¸
	if (_animMap.find(state) == _animMap.end())
	{
		// –³‚¢‚Ì‚Åg‚¦‚È‚¢
		return false;
	}
	// ‚ ‚Á‚½‚ç“o˜^
	if (_state != state)
	{
		// “¯‚¶·°‚Å‚È‚¯‚ê‚Î0¸Ø
		_animFrame = 0;
		_animCount = 0;
	}

	_state = state;
	return true;
}

const STATE Obj::state(void) const
{
	return _state;
}

bool Obj::SetAnim(const STATE state, AnimVector& data)
{
	// c++17ˆÈ~
	return (_animMap.try_emplace(state, std::move(data))).second;

	//// ‚·‚Å‚É‚ ‚é‚©Áª¯¸
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	// –³‚©‚Á‚½‚ç“o˜^
	//	_animMap[key] = data;
	//	return true;
	//}
	//return false;
}

bool Obj::SetAlive(bool alive)
{
	_alive = alive;
	if (!_alive)
	{
		state(STATE::DEATH);
	}
	return true;
}

bool Obj::isAnimEnd(void)
{
	// ”O‚Ì‚½‚ß·°Áª¯¸
	if (_animMap.find(_state) == _animMap.end())
	{
		// ‘¶İ‚µ‚È‚©‚Á‚½‚çI‚í‚Á‚Ä‚¢‚éˆµ‚¢
		return true;
	}
	// ±ÆÒ°¼®İÌÚ°Ñ‚àÁª¯¸
	if (_animMap[_state].size() <= _animFrame ||
		0 > _animFrame)
	{
		// ‘¶İ‚µ‚È‚©‚Á‚½‚çI‚í‚Á‚Ä‚¢‚éˆµ‚¢
		return true;
	}
	// ±ÆÒ°¼®İ‚ªI—¹‚µ‚Ä‚¢‚é‚©Áª¯¸
	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	return false;
}

bool Obj::DestroyProc(void)
{
	// ¶‚«‚Ä‚é‚©
	if (_alive)
	{
		// ¶‚«‚Ä‚½‚çreturn
		return false;
	}
	// ±ÆÒ°¼®İI—¹‚µ‚Ä‚¢‚é‚©
	if (isAnimEnd())
	{
		// I—¹‚µ‚Ä‚¢‚½‚çÌ×¸Şµİ
		_dead = true;
	}
	// €‚ñ‚Å‚½‚çtrue
	return true;
}

void Obj::Draw(void)
{
	// ”O‚Ì‚½‚ß·°Áª¯¸
	if (_animMap.find(_state) == _animMap.end())
	{
		// ‘¶İ‚µ‚È‚©‚Á‚½‚çreturn
		return;
	}
	// ±ÆÒ°¼®İÌÚ°Ñ‚àÁª¯¸
	if (_animMap[_state].size() <= _animFrame ||
		0 > _animFrame)
	{
		// ‘¶İ‚µ‚È‚©‚Á‚½‚çreturn
		return;
	}
	// Üİ¼®¯Ä‚Ì±ÆÒ°¼®İ‚È‚çˆ—‚ğ‚µ‚È‚¢
	if (_animMap[_state][_animFrame].first >= 0)
	{
		// ¶³İÀ‚Æ±ÆÒ°¼®İÌÚ°Ñ‚ğ”ä‚×‚ÄØ‚è‘Ö‚¦À²Ğİ¸Ş‚È‚çØ‚è‘Ö‚¦
		if (_animCount >= _animMap[_state][_animFrame].second)
		{
			_animFrame++;
		}

		// ”ÍˆÍŠOÁª¯¸
		if (_animMap[_state].size() > _animFrame)
		{
			// ”ÍˆÍ“à‚È‚ç¶³İÀ‚Ì‰ÁZ
			_animCount++;

		}
		else
		{
			// ”ÍˆÍŠO‚È‚çØ¾¯Ä
			_animFrame = 0;
			_animCount = 0;
		}
	}

	// ·­°‚Ö‚Ì’Ç‰Á
	lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,_pos.x + lpSceneMng.GameScreenOffset.x,_pos.y+lpSceneMng.GameScreenOffset.y,_rad,_zOrder,LAYER::CHAR});
}

void Obj::Draw(int id)
{
	// ·­°‚Ö‚Ì’Ç‰Á
	lpSceneMng.AddDrawQue({ id, _pos.x+lpSceneMng.GameScreenOffset.x,_pos.y+ lpSceneMng.GameScreenOffset.y,_rad,_zOrder,LAYER::CHAR});
}

