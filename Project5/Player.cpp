#include <DxLib.h>
#include <ImageMng.h>
#include "Player.h"
#include <KeyState.h>
#include <SceneMng.h>
#include "_DebugDispOut.h"


void Player::Init(void)
{
	// ﾌﾟﾚｲﾔｰｱﾆﾒｰｼｮﾝｾｯﾄ
	AnimVector data;
	data.reserve(5);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[0], 30);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(IMAGE_ID("ｷｬﾗ")[2], 0);
	SetAnim(STATE::EX, data);
	data.emplace_back(IMAGE_ID("PL爆発")[0], 10);
	data.emplace_back(IMAGE_ID("PL爆発")[1], 15);
	data.emplace_back(IMAGE_ID("PL爆発")[2], 20);
	data.emplace_back(IMAGE_ID("PL爆発")[3], 25);
	data.emplace_back(-1, 40);							// ﾜﾝｼｮｯﾄﾉｱﾆﾒｰｼｮﾝにしたいので-1
	SetAnim(STATE::DEATH, data);

	// ﾕﾆｰｸﾎﾟｲﾝﾀ 中身は後 c++14以降
	_input = std::make_shared<KeyState>();

	state(STATE::NORMAL);
}


Player::Player(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_unitID = UNIT_ID::PLAYER;

	_glowID = MakeScreen(static_cast<int>(_size.x*2.0), static_cast<int>(_size.y*2.0), false);

	Init();
}

void Player::Update(sharedObj plObj)
{
	// 状態ﾁｪｯｸ
	if (DestroyProc())
	{
		// 死んでるならreturn
		return;
	}

	// ｷｰ関係ｱｯﾌﾟﾃﾞｰﾄ呼び出し
	(*_input).Update();

	// ﾗﾑﾀﾞ式で移動制御　引数で方向管理することによって処理を1つしか書かなくてよい
						// weak_ptrは見ることしかできない 合法的な参照 shared等が存在してるか確認できる
	auto move = [](std::weak_ptr<InputState> keyData, INPUT_ID id, double& pNum, const int speed) {
		// 監視対象が生きているか確認 0以外で死んでる
		if (!keyData.expired())
		{
			// 監視対象取得
			if ((*keyData.lock()).state(id).first)
			{
				pNum += speed;
			}
		}
	};
	// 移動制限
	if (_pos.x - (_size.x / 2.0) > 0)
	{
		// 左
		move(_input, INPUT_ID::LEFT, _pos.x, -2);
	}
	if (_pos.x + (_size.x / 2.0) < lpSceneMng.GameScreenSize.x)
	{
		// 右
		move(_input, INPUT_ID::RIGHT, _pos.x, +2);
	}
	move(_input, INPUT_ID::UP, _pos.y, -2);
	move(_input, INPUT_ID::DOWN, _pos.y, +2);

	// shotの発射
	if ((*_input).state(INPUT_ID::BTN_1).first&&!(*_input).state(INPUT_ID::BTN_1).second)
	{
		lpSceneMng.AddActQue({ ACT_QUE::SHOT,*this });
	}
	return;
}


Player::~Player()
{
}

void Player::Draw(void)
{
	Obj::Draw();

	SetDrawScreen(_glowID);
	ClsDrawScreen();
	SetDrawBright(255, 0, 0);
	DrawRotaGraph(static_cast<int>(_size.x), static_cast<int>(_size.y), 1.0, 0, _animMap[_state][_animFrame].first, true);
	SetDrawBright(255, 255, 255);
	GraphFilter(_glowID, DX_GRAPH_FILTER_GAUSS, 8, 100);
	GraphFilter(_glowID, DX_GRAPH_FILTER_TWO_COLOR, 10,0,255,0x00ff00,255);
	lpSceneMng.AddDrawQue({ _glowID, lpSceneMng.GameScreenOffset.x + _pos.x, lpSceneMng.GameScreenOffset.y + _pos.y, _rad, _zOrder - 1, LAYER::CHAR, DX_BLENDMODE_ADD, 255 });
}
