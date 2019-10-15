#pragma once
#include <map>

// ��ؽēI��
enum class INPUT_ID
{
	LEFT,				// ��
	RIGHT,				// �E
	UP,					// ��
	DOWN,				// ��
	BTN_1,
	BTN_2,
	BTN_3,
	BTN_4,
	MAX
};

using KeyPair = std::pair<int, int>;				// �����i�[�p old��new
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	const KeyMap& state(void)const;				// KeyMap�ہX�擾
	const KeyPair& state(INPUT_ID &id)const;	// KeyMap����KeyPair���擾
private:
	KeyMap _state;
};

