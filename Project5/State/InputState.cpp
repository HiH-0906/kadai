#include "InputState.h"
#include <_DebugConOut.h>

InputState::InputState()
{
	// �����l���
	for (auto id:INPUT_ID())
	{
		_state.try_emplace(id, KeyPair{ 0,1 });
	}
}


InputState::~InputState()
{
}

const KeyMap & InputState::state()const
{
	// ���̂܂ܕԂ�
	return _state;
}

const KeyPair & InputState::state(INPUT_ID id) const
{
	// ��O�̎��̕Ԃ�l�p��а��
	static KeyPair defData = { 0,0 };
	try
	{
		// �Ƃ肠����try
		return _state.at(id);
	}
	catch (...)					// �ǂ�ȴװ���w�� ����͑S���@...��1�ȏ�̕����̏ꍇ
	{
		// �װ���N�������鏈����`��
		AST();
		return defData;
	}
}

bool InputState::state(INPUT_ID id, int data)
{
	// id�����݂��Ă��邩����
	if (_state.find(id) != _state.end())
	{
		// first��new
		_state[id].first = data;
		return true;
	}
	// ���݂��Ȃ������牽�����Ȃ�
	return false;
}

void InputState::SetOld(void)
{
	for (auto id : INPUT_ID())
	{
		try
		{
			_state[id].second = _state[id].first;
		}
		catch (...)
		{
			// ��������������쐬
			AST();
			_state.emplace(id, KeyPair{ 0,1 });
		}
	}
}



