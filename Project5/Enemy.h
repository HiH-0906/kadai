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
	TYPE,
	VECTOR,
	SIZE,
	MAX
};

using EnemyState = std::tuple<ENEMY_TYPE, Vector2Template<int>, Vector2Template<int>>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState &state);
	void Update(void) override;
	~Enemy();
private:
	EnemyMove moveCtl{ _pos };					// ｴﾈﾐｰの動き管理用Obj
	void Init();
	ENEMY_TYPE _type;							// ｴﾈﾐｰtype識別用
};

