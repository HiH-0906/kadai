#include <algorithm>
#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>


GameScene::GameScene()
{
	lpImageMng.GetID("ｷｬﾗ", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("弾", "image/shot.png", {8, 3}, { 1, 2});
	lpImageMng.GetID("敵爆発", "image/en_blast.png", { 64,64 }, { 5, 1 });
	lpImageMng.GetID("PL爆発", "image/pl_blast.png", { 64,64 }, { 4, 1 });

	TREACE("ｹﾞｰﾑｼｰﾝの生成");
	_objList.emplace_back(
		new Player({ 100,100 }, { 0,0 })
	);
	_objList.emplace_back(
		new Player({ 250,250 }, { 0,0 })
	);
}


GameScene::~GameScene()
{
}

unipueBase GameScene::Update(unipueBase own)
{
	// 先頭を取り出し、最後の要素まで回してくれる
	for (auto data : _objList)
	{
		// ｽﾏｰﾄﾎﾟｲﾝﾀへのアクセス方法はどちらどもよい
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}
		data->Draw();
	}

	std::remove_if(
		_objList.begin(),									// ﾁｪｯｸ範囲の開始地点
		_objList.end(),										// ﾁｪｯｸ範囲の終了地点
		[](sharedObj&obj) {return (*obj).isDead(); }		// ﾚｯﾂﾗﾑﾀﾞ式
		);

	return std::move(own);
}
