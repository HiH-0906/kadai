#include "EnemyMove.h"
#include <_DebugConOut.h>
#include <cmath>
#include "_DebugDispOut.h"
#include <SceneMng.h>

int EnemyMove::_InCount = 0;
// �G�ő吔�ݒ�
int EnemyMove::_enemyMax = ENEMY_MAX;
EnemyMove::EnemyMove(Vector2Dbl & pos,double & rad,int &speed,bool &flag): _pos(pos),_rad(rad),_atackFlag(flag)			// �Q�Ƃ͑��݂��ĂȂ��Ƃ����Ȃ��̂ł����ɏ���
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
	// ���g����
	if (_move != nullptr)
	{
		// �Ăяo��
		(this->*_move)();
	}
}


void EnemyMove::InCount(void)
{
	// �GPitInCnt���Z
	_InCount++;
}

MOVE_TYPE EnemyMove::aimMove(void)
{
	if (_aim.size() <= _aimCnt)
	{
		// �v�f�����_aimCnt���������WAIT�ŕԂ�
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
		// ���g������
		_aim.clear();
	}
	_aim = std::move(state);		// ��߰����肽���Ȃ��̂ŏ��L�����n
	
	if (newFlag)
	{
		// �؂�ւ�
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
			// SCALE�܂Ŋ����߂�
			if (_aim[_aimCnt].first == MOVE_TYPE::SCALE)
			{
				return true;
			}
		}
		return false;
	};

	// �͈�����
	if (_aim.size() <= _aimCnt)
	{
		if (!checkAim())
		{
			// �͈͊O�Ȃ�return
			return;
		}
	}
	if (_pos.y > lpSceneMng.GameScreenSize.y)
	{
		// ��ʉ����֍s�������ʏ㕔��
		_pos.y = -100.0;
	}
	// ���Ĉʒu�ۑ�
	_startPos = _pos;
	// �ړI�n�ۑ�
	_endPos = _aim[_aimCnt].second;

	// bimCnt�ɍ��킹��_move�̒��g�ύX
	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = &EnemyMove::Wait;
		_count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		// ��
		_moveGain = -5.0;
		// �ړI�n�܂ł̋���
		_lenght = _endPos - _startPos;
		_lenght.x /= SIGMOID_TIME;
		_oldPos = _pos;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		// �p�x����
		_cntRad = 0.0;
		_tmpRad = PI * _endPos.y;
		_moveRad = PI / 20.0*_endPos.x*(1-(2*_endPos.y));
		// �~�̒��S����
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
		// 2�_��
		_lenght = _endPos - _pos;
		// 1�ڰтɐi�ދ���
		_oneMoveVec = (_endPos - _startPos) / static_cast<double>(PITIN_TIME);
		_count = 0;
		break;
	case MOVE_TYPE::LR:
		_count = 0;
		_move = &EnemyMove::MoveLR;
		// PitIn�I��������H����
		_InCount++;
		break;
	case MOVE_TYPE::SCALE:
		_move = &EnemyMove::MoveScale;
		// �G����
		_center = { lpSceneMng.GameScreenSize.x / 2.0,40.0 * 3.0 };
		_range = _endPos - _center;
		if (_startFlam == 0)
		{
			// SCALE���n�܂����ڰѐ��L��
			_startFlam = lpSceneMng.fCnt;
		}
		break;
	case MOVE_TYPE::ATACK:
		_move = &EnemyMove::MoveAtack;
		// 1�ڰтɓ����p�x
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
		// x�W��
		_moveGain += 10.0 / SIGMOID_TIME;
		// ���Ӳ�ފ֐��ɂ���ē����l���g��
		_pos.y = _startPos.y + 1.0 / (1.0 + exp(-1.5*_moveGain+1.0)) * _lenght.y;
		_pos.x = _pos.x + _lenght.x;
		_rad = atan2(_pos.y - _oldPos.y, _pos.x - _oldPos.x) + PI / 2;
	}
	else
	{
		// �ʒu����
		_pos = _endPos;
		SetMovePrg();
	}
}

void EnemyMove::MoveSpiral(void)
{
	_oldPos = _pos;
	if (SPIRAL_MAX - abs(_cntRad) > 0)
	{
		// �~�̃X�^�[�g�ʒu���炵�̂��߂�cos,sin�t�]
		_pos.y = _endPos.y + radius * std::cos(_tmpRad);
		_pos.x = _endPos.x + radius * std::sin(_tmpRad);
		// ��ׂ̌����Ă����������
		_rad = atan2(_pos.y - _oldPos.y, _pos.x - _oldPos.x) + PI / 2;
		radius -= 0.5;
		_tmpRad += _moveRad;
		_cntRad += abs(_moveRad);
	}
	else
	{
		SetMovePrg();
		TREACE("Spairal�I������[\n");
	}
}

void EnemyMove::PitIn(void)
{
	// 1 �ڰтɐi�ދ������_endPos�܂ł̋������Z���Ȃ�ړ��I��
	if (_count < PITIN_TIME)
	{
		_pos += _oneMoveVec;
		_rad = atan2(_lenght.y, _lenght.x) + PI / 2.0;
	}
	else
	{
		// �ʒu����
		_pos = _endPos;
		_rad = 0.0;
		// �s���؂�ւ�
		SetMovePrg();
		// �ꉞ�؂�ւ��\��
		TREACE("Pitin�I������[\n");
	}
	_count++;
}

void EnemyMove::Wait(void)
{
	// ���Ă��s���J�n����l�܂ŗ��Ă��邩�����@second��x���s���J�n���鶳�ĂƂ��Ĉ���
	if (_count >= _endPos.x)
	{
		// �s���̐؂�ւ�
		SetMovePrg();
		// �ꉞ�؂�ւ��\��
		TREACE("Wait�I������[\n");
	}
	// ���Ă̑���
	_count++;
}

void EnemyMove::MoveLR(void)
{
	_pos.x = _endPos.x + (std::abs(lpSceneMng.fCnt % (LR_LIMT * 2) - LR_LIMT) - (LR_LIMT/2));
	if (_InCount >= _enemyMax && lpSceneMng.fCnt % (LR_LIMT * 2) == (LR_LIMT / 2))
	{
		SetMovePrg();
		_startFlam = lpSceneMng.fCnt;
		TREACE("LR�I������[\n");
	}
}

void EnemyMove::MoveScale(void)
{
	_pos = _center + _range * static_cast<double>(100 + (std::abs(std::abs(((lpSceneMng.fCnt - _startFlam) % (SCALE_LIMT * 2) - SCALE_LIMT)) - SCALE_LIMT))) / 100.0;
	// �U�����߂����ł��Ă���ڍs
	if (_atackFlag)
	{
		SetMovePrg();
		_atackFlag = false;
		TREACE("Scale�I������[\n");
	}
}

void EnemyMove::MoveAtack(void)
{
	if (_count < ATACK_MAX)
	{
		// ���
		_rad += _tmpRad;
	}
	else
	{
		// PitIn�U��
		_shotFlag = true;
		_move = &EnemyMove::PitIn;
		_lenght = (_plPos - _pos)*1.5;
		_endPos = _pos + _lenght;
		// 2�_��
		_lenght = _endPos - _pos;
		// 1�ڰтɐi�ދ���
		_oneMoveVec = _lenght / static_cast<double>(PITIN_TIME);
		_count = 0;
	}
	_count++;
}
