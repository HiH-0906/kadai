#include <algorithm>
#include <DxLib.h>
#include <time.h>
#include <_DebugConOut.h>
#include <SceneMng.h>
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
	TREACE("�ްѼ�݂̐���\n");
	// ؽĂւ̕\���o�^
	_objList.emplace_back(
		new Player({ lpSceneMng.GameScreenSize.x / 2.0,lpSceneMng.GameScreenSize.y-16.0 }, { 0,0 })
	);
	int tmpFcnt = lpSceneMng.fCnt;
	int formation = 3;
	for (int cnt = 0; cnt < 5*10; cnt++)
	{
			// ������邽�߂��ް��쐬
			MoveState tmpEnemyState;
			// Wait���Ԑݒ�
			tmpEnemyState.emplace_back(MOVE_TYPE::WAIT, Vector2Dbl{ 10.0*(cnt % formation) + 50.0*(cnt / formation),0.0 });
			tmpEnemyState.emplace_back(MOVE_TYPE::SIGMOID, Vector2Dbl{ lpSceneMng.GameScreenSize.x - 96.0 - ((lpSceneMng.GameScreenSize.x - 192.0) * (cnt/ formation % 2)),lpSceneMng.GameScreenSize.y *(6.0 / 7.0) - (128.0 * ((cnt/ formation % 6) / 4))});
			tmpEnemyState.emplace_back(MOVE_TYPE::SPIRAL, Vector2Dbl{ 1.0 - (2 * (cnt/ formation % 2)),static_cast<double>((cnt/ formation / 2) % 3 / 2)});
			tmpEnemyState.emplace_back(MOVE_TYPE::PITIN, Vector2Dbl{ (16.0 + (35.0*(cnt % 10))) , 40.0 + ((40.0)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::LR, Vector2Dbl{ 16.0 + (35.0*(cnt % 10)) ,0.0});
			tmpEnemyState.emplace_back(MOVE_TYPE::SCALE, Vector2Dbl{ lpSceneMng.GameScreenSize.x/2.0,40.0 });
			EnemyState state = { static_cast<ENEMY_TYPE>(rand() % static_cast<int>(ENEMY_TYPE::MAX)),																				// ���߂̐ݒ�
								{ static_cast<double>((lpSceneMng.GameScreenSize.x*(((cnt / formation) % 6) % 2) - 16) + (35 * (((cnt / formation) % 6) % 2))),					// ���WX�̐ݒ�
								static_cast<double>(((lpSceneMng.GameScreenSize.y-30)/2)*((((cnt / formation) % 6) / 2) % 3) - 16)},												// ���WY�̐ݒ�
								{ 30.0,32.0 },																																		// ���ނ̐ݒ�																													// ��߰��
								0.0,																																				// �p�x
								tmpEnemyState																																		// �s���Ǘ��̐ݒ�
								};
			_objList.emplace_back(
				new Enemy(state)
			);
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
