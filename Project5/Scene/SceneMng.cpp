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
	// _drawList‚ğ¸‡‚É¿°Ä
	std::sort(_drawList.begin(),_drawList.end(),
		// ”ä‚×‚é‚©‚ç“ñ‚Â
		[](const DrawQueT& dQueA, const DrawQueT& dQueB)
	{
		//// layer‚ªˆá‚¤‚È‚çÚ²Ô°‡‚Å•À‚Ñ‘Ö‚¦
		//if (std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA) != std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB))
		//{
		//	// layer‚Å”ä‚×‚é
		//	return std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA) < std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB);
		//}
		//else
		//{
		//	// _zOrder‚Å”ä‚×‚é
		//	return std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA) < std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB);
		//}

		// ã‚Ì“à—e‚ğ1s‚Å ‚â‚Á‚Ä‚¢‚é‚±‚Æ‚Í‘S‚­“¯‚¶
		return
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueA), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueA))
			<
		std::tie(std::get<static_cast<int>(DRAW_QUE::LAYER)>(dQueB), std::get<static_cast<int>(DRAW_QUE::ZORDER)>(dQueB));

	});
	SetDrawScreen(DX_SCREEN_BACK);			// •`‰ææİ’è
	ClsDrawScreen();

	// ½À¯¸‚É—­‚Ü‚Á‚Ä‚¢‚éQue‚ğ•`‰æ‚·‚é
	//	”ÍˆÍfor•¶
	for (auto dQue:_drawList)
	{
		// tuple‚Ìî•ñ‚ğ‚Î‚ç‚µ‚½Œã‚É•Û‘¶‚·‚é•Ï”’è‹`
		double x, y,rad;
		int id;
		LAYER layer;

		// tuple‚ğ‚Î‚ç‚Î‚ç‚É
		std::tie(id, x, y, rad, std::ignore, layer) = dQue;

		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true);
	}
	//// iteratorfor•¶
	//for (auto dQue = _drawList.begin(); dQue != _drawList.end; dQue++)
	//{
	//	DrawGraph(
	//		std::get<static_cast<int>(DRAW_QUE::X)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::Y)>(*dQue),
	//		std::get<static_cast<int>(DRAW_QUE::IMAGE)>(*dQue),
	//		true);
	//}
	//// ¡‚Ü‚Å‚Ìfor•¶
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
	// ÕÆ°¸Îß²İÀì¬
	_activeScene = std::make_unique<GameScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		_drawList.clear();			// Ø½Ä‚Ìíœ
		AddDrawQue({IMAGE_ID("˜g")[0],400.0,300.0,0.0,0,LAYER::UI});
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		Draw();						// •`‰æ
	}
}

bool SceneMng::AddDrawQue(DrawQueT dQue)
{
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) <= 0)
	{
		// ‰æ‘œID‚ª•s³‚È‚Ì‚ÅA’Ç‰Á‚µ‚È‚¢
		return false;
	}
	// Que‚ğ’Ç‰Á
	_drawList.emplace_back(dQue);

	return true;
}

bool SceneMng::SysInit(void)
{
	// ¼½ÃÑˆ—
	SetWindowText("1916035_‹´–{ ‘å‹P ‰Û‘è5");

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);	// 800*600ÄŞ¯ÄA65536FÓ°ÄŞ‚Éİ’è
	ChangeWindowMode(true);							// true:Window flse:ÌÙ½¸Ø°İ

	if (DxLib_Init() == -1)							// DX×²ÌŞ×Ø‚Ì‰Šú‰»İ’è
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);					// •`Êæ‚ğÊŞ¯¸ÊŞ¯Ì§‚Éİ’è
	
	for (auto id : LAYER())
	{
		if(_screenID[])
	}

	_dbgSetup(255);

	lpImageMng.GetID("˜g","image/frame.png");

	return false;
}
