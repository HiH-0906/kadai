#include <algorithm>
#include <DxLib.h>
#include <time.h>
#include <_DebugConOut.h>
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
		for (int x = 0; x < 5; x++)
		{
			// 代入するためのﾃﾞｰﾀ作成
			MoveState tmpEnemyState;
			tmpEnemyState.emplace_back(MOVE_TYPE::WAIT, Vector2Dbl{180.0,0.0});
			tmpEnemyState.emplace_back(MOVE_TYPE::LR, Vector2Dbl{ 180.0,0.0 });

			EnemyState state = { static_cast<ENEMY_TYPE>(rand() % static_cast<int>(ENEMY_TYPE::MAX)),							// ﾀｲﾌﾟの設定
								{ static_cast <double>(50 + x * 50) , static_cast <double>((100 + y * 50)) },					// 座標の設定
								{ 0,0 },																							// ｻｲｽﾞの設定
								tmpEnemyState
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
