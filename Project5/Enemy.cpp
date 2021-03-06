#include "Enemy.h"
#include <ImageMng.h>
#include <SceneMng.h>
#include "_DebugDispOut.h"


bool Enemy::SetAlive(bool alive)
{
	if (!alive)
	{
		// 画面揺らしのQueを投げる
		lpSceneMng.AddActQue({ ACT_QUE::SHAKE,*this });
	}
	return Obj::SetAlive(alive);
}

void Enemy::Init()
{
	// ｴﾈﾐｰｱﾆﾒｰｼｮﾝﾃﾞｰﾀ作成
	AnimVector data;
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[10 + 10 * static_cast<int>(_type)], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[11 + 10 * static_cast<int>(_type)], 60);
	SetAnim(STATE::NORMAL, data);

	data.emplace_back(IMAGE_ID("敵爆発")[0], 10);
	data.emplace_back(IMAGE_ID("敵爆発")[1], 15);
	data.emplace_back(IMAGE_ID("敵爆発")[2], 20);
	data.emplace_back(IMAGE_ID("敵爆発")[3], 25);
	data.emplace_back(IMAGE_ID("敵爆発")[4], 30);
	data.emplace_back(-1, 35);
	SetAnim(STATE::DEATH, data);


	state(STATE::NORMAL);
}


Enemy::Enemy(EnemyState &state)
{
	// 引数でもらった値による初期化
	_type = std::get<static_cast<int>(ENEMY_STATE::TYPE)>(state);								// ﾀｲﾌﾟの設定
	_pos = std::move(std::get<static_cast<int>(ENEMY_STATE::VECTOR)>(state));					// 座標の設定
	_size = std::move(std::get<static_cast<int>(ENEMY_STATE::SIZE)>(state));					// ｻｲｽﾞの設定
	_rad = std::move(std::get<static_cast<int>(ENEMY_STATE::RAD)>(state));						// 角度の設定
	_moveCtl.SetMoveState(std::get<static_cast<int>(ENEMY_STATE::AIM)>(state),true);			// 行動の設定
	_unitID = UNIT_ID::ENEMY;																	// 識別ﾀｸﾞの設定
	Init();
}

bool Enemy::exFlag(bool flag)
{
	// 動きがSCALEじゃ無かったら変更しない
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
	// 敵自機突撃時弾発射
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
		// LR以外で死んだときSCALEがずれないようにするためのｶｳﾝﾄｱｯﾌﾟ
		_moveCtl.InCount();
	}
}
