#include "Enemy.h"
#include <ImageMng.h>
#include <SceneMng.h>
#include "_DebugDispOut.h"


void Enemy::Init()
{
	// ��а��Ұ����ް��쐬
	AnimVector data;
	data.emplace_back(IMAGE_ID("���")[10 + 10 * static_cast<int>(_type)], 30);
	data.emplace_back(IMAGE_ID("���")[11 + 10 * static_cast<int>(_type)], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("�G����")[0], 10);
	data.emplace_back(IMAGE_ID("�G����")[1], 15);
	data.emplace_back(IMAGE_ID("�G����")[2], 20);
	data.emplace_back(IMAGE_ID("�G����")[3], 25);
	data.emplace_back(IMAGE_ID("�G����")[4], 30);
	data.emplace_back(-1, 35);
	SetAnim(STATE::DEATH, data);


	state(STATE::NORMAL);
}


Enemy::Enemy(EnemyState &state)
{
	// �����ł�������l�ɂ�鏉����
	_type = std::get<static_cast<int>(ENEMY_STATE::TYPE)>(state);								// ���߂̐ݒ�
	_pos = std::move(std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(state));					// ���W�̐ݒ�
	_size = std::move(std::get<static_cast<int>(ENEMY_STATE::SIZE)>(state));					// ���ނ̐ݒ�
	_rad = std::move(std::get<static_cast<int>(ENEMY_STATE::RAD)>(state));						// �p�x�̐ݒ�
	_moveCtl.SetMoveState(std::get<static_cast<int>(ENEMY_STATE::AIM)>(state),true);			// �s���̐ݒ�
	_unitID = UNIT_ID::ENEMY;																	// ������ނ̐ݒ�
	Init();
}

bool Enemy::exFlag(bool flag)
{
	// ������SCALE���ᖳ��������ύX���Ȃ�
	if (_moveCtl.aimMove()!=MOVE_TYPE::SCALE)
	{
		return false;
	}
	_exFlag = flag;
	return true;
}

void Enemy::Update(sharedObj plObj)
{
	if (DestroyProc())
	{
		return;
	}
	_moveCtl.Update(plObj);
	// �G���@�ˌ����e����
	if (_moveCtl.shotFlag() && rand() % 100 == 0)
	{
		lpSceneMng.AddActQue({ ACT_QUE::SHOT, *this });
		_moveCtl.shotFlag(false);
	}
	_dbgDrawPixel(_pos.x+lpSceneMng.GameScreenOffset.x, _pos.y + lpSceneMng.GameScreenOffset.y, 0xffffff);
}


Enemy::~Enemy()
{
	if (_moveCtl.aimMove() != MOVE_TYPE::LR)
	{
		// LR�ȊO�Ŏ��񂾂Ƃ�SCALE������Ȃ��悤�ɂ��邽�߂̶��ı���
		_moveCtl.InCount();
	}
}
