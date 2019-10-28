#include "TitleScene.h"
#include "GameScene.h"
#include <DxLib.h>


TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

unipueBase TitleScene::Update(unipueBase own)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		return std::make_unique<GameScene>();			// º∞›êÿÇËë÷Ç¶
	}
	return std::move(own);
}
