#include "EnemyMove.h"
#include <_DebugConOut.h>


EnemyMove::EnemyMove(Vector2Dbl & pos,double & rad): _pos(pos),_rad(rad)			// �Q�Ƃ͑��݂��ĂȂ��Ƃ����Ȃ��̂ł����ɏ���
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
		break;
	case MOVE_TYPE::SPIRAL:
		_move = &EnemyMove::MoveSpiral;
		break;
	case MOVE_TYPE::PITIN:
		_move = &EnemyMove::PitIn;
		// 1�ڰтɐi�ދ���
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
	// 2�_��
	_lenght = _endPos - _pos;

	// 1 �ڰтɐi�ދ������_endPos�܂ł̋������Z���Ȃ�ړ��I��
	if (abs(_endPos - _pos)>=abs(_oneMoveVec))
	{
		_pos += _oneMoveVec;
		_rad = atan2(_lenght.y, _lenght.x) + 3.141592 / 2;
	}
	else
	{
		// �ʒu����
		_pos = _endPos;
		// �s���؂�ւ�
		SetMovePrg();
		_rad = 0;
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
	/*_pos.x++;*/
}
