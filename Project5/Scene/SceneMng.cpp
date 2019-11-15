#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"
#include <_DebugDispOut.h>
#include <ImageMng.h>
#include <algorithm>

SceneMng* SceneMng::sInstance = nullptr;

LAYER begin(LAYER)
{
	return LAYER::BG;
}

LAYER end(LAYER)
{
	return LAYER::MAX;
}
LAYER operator*(LAYER key)
{
	return key;
}

LAYER operator++(LAYER & key)
{
	// 基底の型を見て云々
	return key = static_cast<LAYER>(std::underlying_type<LAYER>::type(key) + 1);
}

void SceneMng::Draw(void)
{
	_dbgAddDraw();
	// _drawListを昇順にｿｰﾄ
	std::sort(_drawList.begin(),_drawList.end(),
		// 比べるから二つ
		[](const DrawQueT& dQueA, const DrawQueT& dQueB)
	{
		//// layerが違うならﾚｲﾔｰ順で並び替え
		//if (std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA) != std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB))
		//{
		//	// layerで比べる
		//	return std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA) < std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB);
		//}
		//else
		//{
		//	// _zOrderで比べる
		//	return std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA) < std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB);
		//}

		// 上の内容を1行で やっていることは全く同じ
		return
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA))
			<
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB));

	});
	SetDrawScreen(DX_SCREEN_BACK);			// 描画先設定
	ClsDrawScreen();

	// ｽﾀｯｸに溜まっているQueを描画する
	//	範囲for文
	for (auto dQue:_drawList)
	{
		// tupleの情報をばらした後に保存する変数定義
		double x, y,rad;
		int id;
		LAYER layer;

		// tupleをばらばらに
		std::tie(id, x, y, rad, std::ignore, layer) = dQue;
		// 現在の描画ｽｸﾘｰﾝと違えば変更
		if (_screenID[layer]!=GetDrawScreen())
		{
			SetDrawScreen(_screenID[layer]);
			ClsDrawScreen();
		}
		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true);
	}
	SetDrawScreen(DX_SCREEN_BACK);
	// 各ﾚｲﾔｰを描画
	for (auto layer : LAYER())
	{
		DrawRotaGraph(lpSceneMng.ScreenSize.x / 2, lpSceneMng.ScreenSize.y / 2, 1.0, 0, _screenID[layer], true);
	}
	//// iteratorfor文
	//for (auto dQue = _drawList.begin(); dQue != _drawList.end; dQue++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(*dQue),
	//		true);
	//}
	//// 今までのfor文
	//for (int i = 0; i < _drawList.size(); i++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(_drawList[i]),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(_drawList[i]),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_drawList[i]),
	//		true);
	//}

	ScreenFlip();
}
SceneMng::SceneMng():ScreenSize{800,600}
{
}


SceneMng::~SceneMng()
{
}

void SceneMng::Ran(void)
{
	SysInit();
	// ﾕﾆｰｸﾎﾟｲﾝﾀ作成
	_activeScene = std::make_unique<GameScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		_drawList.clear();			// ﾘｽﾄの削除
		AddDrawQue({IMAGE_ID("枠")[0],400.0,300.0,0.0,0,LAYER::UI});
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		Draw();						// 描画
	}
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		// 画像IDが不正なので、追加しない
		return false;
	}
	// Queを追加
	_drawList.emplace_back(dQue);

	return true;
}

bool SceneMng::SysInit(void)
{
	// ｼｽﾃﾑ処理
	SetWindowText("1916035_橋本 大輝 課題5");

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);	// 800*600ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);							// true:Window flse:ﾌﾙｽｸﾘｰﾝ

	if (DxLib_Init() == -1)							// DXﾗｲﾌﾞﾗﾘの初期化設定
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);					// 描写先をﾊﾞｯｸﾊﾞｯﾌｧに設定
	
	for (auto id : LAYER())
	{
		if (_screenID.find(id) == _screenID.end())
		{
			_screenID[id] = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, true);
		}
	}

	_dbgSetup(255);

	lpImageMng.GetID("枠","image/frame.png");

	return false;
}
