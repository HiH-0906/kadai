#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"
#include <_DebugDispOut.h>
#include <ImageMng.h>
#include <algorithm>

SceneMng* SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 800,600 }, ScreenCenter{ ScreenSize / 2 }, GameScreenSize{ 500,390 }, GameScreenOffset{ (ScreenSize - GameScreenSize) / 2 }	// ｽｸﾘｰﾝの関係の座標初期化
{
	fCnt = 0;
}


SceneMng::~SceneMng()
{
}

void SceneMng::Draw(void)
{
	_dbgAddDraw();
	// _drawListを昇順にｿｰﾄ
	std::sort(_drawList.begin(),_drawList.end(),
		// 比べるから二つ
		[](const DrawQueT& dQueA, const DrawQueT& dQueB)
	{

		// layerとzOdar比較
		return
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA))
			<
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB));

	});

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	LAYER drawLayer  = begin(LAYER());
	int blendMode    = DX_BLENDMODE_NOBLEND;
	int blendModeNum = 255;

	SetDrawScreen(_layerGID);							// 描画用ｽｸﾘｰﾝに変更
	SetDrawBlendMode(blendMode, blendModeNum);		// 描画ﾓｰﾄﾞ変更
	ClsDrawScreen();

	// ｽﾀｯｸに溜まっているQueを描画する
	//	範囲for文
	for (auto dQue:_drawList)
	{
		// tupleの情報をばらした後に保存する変数定義
		double x, y,rad;
		int id;
		LAYER layer;

		// 1つ前の情報保存
		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		// tupleをばらばらに
		std::tie(id, x, y, rad, std::ignore, layer, blendMode, blendModeNum) = dQue;

		// 取り出したQueの内容が前までのLayerか描画形式が違う場合一旦ﾊﾞｯｸﾊﾞｯﾌｧに書き出す
		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNumOld != blendModeNum))
		{
			// _layerGIDの内容をﾊﾞｯｸﾊﾞｯﾌｧに描画する
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0, _layerGID, true);

			// 次のQueのために初期化して一時描画先に変更
			SetDrawScreen(_layerGID);							// 描画用ｽｸﾘｰﾝに変更
			SetDrawBlendMode(blendMode, blendModeNum);		// 描画ﾓｰﾄﾞ変更
			ClsDrawScreen();
		}
		// Queの描画
		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true);
	}
	// for文抜けるときの最後のQue描画
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(blendMode, blendModeNum);		// 描画ﾓｰﾄﾞ変更
	DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _layerGID, true);

	ScreenFlip();
}


void SceneMng::Ran(void)
{
	SysInit();
	// ﾕﾆｰｸﾎﾟｲﾝﾀ作成
	_activeScene = std::make_unique<TitleScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		_drawList.clear();																				// ﾘｽﾄの削除
		AddDrawQue({ IMAGE_ID("枠")[0],400.0,300.0,0.0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });			// 枠QUE登録
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		(*_activeScene).RunActQue(std::move(_actList));													// Action実行
		Draw();																							// 描画
		fCnt++;																							// ﾌﾚｰﾑｶｳﾝﾄ
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

bool SceneMng::AddActQue(ActQueT aQue)
{
	// ｱｸｼｮﾝ系のｷｭｰのﾘｽﾄへの追加
	_actList.emplace_back(aQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ｼｽﾃﾑ処理
	SetWindowText("1916035_橋本 大輝 課題5");

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);					// 800*600ﾄﾞｯﾄ、65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);											// true:Window flse:ﾌﾙｽｸﾘｰﾝ

	if (DxLib_Init() == -1)											// DXﾗｲﾌﾞﾗﾘの初期化設定
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);									// 描写先をﾊﾞｯｸﾊﾞｯﾌｧに設定
	
	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);		// 描画用ｽｸﾘｰﾝ作成

	_dbgSetup(255);

	lpImageMng.GetID("枠", "image/frame.png");
	lpImageMng.GetID("黒", "image/black.png");
	lpImageMng.GetID("白", "image/white.png");

	return false;
}
