#pragma once
#include <map>
#include "InputId.h"

using KeyPair = std::pair<int, int>;				// ｷｰ情報格納用 oldとnew firstがnew
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();
	virtual void Update(void) = 0;					// ｱｯﾌﾟﾃﾞｰﾄ関数
	const KeyMap& state(void)const;					// _state丸々取得
	const KeyPair& state(INPUT_ID id)const;			// _state内のKeyPairを取得
	bool state(INPUT_ID id, int data);				// _stateの更新
	void SetOld(void);								// 1ﾌﾚｰﾑ前の情報格納用
private:
	KeyMap _state;									// ｷｰ情報格納用変数
};

