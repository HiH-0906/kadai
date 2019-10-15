#pragma once
#include <map>

// ｷｰﾘｽﾄ的な
enum class INPUT_ID
{
	LEFT,				// 左
	RIGHT,				// 右
	UP,					// 上
	DOWN,				// 下
	BTN_1,
	BTN_2,
	BTN_3,
	BTN_4,
	MAX
};

using KeyPair = std::pair<int, int>;				// ｷｰ情報格納用 oldとnew
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	const KeyMap& state(void)const;				// KeyMap丸々取得
	const KeyPair& state(INPUT_ID &id)const;	// KeyMap内のKeyPairを取得
private:
	KeyMap _state;
};

