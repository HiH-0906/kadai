#include "EnemyMove.h"
#include <_DebugConOut.h>
#include <cmath>
#include "_DebugDispOut.h"
#include <SceneMng.h>


EnemyMove::EnemyMove(Vector2Dbl & pos,double & rad,int &speed): _pos(pos),_rad(rad),_speed(speed)			// �Q�Ƃ͑��݂��ĂȂ��Ƃ����Ȃ��̂ł����ɏ���
{
	_move = nullptr;
	_aimCnt = -1;
}

EnemyMove::~EnemyMove()
{
}

void EnemyMove::Update(void)
{
	// ���g����
	if (_move != nullptr)
	{
		// �Ăяo��
		(this->*_move)();
	}
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
	// �͈�����
	if (_aim.size() <= _aimCnt)
	{
		// �͈͊O�Ȃ�return
		return;
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
		// wait�Ŏg���ϐ��̏�����
		count = 0;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = &EnemyMove::MoveSigmoid;
		// ��
		_moveGain = -5.0;
		// �ړI�n�܂ł̋���
		_lenght = _endPos - _startPos;
		_oldPos = _pos;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		// �p�x����
		_cntRad = 0.0;
		_tmpRad = PI * _endPos.y;
		_moveRad = PI / 90.0*_endPos.x*(1-(2*_endPos.y));
		// �~�̒��S����
		radius = 64.0;
		_endPos.y = _pos.y - radius + (radius*2.0 *_endPos.y);
		_endPos.x = _pos.x;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		// 1�ڰтɐi�ދ���
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
		// x�W��
		_moveGain += 10.0 / 180.0;
		// ���Ӳ�ފ֐��ɂ���ē����l���g��
		_pos.y = _startPos.y + 1.0 / (1.0 + exp(-1.3*_moveGain-1.0)) * _lenght.y;
		_pos.x = _startPos.x + (5 + _moveGain)*_lenght.x / 10.0;
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
	if (PI*2.0 - abs(_cntRad) > 0)
	{
		// �~�̃X�^�[�g�ʒu���炵�̂��߂�cos,sin�t�]
		_pos.y = _endPos.y + radius * std::cos(_tmpRad);
		_pos.x = _endPos.x + radius * std::sin(_tmpRad);
		// ��ׂ̌����Ă����������
		_rad = atan2(_pos.y - _oldPos.y, _pos.x - _oldPos.x) + PI / 2;
		radius -= 0.2;
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
	// 2�_��
	_lenght = _endPos - _pos;

	// 1 �ڰтɐi�ދ������_endPos�܂ł̋������Z���Ȃ�ړ��I��
	if (abs(_endPos - _pos)>=abs(_oneMoveVec))
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
}

void EnemyMove::Wait(void)
{
	// ���Ă��s���J�n����l�܂ŗ��Ă��邩�����@second��x���s���J�n���鶳�ĂƂ��Ĉ���
	if (count >= _endPos.x)
	{
		// �s���̐؂�ւ�
		SetMovePrg();
		// �ꉞ�؂�ւ��\��
		TREACE("Wait�I������[\n");
	}
	// ���Ă̑���
	count++;
}

void EnemyMove::MoveLR(void)
{
	_pos.x = _endPos.x;
}
