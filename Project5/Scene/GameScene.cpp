#include <algorithm>
#include <DxLib.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>


GameScene::GameScene()
{
	lpImageMng.GetID("���", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("�e", "image/shot.png", {8, 3}, { 1, 2});
	lpImageMng.GetID("�G����", "image/en_blast.png", { 64,64 }, { 5, 1 });
	lpImageMng.GetID("PL����", "image/pl_blast.png", { 64,64 }, { 4, 1 });

	TREACE("�ްѼ�݂̐���");
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
	// �擪�����o���A�Ō�̗v�f�܂ŉ񂵂Ă����
	for (auto data : _objList)
	{
		// �ϰ��߲���ւ̃A�N�Z�X���@�͂ǂ���ǂ��悢
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}
		data->Draw();
	}

	std::remove_if(
		_objList.begin(),									// �����͈͂̊J�n�n�_
		_objList.end(),										// �����͈͂̏I���n�_
		[](sharedObj&obj) {return (*obj).isDead(); }		// گ����ގ�
		);

	return std::move(own);
}
