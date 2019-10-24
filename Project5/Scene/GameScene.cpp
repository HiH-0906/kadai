#include <algorithm>
#include <DxLib.h>
#include <time.h>
#include <_DebugConOut.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>


GameScene::GameScene()
{
	// �ްѼ�ݗp�̉摜�o�^
	srand((unsigned int)time(NULL));
	lpImageMng.GetID("���", "image/char.png", { 30,32 }, { 10, 10 });
	lpImageMng.GetID("�e", "image/shot.png", {8, 3}, { 1, 2});
	lpImageMng.GetID("�G����", "image/en_blast.png", { 64,64 }, { 5, 1 });
	lpImageMng.GetID("PL����", "image/pl_blast.png", { 64,64 }, { 4, 1 });
	// �ݿ�قւ̕\��
	TREACE("�ްѼ�݂̐���");
	// ؽĂւ̕\���o�^
	_objList.emplace_back(
		new Player({ 100,400 }, { 0,0 })
	);
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			EnemyState state = { static_cast<ENEMY_TYPE>(rand() % static_cast<int>(ENEMY_TYPE::MAX)),{ 50 + x * 50 ,100 + y * 50 },{ 0,0 } };
			_objList.emplace_back(
				new Enemy(state)
			);
		}
	}
}


GameScene::~GameScene()
{
}

unipueBase GameScene::Update(unipueBase own)
{
	// �͈�for��
	for (auto data : _objList)
	{
		(*data).Update();
	}


	// �擪�����o���A�Ō�̗v�f�܂ŉ񂵂Ă����
	for (auto data : _objList)
	{		
		// �ϰ��߲���ւ̱������@�ͱ۰���ͱ��ؽ��ǂ���ł��悢
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			(*data).SetAlive(false);
		}
		data->Draw();
	}

	//auto prg = [](sharedObj&obj) {return (*obj).isDead(); };		// ������Ăяo���ꍇ�͑������Ƃ�������
	//prg(*_objList.begin());

	// ����Ȃ��Ȃ���obj���폜
	_objList.erase(std::remove_if(
							_objList.begin(),											// �����͈͂̊J�n�n�_
							_objList.end(),												// �����͈͂̏I���n�_
							[](sharedObj& obj) {return (*obj).isDead(); }				// گ����ގ� ����ł镨�����邩�m�F
						), 
					_objList.end());
	return std::move(own);
}
