#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"
#include <_DebugDispOut.h>
#include <ImageMng.h>
#include <algorithm>

SceneMng* SceneMng::sInstance = nullptr;

void SceneMng::Draw(void)
{
	_dbgAddDraw();

	std::sort(_drawList.begin(),_drawList.end(),
		[](const DrawQueT& x, const DrawQueT& y) {return static_cast<int>(std::get<static_cast<int>(DRAW_QUE::ZORDER)>(x)) < static_cast<int>(std::get<static_cast<int>(DRAW_QUE::ZORDER)>(y)); });
	SetDrawScreen(DX_SCREEN_BACK);			// 描画先設定
	ClsDrawScreen();

	// ｽﾀｯｸに溜まっているQueを描画する
	//	範囲for文
	for (auto dQue:_drawList)
	{
		DrawRotaGraph(
			static_cast<int>(std::get<static_cast<int>(DRAW_QUE::X)>(dQue)),
			static_cast<int>(std::get<static_cast<int>(DRAW_QUE::Y)>(dQue)),
			1.0,
			std::get<static_cast<int>(DRAW_QUE::RAD)>(dQue),
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue),
			true);
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
		AddDrawQue({IMAGE_ID("BG")[0],400.0,300.0,0.0,32768,LAYER::BG});
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
	lpImageMng.GetID("BG","image/frame.png");
	_dbgSetup(255);

	return false;
}
