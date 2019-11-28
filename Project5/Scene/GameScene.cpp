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
		new Player({ lpSceneMng.GameScreenSize.x / 2.0,lpSceneMng.GameScreenSize.y-16.0 }, { 0,0 })
	);
	for (int cnt = 0; cnt < ENEMY_MAX; cnt++)
	{
			// 代入するためのﾃﾞｰﾀ作成
			MoveState tmpEnemyState;
			// Wait時間設定
			tmpEnemyState.emplace_back(MOVE_TYPE::WAIT, Vector2Dbl{ 10.0*(cnt % FORMATION) + WAIT_TIME *(cnt / FORMATION),0.0 });
			tmpEnemyState.emplace_back(MOVE_TYPE::SIGMOID, Vector2Dbl{ lpSceneMng.GameScreenSize.x - 96.0 - ((lpSceneMng.GameScreenSize.x - 192.0) * (cnt/ FORMATION % 2)),lpSceneMng.GameScreenSize.y *(6.0 / 7.0) - (128.0 * ((cnt/ FORMATION % 6) / 4))});
			tmpEnemyState.emplace_back(MOVE_TYPE::SPIRAL, Vector2Dbl{ 1.0 - (2 * (cnt/ FORMATION % 2)),static_cast<double>((cnt/ FORMATION / 2) % 3 / 2)});
			tmpEnemyState.emplace_back(MOVE_TYPE::PITIN, Vector2Dbl{ ENEMY_OFFSET_X + (16.0 + (35.0*(cnt % 10))) , ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::LR, Vector2Dbl{ ENEMY_OFFSET_X + (16.0 + (35.0*(cnt % 10))) ,ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::SCALE, Vector2Dbl{ ENEMY_OFFSET_X + (16.0 + (35.0*(cnt % 10))) ,ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::ATACK, Vector2Dbl{ ENEMY_OFFSET_X + (16.0 + (35.0*(cnt % 10))) , ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::PITIN, Vector2Dbl{ ENEMY_OFFSET_X +(16.0 + (35.0*(cnt % 10))) , ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			EnemyState state = { ENEMY_TYPE::A,																				// ﾀｲﾌﾟの設定
								{ static_cast<double>((lpSceneMng.GameScreenSize.x*(((cnt / FORMATION) % 6) % 2) - 16) + (35 * (((cnt / FORMATION) % 6) % 2))),						// 座標Xの設定
								static_cast<double>(((lpSceneMng.GameScreenSize.y-30)/2)*((((cnt / FORMATION) % 6) / 2) % 3) - 16)},												// 座標Yの設定
								{ 30.0,32.0 },																																		// ｻｲｽﾞの設定																													// ｽﾋﾟｰﾄﾞ
								0.0,																																				// 角度
								tmpEnemyState																																		// 行動管理の設定
								};
			_objList.emplace_back(
				new Enemy(state)
			);
	}
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
							_objList.begin(),											// ﾁｪｯｸ範囲の開始地点
							_objList.end(),												// ﾁｪｯｸ範囲の終了地点
							[](sharedObj& obj) {return (*obj).isDead(); }				// ﾚｯﾂﾗﾑﾀﾞ式 死んでる物があるか確認
						), 
					_objList.end());
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
			funcQue.at(data.first)(data,_objList);
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
}
