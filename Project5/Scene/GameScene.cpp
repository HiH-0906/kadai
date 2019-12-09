#include <algorithm>
#include <DxLib.h>
#include <time.h>
#include <_DebugConOut.h>
#include <SceneMng.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>
#include <Bullet.h>
#include <Scene/func/FuncBullet.h>
#include <Scene/func/FuncCheckHit.h>
#include <Scene/func/FuncShake.h>

GameScene::GameScene()
{
	initFunc();

	// ｹﾞｰﾑｼｰﾝ用の画像登録
	srand((unsigned int)time(NULL));
	lpImageMng.GetID("ｷｬﾗ", "image/char.png", { CHAR_SIZE_X,CHAR_SIZE_Y }, { 10, 10 });
	lpImageMng.GetID("弾", "image/shot.png", {8, 3}, { 1, 2});
	lpImageMng.GetID("敵爆発", "image/en_blast.png", { 64,64 }, { 5, 1 });
	lpImageMng.GetID("PL爆発", "image/pl_blast.png", { 64,64 }, { 4, 1 });
	// ｺﾝｿｰﾙへの表示
	TREACE("ｹﾞｰﾑｼｰﾝの生成\n");
	// ﾘｽﾄへの表示登録
	_objList.emplace_back(
		new Player({ lpSceneMng.GameScreenSize.x / 2.0,lpSceneMng.GameScreenSize.y - (CHAR_SIZE_Y / 2.0) }, { static_cast<double>(CHAR_SIZE_X),static_cast<double>(CHAR_SIZE_Y) })
	);
	for (int cnt = 0; cnt < ENEMY_MAX; cnt++)
	{
		_enemyDefFomation = { ENEMY_OFFSET_X + (16.0 + (35.0*(cnt % 10))) ,ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) };
		// 代入するためのﾃﾞｰﾀ作成
		MoveState tmpEnemyState;
		// Wait時間設定
		tmpEnemyState.emplace_back(MOVE_TYPE::WAIT, Vector2Dbl   { 10.0*(cnt % FORMATION) + WAIT_TIME *(cnt / FORMATION),0.0 });																	// WAITの設定　待ち時間のみ
		tmpEnemyState.emplace_back(MOVE_TYPE::SIGMOID, Vector2Dbl{ lpSceneMng.GameScreenSize.x - 96.0 - ((lpSceneMng.GameScreenSize.x - 192.0) * (cnt/ FORMATION % 2)),							// SIGMOIDの設定 目的地の左右 上下
																		lpSceneMng.GameScreenSize.y *(6.0 / 7.0) - (128.0 * ((cnt/ FORMATION % 6) / 4))});
		tmpEnemyState.emplace_back(MOVE_TYPE::SPIRAL, Vector2Dbl { 1.0 - (2 * (cnt/ FORMATION % 2)),static_cast<double>((cnt/ FORMATION / 2) % 3 / 2)});											// SPAIRALの設定 開始地点の左右 上下
		tmpEnemyState.emplace_back(MOVE_TYPE::PITIN, _enemyDefFomation);																															// これ以降敵のﾃﾞﾌｫﾙﾄ位置
		tmpEnemyState.emplace_back(MOVE_TYPE::LR,    _enemyDefFomation);
		tmpEnemyState.emplace_back(MOVE_TYPE::SCALE, _enemyDefFomation);
		tmpEnemyState.emplace_back(MOVE_TYPE::ATACK, _enemyDefFomation);
		tmpEnemyState.emplace_back(MOVE_TYPE::PITIN, _enemyDefFomation);
		EnemyState state = { ENEMY_TYPE::A,																																							// ﾀｲﾌﾟの設定
							{ static_cast<double>((lpSceneMng.GameScreenSize.x*(((cnt / FORMATION) % 6) % 2) - CHAR_SIZE_X / 2) + (CHAR_SIZE_X * (((cnt / FORMATION) % 6) % 2))),					// 座標Xの設定
							static_cast<double>(((lpSceneMng.GameScreenSize.y - CHAR_SIZE_Y*2)/2)*((((cnt / FORMATION) % 6) / 2) % 3) + CHAR_SIZE_Y / 2)},											// 座標Yの設定
							{ CHAR_SIZE_X,CHAR_SIZE_Y },																																			// ｻｲｽﾞの設定																													// ｽﾋﾟｰﾄﾞ
							0.0,																																									// 角度
							tmpEnemyState																																							// 行動管理の設定
							};
		_objList.emplace_back(
			new Enemy(state)
		);
	}
	_shakeCount = 0;
}


GameScene::~GameScene()
{
}

unipueBase GameScene::Update(unipueBase own)
{
	// playerのObj検索
	auto plObj= std::find_if(
		_objList.begin(),
		_objList.end(),
		[](sharedObj obj) {return (*obj).unitID() == UNIT_ID::PLAYER; }
	);
	auto SetAtack=[](sharedObj obj) {
		// 突撃するのは敵だけ
		if ((*obj).unitID() == UNIT_ID::ENEMY)
		{
			if (rand() % 3000 == 0)
			{
				return true;
			}
		}
		return false;
	};
	// 範囲for文
	for (auto data : _objList)
	{
		if (SetAtack(data))
		{
			// 3000/1の突撃命令
			(*data).exFlag(true);
		}
		(*data).Update(*plObj);
	}


	// 先頭を取り出し、最後の要素まで回してくれる
	for (auto data : _objList)
	{		
		(*data).Draw();
	}

	// いらなくなったobjを削除
	_objList.erase(std::remove_if(
							_objList.begin(),															// ﾁｪｯｸ範囲の開始地点
							_objList.end(),																// ﾁｪｯｸ範囲の終了地点
		[](sharedObj& obj) {return (*obj).isDead() && (*obj).unitID() != UNIT_ID::PLAYER; }				// ﾚｯﾂﾗﾑﾀﾞ式 死んでる物があるか確認 Player消すと例外参照してしまうので消さない
						), 
					_objList.end());
	if (_shakeCount)
	{
		_shakeCount--;
		_screenPos = { rand() % 20 - 10,rand() % 20 - 10 };
		if (!_shakeCount)
		{
			// ずれたままにならないように補正
			_screenPos = { 0,0 };
		}
	}

	return std::move(own);
}

void GameScene::RunActQue(std::vector<ActQueT> actList)
{
	// 範囲for文
	for (auto data : actList)
	{
		// ｱｸｼｮﾝ種別によって変更
		try
		{
			funcQue.at(data.first)(data,this);
		}
		catch (...)
		{
			AST();
		}
	}
}

void GameScene::initFunc(void)
{
	funcQue[ACT_QUE::SHOT] = FuncBullet();
	funcQue[ACT_QUE::CHECK_HIT] = FuncCheckHit();
	funcQue[ACT_QUE::SHAKE] = FuncShake();
}
