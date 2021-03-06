#include <DxLib.h>
#include <ImageMng.h>
#include <SceneMng.h>
#include "BaseScene.h"


BaseScene::BaseScene()
{
	_fadeScrID = MakeScreen(lpSceneMng.ScreenSize.x, lpSceneMng.ScreenSize.y, false);
	FadeInit("白");
}


BaseScene::~BaseScene()
{
}

void BaseScene::RunActQue(std::vector<ActQueT> actList)
{
	// 消す
	actList.clear();
}

void BaseScene::FadeInit(std::string fadeType)
{
	GetDrawScreenGraph(
		0,
		0,
		lpSceneMng.ScreenSize.x,
		lpSceneMng.ScreenSize.y,
		_fadeScrID
	);
	_fadeCount = 510;					// ｲﾝｱｳﾄやるので510 片方255
	_fadeType = fadeType;
}

bool BaseScene::FadeUpDate(void)
{
	if (_fadeCount)
	{
		if (_fadeCount > 255)
		{
			// ｷｬﾌﾟﾁｬ画面描画
			lpSceneMng.AddDrawQue({ _fadeScrID,lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y,0,0,LAYER::EX,DX_BLENDMODE_NOBLEND,255 });
		}
		// 板描画
		lpSceneMng.AddDrawQue({ lpImageMng.GetID(_fadeType)[0],lpSceneMng.ScreenCenter.x,lpSceneMng.ScreenCenter.y ,0,10,LAYER::EX,DX_BLENDMODE_ALPHA,255 - std::abs(_fadeCount - 255) });

		_fadeCount--;
	}

	return _fadeCount;
}
