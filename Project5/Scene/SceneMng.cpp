#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"

SceneMng* SceneMng::sInstance = nullptr;

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);			// •`‰ææİ’è
	ClsDrawScreen();

	// ½À¯¸‚É—­‚Ü‚Á‚Ä‚¢‚éQue‚ğ•`‰æ‚·‚é
	//	”ÍˆÍfor•¶
	for (auto dQue:_drawList)
	{
		DrawGraph(
			std::get<static_cast<int>(DRAW_QUE::X)>(dQue),
			std::get<static_cast<int>(DRAW_QUE::Y)>(dQue),
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue),
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
	_activeScene = std::make_unique<GameScene>();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_drawList.clear();			// Ø½Ä‚Ìíœ
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

	return false;
}
