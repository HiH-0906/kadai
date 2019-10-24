#include <DxLib.h>
#include "KeyState.h"
#include <_DebugConOut.h>



KeyState::KeyState()
{
	// ���炩���ߐ����킩���Ă���̂���؊m�� 
	_keyConDef.reserve(static_cast<size_t>(end(INPUT_ID())));		// ���ނ��g����INPUT_ID�̏I�[���擾
	
	// ��̫�ķ���̨�ނ��
	_keyConDef.emplace_back(KEY_INPUT_LEFT);
	_keyConDef.emplace_back(KEY_INPUT_RIGHT);
	_keyConDef.emplace_back(KEY_INPUT_UP);
	_keyConDef.emplace_back(KEY_INPUT_DOWN);
	_keyConDef.emplace_back(KEY_INPUT_Z);
	_keyConDef.emplace_back(KEY_INPUT_X);
	_keyConDef.emplace_back(KEY_INPUT_A);
	_keyConDef.emplace_back(KEY_INPUT_S);
	
	// ̧�ٓǂݍ��݉ӏ�

	// ����̨���ް����߰
	_keyCon = _keyConDef;

	// ���ް�֐��߲���֑�� �����I�ɖ��O��Ԃ������Ȃ������
	func = &KeyState::RefKeyData;
}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	// 1�ڰёO�����i�[
	SetOld();
	// �S���̉������擾
	GetHitKeyStateAll(_buf);
	// �֐��Ăяo��
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
	// �ް��̏�������
	int i = 0;
	for (auto id : INPUT_ID())
	{
		state(id,_buf[_keyCon[i]]);
		i++;
	}
	if (_buf[KEY_INPUT_F1] == 1)
	{
		func = &KeyState::SetKeyConfig;
		TREACE("\nSetKeyConfig����[")
	}
}

void KeyState::SetKeyConfig(void)
{
	for (int i = 0; i < 256; i++)
	{
		if (_buf[i])
		{

		}
	}
}
