#include "EnemyMove.h"
#include <_DebugConOut.h>
#include <cmath>


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
		_moveGain = -5.0;
		_lenght = _endPos - _startPos;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		_centr.y = _pos.y - 128.0;
		_centr.x = _pos.x;
		_rad = 0.0;
		radius = 128.0;
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
	if (5 - _moveGain >= 0.05)
	{
		// x係数
		_moveGain += 10.0 / 180.0;
		// ｼｸﾞﾓｲﾄﾞ関数によって得た値を拡大
		_pos.y = _startPos.y + 1.0 / (1.0 + exp(-1.3*_moveGain-2.0)) * _lenght.y;
		_pos.x = _startPos.x + (5 + _moveGain)*_lenght.x / 10.0;
		_rad= atan2(_endPos.y-_pos.y,_endPos.x-_pos.x) + 3.141592 / 2.0;
		TREACE("%f\n", _pos.y);
	}
	else
	{
		// 位置強制
		_pos = _endPos;
		SetMovePrg();
	}
}

void EnemyMove::MoveSpiral(void)
{
	_pos.y = _centr.y + radius*std::cos(_rad);
	_pos.x = _centr.x + radius*std::sin(_rad);
	_rad += 3.141592 / 180.0;
	radius -= 0.1;
}

void EnemyMove::PitIn(void)
{
	// 2点間
	_lenght = _endPos - _pos;

	// 1 ﾌﾚｰﾑに進む距離より_endPosまでの距離が短いなら移動終了
	if (abs(_endPos - _pos)>=abs(_oneMoveVec))
	{
		_pos += _oneMoveVec;
		_rad = atan2(_lenght.y, _lenght.x) + 3.141592 / 2.0;
	}
	else
	{
		// 位置矯正
		_pos = _endPos;
		_rad = 0;
		// 行動切り替え
		SetMovePrg();
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
