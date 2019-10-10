#include <DxLib.h>
#include "Obj.h"
#include <SceneMng.h>
#include <ImageMng.h>


Obj::Obj()
{
	_animFrame = 0;
	_animCount = 0;
}


Obj::~Obj()
{
}

bool Obj::animKey(const std::string key)
{
	// ·°‚ªg‚¦‚é‚©Áª¯¸
	if (_animMap.find(key) == _animMap.end())
	{
		// –³‚¢‚Ì‚Åg‚¦‚È‚¢
		return false;
	}
	// ‚ ‚Á‚½‚ç“o˜^
	if (_animKey != key)
	{
		// “¯‚¶·°‚Å‚È‚¯‚ê‚Î0¸Ø
		_animFrame = 0;
		_animCount = 0;
	}

	_animKey = key;
	return true;
}

const std::string Obj::animKey(void) const
{
	return _animKey;
}

bool Obj::SetAnim(const std::string key, AnimVector& data)
{
	// c++17ˆÈ~
	return (_animMap.try_emplace(key, std::move(data))).second;

	//// ‚·‚Å‚É‚ ‚é‚©Áª¯¸
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	// –³‚©‚Á‚½‚ç“o˜^
	//	_animMap[key] = data;
	//	return true;
	//}
	//return false;
}

void Obj::Update(void)
{
}

void Obj::Draw(void)
{
	// ”O‚Ì‚½‚ß·°Áª¯¸
	if (_animMap.find(_animKey) == _animMap.end())
	{
		// ‘¶İ‚µ‚È‚©‚Á‚½‚çreturn
		return;
	}
	// ±ÆÒ°¼®İÌÚ°Ñ‚àÁª¯¸
	if (_animMap[_animKey].size() <= _animFrame ||
		0 > _animFrame)
	{
		// ‘¶İ‚µ‚È‚©‚Á‚½‚çreturn
		return;
	}
	// Üİ¼®¯Ä‚Ì±ÆÒ°¼®İ‚È‚çˆ—‚ğ‚µ‚È‚¢
	if (_animMap[_animKey][_animFrame].first >= 0)
	{
		// ¶³İÀ‚Æ±ÆÒ°¼®İÌÚ°Ñ‚ğ”ä‚×‚ÄØ‚è‘Ö‚¦À²Ğİ¸Ş‚È‚çØ‚è‘Ö‚¦
		if (_animCount >= _animMap[_animKey][_animFrame].second)
		{

			_animFrame++;

		}

		// ”ÍˆÍŠOÁª¯¸
		if (_animMap[_animKey].size() > _animFrame)
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
	lpSceneMng.AddDrawQue({ _animMap[_animKey][_animFrame].first,_pos.x,_pos.y });
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id, _pos.x,_pos.y });
}

