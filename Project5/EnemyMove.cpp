#include "EnemyMove.h"


EnemyMove::EnemyMove(Vector2Template<int> & pos): _pos(pos)			// �Q�Ƃ͑��݂��ĂȂ��Ƃ����Ȃ��̂ł����ɏ���
{
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	_pos.x++;
}
