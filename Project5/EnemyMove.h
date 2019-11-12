#pragma once

#include <Vector2.h>
#include <vector>

enum class MOVE_TYPE
{
	WAIT,
	SIGMOID,
	SPIRAL,
	PITIN,
	LR
};

using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2Dbl>>;		// �s���ړI�n�Ǘ��p�^

class EnemyMove
{

public:
	EnemyMove(Vector2Dbl& pos,double& rad);					// ����͂킩��₷�����邽�߂ɎQ�ƂŎ󂯎�� �{����GetSet������Ƃ���
	~EnemyMove();
	void Update(void);										// �X�V
	bool SetMoveState(MoveState& state, bool newFlag);		// �s����Ċ֐�
private:
	void SetMovePrg(void);									// �s���؂�ւ�

	void(EnemyMove::*_move)(void);							// ���ފ֐��߲�� move�n
	void MoveSigmoid(void);									// ���Ӳ��
	void MoveSpiral(void);									// ���@�w�ٸ�
	void PitIn(void);										// �߯Ĳ�
	void Wait(void);										// �ҋ@ aim[_aimCnt].second�̒l�܂ŉ��
	void MoveLR(void);										// ���E

	int count;												// wait�p����

	MoveState _aim;											// �ڕW�n�_
	unsigned int _aimCnt;									// �ǂ̖ړI�n������

	Vector2Dbl _startPos;									// �e�ړ��֐��̽��Ēn�_
	Vector2Dbl _endPos;										// �e�ړ��֐��̴��ޒn�_

	Vector2Dbl& _pos;										// ���������а��pos�̏ꏊ�ۑ�
	Vector2Dbl _lenght;										// ����
	Vector2Dbl _oneMoveVec;
	Vector2Dbl _centr;										// �~�̒��S
	double radius;
	double& _rad;											// �p�x
	double _moveGain;										// �ړ��Ǘ�
};

