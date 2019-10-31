#include "EnemyMove.h"
#include <_DebugConOut.h>


EnemyMove::EnemyMove(Vector2Dbl & pos): _pos(pos)			// �Q�Ƃ͑��݂��ĂȂ��Ƃ����Ȃ��̂ł����ɏ���
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
	if (static_cast<int>(_aim.size()) <= _aimCnt)
	{
		// �͈͊O�Ȃ�return
		return;
	}
	_startPos = _pos;
	_endPos = _aim[_aimCnt].second;

	switch (_aim[_aimCnt].first)
	{
	case MOVE_TYPE::WAIT:
		_move = EnemyMove::Wait;
		break;
	case MOVE_TYPE::SIGMOID:
		_move = EnemyMove::MoveSigmoid;
		break;
	case MOVE_TYPE::SPIRAL:
		_move = EnemyMove::MoveSpiral;
		break;
	case MOVE_TYPE::PITIN:
		_move = EnemyMove::PitIn;
		break;
	case MOVE_TYPE::LR:
		_move = EnemyMove::MoveLR;
		break;
	default:
		AST();
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
}

void EnemyMove::Wait(void)
{
}

void EnemyMove::MoveLR(void)
{
}
