#include <algorithm>
#include <DxLib.h>
#include <time.h>
#include <_DebugConOut.h>
#include <SceneMng.h>
#include "GameScene.h"
#include <ImageMng.h>
#include <Player.h>
#include <Enemy.h>
#include <Bullet.h>
#include <Scene/func/FuncBullet.h>
#include <Scene/func/FuncCheckHit.h>

GameScene::GameScene()
{
	initFunc();

	// �ްѼ�ݗp�̉摜�o�^
	srand((unsigned int)time(NULL));
	lpImageMng.GetID("���", "image/char.png", { CHAR_SIZE_X,CHAR_SIZE_Y }, { 10, 10 });
	lpImageMng.GetID("�e", "image/shot.png", {8, 3}, { 1, 2});
	lpImageMng.GetID("�G����", "image/en_blast.png", { 64,64 }, { 5, 1 });
	lpImageMng.GetID("PL����", "image/pl_blast.png", { 64,64 }, { 4, 1 });
	// �ݿ�قւ̕\��
	TREACE("�ްѼ�݂̐���\n");
	// ؽĂւ̕\���o�^
	_objList.emplace_back(
		new Player({ lpSceneMng.GameScreenSize.x / 2.0,lpSceneMng.GameScreenSize.y-16.0 }, { 0,0 })
	);
	for (int cnt = 0; cnt < ENEMY_MAX; cnt++)
	{
			// ������邽�߂��ް��쐬
			MoveState tmpEnemyState;
			// Wait���Ԑݒ�
			tmpEnemyState.emplace_back(MOVE_TYPE::WAIT, Vector2Dbl{ 10.0*(cnt % FORMATION) + WAIT_TIME *(cnt / FORMATION),0.0 });
			tmpEnemyState.emplace_back(MOVE_TYPE::SIGMOID, Vector2Dbl{ lpSceneMng.GameScreenSize.x - 96.0 - ((lpSceneMng.GameScreenSize.x - 192.0) * (cnt/ FORMATION % 2)),lpSceneMng.GameScreenSize.y *(6.0 / 7.0) - (128.0 * ((cnt/ FORMATION % 6) / 4))});
			tmpEnemyState.emplace_back(MOVE_TYPE::SPIRAL, Vector2Dbl{ 1.0 - (2 * (cnt/ FORMATION % 2)),static_cast<double>((cnt/ FORMATION / 2) % 3 / 2)});
			tmpEnemyState.emplace_back(MOVE_TYPE::PITIN, Vector2Dbl{ ENEMY_OFFSET_X + (16.0 + (35.0*(cnt % 10))) , ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::LR, Vector2Dbl{ ENEMY_OFFSET_X + (16.0 + (35.0*(cnt % 10))) ,ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::SCALE, Vector2Dbl{ ENEMY_OFFSET_X + (16.0 + (35.0*(cnt % 10))) ,ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::ATACK, Vector2Dbl{ ENEMY_OFFSET_X + (16.0 + (35.0*(cnt % 10))) , ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			tmpEnemyState.emplace_back(MOVE_TYPE::PITIN, Vector2Dbl{ ENEMY_OFFSET_X +(16.0 + (35.0*(cnt % 10))) , ENEMY_OFFSET_Y + ((ENEMY_OFFSET_Y)*(cnt / 10 % 5)) });
			EnemyState state = { ENEMY_TYPE::A,																				// ���߂̐ݒ�
								{ static_cast<double>((lpSceneMng.GameScreenSize.x*(((cnt / FORMATION) % 6) % 2) - 16) + (35 * (((cnt / FORMATION) % 6) % 2))),						// ���WX�̐ݒ�
								static_cast<double>(((lpSceneMng.GameScreenSize.y-30)/2)*((((cnt / FORMATION) % 6) / 2) % 3) - 16)},												// ���WY�̐ݒ�
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
	// player��Obj����
	auto plObj= std::find_if(
		_objList.begin(),
		_objList.end(),
		[](sharedObj obj) {return (*obj).unitID() == UNIT_ID::PLAYER; }
	);
	auto SetAtack=[](sharedObj obj) {
		if ((*obj).unitID() == UNIT_ID::ENEMY)
		{
			if (rand() % 3000 == 0)
			{
				return true;
			}
		}
		return false;
	};
	// �͈�for��
	for (auto data : _objList)
	{
		if (SetAtack(data))
		{
			(*data).exFlag(true);
		}
		(*data).Update(*plObj);
	}


	// �擪�����o���A�Ō�̗v�f�܂ŉ񂵂Ă����
	for (auto data : _objList)
	{		
		(*data).Draw();
	}

	// ����Ȃ��Ȃ���obj���폜
	_objList.erase(std::remove_if(
							_objList.begin(),											// �����͈͂̊J�n�n�_
							_objList.end(),												// �����͈͂̏I���n�_
							[](sharedObj& obj) {return (*obj).isDead(); }				// گ����ގ� ����ł镨�����邩�m�F
						), 
					_objList.end());
	return std::move(own);
}

void GameScene::RunActQue(std::vector<ActQueT> actList)
{
	// �͈�for��
	for (auto data : actList)
	{
		// ����ݎ�ʂɂ���ĕύX
		try
		{
			funcQue.at(data.first)(data,_objList);
		}
		catch (...)
		{
			AST();
		}
	}
}

void GameScene::initFunc(void)
{
	funcQue[ACT_QUE::SHOT] = FuncBullet();
	funcQue[ACT_QUE::CHECK_HIT] = FuncCheckHit();
}
