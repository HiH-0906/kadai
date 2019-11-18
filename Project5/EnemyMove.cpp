#include "EnemyMove.h"
#include <_DebugConOut.h>
#include <cmath>
#include "_DebugDispOut.h"
#include <SceneMng.h>


EnemyMove::EnemyMove(Vector2Dbl & pos,double & rad,int &speed): _pos(pos),_rad(rad),_speed(speed)			// 参照は存在してないといけないのでここに書く
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
		// 幅
		_moveGain = -5.0;
		// 目的地までの距離
		_lenght = _endPos - _startPos;
		_oldPos = _pos;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		// 角度決め
		_cntRad = 0.0;
		_tmpRad = PI * _endPos.y;
		_moveRad = PI / 90.0*_endPos.x*(1-(2*_endPos.y));
		// 円の中心決め
		radius = 64.0;
		_endPos.y = _pos.y - radius + (radius*2.0 *_endPos.y);
		_endPos.x = _pos.x;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		// 1ﾌﾚｰﾑに進む距離
		_oneMoveVec = (_endPos - _startPos) / 120.0;
		break;
	case MOVE_TYPE::LR:
		_move = &EnemyMove::MoveLR;
		count = 0;
		break;
	default:
		AST();
		_move = &EnemyMove::Wait;
		break;
	}
}

void EnemyMove::MoveSigmoid(void)
{
	_oldPos = _pos;
	if (5 - _moveGain >= 0.05)
	{
		// x係数
		_moveGain += 10.0 / 180.0;
		// ｼｸﾞﾓｲﾄﾞ関数によって得た値を拡大
		_pos.y = _startPos.y + 1.0 / (1.0 + exp(-1.3*_moveGain-1.0)) * _lenght.y;
		_pos.x = _startPos.x + (5 + _moveGain)*_lenght.x / 10.0;
		_rad = atan2(_pos.y - _oldPos.y, _pos.x - _oldPos.x) + PI / 2;
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
	_oldPos = _pos;
	if (PI*2.0 - abs(_cntRad) > 0)
	{
		// 円のスタート位置ずらしのためのcos,sin逆転
		_pos.y = _endPos.y + radius * std::cos(_tmpRad);
		_pos.x = _endPos.x + radius * std::sin(_tmpRad);
		// ｷｬﾗの向いている方向決め
		_rad = atan2(_pos.y - _oldPos.y, _pos.x - _oldPos.x) + PI / 2;
		radius -= 0.2;
		_tmpRad += _moveRad;
		_cntRad += abs(_moveRad);
	}
	else
	{
		SetMovePrg();
		TREACE("Spairal終了だよー\n");
	}
}

void EnemyMove::PitIn(void)
{
	// 2点間
	_lenght = _endPos - _pos;

	// 1 ﾌﾚｰﾑに進む距離より_endPosまでの距離が短いなら移動終了
	if (abs(_endPos - _pos)>=abs(_oneMoveVec))
	{
		_pos += _oneMoveVec;
		_rad = atan2(_lenght.y, _lenght.x) + PI / 2.0;
	}
	else
	{
		// 位置矯正
		_pos = _endPos;
		_rad = 0.0;
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
	_pos.x = _endPos.x;
}
