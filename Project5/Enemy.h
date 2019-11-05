#pragma once
#include <tuple>
#include "Obj.h"
#include "EnemyMove.h"

enum class ENEMY_TYPE
{
	A,
	B,
	C,
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
	Enemy();
	Enemy(EnemyState &state);
	void Update(void) override;
	~Enemy();
private:
	EnemyMove _moveCtl{ _pos ,_rad };					// ��а�̓����Ǘ��pObj
	void Init();
	ENEMY_TYPE _type;							// ��аtype���ʗp
};

