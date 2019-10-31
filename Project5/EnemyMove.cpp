#include "EnemyMove.h"


EnemyMove::EnemyMove(Vector2Dbl & pos): _pos(pos)			// 参照は存在してないといけないのでここに書く
{
	_move = nullptr;
	_aimCnt = -1;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	_pos.x++;
}

bool EnemyMove::SetMoveState(MoveState & state, bool newFlag)
{
	if (newFlag)
	{
		// 中身を消す
		_aim.clear();
	}
	_aim = std::move(state);		// ｺﾋﾟｰを作りたくないので所有権譲渡
	
	if (newFlag)
	{
		// 切り替え
		SetMovePrg();
	}

	return true;
}

void EnemyMove::SetMovePrg(void)
{
	_aimCnt++;
	// 範囲ﾁｪｯｸ
	if (static_cast<int>(_aim.size()) <= _aimCnt)
	{
		// 範囲外ならreturn
		return;
	}
	_startPos = _pos;
	_endPos = _aim[_aimCnt].second;

}

void EnemyMove::MoveSigmoid(void)
{
}

void EnemyMove::MoveSpiral(void)
{
}

void EnemyMove::PitIn(void)
{
}

void EnemyMove::Wait(void)
{
}

void EnemyMove::MoveLR(void)
{
}
