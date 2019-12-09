#pragma once
#include <vector>
#include <functional>
#include "BaseScene.h"
#include "Obj.h"

using funcAct = std::function<bool(ActQueT&, void*)>;						// �����ƕԂ�l���������̂���荞�߂�

#define FORMATION 3															// �G�ґ�������
#define WAIT_TIME 50.0														// �ґ����Ƃ̑҂�����
#define CHAR_SIZE_X 30														// ���@��G��size x
#define CHAR_SIZE_Y 32														// ���@��G��size y
#define ENEMY_OFFSET_X  (CHAR_SIZE_X*2.5)									// �G��̫�Ĉʒu��x�����̾��
#define ENEMY_OFFSET_Y  40.0												// �G��̫�Ĉʒu��y�����̾��

struct FuncCheckHit;
struct FuncBullet;
struct FuncShake;

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	unipueBase Update(unipueBase own) override final;
private:
	friend FuncCheckHit;													// �F�B
	friend FuncBullet;
	friend FuncShake;
	std::vector<sharedObj> _objList;										// List�ł͂Ȃ�Vector
	void RunActQue(std::vector<ActQueT> actList)override final;				// ActQue�̎��s
	void initFunc(void);													// funcQue�ւ̊֐���޼ު�đ��
	std::map<ACT_QUE, funcAct> funcQue;										// �֐���޼ު�ĊǗ�
	Vector2Dbl _enemyDefFomation;											// �G��̫�Ĕz�u
	int _shakeCount;														// ��ʂ��h����ڰѐ�
};

