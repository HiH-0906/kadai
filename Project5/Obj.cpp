#include <DxLib.h>
#include "Obj.h"
#include <SceneMng.h>
#include <ImageMng.h>


Obj::Obj()
{
	_alive = true;			// ��
	_dead = false;			// ��
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
	// �����g���邩����
	if (_animMap.find(state) == _animMap.end())
	{
		// �����̂Ŏg���Ȃ�
		return false;
	}
	// ��������o�^
	if (_state != state)
	{
		// �������łȂ����0��
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
	// c++17�ȍ~
	return (_animMap.try_emplace(state, std::move(data))).second;

	//// ���łɂ��邩����
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	// ����������o�^
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
	// �O�̂��߷�����
	if (_animMap.find(_state) == _animMap.end())
	{
		// ���݂��Ȃ�������I����Ă��鈵��
		return true;
	}
	// ��Ұ����ڰт�����
	if (_animMap[_state].size() <= _animFrame ||
		0 > _animFrame)
	{
		// ���݂��Ȃ�������I����Ă��鈵��
		return true;
	}
	// ��Ұ��݂��I�����Ă��邩����
	if (_animMap[_state][_animFrame].first == -1)
	{
		return true;
	}
	return false;
}

bool Obj::DestroyProc(void)
{
	// �����Ă邩
	if (_alive)
	{
		// �����Ă���return
		return false;
	}
	// ��Ұ��ݏI�����Ă��邩
	if (isAnimEnd())
	{
		// �I�����Ă������׸޵�
		_dead = true;
	}
	// ����ł���true
	return true;
}

void Obj::Draw(void)
{
	// �O�̂��߷�����
	if (_animMap.find(_state) == _animMap.end())
	{
		// ���݂��Ȃ�������return
		return;
	}
	// ��Ұ����ڰт�����
	if (_animMap[_state].size() <= _animFrame ||
		0 > _animFrame)
	{
		// ���݂��Ȃ�������return
		return;
	}
	// �ݼ��Ă̱�Ұ��݂Ȃ珈�������Ȃ�
	if (_animMap[_state][_animFrame].first >= 0)
	{
		// �����Ʊ�Ұ����ڰт��ׂĐ؂�ւ����ݸނȂ�؂�ւ�
		if (_animCount >= _animMap[_state][_animFrame].second)
		{
			_animFrame++;
		}

		// �͈͊O����
		if (_animMap[_state].size() > _animFrame)
		{
			// �͈͓��Ȃ綳���̉��Z
			_animCount++;

		}
		else
		{
			// �͈͊O�Ȃ�ؾ��
			_animFrame = 0;
			_animCount = 0;
		}
	}

	// ����ւ̒ǉ�
	lpSceneMng.AddDrawQue({ _animMap[_state][_animFrame].first,_pos.x + lpSceneMng.GameScreenOffset.x,_pos.y+lpSceneMng.GameScreenOffset.y,_rad,_zOrder,LAYER::CHAR});
}

void Obj::Draw(int id)
{
	// ����ւ̒ǉ�
	lpSceneMng.AddDrawQue({ id, _pos.x+lpSceneMng.GameScreenOffset.x,_pos.y+ lpSceneMng.GameScreenOffset.y,_rad,_zOrder,LAYER::CHAR});
}

