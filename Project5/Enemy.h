#pragma once
#include <tuple>
#include "Obj.h"
#include "EnemyMove.h"


enum class ENEMY_TYPE
{
	A,						// 蜂？
	B,						// 蛾？
	C,						// 蛾？
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
	Enemy(EnemyState &state);
	void Update(sharedObj plObj) override;
	~Enemy();
	bool exFlag(bool flag)override;									// 攻撃命令Flag変更
private:
	EnemyMove _moveCtl{ _pos ,_rad,_speed,_exFlag};					// ｴﾈﾐｰの動き管理用Obj
	void Init();
	ENEMY_TYPE _type;												// ｴﾈﾐｰtype識別用
};

