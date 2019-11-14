#include <algorithm>
#include <DxLib.h>
#include <time.h>
#include <_DebugConOut.h>
#include <SceneMng.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>


GameScene::GameScene()
{
	// ｹﾞｰﾑｼｰﾝ用の画像登録
	srand((unsigned int)time(NULL));
	lpImageMng.GetID("ｷｬﾗ", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("弾", "image/shot.png", {8, 3}, { 1, 2});
	lpImageMng.GetID("敵爆発", "image/en_blast.png", { 64,64 }, { 5, 1 });
	lpImageMng.GetID("PL爆発", "image/pl_blast.png", { 64,64 }, { 4, 1 });
	// ｺﾝｿｰﾙへの表示
	TREACE("ｹﾞｰﾑｼｰﾝの生成\n");
	// ﾘｽﾄへの表示登録
	_objList.emplace_back(
		new Player({ 100,400 }, { 0,0 })
	);
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			int cnt = (y * 10 + x);
			// 代入するためのﾃﾞｰﾀ作成
			MoveState tmpEnemyState;
			// Wait時間設定
			tmpEnemyState.emplace_back(MOVE_TYPE::WAIT, Vector2Dbl{ 30.0*cnt,0.0 });
			tmpEnemyState.emplace_back(MOVE_TYPE::SIGMOID, Vector2Dbl{ lpSceneMng.ScreenSize.x - 128.0 - (544.0 * (cnt % 2)),lpSceneMng.ScreenSize.y *(5.0 / 7.0) - (192.0 * ((cnt % 6) / 4)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::SPIRAL, Vector2Dbl{ 1.0 - (2 * (cnt % 2)),static_cast<double>((cnt / 2) % 3 / 2)});
			tmpEnemyState.emplace_back(MOVE_TYPE::PITIN, Vector2Dbl{ (35.0 * 7) + (35.0*x), 40.0 + ((40.0)*y) });
			tmpEnemyState.emplace_back(MOVE_TYPE::LR, Vector2Dbl{ 180.0,0.0 });
			cnt=cnt % 6;
			EnemyState state = { static_cast<ENEMY_TYPE>(rand() % static_cast<int>(ENEMY_TYPE::MAX)),													// ﾀｲﾌﾟの設定
								{ static_cast<double>((lpSceneMng.ScreenSize.x*(cnt % 2) - 16) + (32 * (cnt % 2))),										// 座標Xの設定
								static_cast<double>(((lpSceneMng.ScreenSize.y-30)/2)*((cnt / 2) % 3) - 16)},											// 座標Yの設定
								{ 30.0,32.0 },																											// ｻｲｽﾞの設定
								std::atan2(40.0 + ((40.0)*y - (((lpSceneMng.ScreenSize.y - 30) / 2)*((cnt / 2) % 3) - 16)),(35.0 * 7) +					// 角度
								(35.0*x) - (lpSceneMng.ScreenSize.x*(cnt % 2) - 15) + (32 * (cnt % 2))) + (3.14159 / 2),
								tmpEnemyState																											// 行動管理の設定
								};
			_objList.emplace_back(
				new Enemy(state)
			);
		}
	}
}


GameScene::~GameScene()
{
}

unipueBase GameScene::Update(unipueBase own)
{
	// 範囲for文
	for (auto data : _objList)
	{
		(*data).Update();
	}


	// 先頭を取り出し、最後の要素まで回してくれる
	for (auto data : _objList)
	{		
		// ｽﾏｰﾄﾎﾟｲﾝﾀへのｱｸｾｽ方法はｱﾛｰ又はｱｽﾀﾘｽｸどちらでもよい
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}
		data->Draw();
	}

	//auto prg = [](sharedObj&obj) {return (*obj).isDead(); };		// 何回も呼び出す場合は代入するといい感じ
	//prg(*_objList.begin());

	// いらなくなったobjを削除
	_objList.erase(std::remove_if(
							_objList.begin(),											// ﾁｪｯｸ範囲の開始地点
							_objList.end(),												// ﾁｪｯｸ範囲の終了地点
							[](sharedObj& obj) {return (*obj).isDead(); }				// ﾚｯﾂﾗﾑﾀﾞ式 死んでる物があるか確認
						), 
					_objList.end());
	return std::move(own);
}
