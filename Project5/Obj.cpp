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
	// �����g���邩����
	if (_animMap.find(key) == _animMap.end())
	{
		// �����̂Ŏg���Ȃ�
		return false;
	}
	// ��������o�^
	if (_animKey != key)
	{
		// �������łȂ����0��
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
	// c++17�ȍ~
	return (_animMap.try_emplace(key, std::move(data))).second;

	//// ���łɂ��邩����
	//if (_animMap.find(key) == _animMap.end())
	//{
	//	// ����������o�^
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
	// �O�̂��߷�����
	if (_animMap.find(_animKey) == _animMap.end())
	{
		// ���݂��Ȃ�������return
		return;
	}
	// ��Ұ����ڰт�����
	if (_animMap[_animKey].size() <= _animFrame ||
		0 > _animFrame)
	{
		// ���݂��Ȃ�������return
		return;
	}
	// �ݼ��Ă̱�Ұ��݂Ȃ珈�������Ȃ�
	if (_animMap[_animKey][_animFrame].first >= 0)
	{
		// �����Ʊ�Ұ����ڰт��ׂĐ؂�ւ����ݸނȂ�؂�ւ�
		if (_animCount >= _animMap[_animKey][_animFrame].second)
		{

			_animFrame++;

		}

		// �͈͊O����
		if (_animMap[_animKey].size() > _animFrame)
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
	lpSceneMng.AddDrawQue({ _animMap[_animKey][_animFrame].first,_pos.x,_pos.y });
}

void Obj::Draw(int id)
{
	lpSceneMng.AddDrawQue({ id, _pos.x,_pos.y });
}

