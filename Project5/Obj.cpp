#include <DxLib.h>
#include "Obj.h"
#include <SceneMng.h>
#include <ImageMng.h>


Obj::Obj()
{
	_alive = true;			// 生
	_dead = false;			// 死
	_animFrame = 0;
	_animCount = 0;
	_rad = 0;
}


Obj::~Obj()
{
}

bool Obj::state(const STATE state)
{
	// ｷｰが使えるかﾁｪｯｸ
	if (_animMap.find(state) == _animMap.end())
	{
		// 無いので使えない
		return false;
	}
	// あったら登録
	if (_state != state)
	{
		// 同じｷｰでなければ0ｸﾘ
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
	// c++17以降
	return (_animMap.try_emplace(state, std::move(data))).second;

	//// すでにあるかﾁｪｯｸ
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	// 無かったら登録
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
	// 念のためｷｰﾁｪｯｸ
	if (_animMap.find(_state) == _animMap.end())
	{
		// 存在しなかったら終わっている扱い
		return true;
	}
	// ｱﾆﾒｰｼｮﾝﾌﾚｰﾑもﾁｪｯｸ
	if (_animMap[_state].size() <= _animFrame ||
		0 > _animFrame)
	{
		// 存在しなかったら終わっている扱い
		return true;
	}
	// ｱﾆﾒｰｼｮﾝが終了しているかﾁｪｯｸ
	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	return false;
}

bool Obj::DestroyProc(void)
{
	// 生きてるか
	if (_alive)
	{
		// 生きてたらreturn
		return false;
	}
	// ｱﾆﾒｰｼｮﾝ終了しているか
	if (isAnimEnd())
	{
		// 終了していたらﾌﾗｸﾞｵﾝ
		_dead = true;
	}
	// 死んでたらtrue
	return true;
}

void Obj::Draw(void)
{
	// 念のためｷｰﾁｪｯｸ
	if (_animMap.find(_state) == _animMap.end())
	{
		// 存在しなかったらreturn
		return;
	}
	// ｱﾆﾒｰｼｮﾝﾌﾚｰﾑもﾁｪｯｸ
	if (_animMap[_state].size() <= _animFrame ||
		0 > _animFrame)
	{
		// 存在しなかったらreturn
		return;
	}
	// ﾜﾝｼｮｯﾄのｱﾆﾒｰｼｮﾝなら処理をしない
	if (_animMap[_state][_animFrame].first >= 0)
	{
		// ｶｳﾝﾀとｱﾆﾒｰｼｮﾝﾌﾚｰﾑを比べて切り替えﾀｲﾐﾝｸﾞなら切り替え
		if (_animCount >= _animMap[_state][_animFrame].second)
		{
			_animFrame++;
		}

		// 範囲外ﾁｪｯｸ
		if (_animMap[_state].size() > _animFrame)
		{
			// 範囲内ならｶｳﾝﾀの加算
			_animCount++;

		}
		else
		{
			// 範囲外ならﾘｾｯﾄ
			_animFrame = 0;
			_animCount = 0;
		}
	}

	// ｷｭｰへの追加
	lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,_pos.x,_pos.y,_rad });
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id, _pos.x,_pos.y,_rad });
}

