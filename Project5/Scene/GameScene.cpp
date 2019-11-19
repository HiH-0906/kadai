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
		new Player({ lpSceneMng.GameScreenSize.x / 2.0,lpSceneMng.GameScreenSize.y-16.0 }, { 0,0 })
	);
	int tmpFcnt = lpSceneMng.fCnt;
	int formation = 3;
	for (int cnt = 0; cnt < 5*10; cnt++)
	{
			// 代入するためのﾃﾞｰﾀ作成
			MoveState tmpEnemyState;
			// Wait時間設定
			tmpEnemyState.emplace_back(MOVE_TYPE::WAIT, Vector2Dbl{ 10.0*(cnt % formation) + 50.0*(cnt / formation),0.0 });
			tmpEnemyState.emplace_back(MOVE_TYPE::SIGMOID, Vector2Dbl{ lpSceneMng.GameScreenSize.x - 96.0 - ((lpSceneMng.GameScreenSize.x - 192.0) * (cnt/ formation % 2)),lpSceneMng.GameScreenSize.y *(6.0 / 7.0) - (128.0 * ((cnt/ formation % 6) / 4))});
			tmpEnemyState.emplace_back(MOVE_TYPE::SPIRAL, Vector2Dbl{ 1.0 - (2 * (cnt/ formation % 2)),static_cast<double>((cnt/ formation / 2) % 3 / 2)});
			tmpEnemyState.emplace_back(MOVE_TYPE::PITIN, Vector2Dbl{ (16.0 + (35.0*(cnt % 10))) , 40.0 + ((40.0)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::LR, Vector2Dbl{ 16.0 + (35.0*(cnt % 10)) ,0.0});
			tmpEnemyState.emplace_back(MOVE_TYPE::SCALE, Vector2Dbl{ lpSceneMng.GameScreenSize.x/2.0,40.0 });
			EnemyState state = { static_cast<ENEMY_TYPE>(rand() % static_cast<int>(ENEMY_TYPE::MAX)),																				// ﾀｲﾌﾟの設定
								{ static_cast<double>((lpSceneMng.GameScreenSize.x*(((cnt / formation) % 6) % 2) - 16) + (35 * (((cnt / formation) % 6) % 2))),					// 座標Xの設定
								static_cast<double>(((lpSceneMng.GameScreenSize.y-30)/2)*((((cnt / formation) % 6) / 2) % 3) - 16)},												// 座標Yの設定
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
