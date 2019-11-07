#include "EnemyMove.h"
#include <_DebugConOut.h>


EnemyMove::EnemyMove(Vector2Dbl & pos,double & rad): _pos(pos),_rad(rad)			// 参照は存在してないといけないのでここに書く
{
	_move = nullptr;
	_aimCnt = -1;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	// 中身ﾁｪｯｸ
	if (_move != nullptr)
	{
		// 呼び出し
		(this->*_move)();
	}
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
	if (_aim.size() <= _aimCnt)
	{
		// 範囲外ならreturn
		return;
	}
	// ｽﾀｰﾄ位置保存
	_startPos = _pos;
	// 目的地保存
	_endPos = _aim[_aimCnt].second;

	// bimCntに合わせて_moveの中身変更
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		// waitで使う変数の初期化
		count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		// 1ﾌﾚｰﾑに進む距離
		_oneMoveVec = (_endPos - _startPos) / 120.0;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		break;
	default:
		AST();
		_move = &EnemyMove::Wait;
		break;
	}
}

void EnemyMove::MoveSigmoid(void)
{
}

void EnemyMove::MoveSpiral(void)
{
}

void EnemyMove::PitIn(void)
{
	// 2点間
	_lenght = _endPos - _pos;

	// 1 ﾌﾚｰﾑに進む距離より_endPosまでの距離が短いなら移動終了
	if (abs(_endPos - _pos)>=abs(_oneMoveVec))
	{
		_pos += _oneMoveVec;
		_rad = atan2(_lenght.y, _lenght.x) + 3.141592 / 2;
	}
	else
	{
		// 位置矯正
		_pos = _endPos;
		// 行動切り替え
		SetMovePrg();
		_rad = 0;
		// 一応切り替え表示
		TREACE("Pitin終了だよー\n");
	}
}

void EnemyMove::Wait(void)
{
	// ｶｳﾝﾄが行動開始する値まで来ているかﾁｪｯｸ　secondのxを行動開始するｶｳﾝﾄとして扱う
	if (count >= _endPos.x)
	{
		// 行動の切り替え
		SetMovePrg();
		// 一応切り替え表示
		TREACE("Wait終了だよー\n");
	}
	// ｶｳﾝﾄの増加
	count++;
}

void EnemyMove::MoveLR(void)
{
	/*_pos.x++;*/
}
