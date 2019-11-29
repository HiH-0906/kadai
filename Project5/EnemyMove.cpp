#include "EnemyMove.h"
#include <_DebugConOut.h>
#include <cmath>
#include "_DebugDispOut.h"
#include <SceneMng.h>

int EnemyMove::_InCount = 0;
// 敵最大数設定
int EnemyMove::_enemyMax = ENEMY_MAX;
EnemyMove::EnemyMove(Vector2Dbl & pos,double & rad,int &speed,bool &flag): _pos(pos),_rad(rad),_atackFlag(flag)			// 参照は存在してないといけないのでここに書く
{
	_move = nullptr;
	_aimCnt = -1;
	_startFlam = 0;
	_shotFlag = false;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(sharedObj plObj)
{
	_plPos = (*plObj).pos();
	// 中身ﾁｪｯｸ
	if (_move != nullptr)
	{
		// 呼び出し
		(this->*_move)();
	}
}


void EnemyMove::InCount(void)
{
	// 敵PitInCnt加算
	_InCount++;
}

MOVE_TYPE EnemyMove::aimMove(void)
{
	if (_aim.size() <= _aimCnt)
	{
		// 要素数より_aimCntが多ければWAITで返す
		return MOVE_TYPE::WAIT;
	}
	return _aim[_aimCnt].first;
}

const bool EnemyMove::shotFlag(void) const
{
	return _shotFlag;
}


bool EnemyMove::shotFlag(bool flag)
{
	_shotFlag = flag;
	return true;
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
	_shotFlag = false;
	auto checkAim = [&]() 
	{
		for (_aimCnt = 0;_aimCnt<_aim.size();_aimCnt++)
		{
			// SCALEまで巻き戻す
			if (_aim[_aimCnt].first == MOVE_TYPE::SCALE)
			{
				return true;
			}
		}
		return false;
	};

	// 範囲ﾁｪｯｸ
	if (_aim.size() <= _aimCnt)
	{
		if (!checkAim())
		{
			// 範囲外ならreturn
			return;
		}
	}
	if (_pos.y > lpSceneMng.GameScreenSize.y)
	{
		// 画面下部へ行ったら画面上部へ
		_pos.y = -100.0;
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
		_count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		// 幅
		_moveGain = -5.0;
		// 目的地までの距離
		_lenght = _endPos - _startPos;
		_lenght.x /= SIGMOID_TIME;
		_oldPos = _pos;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		// 角度決め
		_cntRad = 0.0;
		_tmpRad = PI * _endPos.y;
		_moveRad = PI / 20.0*_endPos.x*(1-(2*_endPos.y));
		// 円の中心決め
		radius = 64.0;
		_endPos.y = _pos.y - radius + (radius*2.0 *_endPos.y);
		_endPos.x = _pos.x;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		if (_startPos.y > 0)
		{
			_endPos.x += (std::abs((lpSceneMng.fCnt + PITIN_TIME) % (LR_LIMT * 2) - LR_LIMT) - (LR_LIMT / 2));
		}
		else
		{
			_endPos = _center + _range * static_cast<double>(100 + (std::abs(std::abs((((lpSceneMng.fCnt - _startFlam) + PITIN_TIME) % (SCALE_LIMT * 2) - SCALE_LIMT)) - SCALE_LIMT))) / 100.0;
		}
		// 2点間
		_lenght = _endPos - _pos;
		// 1ﾌﾚｰﾑに進む距離
		_oneMoveVec = (_endPos - _startPos) / static_cast<double>(PITIN_TIME);
		_count = 0;
		break;
	case MOVE_TYPE::LR:
		_count = 0;
		_move = &EnemyMove::MoveLR;
		// PitIn終わったか？ｶｳﾝﾄ
		_InCount++;
		break;
	case MOVE_TYPE::SCALE:
		_move = &EnemyMove::MoveScale;
		// 敵中央
		_center = { lpSceneMng.GameScreenSize.x / 2.0,40.0 * 3.0 };
		_range = _endPos - _center;
		if (_startFlam == 0)
		{
			// SCALEが始まったﾌﾚｰﾑ数記憶
			_startFlam = lpSceneMng.fCnt;
		}
		break;
	case MOVE_TYPE::ATACK:
		_move = &EnemyMove::MoveAtack;
		// 1ﾌﾚｰﾑに動く角度
		_tmpRad = (atan2(_plPos.y - _pos.y, _plPos.x - _pos.x)+PI / 2)/ATACK_MAX;
		_count = 0;
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
		_moveGain += 10.0 / SIGMOID_TIME;
		// ｼｸﾞﾓｲﾄﾞ関数によって得た値を拡大
		_pos.y = _startPos.y + 1.0 / (1.0 + exp(-1.5*_moveGain+1.0)) * _lenght.y;
		_pos.x = _pos.x + _lenght.x;
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
	if (SPIRAL_MAX - abs(_cntRad) > 0)
	{
		// 円のスタート位置ずらしのためのcos,sin逆転
		_pos.y = _endPos.y + radius * std::cos(_tmpRad);
		_pos.x = _endPos.x + radius * std::sin(_tmpRad);
		// ｷｬﾗの向いている方向決め
		_rad = atan2(_pos.y - _oldPos.y, _pos.x - _oldPos.x) + PI / 2;
		radius -= 0.5;
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
	// 1 ﾌﾚｰﾑに進む距離より_endPosまでの距離が短いなら移動終了
	if (_count < PITIN_TIME)
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
	_count++;
}

void EnemyMove::Wait(void)
{
	// ｶｳﾝﾄが行動開始する値まで来ているかﾁｪｯｸ　secondのxを行動開始するｶｳﾝﾄとして扱う
	if (_count >= _endPos.x)
	{
		// 行動の切り替え
		SetMovePrg();
		// 一応切り替え表示
		TREACE("Wait終了だよー\n");
	}
	// ｶｳﾝﾄの増加
	_count++;
}

void EnemyMove::MoveLR(void)
{
	_pos.x = _endPos.x + (std::abs(lpSceneMng.fCnt % (LR_LIMT * 2) - LR_LIMT) - (LR_LIMT/2));
	if (_InCount >= _enemyMax && lpSceneMng.fCnt % (LR_LIMT * 2) == (LR_LIMT / 2))
	{
		SetMovePrg();
		_startFlam = lpSceneMng.fCnt;
		TREACE("LR終了だよー\n");
	}
}

void EnemyMove::MoveScale(void)
{
	_pos = _center + _range * static_cast<double>(100 + (std::abs(std::abs(((lpSceneMng.fCnt - _startFlam) % (SCALE_LIMT * 2) - SCALE_LIMT)) - SCALE_LIMT))) / 100.0;
	// 攻撃命令が飛んできてたら移行
	if (_atackFlag)
	{
		SetMovePrg();
		_atackFlag = false;
		TREACE("Scale終了だよー\n");
	}
}

void EnemyMove::MoveAtack(void)
{
	if (_count < ATACK_MAX)
	{
		// 回る
		_rad += _tmpRad;
	}
	else
	{
		// PitIn偽装
		_shotFlag = true;
		_move = &EnemyMove::PitIn;
		_lenght = (_plPos - _pos)*1.5;
		_endPos = _pos + _lenght;
		// 2点間
		_lenght = _endPos - _pos;
		// 1ﾌﾚｰﾑに進む距離
		_oneMoveVec = _lenght / static_cast<double>(PITIN_TIME);
		_count = 0;
	}
	_count++;
}
