#include <DxLib.h>
#include <ImageMng.h>
#include "Player.h"
#include <KeyState.h>


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
	_input = std::make_unique<KeyState>();
	//// �オ�g���Ȃ������ꍇ �o���Ă�����
	//_input.reset(new KeyState());

	state(STATE::NORMAL);
}

Player::Player()
{
	Init();
}

Player::Player(Vector2 pos, Vector2 size)
{
	_pos = pos;
	_size = size;

	Init();
}

void Player::Update(void)
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
	auto move = [](const int keyID,int& pNum,const int speed) {
		if(CheckHitKey(keyID))
		{
			pNum += speed;
		}
	};
	// ��
	move(KEY_INPUT_UP,    _pos.y, -2);
	// ��
	move(KEY_INPUT_DOWN,  _pos.y, +2);
	// ��
	move(KEY_INPUT_LEFT,  _pos.x, -2);
	// �E
	move(KEY_INPUT_RIGHT, _pos.x, +2);
}


Player::~Player()
{
}
