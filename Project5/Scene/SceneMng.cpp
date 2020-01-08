#include <DxLib.h>
#include "SceneMng.h"
#include "TitleScene.h"
#include "GameScene.h"
#include <_DebugDispOut.h>
#include <ImageMng.h>
#include <algorithm>

SceneMng* SceneMng::sInstance = nullptr;

SceneMng::SceneMng() :ScreenSize{ 800,600 }, ScreenCenter{ ScreenSize / 2 }, GameScreenSize{ 500,390 }, GameScreenOffset{ (ScreenSize - GameScreenSize) / 2 }	// ½¸Ø°İ‚ÌŠÖŒW‚ÌÀ•W‰Šú‰»
{
	fCnt = 0;
}


SceneMng::~SceneMng()
{
}

void SceneMng::Draw(void)
{
	_dbgAddDraw();
	// _drawList‚ğ¸‡‚É¿°Ä
	std::sort(_drawList.begin(),_drawList.end(),
		// ”ä‚×‚é‚©‚ç“ñ‚Â
		[](const DrawQueT& dQueA, const DrawQueT& dQueB)
	{

		// layer‚ÆzOdar”äŠr
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

	SetDrawScreen(_layerGID);							// •`‰æ—p½¸Ø°İ‚É•ÏX
	SetDrawBlendMode(blendMode, blendModeNum);		// •`‰æÓ°ÄŞ•ÏX
	ClsDrawScreen();

	// ½À¯¸‚É—­‚Ü‚Á‚Ä‚¢‚éQue‚ğ•`‰æ‚·‚é
	//	”ÍˆÍfor•¶
	for (auto dQue:_drawList)
	{
		// tuple‚Ìî•ñ‚ğ‚Î‚ç‚µ‚½Œã‚É•Û‘¶‚·‚é•Ï”’è‹`
		double x, y,rad;
		int id;
		LAYER layer;

		// 1‚Â‘O‚Ìî•ñ•Û‘¶
		int blendModeOld = blendMode;
		int blendModeNumOld = blendModeNum;

		// tuple‚ğ‚Î‚ç‚Î‚ç‚É
		std::tie(id, x, y, rad, std::ignore, layer, blendMode, blendModeNum) = dQue;

		// æ‚èo‚µ‚½Que‚Ì“à—e‚ª‘O‚Ü‚Å‚ÌLayer‚©•`‰æŒ`®‚ªˆá‚¤ê‡ˆê’UÊŞ¯¸ÊŞ¯Ì§‚É‘‚«o‚·
		if ((layer != drawLayer) || (blendModeOld != blendMode) || (blendModeNumOld != blendModeNum))
		{
			// _layerGID‚Ì“à—e‚ğÊŞ¯¸ÊŞ¯Ì§‚É•`‰æ‚·‚é
			SetDrawScreen(DX_SCREEN_BACK);
			SetDrawBlendMode(blendModeOld, blendModeNumOld);
			auto layPos = ScreenCenter + (*_activeScene)._screenPos;
			DrawRotaGraph(layPos.x, layPos.y, 1.0, 0, _layerGID, true);

			// Ÿ‚ÌQue‚Ì‚½‚ß‚É‰Šú‰»‚µ‚Äˆê•`‰ææ‚É•ÏX
			SetDrawScreen(_layerGID);							// •`‰æ—p½¸Ø°İ‚É•ÏX
			SetDrawBlendMode(blendMode, blendModeNum);		// •`‰æÓ°ÄŞ•ÏX
			ClsDrawScreen();
		}
		// Que‚Ì•`‰æ
		DrawRotaGraph(
			static_cast<int>(x),
			static_cast<int>(y),
			1.0,
			rad,
			id,
			true);
	}
	// for•¶”²‚¯‚é‚Æ‚«‚ÌÅŒã‚ÌQue•`‰æ
	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(blendMode, blendModeNum);		// •`‰æÓ°ÄŞ•ÏX
	DrawRotaGraph(ScreenCenter.x, ScreenCenter.y, 1.0, 0, _layerGID, true);

	ScreenFlip();
}


void SceneMng::Ran(void)
{
	SysInit();
	// ÕÆ°¸Îß²İÀì¬
	_activeScene = std::make_unique<TitleScene>();

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		_dbgStartDraw();
		_drawList.clear();																				// Ø½Ä‚Ìíœ
		AddDrawQue({ IMAGE_ID("˜g")[0],400.0,300.0,0.0,0,LAYER::UI,DX_BLENDMODE_NOBLEND,255 });			// ˜gQUE“o˜^
		_activeScene = (*_activeScene).Update(std::move(_activeScene));
		(*_activeScene).RunActQue(std::move(_actList));													// ActionÀs
		Draw();																							// •`‰æ
		fCnt++;																							// ÌÚ°Ñ¶³İÄ
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

bool SceneMng::AddActQue(ActQueT aQue)
{
	// ±¸¼®İŒn‚Ì·­°‚ÌØ½Ä‚Ö‚Ì’Ç‰Á
	_actList.emplace_back(aQue);
	return true;
}

bool SceneMng::SysInit(void)
{
	// ¼½ÃÑˆ—
	SetWindowText("1916035_‹´–{ ‘å‹P ‰Û‘è5");

	SetGraphMode(ScreenSize.x, ScreenSize.y, 16);					// 800*600ÄŞ¯ÄA65536FÓ°ÄŞ‚Éİ’è
	ChangeWindowMode(true);											// true:Window flse:ÌÙ½¸Ø°İ

	if (DxLib_Init() == -1)											// DX×²ÌŞ×Ø‚Ì‰Šú‰»İ’è
	{
		return false;
	}
	SetDrawScreen(DX_SCREEN_BACK);									// •`Êæ‚ğÊŞ¯¸ÊŞ¯Ì§‚Éİ’è
	
	_layerGID = MakeScreen(ScreenSize.x, ScreenSize.y, true);		// •`‰æ—p½¸Ø°İì¬

	_dbgSetup(255);

	lpImageMng.GetID("˜g", "image/frame.png");
	lpImageMng.GetID("•", "image/black.png");
	lpImageMng.GetID("”’", "image/white.png");

	return false;
}
