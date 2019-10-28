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
	FILE* fp = nullptr;
	if (fopen_s(&fp, "data/key.dat", "r") != 0)
	{
		// ����̨���ް����߰
		_keyCon = _keyConDef;
		_modeKeyOld = 1;
	}
	else
	{
		fread(_keyCon.data(),
			sizeof(_keyCon[0]),
			static_cast<size_t>(end(INPUT_ID())),
			fp);
		fclose(fp);															// ̧�ق����
	}


	// ���ް�֐��߲���֑�� �����I�ɖ��O��Ԃ������Ȃ������
	func = &KeyState::RefKeyData;
	_configID = INPUT_ID::LEFT;
}


KeyState::~KeyState()
{
}

void KeyState::Update(void)
{
	// 1�ڰёO�����i�[
	SetOld();
	_modeKeyOld = _buf[KEY_INPUT_F1];
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
	if (_buf[KEY_INPUT_F1] && !_modeKeyOld)
	{
		// ���ފ֐��߲���̐؂�ւ�
		func = &KeyState::SetKeyConfig;
		TREACE("����̨�ފJ�n����[\n");
		_configID = INPUT_ID::LEFT;
		TREACE("��%d/%d�Ԗڂ̷�����[\n", static_cast<int>(_configID) + 1, end(INPUT_ID()));
	}
}

void KeyState::SetKeyConfig(void)
{
	// 0�ر
	for (auto id : INPUT_ID())
	{
		state(id, 0);
	}

	auto CheckKey = [&](int id) {
		// ���ɓ��͂��Ă���Ƃ���܂ł�for��
		for (auto ckId = begin(INPUT_ID()); ckId < _configID; ++ckId)
		{
			// ����Ă��邩����
			if (_keyCon[static_cast<int>(ckId)] == id)
			{
				return false;
			}
		}
		return true;
	};

	// �S������
	for (int id = 0; id < sizeof(_buf); id++)
	{
		// ����ĂȂ�������
		if (!CheckKey(id))
		{
			// ����Ă�����continue
			continue;
		}
		// ������Ă��鷰�T��
		if (_buf[id] && (!_buf[KEY_INPUT_F1]))
		{
			_keyCon[static_cast<int>(_configID)] = id;
			// �O���Z����Ȃ��ƂȂ�̵��ް۰�ނ��킩��Ȃ��̂�NG
			++_configID;
			TREACE("%d��ݒ肵����[\n", id);
			// �؂�ւ�
			if (_configID == end(_configID))
			{
				TREACE("����̨�ޏI������[\n");
				// ���ފ֐��߲���̕ύX
				func = &KeyState::RefKeyData;
				FILE* fp = nullptr;
				if (fopen_s(&fp, "data/key.dat", "w") == 0)
				{
					fwrite(&_keyCon[0],
						sizeof(int),
						static_cast<size_t>(end(INPUT_ID())),
						fp
					);
				}
				break;
			}
			TREACE("��%d/%d�Ԗڂ̷�����[\n", static_cast<int>(_configID) + 1, end(INPUT_ID()));
		}
	}
}
