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
	modeKeyOld = 1;

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
	modeKeyOld = _buf[KEY_INPUT_F1];
	// �S���̉������擾
	GetHitKeyStateAll(_buf);
	// �֐��Ăяo��
	(this->*func)();
}

void KeyState::RefKeyData(void)
{
	// �ް��̏�������
	for (auto id : INPUT_ID())
	{
		state(id,_buf[_keyCon[static_cast<size_t>(id)]]);
	}
	// F1���Ő؂�ւ�
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		// ���ފ֐��߲���̐؂�ւ�
		func = &KeyState::SetKeyConfig;
		TREACE("����̨�ފJ�n����[\n")
		// 0�ر
		for (auto id : INPUT_ID())
		{
			state(id, 0);
		}
	}
}

void KeyState::SetKeyConfig(void)
{
	int num = 0;
	// F1���Ő؂�ւ�
	if (_buf[KEY_INPUT_F1] && !modeKeyOld)
	{
		// ���ފ֐��߲���̐؂�ւ�
		func = &KeyState::RefKeyData;
		TREACE("����̨�ޏI������[\n")
	}

	for (int i = 0; i < 256; i++)
	{
		if (_buf[i])
		{
			_keyCon[num] = i;
			num++;
			break;
		}
	}
}
