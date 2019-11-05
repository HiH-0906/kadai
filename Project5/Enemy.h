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
	TYPE,				// 種別
	VECTOR,				// 座標
	SIZE,				// ｻｲｽﾞ
	RAD,				// 角度
	AIM,				// 目標地点
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
	EnemyMove _moveCtl{ _pos ,_rad };					// ｴﾈﾐｰの動き管理用Obj
	void Init();
	ENEMY_TYPE _type;							// ｴﾈﾐｰtype識別用
};

