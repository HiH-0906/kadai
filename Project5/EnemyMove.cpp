#include "EnemyMove.h"


EnemyMove::EnemyMove(Vector2Dbl & pos): _pos(pos)			// QÆ‚Í‘¶İ‚µ‚Ä‚È‚¢‚Æ‚¢‚¯‚È‚¢‚Ì‚Å‚±‚±‚É‘‚­
{
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	_pos.x++;
}
