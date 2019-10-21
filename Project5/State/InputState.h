#pragma once
#include <map>
#include "InputId.h"

using KeyPair = std::pair<int, int>;				// �����i�[�p old��new first��new
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	virtual void Update(void) = 0;					// �����ްĊ֐�
	const KeyMap& state(void)const;					// _state�ہX�擾
	const KeyPair& state(INPUT_ID id)const;			// _state����KeyPair���擾
	bool state(INPUT_ID id, int data);				// _state�̍X�V
	void SetOld(void);								// 1�ڰёO�̏��i�[�p
private:
	KeyMap _state;									// �����i�[�p�ϐ�
};

