#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>


GameScene::GameScene()
{
	lpImageMng.GetID("·¬×", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("’e", "image/shot.png", {8, 3}, { 1, 2});
	lpImageMng.GetID("“G”š”­", "image/en_blast.png", { 64,64 }, { 5, 1 });
	lpImageMng.GetID("PL”š”­", "image/pl_blast.png", { 64,64 }, { 4, 1 });

	TREACE("¹Þ°Ñ¼°Ý‚Ì¶¬");
	obj.resize(1);

	obj[0] = new Player({100,100}, { 0,0 });

	/*obj[0] = new Obj("image/char.png", { 0,0 }, 10, 10, 30, 32);
	obj[1] = new Obj("image/char.png", { 500,100 }, 10, 10, 30, 32);*/
}


GameScene::~GameScene()
{
}

unipueBase GameScene::Update(unipueBase own)
{
	// æ“ª‚ðŽæ‚èo‚µAÅŒã‚Ì—v‘f‚Ü‚Å‰ñ‚µ‚Ä‚­‚ê‚é
	for(auto data :obj)
	{
		data->Draw();
	}
	return std::move(own);
}
