#pragma once
#include <vector>
#include "InputState.h"
class KeyState :
	public InputState
{
public:
	KeyState();
	~KeyState();
	void Update(void)override;					// �����ް�
private:
	void RefKeyData(void);						// ��̫�ėp
	void SetKeyConfig(void);					// ��̨�޾�ėp
	void (KeyState::*func)(void);				// ���ް�֐��߲��

	std::vector<int> _keyCon;					// ����̨�ޏ��
	std::vector<int> _keyConDef;				// ��̫�ķ���̨�ޏ��
	char _buf[256];								// ���������i�[�p
	int _modeKeyOld;							// F1�p�̵����
	INPUT_ID _configID;							// ����̨�ގ����Ԗڂ����f
};

