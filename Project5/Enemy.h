#pragma once
#include <tuple>
#include "Obj.h"
#include "EnemyMove.h"


enum class ENEMY_TYPE
{
	A,						// �I�H
	B,						// ��H
	C,						// ��H
	MAX
};

enum class ENEMY_STATE
{
	TYPE,				// ���
	VECTOR,				// ���W
	SIZE,				// ����
	RAD,				// �p�x
	AIM,				// �ڕW�n�_
	MAX
};
//								type		pos			size	rad			aim
using EnemyState = std::tuple<ENEMY_TYPE, Vector2Dbl, Vector2Dbl,double, MoveState&>;

class Enemy :
	public Obj
{
public:
	Enemy(EnemyState &state);
	void Update(sharedObj plObj) override;
	~Enemy();
	bool exFlag(bool flag)override;									// �U������Flag�ύX
private:
	EnemyMove _moveCtl{ _pos ,_rad,_speed,_exFlag};					// ��а�̓����Ǘ��pObj
	void Init();
	ENEMY_TYPE _type;												// ��аtype���ʗp
};

