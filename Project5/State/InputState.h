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

using KeyPair = std::pair<int, int>;				// ｷｰ情報格納用 oldとnew firstがnew
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	const KeyMap& state(void)const;					// _state丸々取得
	const KeyPair& state(INPUT_ID id)const;			// _state内のKeyPairを取得
	bool state(INPUT_ID id, int data);				// _stateの更新
private:
	KeyMap _state;									// ｷｰ情報格納用変数
};

