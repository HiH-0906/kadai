#include "InputState.h"
#include <_DebugConOut.h>

InputState::InputState()
{
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



