#include "EnemyMove.h"


EnemyMove::EnemyMove(Vector2Template<int> & pos): _pos(pos)			// 参照は存在してないといけないのでここに書く
{
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	_pos.x++;
}
