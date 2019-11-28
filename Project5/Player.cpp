#include <DxLib.h>
#include <ImageMng.h>
#include "Player.h"
#include <KeyState.h>
#include <SceneMng.h>
#include "_DebugDispOut.h"


void Player::Init(void)
{
	// ��ڲ԰��Ұ��ݾ��
	AnimVector data;
	data.reserve(5);
	data.emplace_back(IMAGE_ID("���")[0], 30);
	data.emplace_back(IMAGE_ID("���")[1], 60);
	SetAnim(STATE::NORMAL, data);

	data.reserve(1);
	data.emplace_back(IMAGE_ID("���")[2], 0);
	SetAnim(STATE::EX, data);
	data.emplace_back(IMAGE_ID("PL����")[0], 10);
	data.emplace_back(IMAGE_ID("PL����")[1], 15);
	data.emplace_back(IMAGE_ID("PL����")[2], 20);
	data.emplace_back(IMAGE_ID("PL����")[3], 25);
	data.emplace_back(-1, 40);							// �ݼ���ɱ�Ұ��݂ɂ������̂�-1
	SetAnim(STATE::DEATH, data);

	// �ư��߲�� ���g�͌� c++14�ȍ~
	_input = std::make_shared<KeyState>();

	state(STATE::NORMAL);
}

Player::Player()
{
	_unitID = UNIT_ID::PLAYER;
	Init();
}

Player::Player(Vector2Dbl pos, Vector2Dbl size)
{
	_pos = pos;
	_size = size;
	_unitID = UNIT_ID::PLAYER;

	Init();
}

void Player::Update(sharedObj plObj)
{
	// �������
	if (DestroyProc())
	{
		// ����ł�Ȃ�return
		return;
	}

	// ���֌W�����ްČĂяo��
	(*_input).Update();

	// ���ގ��ňړ�����@�����ŕ����Ǘ����邱�Ƃɂ���ď�����1���������Ȃ��Ă悢
						// weak_ptr�͌��邱�Ƃ����ł��Ȃ� ���@�I�ȎQ�� shared�������݂��Ă邩�m�F�ł���
	auto move = [](std::weak_ptr<InputState> keyData, INPUT_ID id, double& pNum, const int speed) {
		// �Ď��Ώۂ������Ă��邩�m�F 0�ȊO�Ŏ���ł�
		if (!keyData.expired())
		{
			// �Ď��Ώێ擾
			if ((*keyData.lock()).state(id).first)
			{
				pNum += speed;
			}
		}
	};
	// ��
	move(_input, INPUT_ID::LEFT, _pos.x, -2);
	// �E
	move(_input, INPUT_ID::RIGHT, _pos.x, +2);
	// ��
	move(_input, INPUT_ID::UP, _pos.y, -2);
	// ��
	move(_input, INPUT_ID::DOWN, _pos.y, +2);

	// shot�̔���
	if ((*_input).state(INPUT_ID::BTN_1).first&&!(*_input).state(INPUT_ID::BTN_1).second)
	{
		lpSceneMng.AddActQue({ ACT_QUE::SHOT,*this });
	}
}


Player::~Player()
{
}
