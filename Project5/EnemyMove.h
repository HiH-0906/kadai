#pragma once

#include <Vector2.h>
#include <vector>
#include "Obj.h"

#define ENEMY_MAX 50									// enemy����
#define PITIN_TIME 60									// PitIn�ɂ����鎞��
#define SIGMOID_TIME 60.0								// sigmoid�ɂ����鎞��
#define SPIRAL_MAX (PI*4.0)								// spiral�ŉ�]�����]��
#define LR_LIMT	50										// LR�ړ���
#define SCALE_LIMT 30									// �g��k���{��
#define ATACK_MAX 60									// atack����]����

enum class MOVE_TYPE
{
	WAIT,
	SIGMOID,
	SPIRAL,
	PITIN,
	LR,
	SCALE,
	ATACK
};

using MoveState = std::vector<std::pair<MOVE_TYPE, Vector2Dbl>>;		// �s���ړI�n�Ǘ��p�^

class EnemyMove
{

public:
	EnemyMove(Vector2Dbl& pos,double& rad,int& speed,bool& flag);		// ����͂킩��₷�����邽�߂ɎQ�ƂŎ󂯎�� �{����GetSet������Ƃ���
	~EnemyMove();
	void Update(sharedObj plObj);							// �X�V
	void InCount(void);
	MOVE_TYPE aimMove(void);
	bool SetMoveState(MoveState& state, bool newFlag);		// �s����Ċ֐�
private:
	void SetMovePrg(void);									// �s���؂�ւ�

	void(EnemyMove::*_move)(void);							// ���ފ֐��߲�� move�n

	void MoveSigmoid(void);									// ���Ӳ��
	void MoveSpiral(void);									// ���@�w�ٸ�
	void PitIn(void);										// �߯Ĳ�
	void Wait(void);										// �ҋ@ aim[_aimCnt].second�̒l�܂ŉ��
	void MoveLR(void);										// ���E
	void MoveScale(void);									// �g��k��
	void MoveAtack(void);									// �ˌ�

	int _count;												// wait�p����
	static int _enemyMax;									// �G�ő吔

	MoveState _aim;											// �ڕW�n�_
	unsigned int _aimCnt;									// �ǂ̖ړI�n������

	Vector2Dbl _startPos;									// �e�ړ��֐��̽��Ēn�_
	Vector2Dbl _endPos;										// �e�ړ��֐��̴��ޒn�_

	Vector2Dbl& _pos;										// ���������а��pos�̏ꏊ�ۑ�
	Vector2Dbl _lenght;										// ����
	Vector2Dbl _oneMoveVec;									// 1�ڰтł̈ڑ�����
	Vector2Dbl _oldPos;										// �p�x���߂�p
	Vector2Dbl _center;										// �G���S
	Vector2Dbl _range;										// ���S����̋���

	Vector2Dbl _plPos;										// ��ڲ԰pos�ۑ��p�ϐ�

	int _scaleCnt;
	int _startFlam;											// �g��k���J�n�ڰ�
	static int _InCount;									// �G�߯Ĳݶ���
	double radius;											// ���a
	double& _rad;											// �p�x
	double _tmpRad;											// ��]�p�p�x
	double _cntRad;											// ���ǂꂾ����]������
	double _moveRad;										// 1�ڰтɉ��p�x
	double _moveGain;										// �ړ��Ǘ�
	bool& _atackFlag;
};

