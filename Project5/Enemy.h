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

using EnemyState = std::tuple<ENEMY_TYPE, Vector2Dbl, Vector2Int>;

class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(EnemyState &state);
	void Update(void) override;
	~Enemy();
private:
	EnemyMove moveCtl{ _pos };					// ´ÈĞ°‚Ì“®‚«ŠÇ——pObj
	void Init();
	ENEMY_TYPE _type;							// ´ÈĞ°type¯•Ê—p
};

